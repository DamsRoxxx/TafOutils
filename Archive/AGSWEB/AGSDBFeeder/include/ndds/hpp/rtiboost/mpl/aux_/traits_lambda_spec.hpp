
#ifndef RTIBOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/sequence_tag_fwd.hpp>
#include <rtiboost/mpl/void.hpp>
#include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#include <rtiboost/mpl/aux_/config/lambda.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) /**/

#elif !defined(RTIBOOST_MPL_CFG_MSVC_ETI_BUG)

#   define RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< RTIBOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
/**/

#else

#   define RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< RTIBOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
template<> struct trait<int> \
{ \
    template< RTIBOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
        typedef int type; \
    }; \
}; \
/**/

#endif // RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT


#define RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(i, trait) \
    RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
    template<> struct trait<non_sequence_tag> {}; \
/**/

#endif // RTIBOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED
