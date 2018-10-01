
#ifndef RTIBOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

// flags for MSVC 6.5's so-called "early template instantiation bug"
#if    !defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE) \
    && RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)

#   define RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG

#endif

#if    !defined(RTIBOOST_MPL_CFG_MSVC_70_ETI_BUG) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE) \
    && RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1300)

#   define RTIBOOST_MPL_CFG_MSVC_70_ETI_BUG

#endif

#if    !defined(RTIBOOST_MPL_CFG_MSVC_ETI_BUG) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE) \
    && ( defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG) \
        || defined(RTIBOOST_MPL_CFG_MSVC_70_ETI_BUG) \
        )

#   define RTIBOOST_MPL_CFG_MSVC_ETI_BUG

#endif

#endif // RTIBOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED
