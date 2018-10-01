/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_RS6K_H
#define RTIBOOST_PREDEF_ARCHITECTURE_RS6K_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_ARCH_RS6000`]

[@http://en.wikipedia.org/wiki/RS/6000 RS/6000] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__THW_RS6000`] [__predef_detection__]]
    [[`_IBMR2`] [__predef_detection__]]
    [[`_POWER`] [__predef_detection__]]
    [[`_ARCH_PWR`] [__predef_detection__]]
    [[`_ARCH_PWR2`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_ARCH_RS6000 RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__THW_RS6000) || defined(_IBMR2) || \
    defined(_POWER) || defined(_ARCH_PWR) || \
    defined(_ARCH_PWR2)
#   undef RTIBOOST_ARCH_RS6000
#   define RTIBOOST_ARCH_RS6000 RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_ARCH_RS6000
#   define RTIBOOST_ARCH_RS6000_AVAILABLE
#endif

#define RTIBOOST_ARCH_RS6000_NAME "RS/6000"

#define RTIBOOST_ARCH_PWR RTIBOOST_ARCH_RS6000

#if RTIBOOST_ARCH_PWR
#   define RTIBOOST_ARCH_PWR_AVAILABLE
#endif

#define RTIBOOST_ARCH_PWR_NAME RTIBOOST_ARCH_RS6000_NAME

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_RS6000,RTIBOOST_ARCH_RS6000_NAME)
