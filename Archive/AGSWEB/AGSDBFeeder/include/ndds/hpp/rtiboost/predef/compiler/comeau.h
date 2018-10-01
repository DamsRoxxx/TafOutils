/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_COMEAU_H
#define RTIBOOST_PREDEF_COMPILER_COMEAU_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

#define RTIBOOST_COMP_COMO RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

/*`
[heading `RTIBOOST_COMP_COMO`]

[@http://en.wikipedia.org/wiki/Comeau_C/C%2B%2B Comeau C++] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__COMO__`] [__predef_detection__]]

    [[`__COMO_VERSION__`] [V.R.P]]
    ]
 */

#if defined(__COMO__)
#   if !defined(RTIBOOST_COMP_COMO_DETECTION) && defined(__COMO_VERSION__)
#       define RTIBOOST_COMP_COMO_DETECTION RTIBOOST_PREDEF_MAKE_0X_VRP(__COMO_VERSION__)
#   endif
#   if !defined(RTIBOOST_COMP_COMO_DETECTION)
#       define RTIBOOST_COMP_COMO_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_COMO_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_COMO_EMULATED RTIBOOST_COMP_COMO_DETECTION
#   else
#       undef RTIBOOST_COMP_COMO
#       define RTIBOOST_COMP_COMO RTIBOOST_COMP_COMO_DETECTION
#   endif
#   define RTIBOOST_COMP_COMO_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_COMO_NAME "Comeau C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_COMO,RTIBOOST_COMP_COMO_NAME)

#ifdef RTIBOOST_COMP_COMO_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_COMO_EMULATED,RTIBOOST_COMP_COMO_NAME)
#endif
