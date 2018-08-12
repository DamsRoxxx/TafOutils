/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_HP_ACC_H
#define RTIBOOST_PREDEF_COMPILER_HP_ACC_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_HPACC`]

HP aC++ compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__HP_aCC`] [__predef_detection__]]

    [[`__HP_aCC`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_HPACC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__HP_aCC)
#   if !defined(RTIBOOST_COMP_HPACC_DETECTION) && (__HP_aCC > 1)
#       define RTIBOOST_COMP_HPACC_DETECTION RTIBOOST_PREDEF_MAKE_10_VVRRPP(__HP_aCC)
#   endif
#   if !defined(RTIBOOST_COMP_HPACC_DETECTION)
#       define RTIBOOST_COMP_HPACC_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_HPACC_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_HPACC_EMULATED RTIBOOST_COMP_HPACC_DETECTION
#   else
#       undef RTIBOOST_COMP_HPACC
#       define RTIBOOST_COMP_HPACC RTIBOOST_COMP_HPACC_DETECTION
#   endif
#   define RTIBOOST_COMP_HPACC_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_HPACC_NAME "HP aC++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_HPACC,RTIBOOST_COMP_HPACC_NAME)

#ifdef RTIBOOST_COMP_HPACC_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_HPACC_EMULATED,RTIBOOST_COMP_HPACC_NAME)
#endif
