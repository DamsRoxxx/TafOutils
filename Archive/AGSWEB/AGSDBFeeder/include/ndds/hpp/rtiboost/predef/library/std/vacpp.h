/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_STD_VACPP_H
#define RTIBOOST_PREDEF_LIBRARY_STD_VACPP_H

#include <rtiboost/predef/library/std/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_STD_IBM`]

[@http://www.ibm.com/software/awdtools/xlcpp/ IBM VACPP Standard C++] library.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__IBMCPP__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_LIB_STD_IBM RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__IBMCPP__)
#   undef RTIBOOST_LIB_STD_IBM
#   define RTIBOOST_LIB_STD_IBM RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_LIB_STD_IBM
#   define RTIBOOST_LIB_STD_IBM_AVAILABLE
#endif

#define RTIBOOST_LIB_STD_IBM_NAME "IBM VACPP"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_STD_IBM,RTIBOOST_LIB_STD_IBM_NAME)
