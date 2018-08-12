/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_GREENHILLS_H
#define RTIBOOST_PREDEF_COMPILER_GREENHILLS_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_GHS`]

[@http://en.wikipedia.org/wiki/Green_Hills_Software Green Hills C/C++] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__ghs`] [__predef_detection__]]
    [[`__ghs__`] [__predef_detection__]]

    [[`__GHS_VERSION_NUMBER__`] [V.R.P]]
    [[`__ghs`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_GHS RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__ghs) || defined(__ghs__)
#   if !defined(RTIBOOST_COMP_GHS_DETECTION) && defined(__GHS_VERSION_NUMBER__)
#       define RTIBOOST_COMP_GHS_DETECTION RTIBOOST_PREDEF_MAKE_10_VRP(__GHS_VERSION_NUMBER__)
#   endif
#   if !defined(RTIBOOST_COMP_GHS_DETECTION) && defined(__ghs)
#       define RTIBOOST_COMP_GHS_DETECTION RTIBOOST_PREDEF_MAKE_10_VRP(__ghs)
#   endif
#   if !defined(RTIBOOST_COMP_GHS_DETECTION)
#       define RTIBOOST_COMP_GHS_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_GHS_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_GHS_EMULATED RTIBOOST_COMP_GHS_DETECTION
#   else
#       undef RTIBOOST_COMP_GHS
#       define RTIBOOST_COMP_GHS RTIBOOST_COMP_GHS_DETECTION
#   endif
#   define RTIBOOST_COMP_GHS_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_GHS_NAME "Green Hills C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_GHS,RTIBOOST_COMP_GHS_NAME)

#ifdef RTIBOOST_COMP_GHS_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_GHS_EMULATED,RTIBOOST_COMP_GHS_NAME)
#endif
