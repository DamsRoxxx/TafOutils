/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_EKOPATH_H
#define RTIBOOST_PREDEF_COMPILER_EKOPATH_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_PATH`]

[@http://en.wikipedia.org/wiki/PathScale EKOpath] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__PATHCC__`] [__predef_detection__]]

    [[`__PATHCC__`, `__PATHCC_MINOR__`, `__PATHCC_PATCHLEVEL__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_PATH RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__PATHCC__)
#   define RTIBOOST_COMP_PATH_DETECTION \
        RTIBOOST_VERSION_NUMBER(__PATHCC__,__PATHCC_MINOR__,__PATHCC_PATCHLEVEL__)
#endif

#ifdef RTIBOOST_COMP_PATH_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_PATH_EMULATED RTIBOOST_COMP_PATH_DETECTION
#   else
#       undef RTIBOOST_COMP_PATH
#       define RTIBOOST_COMP_PATH RTIBOOST_COMP_PATH_DETECTION
#   endif
#   define RTIBOOST_COMP_PATH_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_PATH_NAME "EKOpath"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_PATH,RTIBOOST_COMP_PATH_NAME)

#ifdef RTIBOOST_COMP_PATH_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_PATH_EMULATED,RTIBOOST_COMP_PATH_NAME)
#endif
