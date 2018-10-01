/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_METROWERKS_H
#define RTIBOOST_PREDEF_COMPILER_METROWERKS_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_MWERKS`]

[@http://en.wikipedia.org/wiki/CodeWarrior Metrowerks CodeWarrior] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__MWERKS__`] [__predef_detection__]]
    [[`__CWCC__`] [__predef_detection__]]

    [[`__CWCC__`] [V.R.P]]
    [[`__MWERKS__`] [V.R.P >= 4.2.0]]
    [[`__MWERKS__`] [9.R.0]]
    [[`__MWERKS__`] [8.R.0]]
    ]
 */

#define RTIBOOST_COMP_MWERKS RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__MWERKS__) || defined(__CWCC__)
#   if !defined(RTIBOOST_COMP_MWERKS_DETECTION) && defined(__CWCC__)
#       define RTIBOOST_COMP_MWERKS_DETECTION RTIBOOST_PREDEF_MAKE_0X_VRPP(__CWCC__)
#   endif
#   if !defined(RTIBOOST_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x4200)
#       define RTIBOOST_COMP_MWERKS_DETECTION RTIBOOST_PREDEF_MAKE_0X_VRPP(__MWERKS__)
#   endif
#   if !defined(RTIBOOST_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3204) // note the "skip": 04->9.3
#       define RTIBOOST_COMP_MWERKS_DETECTION RTIBOOST_VERSION_NUMBER(9,(__MWERKS__)%100-1,0)
#   endif
#   if !defined(RTIBOOST_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3200)
#       define RTIBOOST_COMP_MWERKS_DETECTION RTIBOOST_VERSION_NUMBER(9,(__MWERKS__)%100,0)
#   endif
#   if !defined(RTIBOOST_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3000)
#       define RTIBOOST_COMP_MWERKS_DETECTION RTIBOOST_VERSION_NUMBER(8,(__MWERKS__)%100,0)
#   endif
#   if !defined(RTIBOOST_COMP_MWERKS_DETECTION)
#       define RTIBOOST_COMP_MWERKS_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_MWERKS_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_MWERKS_EMULATED RTIBOOST_COMP_MWERKS_DETECTION
#   else
#       undef RTIBOOST_COMP_MWERKS
#       define RTIBOOST_COMP_MWERKS RTIBOOST_COMP_MWERKS_DETECTION
#   endif
#   define RTIBOOST_COMP_MWERKS_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_MWERKS_NAME "Metrowerks CodeWarrior"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_MWERKS,RTIBOOST_COMP_MWERKS_NAME)

#ifdef RTIBOOST_COMP_MWERKS_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_MWERKS_EMULATED,RTIBOOST_COMP_MWERKS_NAME)
#endif
