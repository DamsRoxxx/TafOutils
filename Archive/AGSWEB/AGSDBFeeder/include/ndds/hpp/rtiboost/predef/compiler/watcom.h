/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_WATCOM_H
#define RTIBOOST_PREDEF_COMPILER_WATCOM_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_WATCOM`]

[@http://en.wikipedia.org/wiki/Watcom Watcom C++] compiler.
Version number available as major, and minor.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__WATCOMC__`] [__predef_detection__]]

    [[`__WATCOMC__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_WATCOM RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__WATCOMC__)
#   define RTIBOOST_COMP_WATCOM_DETECTION RTIBOOST_PREDEF_MAKE_10_VVRR(__WATCOMC__)
#endif

#ifdef RTIBOOST_COMP_WATCOM_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_WATCOM_EMULATED RTIBOOST_COMP_WATCOM_DETECTION
#   else
#       undef RTIBOOST_COMP_WATCOM
#       define RTIBOOST_COMP_WATCOM RTIBOOST_COMP_WATCOM_DETECTION
#   endif
#   define RTIBOOST_COMP_WATCOM_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_WATCOM_NAME "Watcom C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_WATCOM,RTIBOOST_COMP_WATCOM_NAME)

#ifdef RTIBOOST_COMP_WATCOM_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_WATCOM_EMULATED,RTIBOOST_COMP_WATCOM_NAME)
#endif
