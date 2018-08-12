/*
Copyright Jessica Hamilton 2014
Copyright Rene Rivera 2014-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_HAIKU_H
#define RTIBOOST_PREDEF_OS_HAIKU_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_OS_HAIKU`]

[@http://en.wikipedia.org/wiki/Haiku_(operating_system) Haiku] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__HAIKU__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_HAIKU RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__HAIKU__) \
    )
#   undef RTIBOOST_OS_HAIKU
#   define RTIBOOST_OS_HAIKU RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_HAIKU
#   define RTIBOOST_OS_HAIKU_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_HAIKU_NAME "Haiku"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_HAIKU,RTIBOOST_OS_HAIKU_NAME)
