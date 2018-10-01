/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_STD_MODENA_H
#define RTIBOOST_PREDEF_LIBRARY_STD_MODENA_H

#include <rtiboost/predef/library/std/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_STD_MSIPL`]

[@http://modena.us/ Modena Software Lib++] Standard C++ Library.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`MSIPL_COMPILE_H`] [__predef_detection__]]
    [[`__MSIPL_COMPILE_H`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_LIB_STD_MSIPL RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(MSIPL_COMPILE_H) || defined(__MSIPL_COMPILE_H)
#   undef RTIBOOST_LIB_STD_MSIPL
#   define RTIBOOST_LIB_STD_MSIPL RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_LIB_STD_MSIPL
#   define RTIBOOST_LIB_STD_MSIPL_AVAILABLE
#endif

#define RTIBOOST_LIB_STD_MSIPL_NAME "Modena Software Lib++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_STD_MSIPL,RTIBOOST_LIB_STD_MSIPL_NAME)
