/*
Copyright Charly Chevalier 2015
Copyright Joel Falcou 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_HARDWARE_SIMD_X86_AMD_H
#define RTIBOOST_PREDEF_HARDWARE_SIMD_X86_AMD_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/hardware/simd/x86_amd/versions.h>

/*`
 [heading `RTIBOOST_HW_SIMD_X86_AMD`]

 The SIMD extension for x86 (AMD) (*if detected*).
 Version number depends on the most recent detected extension.

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__SSE4A__`] [__predef_detection__]]

     [[`__FMA4__`] [__predef_detection__]]

     [[`__XOP__`] [__predef_detection__]]

     [[`RTIBOOST_HW_SIMD_X86`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__SSE4A__`] [RTIBOOST_HW_SIMD_X86_SSE4A_VERSION]]

     [[`__FMA4__`] [RTIBOOST_HW_SIMD_X86_FMA4_VERSION]]

     [[`__XOP__`] [RTIBOOST_HW_SIMD_X86_XOP_VERSION]]

     [[`RTIBOOST_HW_SIMD_X86`] [RTIBOOST_HW_SIMD_X86]]
     ]

 [note This predef includes every other x86 SIMD extensions and also has other
 more specific extensions (FMA4, XOP, SSE4a). You should use this predef
 instead of `RTIBOOST_HW_SIMD_X86` to test if those specific extensions have
 been detected.]

 */

#define RTIBOOST_HW_SIMD_X86_AMD RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

// AMD CPUs also use x86 architecture. We first try to detect if any AMD
// specific extension are detected, if yes, then try to detect more recent x86
// common extensions.

#undef RTIBOOST_HW_SIMD_X86_AMD
#if !defined(RTIBOOST_HW_SIMD_X86_AMD) && defined(__XOP__)
#   define RTIBOOST_HW_SIMD_X86_AMD RTIBOOST_HW_SIMD_X86_AMD_XOP_VERSION
#endif
#if !defined(RTIBOOST_HW_SIMD_X86_AMD) && defined(__FMA4__)
#   define RTIBOOST_HW_SIMD_X86_AMD RTIBOOST_HW_SIMD_X86_AMD_FMA4_VERSION
#endif
#if !defined(RTIBOOST_HW_SIMD_X86_AMD) && defined(__SSE4A__)
#   define RTIBOOST_HW_SIMD_X86_AMD RTIBOOST_HW_SIMD_X86_AMD_SSE4A_VERSION
#endif

#if !defined(RTIBOOST_HW_SIMD_X86_AMD)
#   define RTIBOOST_HW_SIMD_X86_AMD RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE
#else
    // At this point, we know that we have an AMD CPU, we do need to check for
    // other x86 extensions to determine the final version number.
#   include <rtiboost/predef/hardware/simd/x86.h>
#   if RTIBOOST_HW_SIMD_X86 > RTIBOOST_HW_SIMD_X86_AMD
#      undef RTIBOOST_HW_SIMD_X86_AMD
#      define RTIBOOST_HW_SIMD_X86_AMD RTIBOOST_HW_SIMD_X86
#   endif
#   define RTIBOOST_HW_SIMD_X86_AMD_AVAILABLE
#endif

#define RTIBOOST_HW_SIMD_X86_AMD_NAME "x86 (AMD) SIMD"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_HW_SIMD_X86_AMD, RTIBOOST_HW_SIMD_X86_AMD_NAME)
