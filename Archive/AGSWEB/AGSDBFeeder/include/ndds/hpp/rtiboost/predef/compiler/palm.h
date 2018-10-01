/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_PALM_H
#define RTIBOOST_PREDEF_COMPILER_PALM_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_PALM`]

Palm C/C++ compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`_PACC_VER`] [__predef_detection__]]

    [[`_PACC_VER`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_PALM RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(_PACC_VER)
#   define RTIBOOST_COMP_PALM_DETECTION RTIBOOST_PREDEF_MAKE_0X_VRRPP000(_PACC_VER)
#endif

#ifdef RTIBOOST_COMP_PALM_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_PALM_EMULATED RTIBOOST_COMP_PALM_DETECTION
#   else
#       undef RTIBOOST_COMP_PALM
#       define RTIBOOST_COMP_PALM RTIBOOST_COMP_PALM_DETECTION
#   endif
#   define RTIBOOST_COMP_PALM_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_PALM_NAME "Palm C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_PALM,RTIBOOST_COMP_PALM_NAME)

#ifdef RTIBOOST_COMP_PALM_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_PALM_EMULATED,RTIBOOST_COMP_PALM_NAME)
#endif
