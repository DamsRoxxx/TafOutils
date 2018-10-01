/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_SYS370_H
#define RTIBOOST_PREDEF_ARCHITECTURE_SYS370_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_ARCH_SYS370`]

[@http://en.wikipedia.org/wiki/System/370 System/370] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__370__`] [__predef_detection__]]
    [[`__THW_370__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_ARCH_SYS370 RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__370__) || defined(__THW_370__)
#   undef RTIBOOST_ARCH_SYS370
#   define RTIBOOST_ARCH_SYS370 RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_ARCH_SYS370
#   define RTIBOOST_ARCH_SYS370_AVAILABLE
#endif

#define RTIBOOST_ARCH_SYS370_NAME "System/370"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_SYS370,RTIBOOST_ARCH_SYS370_NAME)
