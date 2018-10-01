/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_CYGWIN_H
#define RTIBOOST_PREDEF_OS_CYGWIN_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_OS_CYGWIN`]

[@http://en.wikipedia.org/wiki/Cygwin Cygwin] evironment.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__CYGWIN__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_CYGWIN RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__CYGWIN__) \
    )
#   undef RTIBOOST_OS_CYGWIN
#   define RTIBOOST_OS_CYGWIN RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_CYGWIN
#   define RTIBOOST_OS_CYGWIN_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_CYGWIN_NAME "Cygwin"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_CYGWIN,RTIBOOST_OS_CYGWIN_NAME)
