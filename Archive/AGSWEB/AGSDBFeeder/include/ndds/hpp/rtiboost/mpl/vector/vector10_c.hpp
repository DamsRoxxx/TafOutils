
#ifndef RTIBOOST_MPL_VECTOR_VECTOR10_C_HPP_INCLUDED
#define RTIBOOST_MPL_VECTOR_VECTOR10_C_HPP_INCLUDED

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
#   include <rtiboost/mpl/vector/vector0_c.hpp>
#   include <rtiboost/mpl/vector/vector10.hpp>
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER vector10_c.hpp
#   include <rtiboost/mpl/vector/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/aux_/config/typeof.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>

namespace rtiboost { namespace mpl {

#   define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, 10, <rtiboost/mpl/vector/aux_/numbered_c.hpp>))
#   include RTIBOOST_PP_ITERATE()

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // RTIBOOST_MPL_VECTOR_VECTOR10_C_HPP_INCLUDED
