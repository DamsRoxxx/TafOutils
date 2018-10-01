
#ifndef RTIBOOST_MPL_VECTOR_HPP_INCLUDED
#define RTIBOOST_MPL_VECTOR_HPP_INCLUDED

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
#   include <rtiboost/mpl/limits/vector.hpp>
#   include <rtiboost/mpl/aux_/na.hpp>
#   include <rtiboost/mpl/aux_/config/preprocessor.hpp>

#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>
#   include <rtiboost/preprocessor/stringize.hpp>

#if !defined(RTIBOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define RTIBOOST_AUX778076_VECTOR_HEADER \
    RTIBOOST_PP_CAT(vector, RTIBOOST_MPL_LIMIT_VECTOR_SIZE).hpp \
    /**/
#else
#   define RTIBOOST_AUX778076_VECTOR_HEADER \
    RTIBOOST_PP_CAT(vector, RTIBOOST_MPL_LIMIT_VECTOR_SIZE)##.hpp \
    /**/
#endif

#   include RTIBOOST_PP_STRINGIZE(rtiboost/mpl/vector/RTIBOOST_AUX778076_VECTOR_HEADER)
#   undef RTIBOOST_AUX778076_VECTOR_HEADER
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER vector.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/vector.hpp>

#   define RTIBOOST_AUX778076_SEQUENCE_NAME vector
#   define RTIBOOST_AUX778076_SEQUENCE_LIMIT RTIBOOST_MPL_LIMIT_VECTOR_SIZE
#   include <rtiboost/mpl/aux_/sequence_wrapper.hpp>

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_VECTOR_HPP_INCLUDED
