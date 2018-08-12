//  (C) Copyright Noel Belcourt 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  PGI C++ compiler setup:

#define RTIBOOST_COMPILER_VERSION __PGIC__##__PGIC_MINOR__
#define RTIBOOST_COMPILER "PGI compiler version " RTIBOOST_STRINGIZE(RTIBOOST_COMPILER_VERSION)

//
// Threading support:
// Turn this on unconditionally here, it will get turned off again later
// if no threading API is detected.
//

#if __PGIC__ >= 11

// options requested by configure --enable-test
#define RTIBOOST_HAS_PTHREADS
#define RTIBOOST_HAS_THREADS
#define RTIBOOST_HAS_PTHREAD_YIELD
#define RTIBOOST_HAS_NRVO
#define RTIBOOST_HAS_LONG_LONG

// options --enable-test wants undefined
#undef RTIBOOST_NO_STDC_NAMESPACE
#undef RTIBOOST_NO_EXCEPTION_STD_NAMESPACE
#undef RTIBOOST_DEDUCED_TYPENAME

#define RTIBOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#define RTIBOOST_NO_TWO_PHASE_NAME_LOOKUP
#define RTIBOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define RTIBOOST_NO_CXX11_AUTO_DECLARATIONS

#elif __PGIC__ >= 10

// options requested by configure --enable-test
#define RTIBOOST_HAS_THREADS
#define RTIBOOST_HAS_NRVO
#define RTIBOOST_HAS_LONG_LONG
#if defined(linux) || defined(__linux) || defined(__linux__)
#  define RTIBOOST_HAS_STDINT_H
#endif

// options --enable-test wants undefined
#undef RTIBOOST_NO_STDC_NAMESPACE
#undef RTIBOOST_NO_EXCEPTION_STD_NAMESPACE
#undef RTIBOOST_DEDUCED_TYPENAME

#elif __PGIC__ >= 7

#define RTIBOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#define RTIBOOST_NO_TWO_PHASE_NAME_LOOKUP
#define RTIBOOST_NO_SWPRINTF
#define RTIBOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#define RTIBOOST_NO_CXX11_AUTO_DECLARATIONS

#else

#  error "Pgi compiler not configured - please reconfigure"

#endif
//
// C++0x features
//
//   See boost\config\suffix.hpp for RTIBOOST_NO_LONG_LONG
//
#define RTIBOOST_NO_CXX11_CHAR16_T
#define RTIBOOST_NO_CXX11_CHAR32_T
#define RTIBOOST_NO_CXX11_CONSTEXPR
#define RTIBOOST_NO_CXX11_DECLTYPE
#define RTIBOOST_NO_CXX11_DECLTYPE_N3276
#define RTIBOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#define RTIBOOST_NO_CXX11_DELETED_FUNCTIONS
#define RTIBOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define RTIBOOST_NO_CXX11_EXTERN_TEMPLATE
#define RTIBOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define RTIBOOST_NO_CXX11_LAMBDAS
#define RTIBOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define RTIBOOST_NO_CXX11_NOEXCEPT
#define RTIBOOST_NO_CXX11_NULLPTR
#define RTIBOOST_NO_CXX11_NUMERIC_LIMITS
#define RTIBOOST_NO_CXX11_RANGE_BASED_FOR
#define RTIBOOST_NO_CXX11_RAW_LITERALS
#define RTIBOOST_NO_CXX11_RVALUE_REFERENCES
#define RTIBOOST_NO_CXX11_SCOPED_ENUMS
#define RTIBOOST_NO_SFINAE_EXPR
#define RTIBOOST_NO_CXX11_STATIC_ASSERT
#define RTIBOOST_NO_SWPRINTF
#define RTIBOOST_NO_CXX11_TEMPLATE_ALIASES
#define RTIBOOST_NO_CXX11_UNICODE_LITERALS
#define RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES
#define RTIBOOST_NO_CXX11_VARIADIC_MACROS
#define RTIBOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX

#define RTIBOOST_NO_CXX11_HDR_UNORDERED_SET
#define RTIBOOST_NO_CXX11_HDR_UNORDERED_MAP
#define RTIBOOST_NO_CXX11_HDR_TYPEINDEX
#define RTIBOOST_NO_CXX11_HDR_TYPE_TRAITS
#define RTIBOOST_NO_CXX11_HDR_TUPLE
#define RTIBOOST_NO_CXX11_HDR_THREAD
#define RTIBOOST_NO_CXX11_HDR_SYSTEM_ERROR
#define RTIBOOST_NO_CXX11_HDR_REGEX
#define RTIBOOST_NO_CXX11_HDR_RATIO
#define RTIBOOST_NO_CXX11_HDR_RANDOM
#define RTIBOOST_NO_CXX11_HDR_MUTEX
#define RTIBOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define RTIBOOST_NO_CXX11_HDR_FUTURE
#define RTIBOOST_NO_CXX11_HDR_FORWARD_LIST
#define RTIBOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#define RTIBOOST_NO_CXX11_HDR_CODECVT
#define RTIBOOST_NO_CXX11_HDR_CHRONO
#define RTIBOOST_NO_CXX11_HDR_ARRAY
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
// version check:
// probably nothing to do here?

