
#ifndef RTIBOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/aux_/config/has_xxx.hpp>
#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_HAS_APPLY) \
    && (   defined(RTIBOOST_MPL_CFG_NO_HAS_XXX) \
        || RTIBOOST_WORKAROUND(__EDG_VERSION__, < 300) \
        || RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1300) \
        || RTIBOOST_WORKAROUND(__MWERKS__, RTIBOOST_TESTED_AT(0x3202)) \
        )

#   define RTIBOOST_MPL_CFG_NO_HAS_APPLY

#endif

#endif // RTIBOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED
