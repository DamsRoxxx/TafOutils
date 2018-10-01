//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  CodeGear C++ compiler setup:

#if !defined( RTIBOOST_WITH_CODEGEAR_WARNINGS )
// these warnings occur frequently in optimized template code
# pragma warn -8004 // var assigned value, but never used
# pragma warn -8008 // condition always true/false
# pragma warn -8066 // dead code can never execute
# pragma warn -8104 // static members with ctors not threadsafe
# pragma warn -8105 // reference member in class without ctors
#endif
//
// versions check:
// last known and checked version is 0x621
#if (__CODEGEARC__ > 0x621)
#  if defined(RTIBOOST_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  else
#     pragma message( "Unknown compiler version - please run the configure tests and report the results")
#  endif
#endif

// CodeGear C++ Builder 2009
#if (__CODEGEARC__ <= 0x613)
#  define RTIBOOST_NO_INTEGRAL_INT64_T
#  define RTIBOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#  define RTIBOOST_NO_PRIVATE_IN_AGGREGATE
#  define RTIBOOST_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
   // we shouldn't really need this - but too many things choke
   // without it, this needs more investigation:
#  define RTIBOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  define RTIBOOST_SP_NO_SP_CONVERTIBLE
#endif

// CodeGear C++ Builder 2010
#if (__CODEGEARC__ <= 0x621)
#  define RTIBOOST_NO_TYPENAME_WITH_CTOR    // Cannot use typename keyword when making temporaries of a dependant type
#  define RTIBOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  define RTIBOOST_NO_MEMBER_TEMPLATE_FRIENDS
#  define RTIBOOST_NO_NESTED_FRIENDSHIP     // TC1 gives nested classes access rights as any other member
#  define RTIBOOST_NO_USING_TEMPLATE
#  define RTIBOOST_NO_TWO_PHASE_NAME_LOOKUP
// Temporary hack, until specific MPL preprocessed headers are generated
#  define RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

// CodeGear has not yet completely implemented value-initialization, for
// example for array types, as I reported in 2010: Embarcadero Report 83751,
// "Value-initialization: arrays should have each element value-initialized",
// http://qc.embarcadero.com/wc/qcmain.aspx?d=83751
// Last checked version: Embarcadero C++ 6.21
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
// (Niels Dekker, LKEB, April 2010)
#  define RTIBOOST_NO_COMPLETE_VALUE_INITIALIZATION

#  if defined(NDEBUG) && defined(__cplusplus)
      // fix broken <cstring> so that Boost.test works:
#     include <cstring>
#     undef strcmp
#  endif
   // fix broken errno declaration:
#  include <errno.h>
#  ifndef errno
#     define errno errno
#  endif

#endif

// Reportedly, #pragma once is supported since C++ Builder 2010
#if (__CODEGEARC__ >= 0x620)
#  define RTIBOOST_HAS_PRAGMA_ONCE
#endif

//
// C++0x macros:
//
#if (__CODEGEARC__ <= 0x620)
#define RTIBOOST_NO_CXX11_STATIC_ASSERT
#else
#define RTIBOOST_HAS_STATIC_ASSERT
#endif
#define RTIBOOST_HAS_CHAR16_T
#define RTIBOOST_HAS_CHAR32_T
#define RTIBOOST_HAS_LONG_LONG
// #define RTIBOOST_HAS_ALIGNOF
#define RTIBOOST_HAS_DECLTYPE
#define RTIBOOST_HAS_EXPLICIT_CONVERSION_OPS
// #define RTIBOOST_HAS_RVALUE_REFS
#define RTIBOOST_HAS_SCOPED_ENUM
// #define RTIBOOST_HAS_STATIC_ASSERT
#define RTIBOOST_HAS_STD_TYPE_TRAITS

#define RTIBOOST_NO_CXX11_AUTO_DECLARATIONS
#define RTIBOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define RTIBOOST_NO_CXX11_CONSTEXPR
#define RTIBOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define RTIBOOST_NO_CXX11_DELETED_FUNCTIONS
#define RTIBOOST_NO_CXX11_EXTERN_TEMPLATE
#define RTIBOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define RTIBOOST_NO_CXX11_LAMBDAS
#define RTIBOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define RTIBOOST_NO_CXX11_NOEXCEPT
#define RTIBOOST_NO_CXX11_NULLPTR
#define RTIBOOST_NO_CXX11_RANGE_BASED_FOR
#define RTIBOOST_NO_CXX11_RAW_LITERALS
#define RTIBOOST_NO_CXX11_RVALUE_REFERENCES
#define RTIBOOST_NO_SFINAE_EXPR
#define RTIBOOST_NO_CXX11_TEMPLATE_ALIASES
#define RTIBOOST_NO_CXX11_UNICODE_LITERALS
#define RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES
#define RTIBOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define RTIBOOST_NO_CXX11_USER_DEFINED_LITERALS
#define RTIBOOST_NO_CXX11_ALIGNAS
#define RTIBOOST_NO_CXX11_TRAILING_RESULT_TYPES
#define RTIBOOST_NO_CXX11_INLINE_NAMESPACES
#define RTIBOOST_NO_CXX11_REF_QUALIFIERS
#define RTIBOOST_NO_CXX11_FINAL

// C++ 14:
#if !defined(__cpp_aggregate_nsdmi) || (__cpp_aggregate_nsdmi < 201304)
#  define RTIBOOST_NO_CXX14_AGGREGATE_NSDMI
#endif
#if !defined(__cpp_binary_literals) || (__cpp_binary_literals < 201304)
#  define RTIBOOST_NO_CXX14_BINARY_LITERALS
#endif
#if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#  define RTIBOOST_NO_CXX14_CONSTEXPR
#endif
#if !defined(__cpp_decltype_auto) || (__cpp_decltype_auto < 201304)
#  define RTIBOOST_NO_CXX14_DECLTYPE_AUTO
#endif
#if (__cplusplus < 201304) // There's no SD6 check for this....
#  define RTIBOOST_NO_CXX14_DIGIT_SEPARATORS
#endif
#if !defined(__cpp_generic_lambdas) || (__cpp_generic_lambdas < 201304)
#  define RTIBOOST_NO_CXX14_GENERIC_LAMBDAS
#endif
#if !defined(__cpp_init_captures) || (__cpp_init_captures < 201304)
#  define RTIBOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif
#if !defined(__cpp_return_type_deduction) || (__cpp_return_type_deduction < 201304)
#  define RTIBOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif
#if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#  define RTIBOOST_NO_CXX14_VARIABLE_TEMPLATES
#endif

//
// TR1 macros:
//
#define RTIBOOST_HAS_TR1_HASH
#define RTIBOOST_HAS_TR1_TYPE_TRAITS
#define RTIBOOST_HAS_TR1_UNORDERED_MAP
#define RTIBOOST_HAS_TR1_UNORDERED_SET

#define RTIBOOST_HAS_MACRO_USE_FACET

#define RTIBOOST_NO_CXX11_HDR_INITIALIZER_LIST

// On non-Win32 platforms let the platform config figure this out:
#ifdef _WIN32
#  define RTIBOOST_HAS_STDINT_H
#endif

//
// __int64:
//
#if !defined(__STRICT_ANSI__)
#  define RTIBOOST_HAS_MS_INT64
#endif
//
// check for exception handling support:
//
#if !defined(_CPPUNWIND) && !defined(RTIBOOST_CPPUNWIND) && !defined(__EXCEPTIONS) && !defined(RTIBOOST_NO_EXCEPTIONS)
#  define RTIBOOST_NO_EXCEPTIONS
#endif
//
// all versions have a <dirent.h>:
//
#if !defined(__STRICT_ANSI__)
#  define RTIBOOST_HAS_DIRENT_H
#endif
//
// all versions support __declspec:
//
#if defined(__STRICT_ANSI__)
// config/platform/win32.hpp will define RTIBOOST_SYMBOL_EXPORT, etc., unless already defined
#  define RTIBOOST_SYMBOL_EXPORT
#endif
//
// ABI fixing headers:
//
#ifndef RTIBOOST_ABI_PREFIX
#  define RTIBOOST_ABI_PREFIX "rtiboost/config/abi/borland_prefix.hpp"
#endif
#ifndef RTIBOOST_ABI_SUFFIX
#  define RTIBOOST_ABI_SUFFIX "rtiboost/config/abi/borland_suffix.hpp"
#endif
//
// Disable Win32 support in ANSI mode:
//
#  pragma defineonoption RTIBOOST_DISABLE_WIN32 -A
//
// MSVC compatibility mode does some nasty things:
// TODO: look up if this doesn't apply to the whole 12xx range
//
#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#  define RTIBOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#  define RTIBOOST_NO_VOID_RETURNS
#endif

#define RTIBOOST_COMPILER "CodeGear C++ version " RTIBOOST_STRINGIZE(__CODEGEARC__)

