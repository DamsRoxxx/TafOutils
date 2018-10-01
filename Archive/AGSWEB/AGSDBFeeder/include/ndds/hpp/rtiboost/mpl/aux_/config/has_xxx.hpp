
#ifndef RTIBOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
// Copyright David Abrahams 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/aux_/config/overload_resolution.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

// agurt, 11/jan/03: signals a stub-only 'has_xxx' implementation

#if !defined(RTIBOOST_MPL_CFG_NO_HAS_XXX) \
    && (   defined(RTIBOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
        || RTIBOOST_WORKAROUND(__GNUC__, <= 2) \
        || RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840)) \
        )

#   define RTIBOOST_MPL_CFG_NO_HAS_XXX
#   define RTIBOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#endif

#endif // RTIBOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED
