/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_BSD_H
#define RTIBOOST_PREDEF_OS_BSD_H

/* Special case: OSX will define BSD predefs if the sys/param.h
 * header is included. We can guard against that, but only if we
 * detect OSX first. Hence we will force include OSX detection
 * before doing any BSD detection.
 */
#include <rtiboost/predef/os/macos.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_OS_BSD`]

[@http://en.wikipedia.org/wiki/Berkeley_Software_Distribution BSD] operating system.

BSD has various branch operating systems possible and each detected
individually. This detects the following variations and sets a specific
version number macro to match:

* `RTIBOOST_OS_BSD_DRAGONFLY` [@http://en.wikipedia.org/wiki/DragonFly_BSD DragonFly BSD]
* `RTIBOOST_OS_BSD_FREE` [@http://en.wikipedia.org/wiki/Freebsd FreeBSD]
* `RTIBOOST_OS_BSD_BSDI` [@http://en.wikipedia.org/wiki/BSD/OS BSDi BSD/OS]
* `RTIBOOST_OS_BSD_NET` [@http://en.wikipedia.org/wiki/Netbsd NetBSD]
* `RTIBOOST_OS_BSD_OPEN` [@http://en.wikipedia.org/wiki/Openbsd OpenBSD]

[note The general `RTIBOOST_OS_BSD` is set in all cases to indicate some form
of BSD. If the above variants is detected the corresponding macro is also set.]

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`BSD`] [__predef_detection__]]
    [[`_SYSTYPE_BSD`] [__predef_detection__]]

    [[`BSD4_2`] [4.2.0]]
    [[`BSD4_3`] [4.3.0]]
    [[`BSD4_4`] [4.4.0]]
    [[`BSD`] [V.R.0]]
    ]
 */

#include <rtiboost/predef/os/bsd/bsdi.h>
#include <rtiboost/predef/os/bsd/dragonfly.h>
#include <rtiboost/predef/os/bsd/free.h>
#include <rtiboost/predef/os/bsd/open.h>
#include <rtiboost/predef/os/bsd/net.h>

#ifndef RTIBOOST_OS_BSD
#define RTIBOOST_OS_BSD RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE
#endif

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(BSD) || \
    defined(_SYSTYPE_BSD) \
    )
#   undef RTIBOOST_OS_BSD
#   include <sys/param.h>
#   if !defined(RTIBOOST_OS_BSD) && defined(BSD4_4)
#       define RTIBOOST_OS_BSD RTIBOOST_VERSION_NUMBER(4,4,0)
#   endif
#   if !defined(RTIBOOST_OS_BSD) && defined(BSD4_3)
#       define RTIBOOST_OS_BSD RTIBOOST_VERSION_NUMBER(4,3,0)
#   endif
#   if !defined(RTIBOOST_OS_BSD) && defined(BSD4_2)
#       define RTIBOOST_OS_BSD RTIBOOST_VERSION_NUMBER(4,2,0)
#   endif
#   if !defined(RTIBOOST_OS_BSD) && defined(BSD)
#       define RTIBOOST_OS_BSD RTIBOOST_PREDEF_MAKE_10_VVRR(BSD)
#   endif
#   if !defined(RTIBOOST_OS_BSD)
#       define RTIBOOST_OS_BSD RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if RTIBOOST_OS_BSD
#   define RTIBOOST_OS_BSD_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_BSD_NAME "BSD"

#else

#include <rtiboost/predef/os/bsd/bsdi.h>
#include <rtiboost/predef/os/bsd/dragonfly.h>
#include <rtiboost/predef/os/bsd/free.h>
#include <rtiboost/predef/os/bsd/open.h>
#include <rtiboost/predef/os/bsd/net.h>

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_BSD,RTIBOOST_OS_BSD_NAME)
