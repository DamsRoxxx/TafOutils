/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_KAI_H
#define RTIBOOST_PREDEF_COMPILER_KAI_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_KCC`]

Kai C++ compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__KCC`] [__predef_detection__]]

    [[`__KCC_VERSION`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_KCC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__KCC)
#   define RTIBOOST_COMP_KCC_DETECTION RTIBOOST_PREDEF_MAKE_0X_VRPP(__KCC_VERSION)
#endif

#ifdef RTIBOOST_COMP_KCC_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_KCC_EMULATED RTIBOOST_COMP_KCC_DETECTION
#   else
#       undef RTIBOOST_COMP_KCC
#       define RTIBOOST_COMP_KCC RTIBOOST_COMP_KCC_DETECTION
#   endif
#   define RTIBOOST_COMP_KCC_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_KCC_NAME "Kai C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_KCC,RTIBOOST_COMP_KCC_NAME)

#ifdef RTIBOOST_COMP_KCC_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_KCC_EMULATED,RTIBOOST_COMP_KCC_NAME)
#endif
