/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_CLANG_H
#define RTIBOOST_PREDEF_COMPILER_CLANG_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_CLANG`]

[@http://en.wikipedia.org/wiki/Clang Clang] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__clang__`] [__predef_detection__]]

    [[`__clang_major__`, `__clang_minor__`, `__clang_patchlevel__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_CLANG RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__clang__)
#   define RTIBOOST_COMP_CLANG_DETECTION RTIBOOST_VERSION_NUMBER(__clang_major__,__clang_minor__,__clang_patchlevel__)
#endif

#ifdef RTIBOOST_COMP_CLANG_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_CLANG_EMULATED RTIBOOST_COMP_CLANG_DETECTION
#   else
#       undef RTIBOOST_COMP_CLANG
#       define RTIBOOST_COMP_CLANG RTIBOOST_COMP_CLANG_DETECTION
#   endif
#   define RTIBOOST_COMP_CLANG_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_CLANG_NAME "Clang"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_CLANG,RTIBOOST_COMP_CLANG_NAME)

#ifdef RTIBOOST_COMP_CLANG_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_CLANG_EMULATED,RTIBOOST_COMP_CLANG_NAME)
#endif
