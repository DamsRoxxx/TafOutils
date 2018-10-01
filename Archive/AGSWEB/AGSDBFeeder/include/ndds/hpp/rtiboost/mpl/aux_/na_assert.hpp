
#ifndef RTIBOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/na.hpp>
#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if !RTIBOOST_WORKAROUND(_MSC_FULL_VER, <= 140050601)    \
    && !RTIBOOST_WORKAROUND(__EDG_VERSION__, <= 243)
#   include <rtiboost/mpl/assert.hpp>
#   define RTIBOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    RTIBOOST_MPL_ASSERT_NOT((rtiboost::mpl::is_na<type>)) \
/**/
#else
#   include <rtiboost/static_assert.hpp>
#   define RTIBOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    RTIBOOST_STATIC_ASSERT(!rtiboost::mpl::is_na<x>::value) \
/**/
#endif

#endif // RTIBOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED
