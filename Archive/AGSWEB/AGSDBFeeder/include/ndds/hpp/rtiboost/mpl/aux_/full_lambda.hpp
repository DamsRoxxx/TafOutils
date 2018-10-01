
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED

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

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   include <rtiboost/mpl/lambda_fwd.hpp>
#   include <rtiboost/mpl/bind_fwd.hpp>
#   include <rtiboost/mpl/protect.hpp>
#   include <rtiboost/mpl/quote.hpp>
#   include <rtiboost/mpl/arg.hpp>
#   include <rtiboost/mpl/bool.hpp>
#   include <rtiboost/mpl/int_fwd.hpp>
#   include <rtiboost/mpl/aux_/template_arity.hpp>
#   include <rtiboost/mpl/aux_/na_spec.hpp>
#   include <rtiboost/mpl/aux_/config/ttp.hpp>
#   if defined(RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
#       include <rtiboost/mpl/if.hpp>
#   endif
#endif

#include <rtiboost/mpl/aux_/lambda_arity_param.hpp>
#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER full_lambda.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/repeat.hpp>
#   include <rtiboost/mpl/aux_/config/dmc_ambiguous_ctps.hpp>

#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

namespace rtiboost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, param) \
    RTIBOOST_MPL_PP_PARAMS(i_, param) \
    /**/

#   define RTIBOOST_AUX778076_BIND_PARAMS(param) \
    RTIBOOST_MPL_PP_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define RTIBOOST_AUX778076_BIND_N_PARAMS(i_, param) \
    RTIBOOST_PP_COMMA_IF(i_) \
    RTIBOOST_MPL_PP_PARAMS(i_, param) \
    /**/

#   define RTIBOOST_AUX778076_ARITY_PARAM(param) \
    RTIBOOST_MPL_AUX_LAMBDA_ARITY_PARAM(param) \
    /**/


#define n_ RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
namespace aux {

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

} // namespace aux
#undef n_

template<
      typename T
    , typename Tag
    RTIBOOST_AUX778076_ARITY_PARAM(typename Arity)
    >
struct lambda
{
    typedef false_ is_le;
    typedef T result_;
    typedef T type;
};

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};


template< int N, typename Tag >
struct lambda< arg<N>,Tag RTIBOOST_AUX778076_ARITY_PARAM(int_<-1>) >
{
    typedef true_ is_le;
    typedef mpl::arg<N> result_; // qualified for the sake of MIPSpro 7.41
    typedef mpl::protect<result_> type; 
};


#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/aux_/full_lambda.hpp>))
#include RTIBOOST_PP_ITERATE()

/// special case for 'protect'
template< typename T, typename Tag >
struct lambda< mpl::protect<T>,Tag RTIBOOST_AUX778076_ARITY_PARAM(int_<1>) >
{
    typedef false_ is_le;
    typedef mpl::protect<T> result_;
    typedef result_ type;
};

/// specializations for the main 'bind' form
template<
      typename F, RTIBOOST_AUX778076_BIND_PARAMS(typename T)
    , typename Tag
    >
struct lambda<
          bind<F,RTIBOOST_AUX778076_BIND_PARAMS(T)>
        , Tag
        RTIBOOST_AUX778076_ARITY_PARAM(int_<RTIBOOST_PP_INC(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY)>)
        >
{
    typedef false_ is_le;
    typedef bind<F, RTIBOOST_AUX778076_BIND_PARAMS(T)> result_;
    typedef result_ type;
};


#if defined(RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)

template<
      typename F
    , typename Tag1
    , typename Tag2
    , typename Arity
    >
struct lambda<
          lambda<F,Tag1,Arity>
        , Tag2
        , int_<3>
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;

    typedef typename l1::is_le is_le;
    typedef bind1< quote1<aux::template_arity>, typename l1::result_ > arity_;
    typedef lambda< typename if_<is_le,arity_,Arity>::type,Tag2 > l3;
    
    typedef aux::le_result3<is_le, Tag2, mpl::lambda, l1, l2, l3> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

#elif !defined(RTIBOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)

/// workaround for MWCW 8.3+/EDG < 303, leads to ambiguity on Digital Mars
template<
      typename F, typename Tag1, typename Tag2
    >
struct lambda<
          lambda< F,Tag1 >
        , Tag2
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;
    
    typedef typename l1::is_le is_le;
    typedef aux::le_result2<is_le, Tag2, mpl::lambda, l1, l2> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

#endif

#   undef RTIBOOST_AUX778076_ARITY_PARAM
#   undef RTIBOOST_AUX778076_BIND_N_PARAMS
#   undef RTIBOOST_AUX778076_BIND_PARAMS
#   undef RTIBOOST_AUX778076_LAMBDA_PARAMS

#if !defined(RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
RTIBOOST_MPL_AUX_NA_SPEC(2, lambda)
#else
RTIBOOST_MPL_AUX_NA_SPEC2(2, 3, lambda)
#endif

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// RTIBOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // RTIBOOST_PP_IS_ITERATING
#if RTIBOOST_PP_ITERATION_DEPTH() == 1
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

#if i_ > 0

namespace aux {

#   define RTIBOOST_AUX778076_RESULT(unused, i_, T) \
    RTIBOOST_PP_COMMA_IF(i_) \
    typename RTIBOOST_PP_CAT(T, RTIBOOST_PP_INC(i_))::result_ \
    /**/

#   define RTIBOOST_AUX778076_TYPE(unused, i_, T) \
    RTIBOOST_PP_COMMA_IF(i_) \
    typename RTIBOOST_PP_CAT(T, RTIBOOST_PP_INC(i_))::type \
    /**/

template<
      typename IsLE, typename Tag
    , template< RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, typename L)
    >
struct RTIBOOST_PP_CAT(le_result,i_)
{
    typedef F<
          RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_TYPE, L)
        > result_;
    
    typedef result_ type;
};

template<
      typename Tag
    , template< RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, typename L)
    >
struct RTIBOOST_PP_CAT(le_result,i_)< true_,Tag,F,RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, L) >
{
    typedef RTIBOOST_PP_CAT(bind,i_)<
          RTIBOOST_PP_CAT(quote,i_)<F,Tag>
        , RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_RESULT, L)
        > result_;

    typedef mpl::protect<result_> type;
};

#   undef RTIBOOST_AUX778076_TYPE
#   undef RTIBOOST_AUX778076_RESULT

} // namespace aux


#   define RTIBOOST_AUX778076_LAMBDA_TYPEDEF(unused, i_, T) \
    typedef lambda< RTIBOOST_PP_CAT(T, RTIBOOST_PP_INC(i_)), Tag > \
        RTIBOOST_PP_CAT(l,RTIBOOST_PP_INC(i_)); \
/**/

#   define RTIBOOST_AUX778076_IS_LE_TYPEDEF(unused, i_, unused2) \
    typedef typename RTIBOOST_PP_CAT(l,RTIBOOST_PP_INC(i_))::is_le \
        RTIBOOST_PP_CAT(is_le,RTIBOOST_PP_INC(i_)); \
/**/

#   define RTIBOOST_AUX778076_IS_LAMBDA_EXPR(unused, i_, unused2) \
    RTIBOOST_PP_COMMA_IF(i_) \
    RTIBOOST_PP_CAT(is_le,RTIBOOST_PP_INC(i_))::value \
/**/

template<
      template< RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda< 
          F<RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, T)>
        , Tag
        RTIBOOST_AUX778076_ARITY_PARAM(int_<i_>)
        >
{
    RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_LAMBDA_TYPEDEF, T)
    RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_IS_LE_TYPEDEF, unused)

    typedef typename aux::lambda_or<
          RTIBOOST_MPL_PP_REPEAT(i_, RTIBOOST_AUX778076_IS_LAMBDA_EXPR, unused)
        >::type is_le;

    typedef aux::RTIBOOST_PP_CAT(le_result,i_)<
          is_le, Tag, F, RTIBOOST_AUX778076_LAMBDA_PARAMS(i_, l)
        > le_result_;
    
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};


#   undef RTIBOOST_AUX778076_IS_LAMBDA_EXPR
#   undef RTIBOOST_AUX778076_IS_LE_TYPEDEF
#   undef RTIBOOST_AUX778076_LAMBDA_TYPEDEF

#endif // i_ > 0

template<
      typename F RTIBOOST_AUX778076_BIND_N_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda<
          RTIBOOST_PP_CAT(bind,i_)<F RTIBOOST_AUX778076_BIND_N_PARAMS(i_, T)>
        , Tag
        RTIBOOST_AUX778076_ARITY_PARAM(int_<RTIBOOST_PP_INC(i_)>)
        >
{
    typedef false_ is_le;
    typedef RTIBOOST_PP_CAT(bind,i_)<
          F
        RTIBOOST_AUX778076_BIND_N_PARAMS(i_, T)
        > result_;
        
    typedef result_ type;
};

#undef i_
#endif // RTIBOOST_PP_ITERATION_DEPTH()
#endif // RTIBOOST_PP_IS_ITERATING
