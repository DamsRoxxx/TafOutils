
#ifndef RTIBOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED

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

#include <rtiboost/mpl/limits/arity.hpp>
#include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#include <rtiboost/mpl/aux_/preprocessor/sub.hpp>
#include <rtiboost/preprocessor/comma_if.hpp>

#define RTIBOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
RTIBOOST_MPL_PP_PARAMS(n, param) \
RTIBOOST_PP_COMMA_IF(RTIBOOST_MPL_PP_SUB(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY,n)) \
RTIBOOST_MPL_PP_ENUM( \
      RTIBOOST_MPL_PP_SUB(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY,n) \
    , def \
    ) \
/**/

#endif // RTIBOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED
