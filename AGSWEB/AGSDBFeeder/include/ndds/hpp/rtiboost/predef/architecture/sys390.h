/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_SYS390_H
#define RTIBOOST_PREDEF_ARCHITECTURE_SYS390_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_ARCH_SYS390`]

[@http://en.wikipedia.org/wiki/System/390 System/390] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__s390__`] [__predef_detection__]]
    [[`__s390x__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_ARCH_SYS390 RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__s390__) || defined(__s390x__)
#   undef RTIBOOST_ARCH_SYS390
#   define RTIBOOST_ARCH_SYS390 RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_ARCH_SYS390
#   define RTIBOOST_ARCH_SYS390_AVAILABLE
#endif

#define RTIBOOST_ARCH_SYS390_NAME "System/390"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_SYS390,RTIBOOST_ARCH_SYS390_NAME)
