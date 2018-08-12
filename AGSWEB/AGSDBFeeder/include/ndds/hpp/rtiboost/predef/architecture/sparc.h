/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_SPARC_H
#define RTIBOOST_PREDEF_ARCHITECTURE_SPARC_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_ARCH_SPARC`]

[@http://en.wikipedia.org/wiki/SPARC SPARC] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__sparc__`] [__predef_detection__]]
    [[`__sparc`] [__predef_detection__]]

    [[`__sparcv9`] [9.0.0]]
    [[`__sparcv8`] [8.0.0]]
    ]
 */

#define RTIBOOST_ARCH_SPARC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__sparc__) || defined(__sparc)
#   undef RTIBOOST_ARCH_SPARC
#   if !defined(RTIBOOST_ARCH_SPARC) && defined(__sparcv9)
#       define RTIBOOST_ARCH_SPARC RTIBOOST_VERSION_NUMBER(9,0,0)
#   endif
#   if !defined(RTIBOOST_ARCH_SPARC) && defined(__sparcv8)
#       define RTIBOOST_ARCH_SPARC RTIBOOST_VERSION_NUMBER(8,0,0)
#   endif
#   if !defined(RTIBOOST_ARCH_SPARC)
#       define RTIBOOST_ARCH_SPARC RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if RTIBOOST_ARCH_SPARC
#   define RTIBOOST_ARCH_SPARC_AVAILABLE
#endif

#define RTIBOOST_ARCH_SPARC_NAME "SPARC"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_SPARC,RTIBOOST_ARCH_SPARC_NAME)
