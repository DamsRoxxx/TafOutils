/*
Copyright Rene Rivera 2012-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_BSD_FREE_H
#define RTIBOOST_PREDEF_OS_BSD_FREE_H

#include <rtiboost/predef/os/bsd.h>

/*`
[heading `RTIBOOST_OS_BSD_FREE`]

[@http://en.wikipedia.org/wiki/Freebsd FreeBSD] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__FreeBSD__`] [__predef_detection__]]

    [[`__FreeBSD_version`] [V.R.P]]
    ]
 */

#define RTIBOOST_OS_BSD_FREE RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__FreeBSD__) \
    )
#   ifndef RTIBOOST_OS_BSD_AVAILABLE
#       define RTIBOOST_OS_BSD RTIBOOST_VERSION_NUMBER_AVAILABLE
#       define RTIBOOST_OS_BSD_AVAILABLE
#   endif
#   undef RTIBOOST_OS_BSD_FREE
#   if defined(__FreeBSD_version)
#       if __FreeBSD_version < 500000
#           define RTIBOOST_OS_BSD_FREE \
                RTIBOOST_PREDEF_MAKE_10_VRP000(__FreeBSD_version)
#       else
#           define RTIBOOST_OS_BSD_FREE \
                RTIBOOST_PREDEF_MAKE_10_VRR000(__FreeBSD_version)
#       endif
#   else
#       define RTIBOOST_OS_BSD_FREE RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if RTIBOOST_OS_BSD_FREE
#   define RTIBOOST_OS_BSD_FREE_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_BSD_FREE_NAME "Free BSD"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_BSD_FREE,RTIBOOST_OS_BSD_FREE_NAME)
