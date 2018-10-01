/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_MPW_H
#define RTIBOOST_PREDEF_COMPILER_MPW_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_MPW`]

[@http://en.wikipedia.org/wiki/Macintosh_Programmer%27s_Workshop MPW C++] compiler.
Version number available as major, and minor.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__MRC__`] [__predef_detection__]]
    [[`MPW_C`] [__predef_detection__]]
    [[`MPW_CPLUS`] [__predef_detection__]]

    [[`__MRC__`] [V.R.0]]
    ]
 */

#define RTIBOOST_COMP_MPW RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__MRC__) || defined(MPW_C) || defined(MPW_CPLUS)
#   if !defined(RTIBOOST_COMP_MPW_DETECTION) && defined(__MRC__)
#       define RTIBOOST_COMP_MPW_DETECTION RTIBOOST_PREDEF_MAKE_0X_VVRR(__MRC__)
#   endif
#   if !defined(RTIBOOST_COMP_MPW_DETECTION)
#       define RTIBOOST_COMP_MPW_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_MPW_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_MPW_EMULATED RTIBOOST_COMP_MPW_DETECTION
#   else
#       undef RTIBOOST_COMP_MPW
#       define RTIBOOST_COMP_MPW RTIBOOST_COMP_MPW_DETECTION
#   endif
#   define RTIBOOST_COMP_MPW_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_MPW_NAME "MPW C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_MPW,RTIBOOST_COMP_MPW_NAME)

#ifdef RTIBOOST_COMP_MPW_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_MPW_EMULATED,RTIBOOST_COMP_MPW_NAME)
#endif
