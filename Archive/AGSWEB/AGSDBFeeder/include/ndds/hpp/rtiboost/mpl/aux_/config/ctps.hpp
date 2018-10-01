
#ifndef RTIBOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/workaround.hpp>
#include <rtiboost/config.hpp>

#if    !defined(RTIBOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE) \
    && RTIBOOST_WORKAROUND(__BORLANDC__, < 0x582)

#   define RTIBOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC

#endif

// RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION is defined in <rtiboost/config.hpp>

#endif // RTIBOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED
