/*
Copyright Rene Rivera 2012-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_BSD_DRAGONFLY_H
#define RTIBOOST_PREDEF_OS_BSD_DRAGONFLY_H

#include <rtiboost/predef/os/bsd.h>

/*`
[heading `RTIBOOST_OS_BSD_DRAGONFLY`]

[@http://en.wikipedia.org/wiki/DragonFly_BSD DragonFly BSD] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__DragonFly__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_BSD_DRAGONFLY RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__DragonFly__) \
    )
#   ifndef RTIBOOST_OS_BSD_AVAILABLE
#       define RTIBOOST_OS_BSD RTIBOOST_VERSION_NUMBER_AVAILABLE
#       define RTIBOOST_OS_BSD_AVAILABLE
#   endif
#   undef RTIBOOST_OS_BSD_DRAGONFLY
#   if defined(__DragonFly__)
#       define RTIBOOST_OS_DRAGONFLY_BSD RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if RTIBOOST_OS_BSD_DRAGONFLY
#   define RTIBOOST_OS_BSD_DRAGONFLY_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_BSD_DRAGONFLY_NAME "DragonFly BSD"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_BSD_DRAGONFLY,RTIBOOST_OS_BSD_DRAGONFLY_NAME)
