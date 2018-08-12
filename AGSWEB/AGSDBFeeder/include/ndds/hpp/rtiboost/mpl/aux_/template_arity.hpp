
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/aux_/config/ttp.hpp>
#include <rtiboost/mpl/aux_/config/lambda.hpp>

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   include <rtiboost/mpl/aux_/template_arity_fwd.hpp>
#   include <rtiboost/mpl/int.hpp>
#   if !defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   if defined(RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
#       include <rtiboost/mpl/aux_/type_wrapper.hpp>
#   endif
#   else
#       include <rtiboost/mpl/aux_/has_rebind.hpp>
#   endif
#endif

#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER template_arity.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   if !defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   if defined(RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/range.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/repeat.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>

#   include <rtiboost/preprocessor/seq/fold_left.hpp>
#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_AUX778076_ARITY RTIBOOST_PP_INC(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY)

namespace rtiboost { namespace mpl { namespace aux {

template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N) > struct arity_tag
{
    typedef char (&type)[N + 1];
};

#   define RTIBOOST_AUX778076_MAX_ARITY_OP(unused, state, i_) \
    ( RTIBOOST_PP_CAT(C,i_) > 0 ? RTIBOOST_PP_CAT(C,i_) : state ) \
/**/

template<
      RTIBOOST_MPL_PP_PARAMS(RTIBOOST_AUX778076_ARITY, RTIBOOST_MPL_AUX_NTTP_DECL(int, C))
    >
struct max_arity
{
    RTIBOOST_STATIC_CONSTANT(int, value = 
          RTIBOOST_PP_SEQ_FOLD_LEFT(
              RTIBOOST_AUX778076_MAX_ARITY_OP
            , -1
            , RTIBOOST_MPL_PP_RANGE(1, RTIBOOST_AUX778076_ARITY)
            )
        );
};

#   undef RTIBOOST_AUX778076_MAX_ARITY_OP

arity_tag<0>::type arity_helper(...);

#   define RTIBOOST_PP_ITERATION_LIMITS (1, RTIBOOST_AUX778076_ARITY)
#   define RTIBOOST_PP_FILENAME_1 <rtiboost/mpl/aux_/template_arity.hpp>
#   include RTIBOOST_PP_ITERATE()

template< typename F, RTIBOOST_MPL_AUX_NTTP_DECL(int, N) >
struct template_arity_impl
{
    RTIBOOST_STATIC_CONSTANT(int, value = 
          sizeof(::rtiboost::mpl::aux::arity_helper(type_wrapper<F>(),arity_tag<N>())) - 1
        );
};

#   define RTIBOOST_AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION(unused, i_, F) \
    RTIBOOST_PP_COMMA_IF(i_) template_arity_impl<F,RTIBOOST_PP_INC(i_)>::value \
/**/

template< typename F >
struct template_arity
{
    RTIBOOST_STATIC_CONSTANT(int, value = (
          max_arity< RTIBOOST_MPL_PP_REPEAT(
              RTIBOOST_AUX778076_ARITY
            , RTIBOOST_AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION
            , F
            ) >::value
        ));
        
    typedef mpl::int_<value> type;
};

#   undef RTIBOOST_AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION

#   undef RTIBOOST_AUX778076_ARITY

}}}

#   endif // RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING
#   else // RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <rtiboost/mpl/aux_/config/eti.hpp>

namespace rtiboost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_<-1>
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::rtiboost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

#if defined(RTIBOOST_MPL_CFG_MSVC_ETI_BUG)
template<>
struct template_arity<int>
    : mpl::int_<-1>
{
};
#endif

}}}

#   endif // RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED

///// iteration

#else
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

template<
      template< RTIBOOST_MPL_PP_PARAMS(i_, typename P) > class F
    , RTIBOOST_MPL_PP_PARAMS(i_, typename T)
    >
typename arity_tag<i_>::type
arity_helper(type_wrapper< F<RTIBOOST_MPL_PP_PARAMS(i_, T)> >, arity_tag<i_>);

#undef i_
#endif // RTIBOOST_PP_IS_ITERATING
