/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_AMIGAOS_H
#define RTIBOOST_PREDEF_OS_AMIGAOS_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_OS_AMIGAOS`]

[@http://en.wikipedia.org/wiki/AmigaOS AmigaOS] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`AMIGA`] [__predef_detection__]]
    [[`__amigaos__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_AMIGAOS RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(AMIGA) || defined(__amigaos__) \
    )
#   undef RTIBOOST_OS_AMIGAOS
#   define RTIBOOST_OS_AMIGAOS RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_AMIGAOS
#   define RTIBOOST_OS_AMIGAOS_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_AMIGAOS_NAME "AmigaOS"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_AMIGAOS,RTIBOOST_OS_AMIGAOS_NAME)
