/*
Copyright Charly Chevalier 2015
Copyright Joel Falcou 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include <rtiboost/predef/hardware/simd/x86.h>
#include <rtiboost/predef/hardware/simd/x86_amd.h>
#include <rtiboost/predef/hardware/simd/arm.h>
#include <rtiboost/predef/hardware/simd/ppc.h>

#ifndef RTIBOOST_PREDEF_HARDWARE_SIMD_H
#define RTIBOOST_PREDEF_HARDWARE_SIMD_H

#include <rtiboost/predef/version_number.h>

/*`
 [section Using the `RTIBOOST_HW_SIMD_*` predefs]
 [include ../doc/hardware_simd.qbk]
 [endsect]

 [/ --------------------------- ]

 [section `RTIBOOST_HW_SIMD_*`]

 [heading `RTIBOOST_HW_SIMD`]

 The SIMD extension detected for a specific architectures.
 Version number depends on the detected extension.

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`RTIBOOST_HW_SIMD_X86_AVAILABLE`] [__predef_detection__]]
     [[`RTIBOOST_HW_SIMD_X86_AMD_AVAILABLE`] [__predef_detection__]]
     [[`RTIBOOST_HW_SIMD_ARM_AVAILABLE`] [__predef_detection__]]
     [[`RTIBOOST_HW_SIMD_PPC_AVAILABLE`] [__predef_detection__]]
     ]

 [include ../include/boost/predef/hardware/simd/x86.h]
 [include ../include/boost/predef/hardware/simd/x86_amd.h]
 [include ../include/boost/predef/hardware/simd/arm.h]
 [include ../include/boost/predef/hardware/simd/ppc.h]

 [endsect]

 [/ --------------------------- ]

 [section `RTIBOOST_HW_SIMD_X86_*_VERSION`]
 [include ../include/boost/predef/hardware/simd/x86/versions.h]
 [endsect]

 [section `RTIBOOST_HW_SIMD_X86_AMD_*_VERSION`]
 [include ../include/boost/predef/hardware/simd/x86_amd/versions.h]
 [endsect]

 [section `RTIBOOST_HW_SIMD_ARM_*_VERSION`]
 [include ../include/boost/predef/hardware/simd/arm/versions.h]
 [endsect]

 [section `RTIBOOST_HW_SIMD_PPC_*_VERSION`]
 [include ../include/boost/predef/hardware/simd/ppc/versions.h]
 [endsect]

 */

// We check if SIMD extension of multiples architectures have been detected,
// if yes, then this is an error!
//
// NOTE: _X86_AMD implies _X86, so there is no need to check for it here!
//
#if defined(RTIBOOST_HW_SIMD_ARM_AVAILABLE) && defined(RTIBOOST_HW_SIMD_PPC_AVAILABLE) ||\
    defined(RTIBOOST_HW_SIMD_ARM_AVAILABLE) && defined(RTIBOOST_HW_SIMD_X86_AVAILABLE) ||\
    defined(RTIBOOST_HW_SIMD_PPC_AVAILABLE) && defined(RTIBOOST_HW_SIMD_X86_AVAILABLE)
#   error "Multiple SIMD architectures detected, this cannot happen!"
#endif

#if defined(RTIBOOST_HW_SIMD_X86_AVAILABLE) && defined(RTIBOOST_HW_SIMD_X86_AMD_AVAILABLE)
    // If both standard _X86 and _X86_AMD are available,
    // then take the biggest version of the two!
#   if RTIBOOST_HW_SIMD_X86 >= RTIBOOST_HW_SIMD_X86_AMD
#      define RTIBOOST_HW_SIMD RTIBOOST_HW_SIMD_X86
#   else
#      define RTIBOOST_HW_SIMD RTIBOOST_HW_SIMD_X86_AMD
#   endif
#endif

#if !defined(RTIBOOST_HW_SIMD)
    // At this point, only one of these two is defined
#   if defined(RTIBOOST_HW_SIMD_X86_AVAILABLE)
#      define RTIBOOST_HW_SIMD RTIBOOST_HW_SIMD_X86
#   endif
#   if defined(RTIBOOST_HW_SIMD_X86_AMD_AVAILABLE)
#      define RTIBOOST_HW_SIMD RTIBOOST_HW_SIMD_X86_AMD
#   endif
#endif

#if defined(RTIBOOST_HW_SIMD_ARM_AVAILABLE)
#   define RTIBOOST_HW_SIMD RTIBOOST_HW_SIMD_ARM
#endif

#if defined(RTIBOOST_HW_SIMD_PPC_AVAILABLE)
#   define RTIBOOST_HW_SIMD RTIBOOST_HW_SIMD_PPC
#endif

#if defined(RTIBOOST_HW_SIMD)
#   define RTIBOOST_HW_SIMD_AVAILABLE
#else
#   define RTIBOOST_HW_SIMD RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE
#endif

#define RTIBOOST_HW_SIMD_NAME "Hardware SIMD"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_HW_SIMD, RTIBOOST_HW_SIMD_NAME)
