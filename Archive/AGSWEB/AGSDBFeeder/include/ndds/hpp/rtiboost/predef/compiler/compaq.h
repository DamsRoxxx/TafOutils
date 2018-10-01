/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_COMPAQ_H
#define RTIBOOST_PREDEF_COMPILER_COMPAQ_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_DEC`]

[@http://www.openvms.compaq.com/openvms/brochures/deccplus/ Compaq C/C++] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__DECCXX`] [__predef_detection__]]
    [[`__DECC`] [__predef_detection__]]

    [[`__DECCXX_VER`] [V.R.P]]
    [[`__DECC_VER`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_DEC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__DECC) || defined(__DECCXX)
#   if !defined(RTIBOOST_COMP_DEC_DETECTION) && defined(__DECCXX_VER)
#       define RTIBOOST_COMP_DEC_DETECTION RTIBOOST_PREDEF_MAKE_10_VVRR0PP00(__DECCXX_VER)
#   endif
#   if !defined(RTIBOOST_COMP_DEC_DETECTION) && defined(__DECC_VER)
#       define RTIBOOST_COMP_DEC_DETECTION RTIBOOST_PREDEF_MAKE_10_VVRR0PP00(__DECC_VER)
#   endif
#   if !defined(RTIBOOST_COMP_DEC_DETECTION)
#       define RTIBOOST_COM_DEC_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_DEC_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_DEC_EMULATED RTIBOOST_COMP_DEC_DETECTION
#   else
#       undef RTIBOOST_COMP_DEC
#       define RTIBOOST_COMP_DEC RTIBOOST_COMP_DEC_DETECTION
#   endif
#   define RTIBOOST_COMP_DEC_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_DEC_NAME "Compaq C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_DEC,RTIBOOST_COMP_DEC_NAME)

#ifdef RTIBOOST_COMP_DEC_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_DEC_EMULATED,RTIBOOST_COMP_DEC_NAME)
#endif
