
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   include <rtiboost/mpl/lambda_fwd.hpp>
#   include <rtiboost/mpl/bind_fwd.hpp>
#   include <rtiboost/mpl/protect.hpp>
#   include <rtiboost/mpl/is_placeholder.hpp>
#   include <rtiboost/mpl/if.hpp>
#   include <rtiboost/mpl/identity.hpp>
#   include <rtiboost/mpl/bool.hpp>
#   include <rtiboost/mpl/aux_/na_spec.hpp>
#   include <rtiboost/mpl/aux_/lambda_support.hpp>
#   include <rtiboost/mpl/aux_/template_arity.hpp>
#   include <rtiboost/mpl/aux_/value_wknd.hpp>
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if    !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER lambda_no_ctps.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/repeat.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#   include <rtiboost/mpl/aux_/config/msvc.hpp>
#   include <rtiboost/mpl/aux_/config/workaround.hpp>

#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

namespace rtiboost { namespace mpl {

#   define RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, param) \
    RTIBOOST_MPL_PP_PARAMS(i_, param) \
    /**/

namespace aux {

#define n_ RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
template<
      RTIBOOST_MPL_PP_DEFAULT_PARAMS(n_,bool C,false)
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< RTIBOOST_MPL_PP_ENUM(n_,false) >
    : false_
{
};
#undef n_

template< typename Arity > struct lambda_impl
{
    template< typename T, typename Tag, typename Protect > struct result_
    {
        typedef T type;
        typedef is_placeholder<T> is_le;
    };
};

#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/aux_/lambda_no_ctps.hpp>))
#include RTIBOOST_PP_ITERATE()

} // namespace aux

template<
      typename T
    , typename Tag
    , typename Protect
    >
struct lambda
{
    /// Metafunction forwarding confuses MSVC 6.x
    typedef typename aux::template_arity<T>::type arity_;
    typedef typename aux::lambda_impl<arity_>
        ::template result_< T,Tag,Protect > l_;

    typedef typename l_::type type;
    typedef typename l_::is_le is_le;
    
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(3, lambda, (T, Tag, Protect))
};

RTIBOOST_MPL_AUX_NA_SPEC2(1, 3, lambda)

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};

#   undef RTIBOOST_AUX778076_LAMBDA_PARAMS

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED

///// iteration, depth == 1

#else

#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

#   define RTIBOOST_AUX778076_LAMBDA_TYPEDEF(unused, i_, F) \
    typedef lambda< \
          typename F::RTIBOOST_PP_CAT(arg,RTIBOOST_PP_INC(i_)) \
        , Tag \
        , false_ \
        > RTIBOOST_PP_CAT(l,RTIBOOST_PP_INC(i_)); \
    /**/

#   define RTIBOOST_AUX778076_IS_LE_TYPEDEF(unused, i_, unused2) \
    typedef typename RTIBOOST_PP_CAT(l,RTIBOOST_PP_INC(i_))::is_le \
        RTIBOOST_PP_CAT(is_le,RTIBOOST_PP_INC(i_)); \
    /**/

#   define RTIBOOST_AUX778076_IS_LAMBDA_EXPR(unused, i_, unused2) \
    RTIBOOST_PP_COMMA_IF(i_) \
    RTIBOOST_MPL_AUX_MSVC_VALUE_WKND(RTIBOOST_PP_CAT(is_le,RTIBOOST_PP_INC(i_)))::value \
    /**/

#   define RTIBOOST_AUX778076_LAMBDA_RESULT(unused, i_, unused2) \
    , typename RTIBOOST_PP_CAT(l,RTIBOOST_PP_INC(i_))::type \
    /**/

template<> struct lambda_impl< int_<i_> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_LAMBDA_TYPEDEF, F)
        RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_IS_LE_TYPEDEF, unused)

        typedef aux::lambda_or<
              RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_IS_LAMBDA_EXPR, unused)
            > is_le;

        typedef RTIBOOST_PP_CAT(bind,i_)<
              typename F::rebind
            RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_LAMBDA_RESULT, unused)
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;
    
        typedef typename type_::type type;
    };
};

#   undef RTIBOOST_AUX778076_LAMBDA_RESULT
#   undef RTIBOOST_AUX778076_IS_LAMBDA_EXPR
#   undef RTIBOOST_AUX778076_IS_LE_TYPEDEF
#   undef RTIBOOST_AUX778076_LAMBDA_TYPEDEF

#undef i_

#endif // RTIBOOST_PP_IS_ITERATING
