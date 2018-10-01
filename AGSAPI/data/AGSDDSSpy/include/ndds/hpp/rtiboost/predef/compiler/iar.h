/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_IAR_H
#define RTIBOOST_PREDEF_COMPILER_IAR_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_IAR`]

IAR C/C++ compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__IAR_SYSTEMS_ICC__`] [__predef_detection__]]

    [[`__VER__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_IAR RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__IAR_SYSTEMS_ICC__)
#   define RTIBOOST_COMP_IAR_DETECTION RTIBOOST_PREDEF_MAKE_10_VVRR(__VER__)
#endif

#ifdef RTIBOOST_COMP_IAR_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_IAR_EMULATED RTIBOOST_COMP_IAR_DETECTION
#   else
#       undef RTIBOOST_COMP_IAR
#       define RTIBOOST_COMP_IAR RTIBOOST_COMP_IAR_DETECTION
#   endif
#   define RTIBOOST_COMP_IAR_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_IAR_NAME "IAR C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_IAR,RTIBOOST_COMP_IAR_NAME)

#ifdef RTIBOOST_COMP_IAR_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_IAR_EMULATED,RTIBOOST_COMP_IAR_NAME)
#endif
