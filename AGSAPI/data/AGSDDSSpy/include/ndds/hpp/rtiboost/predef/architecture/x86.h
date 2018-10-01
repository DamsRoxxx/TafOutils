/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include <rtiboost/predef/architecture/x86/32.h>
#include <rtiboost/predef/architecture/x86/64.h>

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_X86_H
#define RTIBOOST_PREDEF_ARCHITECTURE_X86_H

/*`
[heading `RTIBOOST_ARCH_X86`]

[@http://en.wikipedia.org/wiki/X86 Intel x86] architecture. This is
a category to indicate that either `RTIBOOST_ARCH_X86_32` or
`RTIBOOST_ARCH_X86_64` is detected.
 */

#define RTIBOOST_ARCH_X86 RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if RTIBOOST_ARCH_X86_32 || RTIBOOST_ARCH_X86_64
#   undef RTIBOOST_ARCH_X86
#   define RTIBOOST_ARCH_X86 RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_ARCH_X86
#   define RTIBOOST_ARCH_X86_AVAILABLE
#endif

#define RTIBOOST_ARCH_X86_NAME "Intel x86"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_X86,RTIBOOST_ARCH_X86_NAME)
