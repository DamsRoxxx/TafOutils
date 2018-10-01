/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_LLVM_H
#define RTIBOOST_PREDEF_COMPILER_LLVM_H

/* Other compilers that emulate this one need to be detected first. */

#include <rtiboost/predef/compiler/clang.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_LLVM`]

[@http://en.wikipedia.org/wiki/LLVM LLVM] compiler.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__llvm__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_COMP_LLVM RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__llvm__)
#   define RTIBOOST_COMP_LLVM_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#ifdef RTIBOOST_COMP_LLVM_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_LLVM_EMULATED RTIBOOST_COMP_LLVM_DETECTION
#   else
#       undef RTIBOOST_COMP_LLVM
#       define RTIBOOST_COMP_LLVM RTIBOOST_COMP_LLVM_DETECTION
#   endif
#   define RTIBOOST_COMP_LLVM_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_LLVM_NAME "LLVM"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_LLVM,RTIBOOST_COMP_LLVM_NAME)

#ifdef RTIBOOST_COMP_LLVM_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_LLVM_EMULATED,RTIBOOST_COMP_LLVM_NAME)
#endif
