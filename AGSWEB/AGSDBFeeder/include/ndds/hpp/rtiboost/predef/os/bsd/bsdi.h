/*
Copyright Rene Rivera 2012-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_BSD_BSDI_H
#define RTIBOOST_PREDEF_OS_BSD_BSDI_H

#include <rtiboost/predef/os/bsd.h>

/*`
[heading `RTIBOOST_OS_BSD_BSDI`]

[@http://en.wikipedia.org/wiki/BSD/OS BSDi BSD/OS] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__bsdi__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_BSD_BSDI RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__bsdi__) \
    )
#   ifndef RTIBOOST_OS_BSD_AVAILABLE
#       define RTIBOOST_OS_BSD RTIBOOST_VERSION_NUMBER_AVAILABLE
#       define RTIBOOST_OS_BSD_AVAILABLE
#   endif
#   undef RTIBOOST_OS_BSD_BSDI
#   define RTIBOOST_OS_BSD_BSDI RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_BSD_BSDI
#   define RTIBOOST_OS_BSD_BSDI_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_BSD_BSDI_NAME "BSDi BSD/OS"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_BSD_BSDI,RTIBOOST_OS_BSD_BSDI_NAME)
