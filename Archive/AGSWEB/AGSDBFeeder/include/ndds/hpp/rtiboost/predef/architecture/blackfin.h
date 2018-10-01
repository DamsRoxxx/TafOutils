/*
Copyright Rene Rivera 2013-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_BLACKFIN_H
#define RTIBOOST_PREDEF_ARCHITECTURE_BLACKFIN_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_ARCH_BLACKFIN`]

Blackfin Processors from Analog Devices.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__bfin__`] [__predef_detection__]]
    [[`__BFIN__`] [__predef_detection__]]
    [[`bfin`] [__predef_detection__]]
    [[`BFIN`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_ARCH_BLACKFIN RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__bfin__) || defined(__BFIN__) || \
    defined(bfin) || defined(BFIN)
#   undef RTIBOOST_ARCH_BLACKFIN
#   define RTIBOOST_ARCH_BLACKFIN RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_ARCH_BLACKFIN
#   define RTIBOOST_ARCH_BLACKFIN_AVAILABLE
#endif

#define RTIBOOST_ARCH_BLACKFIN_NAME "Blackfin"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_BLACKFIN,RTIBOOST_ARCH_BLACKFIN_NAME)
