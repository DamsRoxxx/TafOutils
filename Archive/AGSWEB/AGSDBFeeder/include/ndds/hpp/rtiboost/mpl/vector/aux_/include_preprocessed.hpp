
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

#include <rtiboost/mpl/aux_/config/typeof.hpp>
#include <rtiboost/mpl/aux_/config/ctps.hpp>
#include <rtiboost/mpl/aux_/config/preprocessor.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#include <rtiboost/preprocessor/cat.hpp>
#include <rtiboost/preprocessor/stringize.hpp>

#if defined(RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
#   define RTIBOOST_AUX778076_INCLUDE_DIR typeof_based
#elif defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
   || defined(RTIBOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#   define RTIBOOST_AUX778076_INCLUDE_DIR no_ctps
#else
#   define RTIBOOST_AUX778076_INCLUDE_DIR plain
#endif

#if !defined(RTIBOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define RTIBOOST_AUX778076_HEADER \
    RTIBOOST_AUX778076_INCLUDE_DIR/RTIBOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define RTIBOOST_AUX778076_HEADER \
    RTIBOOST_PP_CAT(RTIBOOST_AUX778076_INCLUDE_DIR,/)##RTIBOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif


#if RTIBOOST_WORKAROUND(__IBMCPP__, RTIBOOST_TESTED_AT(700))
#   define RTIBOOST_AUX778076_INCLUDE_STRING RTIBOOST_PP_STRINGIZE(rtiboost/mpl/vector/aux_/preprocessed/RTIBOOST_AUX778076_HEADER)
#   include RTIBOOST_AUX778076_INCLUDE_STRING
#   undef RTIBOOST_AUX778076_INCLUDE_STRING
#else
#   include RTIBOOST_PP_STRINGIZE(rtiboost/mpl/vector/aux_/preprocessed/RTIBOOST_AUX778076_HEADER)
#endif

#   undef RTIBOOST_AUX778076_HEADER
#   undef RTIBOOST_AUX778076_INCLUDE_DIR

#undef RTIBOOST_MPL_PREPROCESSED_HEADER
