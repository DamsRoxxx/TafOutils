
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/aux_/config/compiler.hpp>
#include <rtiboost/mpl/aux_/config/preprocessor.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>
#include <rtiboost/preprocessor/cat.hpp>
#include <rtiboost/preprocessor/stringize.hpp>

#if !defined(RTIBOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define RTIBOOST_AUX778076_PREPROCESSED_HEADER \
    RTIBOOST_MPL_CFG_COMPILER_DIR/RTIBOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define RTIBOOST_AUX778076_PREPROCESSED_HEADER \
    RTIBOOST_PP_CAT(RTIBOOST_MPL_CFG_COMPILER_DIR,/)##RTIBOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if RTIBOOST_WORKAROUND(__IBMCPP__, RTIBOOST_TESTED_AT(700))
#   define RTIBOOST_AUX778076_INCLUDE_STRING RTIBOOST_PP_STRINGIZE(rtiboost/mpl/aux_/preprocessed/RTIBOOST_AUX778076_PREPROCESSED_HEADER)
#   include RTIBOOST_AUX778076_INCLUDE_STRING
#   undef RTIBOOST_AUX778076_INCLUDE_STRING
#else
#   include RTIBOOST_PP_STRINGIZE(rtiboost/mpl/aux_/preprocessed/RTIBOOST_AUX778076_PREPROCESSED_HEADER)
#endif

#   undef RTIBOOST_AUX778076_PREPROCESSED_HEADER

#undef RTIBOOST_MPL_PREPROCESSED_HEADER
