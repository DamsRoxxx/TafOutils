/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_UNIX_H
#define RTIBOOST_PREDEF_OS_UNIX_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_OS_UNIX`]

[@http://en.wikipedia.org/wiki/Unix Unix Environment] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`unix`] [__predef_detection__]]
    [[`__unix`] [__predef_detection__]]
    [[`_XOPEN_SOURCE`] [__predef_detection__]]
    [[`_POSIX_SOURCE`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_UNIX RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(unix) || defined(__unix) || \
    defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#   undef RTIBOOST_OS_UNIX
#   define RTIBOOST_OS_UNIX RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_UNIX
#   define RTIBOOST_OS_UNIX_AVAILABLE
#endif

#define RTIBOOST_OS_UNIX_NAME "Unix Environment"

/*`
[heading `RTIBOOST_OS_SVR4`]

[@http://en.wikipedia.org/wiki/UNIX_System_V SVR4 Environment] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__sysv__`] [__predef_detection__]]
    [[`__SVR4`] [__predef_detection__]]
    [[`__svr4__`] [__predef_detection__]]
    [[`_SYSTYPE_SVR4`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_SVR4 RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__sysv__) || defined(__SVR4) || \
    defined(__svr4__) || defined(_SYSTYPE_SVR4)
#   undef RTIBOOST_OS_SVR4
#   define RTIBOOST_OS_SVR4 RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_SVR4
#   define RTIBOOST_OS_SVR4_AVAILABLE
#endif

#define RTIBOOST_OS_SVR4_NAME "SVR4 Environment"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_UNIX,RTIBOOST_OS_UNIX_NAME)
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_SVR4,RTIBOOST_OS_SVR4_NAME)
