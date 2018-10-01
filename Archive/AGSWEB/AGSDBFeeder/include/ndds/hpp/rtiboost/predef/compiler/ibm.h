/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_IBM_H
#define RTIBOOST_PREDEF_COMPILER_IBM_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_IBM`]

[@http://en.wikipedia.org/wiki/VisualAge IBM XL C/C++] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__IBMCPP__`] [__predef_detection__]]
    [[`__xlC__`] [__predef_detection__]]
    [[`__xlc__`] [__predef_detection__]]

    [[`__COMPILER_VER__`] [V.R.P]]
    [[`__xlC__`] [V.R.P]]
    [[`__xlc__`] [V.R.P]]
    [[`__IBMCPP__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_IBM RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__IBMCPP__) || defined(__xlC__) || defined(__xlc__)
#   if !defined(RTIBOOST_COMP_IBM_DETECTION) && defined(__COMPILER_VER__)
#       define RTIBOOST_COMP_IBM_DETECTION RTIBOOST_PREDEF_MAKE_0X_VRRPPPP(__COMPILER_VER__)
#   endif
#   if !defined(RTIBOOST_COMP_IBM_DETECTION) && defined(__xlC__)
#       define RTIBOOST_COMP_IBM_DETECTION RTIBOOST_PREDEF_MAKE_0X_VVRR(__xlC__)
#   endif
#   if !defined(RTIBOOST_COMP_IBM_DETECTION) && defined(__xlc__)
#       define RTIBOOST_COMP_IBM_DETECTION RTIBOOST_PREDEF_MAKE_0X_VVRR(__xlc__)
#   endif
#   if !defined(RTIBOOST_COMP_IBM_DETECTION)
#       define RTIBOOST_COMP_IBM_DETECTION RTIBOOST_PREDEF_MAKE_10_VRP(__IBMCPP__)
#   endif
#endif

#ifdef RTIBOOST_COMP_IBM_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_IBM_EMULATED RTIBOOST_COMP_IBM_DETECTION
#   else
#       undef RTIBOOST_COMP_IBM
#       define RTIBOOST_COMP_IBM RTIBOOST_COMP_IBM_DETECTION
#   endif
#   define RTIBOOST_COMP_IBM_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_IBM_NAME "IBM XL C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_IBM,RTIBOOST_COMP_IBM_NAME)

#ifdef RTIBOOST_COMP_IBM_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_IBM_EMULATED,RTIBOOST_COMP_IBM_NAME)
#endif
