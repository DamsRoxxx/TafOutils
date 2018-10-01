/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_BORLAND_H
#define RTIBOOST_PREDEF_COMPILER_BORLAND_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_BORLAND`]

[@http://en.wikipedia.org/wiki/C_plus_plus_builder Borland C++] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__BORLANDC__`] [__predef_detection__]]
    [[`__CODEGEARC__`] [__predef_detection__]]

    [[`__BORLANDC__`] [V.R.P]]
    [[`__CODEGEARC__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_BORLAND RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__BORLANDC__) || defined(__CODEGEARC__)
#   if !defined(RTIBOOST_COMP_BORLAND_DETECTION) && (defined(__CODEGEARC__))
#       define RTIBOOST_COMP_BORLAND_DETECTION RTIBOOST_PREDEF_MAKE_0X_VVRP(__CODEGEARC__)
#   endif
#   if !defined(RTIBOOST_COMP_BORLAND_DETECTION)
#       define RTIBOOST_COMP_BORLAND_DETECTION RTIBOOST_PREDEF_MAKE_0X_VVRP(__BORLANDC__)
#   endif
#endif

#ifdef RTIBOOST_COMP_BORLAND_DETECTION
#   define RTIBOOST_COMP_BORLAND_AVAILABLE
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_BORLAND_EMULATED RTIBOOST_COMP_BORLAND_DETECTION
#   else
#       undef RTIBOOST_COMP_BORLAND
#       define RTIBOOST_COMP_BORLAND RTIBOOST_COMP_BORLAND_DETECTION
#   endif
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_BORLAND_NAME "Borland C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_BORLAND,RTIBOOST_COMP_BORLAND_NAME)

#ifdef RTIBOOST_COMP_BORLAND_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_BORLAND_EMULATED,RTIBOOST_COMP_BORLAND_NAME)
#endif
