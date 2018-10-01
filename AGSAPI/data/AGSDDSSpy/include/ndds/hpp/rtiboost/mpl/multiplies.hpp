
#ifndef RTIBOOST_MPL_MULTIPLIES_HPP_INCLUDED
#define RTIBOOST_MPL_MULTIPLIES_HPP_INCLUDED

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

#include <rtiboost/mpl/times.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>
#include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#include <rtiboost/mpl/aux_/config/ctps.hpp>

// backward compatibility header, deprecated

namespace rtiboost { namespace mpl {

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   define RTIBOOST_AUX778076_OP_ARITY RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
#else
#   define RTIBOOST_AUX778076_OP_ARITY 2
#endif

template<
      RTIBOOST_MPL_PP_DEFAULT_PARAMS(RTIBOOST_AUX778076_OP_ARITY, typename N, na)
    >
struct multiplies
    : times< RTIBOOST_MPL_PP_PARAMS(RTIBOOST_AUX778076_OP_ARITY, N) >
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(
          RTIBOOST_AUX778076_OP_ARITY
        , multiplies
        , ( RTIBOOST_MPL_PP_PARAMS(RTIBOOST_AUX778076_OP_ARITY, N) )
        )
};

RTIBOOST_MPL_AUX_NA_SPEC(RTIBOOST_AUX778076_OP_ARITY, multiplies)

#undef RTIBOOST_AUX778076_OP_ARITY

}}

#endif // RTIBOOST_MPL_MULTIPLIES_HPP_INCLUDED
