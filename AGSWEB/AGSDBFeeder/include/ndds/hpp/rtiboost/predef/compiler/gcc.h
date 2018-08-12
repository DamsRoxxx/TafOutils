/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_GCC_H
#define RTIBOOST_PREDEF_COMPILER_GCC_H

/* Other compilers that emulate this one need to be detected first. */

#include <rtiboost/predef/compiler/clang.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_GNUC`]

[@http://en.wikipedia.org/wiki/GNU_Compiler_Collection Gnu GCC C/C++] compiler.
Version number available as major, minor, and patch (if available).

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__GNUC__`] [__predef_detection__]]

    [[`__GNUC__`, `__GNUC_MINOR__`, `__GNUC_PATCHLEVEL__`] [V.R.P]]
    [[`__GNUC__`, `__GNUC_MINOR__`] [V.R.0]]
    ]
 */

#define RTIBOOST_COMP_GNUC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__GNUC__)
#   if !defined(RTIBOOST_COMP_GNUC_DETECTION) && defined(__GNUC_PATCHLEVEL__)
#       define RTIBOOST_COMP_GNUC_DETECTION \
            RTIBOOST_VERSION_NUMBER(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)
#   endif
#   if !defined(RTIBOOST_COMP_GNUC_DETECTION)
#       define RTIBOOST_COMP_GNUC_DETECTION \
            RTIBOOST_VERSION_NUMBER(__GNUC__,__GNUC_MINOR__,0)
#   endif
#endif

#ifdef RTIBOOST_COMP_GNUC_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_GNUC_EMULATED RTIBOOST_COMP_GNUC_DETECTION
#   else
#       undef RTIBOOST_COMP_GNUC
#       define RTIBOOST_COMP_GNUC RTIBOOST_COMP_GNUC_DETECTION
#   endif
#   define RTIBOOST_COMP_GNUC_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_GNUC_NAME "Gnu GCC C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_GNUC,RTIBOOST_COMP_GNUC_NAME)

#ifdef RTIBOOST_COMP_GNUC_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_GNUC_EMULATED,RTIBOOST_COMP_GNUC_NAME)
#endif
