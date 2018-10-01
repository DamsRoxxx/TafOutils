
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_ARG_HPP_INCLUDED
#define RTIBOOST_MPL_ARG_HPP_INCLUDED

// Copyright Peter Dimov 2001-2002
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
#   include <rtiboost/mpl/arg_fwd.hpp>
#   include <rtiboost/mpl/aux_/na.hpp>
#   include <rtiboost/mpl/aux_/na_assert.hpp>
#   include <rtiboost/mpl/aux_/arity_spec.hpp>
#   include <rtiboost/mpl/aux_/arg_typedef.hpp>
#endif

#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER arg.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/config/lambda.hpp>
#   include <rtiboost/mpl/aux_/config/dtp.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>

#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

// local macro, #undef-ined at the end of the header
#if !defined(RTIBOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define RTIBOOST_AUX778076_ARG_N_DEFAULT_PARAMS(param,value) \
    RTIBOOST_MPL_PP_DEFAULT_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/
#else
#   define RTIBOOST_AUX778076_ARG_N_DEFAULT_PARAMS(param,value) \
    RTIBOOST_MPL_PP_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/
#endif

#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/arg.hpp>))
#include RTIBOOST_PP_ITERATE()


#   undef RTIBOOST_AUX778076_ARG_N_DEFAULT_PARAMS

RTIBOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int,arg)

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_ARG_HPP_INCLUDED

///// iteration

#else
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

#if i_ > 0

template<> struct arg<i_>
{
    RTIBOOST_STATIC_CONSTANT(int, value = i_);
    typedef arg<RTIBOOST_PP_INC(i_)> next;
    RTIBOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    RTIBOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          RTIBOOST_AUX778076_ARG_N_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
        typedef RTIBOOST_PP_CAT(U,i_) type;
        RTIBOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

#else

template<> struct arg<-1>
{
    RTIBOOST_STATIC_CONSTANT(int, value = -1);
    RTIBOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    RTIBOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          RTIBOOST_AUX778076_ARG_N_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
        typedef U1 type;
        RTIBOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

#endif // i_ > 0

#undef i_
#endif // RTIBOOST_PP_IS_ITERATING
