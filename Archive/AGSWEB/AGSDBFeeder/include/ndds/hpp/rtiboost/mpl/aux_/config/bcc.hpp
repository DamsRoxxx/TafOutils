
#ifndef RTIBOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if    !defined(RTIBOOST_MPL_CFG_BCC590_WORKAROUNDS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE) \
    && RTIBOOST_WORKAROUND(__BORLANDC__, >= 0x590) \
    && RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x610))

#   define RTIBOOST_MPL_CFG_BCC590_WORKAROUNDS

#endif

#endif // RTIBOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED
