/*
Copyright Rene Rivera 2011-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LANGUAGE_OBJC_H
#define RTIBOOST_PREDEF_LANGUAGE_OBJC_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LANG_OBJC`]

[@http://en.wikipedia.org/wiki/Objective-C Objective-C] language.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__OBJC__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_LANG_OBJC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__OBJC__)
#   undef RTIBOOST_LANG_OBJC
#   define RTIBOOST_LANG_OBJC RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_LANG_OBJC
#   define RTIBOOST_LANG_OBJC_AVAILABLE
#endif

#define RTIBOOST_LANG_OBJC_NAME "Objective-C"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LANG_OBJC,RTIBOOST_LANG_OBJC_NAME)
