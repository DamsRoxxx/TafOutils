/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_SOLARIS_H
#define RTIBOOST_PREDEF_OS_SOLARIS_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_OS_SOLARIS`]

[@http://en.wikipedia.org/wiki/Solaris_Operating_Environment Solaris] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`sun`] [__predef_detection__]]
    [[`__sun`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_SOLARIS RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(sun) || defined(__sun) \
    )
#   undef RTIBOOST_OS_SOLARIS
#   define RTIBOOST_OS_SOLARIS RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_SOLARIS
#   define RTIBOOST_OS_SOLARIS_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_SOLARIS_NAME "Solaris"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_SOLARIS,RTIBOOST_OS_SOLARIS_NAME)
