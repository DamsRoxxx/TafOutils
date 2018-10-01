/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_Z_H
#define RTIBOOST_PREDEF_ARCHITECTURE_Z_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_ARCH_Z`]

[@http://en.wikipedia.org/wiki/Z/Architecture z/Architecture] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__SYSC_ZARCH__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_ARCH_Z RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__SYSC_ZARCH__)
#   undef RTIBOOST_ARCH_Z
#   define RTIBOOST_ARCH_Z RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_ARCH_Z
#   define RTIBOOST_ARCH_Z_AVAILABLE
#endif

#define RTIBOOST_ARCH_Z_NAME "z/Architecture"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_Z,RTIBOOST_ARCH_Z_NAME)
