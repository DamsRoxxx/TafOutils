/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_STD_STLPORT_H
#define RTIBOOST_PREDEF_LIBRARY_STD_STLPORT_H

#include <rtiboost/predef/library/std/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_STD_STLPORT`]

[@http://sourceforge.net/projects/stlport/ STLport Standard C++] library.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__SGI_STL_PORT`] [__predef_detection__]]
    [[`_STLPORT_VERSION`] [__predef_detection__]]

    [[`_STLPORT_MAJOR`, `_STLPORT_MINOR`, `_STLPORT_PATCHLEVEL`] [V.R.P]]
    [[`_STLPORT_VERSION`] [V.R.P]]
    [[`__SGI_STL_PORT`] [V.R.P]]
    ]
 */

#define RTIBOOST_LIB_STD_STLPORT RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#   undef RTIBOOST_LIB_STD_STLPORT
#   if !defined(RTIBOOST_LIB_STD_STLPORT) && defined(_STLPORT_MAJOR)
#       define RTIBOOST_LIB_STD_STLPORT \
            RTIBOOST_VERSION_NUMBER(_STLPORT_MAJOR,_STLPORT_MINOR,_STLPORT_PATCHLEVEL)
#   endif
#   if !defined(RTIBOOST_LIB_STD_STLPORT) && defined(_STLPORT_VERSION)
#       define RTIBOOST_LIB_STD_STLPORT RTIBOOST_PREDEF_MAKE_0X_VRP(_STLPORT_VERSION)
#   endif
#   if !defined(RTIBOOST_LIB_STD_STLPORT)
#       define RTIBOOST_LIB_STD_STLPORT RTIBOOST_PREDEF_MAKE_0X_VRP(__SGI_STL_PORT)
#   endif
#endif

#if RTIBOOST_LIB_STD_STLPORT
#   define RTIBOOST_LIB_STD_STLPORT_AVAILABLE
#endif

#define RTIBOOST_LIB_STD_STLPORT_NAME "STLport"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_STD_STLPORT,RTIBOOST_LIB_STD_STLPORT_NAME)
