
#ifndef RTIBOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/gcc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && ( defined(RTIBOOST_NO_TEMPLATE_TEMPLATES) \
      || RTIBOOST_WORKAROUND( __BORLANDC__, RTIBOOST_TESTED_AT( 0x590) ) \
       )

#   define RTIBOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS

#endif


#if    !defined(RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE) \
    && (   RTIBOOST_WORKAROUND(RTIBOOST_MPL_CFG_GCC, RTIBOOST_TESTED_AT(0x0302)) \
        || RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x610)) \
        )

#   define RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING

#endif

#endif // RTIBOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
