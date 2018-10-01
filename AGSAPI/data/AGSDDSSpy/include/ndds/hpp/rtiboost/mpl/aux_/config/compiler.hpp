
#ifndef RTIBOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(RTIBOOST_MPL_CFG_COMPILER_DIR)

#   include <rtiboost/mpl/aux_/config/dtp.hpp>
#   include <rtiboost/mpl/aux_/config/ttp.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/config/msvc.hpp>
#   include <rtiboost/mpl/aux_/config/gcc.hpp>
#   include <rtiboost/mpl/aux_/config/workaround.hpp>

#   if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
#       define RTIBOOST_MPL_CFG_COMPILER_DIR msvc60

#   elif RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1300)
#       define RTIBOOST_MPL_CFG_COMPILER_DIR msvc70

#   elif RTIBOOST_WORKAROUND(RTIBOOST_MPL_CFG_GCC, RTIBOOST_TESTED_AT(0x0304))
#       define RTIBOOST_MPL_CFG_COMPILER_DIR gcc

#   elif RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x610))
#       if !defined(RTIBOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#           define RTIBOOST_MPL_CFG_COMPILER_DIR bcc551
#       elif RTIBOOST_WORKAROUND(__BORLANDC__, >= 0x590)
#           define RTIBOOST_MPL_CFG_COMPILER_DIR bcc
#       else
#           define RTIBOOST_MPL_CFG_COMPILER_DIR bcc_pre590
#       endif

#   elif RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840))
#       define RTIBOOST_MPL_CFG_COMPILER_DIR dmc

#   elif defined(__MWERKS__)
#       if defined(RTIBOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#           define RTIBOOST_MPL_CFG_COMPILER_DIR mwcw
#       else
#           define RTIBOOST_MPL_CFG_COMPILER_DIR plain
#       endif

#   elif defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       define RTIBOOST_MPL_CFG_COMPILER_DIR no_ctps

#   elif defined(RTIBOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS)
#       define RTIBOOST_MPL_CFG_COMPILER_DIR no_ttp

#   else
#       define RTIBOOST_MPL_CFG_COMPILER_DIR plain
#   endif

#endif // RTIBOOST_MPL_CFG_COMPILER_DIR

#endif // RTIBOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED
