/*
Copyright Rene Rivera 2011-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_PYRAMID_H
#define RTIBOOST_PREDEF_ARCHITECTURE_PYRAMID_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_ARCH_PYRAMID`]

Pyramid 9810 architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`pyr`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_ARCH_PYRAMID RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(pyr)
#   undef RTIBOOST_ARCH_PYRAMID
#   define RTIBOOST_ARCH_PYRAMID RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_ARCH_PYRAMID
#   define RTIBOOST_ARCH_PYRAMID_AVAILABLE
#endif

#define RTIBOOST_ARCH_PYRAMID_NAME "Pyramid 9810"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_PYRAMID,RTIBOOST_ARCH_PYRAMID_NAME)
