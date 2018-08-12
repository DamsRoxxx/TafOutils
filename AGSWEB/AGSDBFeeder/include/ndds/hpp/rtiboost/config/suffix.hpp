//  Boost config.hpp configuration header file  ------------------------------//
//  boostinspect:ndprecated_macros -- tell the inspect tool to ignore this file

//  Copyright (c) 2001-2003 John Maddock
//  Copyright (c) 2001 Darin Adler
//  Copyright (c) 2001 Peter Dimov
//  Copyright (c) 2002 Bill Kempf
//  Copyright (c) 2002 Jens Maurer
//  Copyright (c) 2002-2003 David Abrahams
//  Copyright (c) 2003 Gennaro Prota
//  Copyright (c) 2003 Eric Friedman
//  Copyright (c) 2010 Eric Jourdanneau, Joel Falcou
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for most recent version.

//  Boost config.hpp policy and rationale documentation has been moved to
//  http://www.boost.org/libs/config/
//
//  This file is intended to be stable, and relatively unchanging.
//  It should contain boilerplate code only - no compiler specific
//  code unless it is unavoidable - no changes unless unavoidable.

#ifndef RTIBOOST_CONFIG_SUFFIX_HPP
#define RTIBOOST_CONFIG_SUFFIX_HPP

#if defined(__GNUC__) && (__GNUC__ >= 4)
//
// Some GCC-4.x versions issue warnings even when __extension__ is used,
// so use this as a workaround:
//
#pragma GCC system_header
#endif

//
// ensure that visibility macros are always defined, thus symplifying use
//
#ifndef RTIBOOST_SYMBOL_EXPORT
# define RTIBOOST_SYMBOL_EXPORT
#endif
#ifndef RTIBOOST_SYMBOL_IMPORT
# define RTIBOOST_SYMBOL_IMPORT
#endif
#ifndef RTIBOOST_SYMBOL_VISIBLE
# define RTIBOOST_SYMBOL_VISIBLE
#endif

//
// look for long long by looking for the appropriate macros in <limits.h>.
// Note that we use limits.h rather than climits for maximal portability,
// remember that since these just declare a bunch of macros, there should be
// no namespace issues from this.
//
#if !defined(RTIBOOST_HAS_LONG_LONG) && !defined(RTIBOOST_NO_LONG_LONG)                                              \
   && !defined(RTIBOOST_MSVC) && !defined(__BORLANDC__)
# include <limits.h>
# if (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
#   define RTIBOOST_HAS_LONG_LONG
# else
#   define RTIBOOST_NO_LONG_LONG
# endif
#endif

// GCC 3.x will clean up all of those nasty macro definitions that
// RTIBOOST_NO_CTYPE_FUNCTIONS is intended to help work around, so undefine
// it under GCC 3.x.
#if defined(__GNUC__) && (__GNUC__ >= 3) && defined(RTIBOOST_NO_CTYPE_FUNCTIONS)
#  undef RTIBOOST_NO_CTYPE_FUNCTIONS
#endif

//
// Assume any extensions are in namespace std:: unless stated otherwise:
//
#  ifndef RTIBOOST_STD_EXTENSION_NAMESPACE
#    define RTIBOOST_STD_EXTENSION_NAMESPACE std
#  endif

//
// If cv-qualified specializations are not allowed, then neither are cv-void ones:
//
#  if defined(RTIBOOST_NO_CV_SPECIALIZATIONS) \
      && !defined(RTIBOOST_NO_CV_VOID_SPECIALIZATIONS)
#     define RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
#  endif

//
// If there is no numeric_limits template, then it can't have any compile time
// constants either!
//
#  if defined(RTIBOOST_NO_LIMITS) \
      && !defined(RTIBOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS)
#     define RTIBOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#     define RTIBOOST_NO_MS_INT64_NUMERIC_LIMITS
#     define RTIBOOST_NO_LONG_LONG_NUMERIC_LIMITS
#  endif

//
// if there is no long long then there is no specialisation
// for numeric_limits<long long> either:
//
#if !defined(RTIBOOST_HAS_LONG_LONG) && !defined(RTIBOOST_NO_LONG_LONG_NUMERIC_LIMITS)
#  define RTIBOOST_NO_LONG_LONG_NUMERIC_LIMITS
#endif

//
// if there is no __int64 then there is no specialisation
// for numeric_limits<__int64> either:
//
#if !defined(RTIBOOST_HAS_MS_INT64) && !defined(RTIBOOST_NO_MS_INT64_NUMERIC_LIMITS)
#  define RTIBOOST_NO_MS_INT64_NUMERIC_LIMITS
#endif

//
// if member templates are supported then so is the
// VC6 subset of member templates:
//
#  if !defined(RTIBOOST_NO_MEMBER_TEMPLATES) \
       && !defined(RTIBOOST_MSVC6_MEMBER_TEMPLATES)
#     define RTIBOOST_MSVC6_MEMBER_TEMPLATES
#  endif

//
// Without partial specialization, can't test for partial specialisation bugs:
//
#  if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(RTIBOOST_BCB_PARTIAL_SPECIALIZATION_BUG)
#     define RTIBOOST_BCB_PARTIAL_SPECIALIZATION_BUG
#  endif

//
// Without partial specialization, we can't have array-type partial specialisations:
//
#  if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(RTIBOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
#     define RTIBOOST_NO_ARRAY_TYPE_SPECIALIZATIONS
#  endif

//
// Without partial specialization, std::iterator_traits can't work:
//
#  if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(RTIBOOST_NO_STD_ITERATOR_TRAITS)
#     define RTIBOOST_NO_STD_ITERATOR_TRAITS
#  endif

//
// Without partial specialization, partial
// specialization with default args won't work either:
//
#  if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
      && !defined(RTIBOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
#     define RTIBOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS
#  endif

//
// Without member template support, we can't have template constructors
// in the standard library either:
//
#  if defined(RTIBOOST_NO_MEMBER_TEMPLATES) \
      && !defined(RTIBOOST_MSVC6_MEMBER_TEMPLATES) \
      && !defined(RTIBOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)
#     define RTIBOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  endif

//
// Without member template support, we can't have a conforming
// std::allocator template either:
//
#  if defined(RTIBOOST_NO_MEMBER_TEMPLATES) \
      && !defined(RTIBOOST_MSVC6_MEMBER_TEMPLATES) \
      && !defined(RTIBOOST_NO_STD_ALLOCATOR)
#     define RTIBOOST_NO_STD_ALLOCATOR
#  endif

//
// without ADL support then using declarations will break ADL as well:
//
#if defined(RTIBOOST_NO_ARGUMENT_DEPENDENT_LOOKUP) && !defined(RTIBOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
#  define RTIBOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#endif

//
// Without typeid support we have no dynamic RTTI either:
//
#if defined(RTIBOOST_NO_TYPEID) && !defined(RTIBOOST_NO_RTTI)
#  define RTIBOOST_NO_RTTI
#endif

//
// If we have a standard allocator, then we have a partial one as well:
//
#if !defined(RTIBOOST_NO_STD_ALLOCATOR)
#  define RTIBOOST_HAS_PARTIAL_STD_ALLOCATOR
#endif

//
// We can't have a working std::use_facet if there is no std::locale:
//
#  if defined(RTIBOOST_NO_STD_LOCALE) && !defined(RTIBOOST_NO_STD_USE_FACET)
#     define RTIBOOST_NO_STD_USE_FACET
#  endif

//
// We can't have a std::messages facet if there is no std::locale:
//
#  if defined(RTIBOOST_NO_STD_LOCALE) && !defined(RTIBOOST_NO_STD_MESSAGES)
#     define RTIBOOST_NO_STD_MESSAGES
#  endif

//
// We can't have a working std::wstreambuf if there is no std::locale:
//
#  if defined(RTIBOOST_NO_STD_LOCALE) && !defined(RTIBOOST_NO_STD_WSTREAMBUF)
#     define RTIBOOST_NO_STD_WSTREAMBUF
#  endif

//
// We can't have a <cwctype> if there is no <cwchar>:
//
#  if defined(RTIBOOST_NO_CWCHAR) && !defined(RTIBOOST_NO_CWCTYPE)
#     define RTIBOOST_NO_CWCTYPE
#  endif

//
// We can't have a swprintf if there is no <cwchar>:
//
#  if defined(RTIBOOST_NO_CWCHAR) && !defined(RTIBOOST_NO_SWPRINTF)
#     define RTIBOOST_NO_SWPRINTF
#  endif

//
// If Win32 support is turned off, then we must turn off
// threading support also, unless there is some other
// thread API enabled:
//
#if defined(RTIBOOST_DISABLE_WIN32) && defined(_WIN32) \
   && !defined(RTIBOOST_DISABLE_THREADS) && !defined(RTIBOOST_HAS_PTHREADS)
#  define RTIBOOST_DISABLE_THREADS
#endif

//
// Turn on threading support if the compiler thinks that it's in
// multithreaded mode.  We put this here because there are only a
// limited number of macros that identify this (if there's any missing
// from here then add to the appropriate compiler section):
//
#if (defined(__MT__) || defined(_MT) || defined(_REENTRANT) \
    || defined(_PTHREADS) || defined(__APPLE__) || defined(__DragonFly__)) \
    && !defined(RTIBOOST_HAS_THREADS)
#  define RTIBOOST_HAS_THREADS
#endif

//
// Turn threading support off if RTIBOOST_DISABLE_THREADS is defined:
//
#if defined(RTIBOOST_DISABLE_THREADS) && defined(RTIBOOST_HAS_THREADS)
#  undef RTIBOOST_HAS_THREADS
#endif

//
// Turn threading support off if we don't recognise the threading API:
//
#if defined(RTIBOOST_HAS_THREADS) && !defined(RTIBOOST_HAS_PTHREADS)\
      && !defined(RTIBOOST_HAS_WINTHREADS) && !defined(RTIBOOST_HAS_BETHREADS)\
      && !defined(RTIBOOST_HAS_MPTASKS)
#  undef RTIBOOST_HAS_THREADS
#endif

//
// Turn threading detail macros off if we don't (want to) use threading
//
#ifndef RTIBOOST_HAS_THREADS
#  undef RTIBOOST_HAS_PTHREADS
#  undef RTIBOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  undef RTIBOOST_HAS_PTHREAD_YIELD
#  undef RTIBOOST_HAS_PTHREAD_DELAY_NP
#  undef RTIBOOST_HAS_WINTHREADS
#  undef RTIBOOST_HAS_BETHREADS
#  undef RTIBOOST_HAS_MPTASKS
#endif

//
// If the compiler claims to be C99 conformant, then it had better
// have a <stdint.h>:
//
#  if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#     define RTIBOOST_HAS_STDINT_H
#     ifndef RTIBOOST_HAS_LOG1P
#        define RTIBOOST_HAS_LOG1P
#     endif
#     ifndef RTIBOOST_HAS_EXPM1
#        define RTIBOOST_HAS_EXPM1
#     endif
#  endif

//
// Define RTIBOOST_NO_SLIST and RTIBOOST_NO_HASH if required.
// Note that this is for backwards compatibility only.
//
#  if !defined(RTIBOOST_HAS_SLIST) && !defined(RTIBOOST_NO_SLIST)
#     define RTIBOOST_NO_SLIST
#  endif

#  if !defined(RTIBOOST_HAS_HASH) && !defined(RTIBOOST_NO_HASH)
#     define RTIBOOST_NO_HASH
#  endif

//
// Set RTIBOOST_SLIST_HEADER if not set already:
//
#if defined(RTIBOOST_HAS_SLIST) && !defined(RTIBOOST_SLIST_HEADER)
#  define RTIBOOST_SLIST_HEADER <slist>
#endif

//
// Set RTIBOOST_HASH_SET_HEADER if not set already:
//
#if defined(RTIBOOST_HAS_HASH) && !defined(RTIBOOST_HASH_SET_HEADER)
#  define RTIBOOST_HASH_SET_HEADER <hash_set>
#endif

//
// Set RTIBOOST_HASH_MAP_HEADER if not set already:
//
#if defined(RTIBOOST_HAS_HASH) && !defined(RTIBOOST_HASH_MAP_HEADER)
#  define RTIBOOST_HASH_MAP_HEADER <hash_map>
#endif

//  RTIBOOST_HAS_ABI_HEADERS
//  This macro gets set if we have headers that fix the ABI,
//  and prevent ODR violations when linking to external libraries:
#if defined(RTIBOOST_ABI_PREFIX) && defined(RTIBOOST_ABI_SUFFIX) && !defined(RTIBOOST_HAS_ABI_HEADERS)
#  define RTIBOOST_HAS_ABI_HEADERS
#endif

#if defined(RTIBOOST_HAS_ABI_HEADERS) && defined(RTIBOOST_DISABLE_ABI_HEADERS)
#  undef RTIBOOST_HAS_ABI_HEADERS
#endif

//  RTIBOOST_NO_STDC_NAMESPACE workaround  --------------------------------------//
//  Because std::size_t usage is so common, even in boost headers which do not
//  otherwise use the C library, the <cstddef> workaround is included here so
//  that ugly workaround code need not appear in many other boost headers.
//  NOTE WELL: This is a workaround for non-conforming compilers; <cstddef>
//  must still be #included in the usual places so that <cstddef> inclusion
//  works as expected with standard conforming compilers.  The resulting
//  double inclusion of <cstddef> is harmless.

# if defined(RTIBOOST_NO_STDC_NAMESPACE) && defined(__cplusplus)
#   include <cstddef>
    namespace std { using ::ptrdiff_t; using ::size_t; }
# endif

//  Workaround for the unfortunate min/max macros defined by some platform headers

#define RTIBOOST_PREVENT_MACRO_SUBSTITUTION

#ifndef RTIBOOST_USING_STD_MIN
#  define RTIBOOST_USING_STD_MIN() using std::min
#endif

#ifndef RTIBOOST_USING_STD_MAX
#  define RTIBOOST_USING_STD_MAX() using std::max
#endif

//  RTIBOOST_NO_STD_MIN_MAX workaround  -----------------------------------------//

#  if defined(RTIBOOST_NO_STD_MIN_MAX) && defined(__cplusplus)

namespace std {
  template <class _Tp>
  inline const _Tp& min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (const _Tp& __a, const _Tp& __b) {
    return __b < __a ? __b : __a;
  }
  template <class _Tp>
  inline const _Tp& max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (const _Tp& __a, const _Tp& __b) {
    return  __a < __b ? __b : __a;
  }
}

#  endif

// RTIBOOST_STATIC_CONSTANT workaround --------------------------------------- //
// On compilers which don't allow in-class initialization of static integral
// constant members, we must use enums as a workaround if we want the constants
// to be available at compile-time. This macro gives us a convenient way to
// declare such constants.

#  ifdef RTIBOOST_NO_INCLASS_MEMBER_INITIALIZATION
#       define RTIBOOST_STATIC_CONSTANT(type, assignment) enum { assignment }
#  else
#     define RTIBOOST_STATIC_CONSTANT(type, assignment) static const type assignment
#  endif

// RTIBOOST_USE_FACET / HAS_FACET workaround ----------------------------------//
// When the standard library does not have a conforming std::use_facet there
// are various workarounds available, but they differ from library to library.
// The same problem occurs with has_facet.
// These macros provide a consistent way to access a locale's facets.
// Usage:
//    replace
//       std::use_facet<Type>(loc);
//    with
//       RTIBOOST_USE_FACET(Type, loc);
//    Note do not add a std:: prefix to the front of RTIBOOST_USE_FACET!
//  Use for RTIBOOST_HAS_FACET is analogous.

#if defined(RTIBOOST_NO_STD_USE_FACET)
#  ifdef RTIBOOST_HAS_TWO_ARG_USE_FACET
#     define RTIBOOST_USE_FACET(Type, loc) std::use_facet(loc, static_cast<Type*>(0))
#     define RTIBOOST_HAS_FACET(Type, loc) std::has_facet(loc, static_cast<Type*>(0))
#  elif defined(RTIBOOST_HAS_MACRO_USE_FACET)
#     define RTIBOOST_USE_FACET(Type, loc) std::_USE(loc, Type)
#     define RTIBOOST_HAS_FACET(Type, loc) std::_HAS(loc, Type)
#  elif defined(RTIBOOST_HAS_STLP_USE_FACET)
#     define RTIBOOST_USE_FACET(Type, loc) (*std::_Use_facet<Type >(loc))
#     define RTIBOOST_HAS_FACET(Type, loc) std::has_facet< Type >(loc)
#  endif
#else
#  define RTIBOOST_USE_FACET(Type, loc) std::use_facet< Type >(loc)
#  define RTIBOOST_HAS_FACET(Type, loc) std::has_facet< Type >(loc)
#endif

// RTIBOOST_NESTED_TEMPLATE workaround ------------------------------------------//
// Member templates are supported by some compilers even though they can't use
// the A::template member<U> syntax, as a workaround replace:
//
// typedef typename A::template rebind<U> binder;
//
// with:
//
// typedef typename A::RTIBOOST_NESTED_TEMPLATE rebind<U> binder;

#ifndef RTIBOOST_NO_MEMBER_TEMPLATE_KEYWORD
#  define RTIBOOST_NESTED_TEMPLATE template
#else
#  define RTIBOOST_NESTED_TEMPLATE
#endif

// RTIBOOST_UNREACHABLE_RETURN(x) workaround -------------------------------------//
// Normally evaluates to nothing, unless RTIBOOST_NO_UNREACHABLE_RETURN_DETECTION
// is defined, in which case it evaluates to return x; Use when you have a return
// statement that can never be reached.

#ifndef RTIBOOST_UNREACHABLE_RETURN
#  ifdef RTIBOOST_NO_UNREACHABLE_RETURN_DETECTION
#     define RTIBOOST_UNREACHABLE_RETURN(x) return x;
#  else
#     define RTIBOOST_UNREACHABLE_RETURN(x)
#  endif
#endif

// RTIBOOST_DEDUCED_TYPENAME workaround ------------------------------------------//
//
// Some compilers don't support the use of `typename' for dependent
// types in deduced contexts, e.g.
//
//     template <class T> void f(T, typename T::type);
//                                  ^^^^^^^^
// Replace these declarations with:
//
//     template <class T> void f(T, RTIBOOST_DEDUCED_TYPENAME T::type);

#ifndef RTIBOOST_NO_DEDUCED_TYPENAME
#  define RTIBOOST_DEDUCED_TYPENAME typename
#else
#  define RTIBOOST_DEDUCED_TYPENAME
#endif

#ifndef RTIBOOST_NO_TYPENAME_WITH_CTOR
#  define RTIBOOST_CTOR_TYPENAME typename
#else
#  define RTIBOOST_CTOR_TYPENAME
#endif

// long long workaround ------------------------------------------//
// On gcc (and maybe other compilers?) long long is alway supported
// but it's use may generate either warnings (with -ansi), or errors
// (with -pedantic -ansi) unless it's use is prefixed by __extension__
//
#if defined(RTIBOOST_HAS_LONG_LONG) && defined(__cplusplus)
namespace rtiboost{
#  ifdef __GNUC__
   __extension__ typedef long long long_long_type;
   __extension__ typedef unsigned long long ulong_long_type;
#  else
   typedef long long long_long_type;
   typedef unsigned long long ulong_long_type;
#  endif
}
#endif
// same again for __int128:
#if defined(RTIBOOST_HAS_INT128) && defined(__cplusplus)
namespace rtiboost{
#  ifdef __GNUC__
   __extension__ typedef __int128 int128_type;
   __extension__ typedef unsigned __int128 uint128_type;
#  else
   typedef __int128 int128_type;
   typedef unsigned __int128 uint128_type;
#  endif
}
#endif
// same again for __float128:
#if defined(RTIBOOST_HAS_FLOAT128) && defined(__cplusplus)
namespace rtiboost {
#  ifdef __GNUC__
   __extension__ typedef __float128 float128_type;
#  else
   typedef __float128 float128_type;
#  endif
}
#endif

// RTIBOOST_[APPEND_]EXPLICIT_TEMPLATE_[NON_]TYPE macros --------------------------//

// These macros are obsolete. Port away and remove.

#  define RTIBOOST_EXPLICIT_TEMPLATE_TYPE(t)
#  define RTIBOOST_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define RTIBOOST_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define RTIBOOST_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)

#  define RTIBOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(t)
#  define RTIBOOST_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define RTIBOOST_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define RTIBOOST_APPEND_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)

// When RTIBOOST_NO_STD_TYPEINFO is defined, we can just import
// the global definition into std namespace:
#if defined(RTIBOOST_NO_STD_TYPEINFO) && defined(__cplusplus)
#include <typeinfo>
namespace std{ using ::type_info; }
#endif

// ---------------------------------------------------------------------------//

//
// Helper macro RTIBOOST_STRINGIZE:
// Converts the parameter X to a string after macro replacement
// on X has been performed.
//
#define RTIBOOST_STRINGIZE(X) RTIBOOST_DO_STRINGIZE(X)
#define RTIBOOST_DO_STRINGIZE(X) #X

//
// Helper macro RTIBOOST_JOIN:
// The following piece of macro magic joins the two
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expansion of macro arguments does not
// occur in RTIBOOST_DO_JOIN2 but does in RTIBOOST_DO_JOIN.
//
#define RTIBOOST_JOIN( X, Y ) RTIBOOST_DO_JOIN( X, Y )
#define RTIBOOST_DO_JOIN( X, Y ) RTIBOOST_DO_JOIN2(X,Y)
#define RTIBOOST_DO_JOIN2( X, Y ) X##Y

//
// Set some default values for compiler/library/platform names.
// These are for debugging config setup only:
//
#  ifndef RTIBOOST_COMPILER
#     define RTIBOOST_COMPILER "Unknown ISO C++ Compiler"
#  endif
#  ifndef RTIBOOST_STDLIB
#     define RTIBOOST_STDLIB "Unknown ISO standard library"
#  endif
#  ifndef RTIBOOST_PLATFORM
#     if defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) \
         || defined(_POSIX_SOURCE)
#        define RTIBOOST_PLATFORM "Generic Unix"
#     else
#        define RTIBOOST_PLATFORM "Unknown"
#     endif
#  endif

//
// Set some default values GPU support
//
#  ifndef RTIBOOST_GPU_ENABLED
#  define RTIBOOST_GPU_ENABLED
#  endif

// RTIBOOST_FORCEINLINE ---------------------------------------------//
// Macro to use in place of 'inline' to force a function to be inline
#if !defined(RTIBOOST_FORCEINLINE)
#  if defined(_MSC_VER)
#    define RTIBOOST_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    define RTIBOOST_FORCEINLINE inline __attribute__ ((__always_inline__))
#  else
#    define RTIBOOST_FORCEINLINE inline
#  endif
#endif

// RTIBOOST_NOINLINE ---------------------------------------------//
// Macro to use in place of 'inline' to prevent a function to be inlined
#if !defined(RTIBOOST_NOINLINE)
#  if defined(_MSC_VER)
#    define RTIBOOST_NOINLINE __declspec(noinline)
#  elif defined(__GNUC__) && __GNUC__ > 3
     // Clang also defines __GNUC__ (as 4)
#    if defined(__CUDACC__)
       // nvcc doesn't always parse __noinline__, 
       // see: https://svn.boost.org/trac/boost/ticket/9392
#      define RTIBOOST_NOINLINE __attribute__ ((noinline))
#    else
#      define RTIBOOST_NOINLINE __attribute__ ((__noinline__))
#    endif
#  else
#    define RTIBOOST_NOINLINE
#  endif
#endif

// RTIBOOST_NORETURN ---------------------------------------------//
// Macro to use before a function declaration/definition to designate
// the function as not returning normally (i.e. with a return statement
// or by leaving the function scope, if the function return type is void).
#if !defined(RTIBOOST_NORETURN)
#  if defined(_MSC_VER)
#    define RTIBOOST_NORETURN __declspec(noreturn)
#  elif defined(__GNUC__)
#    define RTIBOOST_NORETURN __attribute__ ((__noreturn__))
#  else
#    define RTIBOOST_NO_NORETURN
#    define RTIBOOST_NORETURN
#  endif
#endif

// Branch prediction hints
// These macros are intended to wrap conditional expressions that yield true or false
//
//  if (RTIBOOST_LIKELY(var == 10))
//  {
//     // the most probable code here
//  }
//
#if !defined(RTIBOOST_LIKELY)
#  define RTIBOOST_LIKELY(x) x
#endif
#if !defined(RTIBOOST_UNLIKELY)
#  define RTIBOOST_UNLIKELY(x) x
#endif

// Type and data alignment specification
//
#if !defined(RTIBOOST_NO_CXX11_ALIGNAS)
#  define RTIBOOST_ALIGNMENT(x) alignas(x)
#elif defined(_MSC_VER)
#  define RTIBOOST_ALIGNMENT(x) __declspec(align(x))
#elif defined(__GNUC__)
#  define RTIBOOST_ALIGNMENT(x) __attribute__ ((__aligned__(x)))
#else
#  define RTIBOOST_NO_ALIGNMENT
#  define RTIBOOST_ALIGNMENT(x)
#endif

// Lack of non-public defaulted functions is implied by the lack of any defaulted functions
#if !defined(RTIBOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS) && defined(RTIBOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
#  define RTIBOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#endif

// Defaulted and deleted function declaration helpers
// These macros are intended to be inside a class definition.
// RTIBOOST_DEFAULTED_FUNCTION accepts the function declaration and its
// body, which will be used if the compiler doesn't support defaulted functions.
// RTIBOOST_DELETED_FUNCTION only accepts the function declaration. It
// will expand to a private function declaration, if the compiler doesn't support
// deleted functions. Because of this it is recommended to use RTIBOOST_DELETED_FUNCTION
// in the end of the class definition.
//
//  class my_class
//  {
//  public:
//      // Default-constructible
//      RTIBOOST_DEFAULTED_FUNCTION(my_class(), {})
//      // Copying prohibited
//      RTIBOOST_DELETED_FUNCTION(my_class(my_class const&))
//      RTIBOOST_DELETED_FUNCTION(my_class& operator= (my_class const&))
//  };
//
#if !(defined(RTIBOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(RTIBOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS))
#   define RTIBOOST_DEFAULTED_FUNCTION(fun, body) fun = default;
#else
#   define RTIBOOST_DEFAULTED_FUNCTION(fun, body) fun body
#endif

#if !defined(RTIBOOST_NO_CXX11_DELETED_FUNCTIONS)
#   define RTIBOOST_DELETED_FUNCTION(fun) fun = delete;
#else
#   define RTIBOOST_DELETED_FUNCTION(fun) private: fun;
#endif

//
// Set RTIBOOST_NO_DECLTYPE_N3276 when RTIBOOST_NO_DECLTYPE is defined
//
#if defined(RTIBOOST_NO_CXX11_DECLTYPE) && !defined(RTIBOOST_NO_CXX11_DECLTYPE_N3276)
#define RTIBOOST_NO_CXX11_DECLTYPE_N3276 RTIBOOST_NO_CXX11_DECLTYPE
#endif

//  -------------------- Deprecated macros for 1.50 ---------------------------
//  These will go away in a future release

//  Use RTIBOOST_NO_CXX11_HDR_UNORDERED_SET or RTIBOOST_NO_CXX11_HDR_UNORDERED_MAP
//           instead of RTIBOOST_NO_STD_UNORDERED
#if defined(RTIBOOST_NO_CXX11_HDR_UNORDERED_MAP) || defined (RTIBOOST_NO_CXX11_HDR_UNORDERED_SET)
# ifndef RTIBOOST_NO_CXX11_STD_UNORDERED
#  define RTIBOOST_NO_CXX11_STD_UNORDERED
# endif
#endif

//  Use RTIBOOST_NO_CXX11_HDR_INITIALIZER_LIST instead of RTIBOOST_NO_INITIALIZER_LISTS
#if defined(RTIBOOST_NO_CXX11_HDR_INITIALIZER_LIST) && !defined(RTIBOOST_NO_INITIALIZER_LISTS)
#  define RTIBOOST_NO_INITIALIZER_LISTS
#endif

//  Use RTIBOOST_NO_CXX11_HDR_ARRAY instead of RTIBOOST_NO_0X_HDR_ARRAY
#if defined(RTIBOOST_NO_CXX11_HDR_ARRAY) && !defined(RTIBOOST_NO_0X_HDR_ARRAY)
#  define RTIBOOST_NO_0X_HDR_ARRAY
#endif
//  Use RTIBOOST_NO_CXX11_HDR_CHRONO instead of RTIBOOST_NO_0X_HDR_CHRONO
#if defined(RTIBOOST_NO_CXX11_HDR_CHRONO) && !defined(RTIBOOST_NO_0X_HDR_CHRONO)
#  define RTIBOOST_NO_0X_HDR_CHRONO
#endif
//  Use RTIBOOST_NO_CXX11_HDR_CODECVT instead of RTIBOOST_NO_0X_HDR_CODECVT
#if defined(RTIBOOST_NO_CXX11_HDR_CODECVT) && !defined(RTIBOOST_NO_0X_HDR_CODECVT)
#  define RTIBOOST_NO_0X_HDR_CODECVT
#endif
//  Use RTIBOOST_NO_CXX11_HDR_CONDITION_VARIABLE instead of RTIBOOST_NO_0X_HDR_CONDITION_VARIABLE
#if defined(RTIBOOST_NO_CXX11_HDR_CONDITION_VARIABLE) && !defined(RTIBOOST_NO_0X_HDR_CONDITION_VARIABLE)
#  define RTIBOOST_NO_0X_HDR_CONDITION_VARIABLE
#endif
//  Use RTIBOOST_NO_CXX11_HDR_FORWARD_LIST instead of RTIBOOST_NO_0X_HDR_FORWARD_LIST
#if defined(RTIBOOST_NO_CXX11_HDR_FORWARD_LIST) && !defined(RTIBOOST_NO_0X_HDR_FORWARD_LIST)
#  define RTIBOOST_NO_0X_HDR_FORWARD_LIST
#endif
//  Use RTIBOOST_NO_CXX11_HDR_FUTURE instead of RTIBOOST_NO_0X_HDR_FUTURE
#if defined(RTIBOOST_NO_CXX11_HDR_FUTURE) && !defined(RTIBOOST_NO_0X_HDR_FUTURE)
#  define RTIBOOST_NO_0X_HDR_FUTURE
#endif

//  Use RTIBOOST_NO_CXX11_HDR_INITIALIZER_LIST
//  instead of RTIBOOST_NO_0X_HDR_INITIALIZER_LIST or RTIBOOST_NO_INITIALIZER_LISTS
#ifdef RTIBOOST_NO_CXX11_HDR_INITIALIZER_LIST
# ifndef RTIBOOST_NO_0X_HDR_INITIALIZER_LIST
#  define RTIBOOST_NO_0X_HDR_INITIALIZER_LIST
# endif
# ifndef RTIBOOST_NO_INITIALIZER_LISTS
#  define RTIBOOST_NO_INITIALIZER_LISTS
# endif
#endif

//  Use RTIBOOST_NO_CXX11_HDR_MUTEX instead of RTIBOOST_NO_0X_HDR_MUTEX
#if defined(RTIBOOST_NO_CXX11_HDR_MUTEX) && !defined(RTIBOOST_NO_0X_HDR_MUTEX)
#  define RTIBOOST_NO_0X_HDR_MUTEX
#endif
//  Use RTIBOOST_NO_CXX11_HDR_RANDOM instead of RTIBOOST_NO_0X_HDR_RANDOM
#if defined(RTIBOOST_NO_CXX11_HDR_RANDOM) && !defined(RTIBOOST_NO_0X_HDR_RANDOM)
#  define RTIBOOST_NO_0X_HDR_RANDOM
#endif
//  Use RTIBOOST_NO_CXX11_HDR_RATIO instead of RTIBOOST_NO_0X_HDR_RATIO
#if defined(RTIBOOST_NO_CXX11_HDR_RATIO) && !defined(RTIBOOST_NO_0X_HDR_RATIO)
#  define RTIBOOST_NO_0X_HDR_RATIO
#endif
//  Use RTIBOOST_NO_CXX11_HDR_REGEX instead of RTIBOOST_NO_0X_HDR_REGEX
#if defined(RTIBOOST_NO_CXX11_HDR_REGEX) && !defined(RTIBOOST_NO_0X_HDR_REGEX)
#  define RTIBOOST_NO_0X_HDR_REGEX
#endif
//  Use RTIBOOST_NO_CXX11_HDR_SYSTEM_ERROR instead of RTIBOOST_NO_0X_HDR_SYSTEM_ERROR
#if defined(RTIBOOST_NO_CXX11_HDR_SYSTEM_ERROR) && !defined(RTIBOOST_NO_0X_HDR_SYSTEM_ERROR)
#  define RTIBOOST_NO_0X_HDR_SYSTEM_ERROR
#endif
//  Use RTIBOOST_NO_CXX11_HDR_THREAD instead of RTIBOOST_NO_0X_HDR_THREAD
#if defined(RTIBOOST_NO_CXX11_HDR_THREAD) && !defined(RTIBOOST_NO_0X_HDR_THREAD)
#  define RTIBOOST_NO_0X_HDR_THREAD
#endif
//  Use RTIBOOST_NO_CXX11_HDR_TUPLE instead of RTIBOOST_NO_0X_HDR_TUPLE
#if defined(RTIBOOST_NO_CXX11_HDR_TUPLE) && !defined(RTIBOOST_NO_0X_HDR_TUPLE)
#  define RTIBOOST_NO_0X_HDR_TUPLE
#endif
//  Use RTIBOOST_NO_CXX11_HDR_TYPE_TRAITS instead of RTIBOOST_NO_0X_HDR_TYPE_TRAITS
#if defined(RTIBOOST_NO_CXX11_HDR_TYPE_TRAITS) && !defined(RTIBOOST_NO_0X_HDR_TYPE_TRAITS)
#  define RTIBOOST_NO_0X_HDR_TYPE_TRAITS
#endif
//  Use RTIBOOST_NO_CXX11_HDR_TYPEINDEX instead of RTIBOOST_NO_0X_HDR_TYPEINDEX
#if defined(RTIBOOST_NO_CXX11_HDR_TYPEINDEX) && !defined(RTIBOOST_NO_0X_HDR_TYPEINDEX)
#  define RTIBOOST_NO_0X_HDR_TYPEINDEX
#endif
//  Use RTIBOOST_NO_CXX11_HDR_UNORDERED_MAP instead of RTIBOOST_NO_0X_HDR_UNORDERED_MAP
#if defined(RTIBOOST_NO_CXX11_HDR_UNORDERED_MAP) && !defined(RTIBOOST_NO_0X_HDR_UNORDERED_MAP)
#  define RTIBOOST_NO_0X_HDR_UNORDERED_MAP
#endif
//  Use RTIBOOST_NO_CXX11_HDR_UNORDERED_SET instead of RTIBOOST_NO_0X_HDR_UNORDERED_SET
#if defined(RTIBOOST_NO_CXX11_HDR_UNORDERED_SET) && !defined(RTIBOOST_NO_0X_HDR_UNORDERED_SET)
#  define RTIBOOST_NO_0X_HDR_UNORDERED_SET
#endif

//  ------------------ End of deprecated macros for 1.50 ---------------------------

//  -------------------- Deprecated macros for 1.51 ---------------------------
//  These will go away in a future release

//  Use     RTIBOOST_NO_CXX11_AUTO_DECLARATIONS instead of   RTIBOOST_NO_AUTO_DECLARATIONS
#if defined(RTIBOOST_NO_CXX11_AUTO_DECLARATIONS) && !defined(RTIBOOST_NO_AUTO_DECLARATIONS)
#  define RTIBOOST_NO_AUTO_DECLARATIONS
#endif
//  Use     RTIBOOST_NO_CXX11_AUTO_MULTIDECLARATIONS instead of   RTIBOOST_NO_AUTO_MULTIDECLARATIONS
#if defined(RTIBOOST_NO_CXX11_AUTO_MULTIDECLARATIONS) && !defined(RTIBOOST_NO_AUTO_MULTIDECLARATIONS)
#  define RTIBOOST_NO_AUTO_MULTIDECLARATIONS
#endif
//  Use     RTIBOOST_NO_CXX11_CHAR16_T instead of   RTIBOOST_NO_CHAR16_T
#if defined(RTIBOOST_NO_CXX11_CHAR16_T) && !defined(RTIBOOST_NO_CHAR16_T)
#  define RTIBOOST_NO_CHAR16_T
#endif
//  Use     RTIBOOST_NO_CXX11_CHAR32_T instead of   RTIBOOST_NO_CHAR32_T
#if defined(RTIBOOST_NO_CXX11_CHAR32_T) && !defined(RTIBOOST_NO_CHAR32_T)
#  define RTIBOOST_NO_CHAR32_T
#endif
//  Use     RTIBOOST_NO_CXX11_TEMPLATE_ALIASES instead of   RTIBOOST_NO_TEMPLATE_ALIASES
#if defined(RTIBOOST_NO_CXX11_TEMPLATE_ALIASES) && !defined(RTIBOOST_NO_TEMPLATE_ALIASES)
#  define RTIBOOST_NO_TEMPLATE_ALIASES
#endif
//  Use     RTIBOOST_NO_CXX11_CONSTEXPR instead of   RTIBOOST_NO_CONSTEXPR
#if defined(RTIBOOST_NO_CXX11_CONSTEXPR) && !defined(RTIBOOST_NO_CONSTEXPR)
#  define RTIBOOST_NO_CONSTEXPR
#endif
//  Use     RTIBOOST_NO_CXX11_DECLTYPE_N3276 instead of   RTIBOOST_NO_DECLTYPE_N3276
#if defined(RTIBOOST_NO_CXX11_DECLTYPE_N3276) && !defined(RTIBOOST_NO_DECLTYPE_N3276)
#  define RTIBOOST_NO_DECLTYPE_N3276
#endif
//  Use     RTIBOOST_NO_CXX11_DECLTYPE instead of   RTIBOOST_NO_DECLTYPE
#if defined(RTIBOOST_NO_CXX11_DECLTYPE) && !defined(RTIBOOST_NO_DECLTYPE)
#  define RTIBOOST_NO_DECLTYPE
#endif
//  Use     RTIBOOST_NO_CXX11_DEFAULTED_FUNCTIONS instead of   RTIBOOST_NO_DEFAULTED_FUNCTIONS
#if defined(RTIBOOST_NO_CXX11_DEFAULTED_FUNCTIONS) && !defined(RTIBOOST_NO_DEFAULTED_FUNCTIONS)
#  define RTIBOOST_NO_DEFAULTED_FUNCTIONS
#endif
//  Use     RTIBOOST_NO_CXX11_DELETED_FUNCTIONS instead of   RTIBOOST_NO_DELETED_FUNCTIONS
#if defined(RTIBOOST_NO_CXX11_DELETED_FUNCTIONS) && !defined(RTIBOOST_NO_DELETED_FUNCTIONS)
#  define RTIBOOST_NO_DELETED_FUNCTIONS
#endif
//  Use     RTIBOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS instead of   RTIBOOST_NO_EXPLICIT_CONVERSION_OPERATORS
#if defined(RTIBOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) && !defined(RTIBOOST_NO_EXPLICIT_CONVERSION_OPERATORS)
#  define RTIBOOST_NO_EXPLICIT_CONVERSION_OPERATORS
#endif
//  Use     RTIBOOST_NO_CXX11_EXTERN_TEMPLATE instead of   RTIBOOST_NO_EXTERN_TEMPLATE
#if defined(RTIBOOST_NO_CXX11_EXTERN_TEMPLATE) && !defined(RTIBOOST_NO_EXTERN_TEMPLATE)
#  define RTIBOOST_NO_EXTERN_TEMPLATE
#endif
//  Use     RTIBOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS instead of   RTIBOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#if defined(RTIBOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) && !defined(RTIBOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#  define RTIBOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif
//  Use     RTIBOOST_NO_CXX11_LAMBDAS instead of   RTIBOOST_NO_LAMBDAS
#if defined(RTIBOOST_NO_CXX11_LAMBDAS) && !defined(RTIBOOST_NO_LAMBDAS)
#  define RTIBOOST_NO_LAMBDAS
#endif
//  Use     RTIBOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS instead of   RTIBOOST_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS
#if defined(RTIBOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS) && !defined(RTIBOOST_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS)
#  define RTIBOOST_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif
//  Use     RTIBOOST_NO_CXX11_NOEXCEPT instead of   RTIBOOST_NO_NOEXCEPT
#if defined(RTIBOOST_NO_CXX11_NOEXCEPT) && !defined(RTIBOOST_NO_NOEXCEPT)
#  define RTIBOOST_NO_NOEXCEPT
#endif
//  Use     RTIBOOST_NO_CXX11_NULLPTR instead of   RTIBOOST_NO_NULLPTR
#if defined(RTIBOOST_NO_CXX11_NULLPTR) && !defined(RTIBOOST_NO_NULLPTR)
#  define RTIBOOST_NO_NULLPTR
#endif
//  Use     RTIBOOST_NO_CXX11_RAW_LITERALS instead of   RTIBOOST_NO_RAW_LITERALS
#if defined(RTIBOOST_NO_CXX11_RAW_LITERALS) && !defined(RTIBOOST_NO_RAW_LITERALS)
#  define RTIBOOST_NO_RAW_LITERALS
#endif
//  Use     RTIBOOST_NO_CXX11_RVALUE_REFERENCES instead of   RTIBOOST_NO_RVALUE_REFERENCES
#if defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(RTIBOOST_NO_RVALUE_REFERENCES)
#  define RTIBOOST_NO_RVALUE_REFERENCES
#endif
//  Use     RTIBOOST_NO_CXX11_SCOPED_ENUMS instead of   RTIBOOST_NO_SCOPED_ENUMS
#if defined(RTIBOOST_NO_CXX11_SCOPED_ENUMS) && !defined(RTIBOOST_NO_SCOPED_ENUMS)
#  define RTIBOOST_NO_SCOPED_ENUMS
#endif
//  Use     RTIBOOST_NO_CXX11_STATIC_ASSERT instead of   RTIBOOST_NO_STATIC_ASSERT
#if defined(RTIBOOST_NO_CXX11_STATIC_ASSERT) && !defined(RTIBOOST_NO_STATIC_ASSERT)
#  define RTIBOOST_NO_STATIC_ASSERT
#endif
//  Use     RTIBOOST_NO_CXX11_STD_UNORDERED instead of   RTIBOOST_NO_STD_UNORDERED
#if defined(RTIBOOST_NO_CXX11_STD_UNORDERED) && !defined(RTIBOOST_NO_STD_UNORDERED)
#  define RTIBOOST_NO_STD_UNORDERED
#endif
//  Use     RTIBOOST_NO_CXX11_UNICODE_LITERALS instead of   RTIBOOST_NO_UNICODE_LITERALS
#if defined(RTIBOOST_NO_CXX11_UNICODE_LITERALS) && !defined(RTIBOOST_NO_UNICODE_LITERALS)
#  define RTIBOOST_NO_UNICODE_LITERALS
#endif
//  Use     RTIBOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX instead of   RTIBOOST_NO_UNIFIED_INITIALIZATION_SYNTAX
#if defined(RTIBOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && !defined(RTIBOOST_NO_UNIFIED_INITIALIZATION_SYNTAX)
#  define RTIBOOST_NO_UNIFIED_INITIALIZATION_SYNTAX
#endif
//  Use     RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES instead of   RTIBOOST_NO_VARIADIC_TEMPLATES
#if defined(RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(RTIBOOST_NO_VARIADIC_TEMPLATES)
#  define RTIBOOST_NO_VARIADIC_TEMPLATES
#endif
//  Use     RTIBOOST_NO_CXX11_VARIADIC_MACROS instead of   RTIBOOST_NO_VARIADIC_MACROS
#if defined(RTIBOOST_NO_CXX11_VARIADIC_MACROS) && !defined(RTIBOOST_NO_VARIADIC_MACROS)
#  define RTIBOOST_NO_VARIADIC_MACROS
#endif
//  Use     RTIBOOST_NO_CXX11_NUMERIC_LIMITS instead of   RTIBOOST_NO_NUMERIC_LIMITS_LOWEST
#if defined(RTIBOOST_NO_CXX11_NUMERIC_LIMITS) && !defined(RTIBOOST_NO_NUMERIC_LIMITS_LOWEST)
#  define RTIBOOST_NO_NUMERIC_LIMITS_LOWEST
#endif
//  ------------------ End of deprecated macros for 1.51 ---------------------------



//
// Helper macros RTIBOOST_NOEXCEPT, RTIBOOST_NOEXCEPT_IF, RTIBOOST_NOEXCEPT_EXPR
// These aid the transition to C++11 while still supporting C++03 compilers
//
#ifdef RTIBOOST_NO_CXX11_NOEXCEPT
#  define RTIBOOST_NOEXCEPT
#  define RTIBOOST_NOEXCEPT_OR_NOTHROW throw()
#  define RTIBOOST_NOEXCEPT_IF(Predicate)
#  define RTIBOOST_NOEXCEPT_EXPR(Expression) false
#else
#  define RTIBOOST_NOEXCEPT noexcept
#  define RTIBOOST_NOEXCEPT_OR_NOTHROW noexcept
#  define RTIBOOST_NOEXCEPT_IF(Predicate) noexcept((Predicate))
#  define RTIBOOST_NOEXCEPT_EXPR(Expression) noexcept((Expression))
#endif
//
// Helper macro RTIBOOST_FALLTHROUGH
// Fallback definition of RTIBOOST_FALLTHROUGH macro used to mark intended
// fall-through between case labels in a switch statement. We use a definition
// that requires a semicolon after it to avoid at least one type of misuse even
// on unsupported compilers.
//
#ifndef RTIBOOST_FALLTHROUGH
#  define RTIBOOST_FALLTHROUGH ((void)0)
#endif

//
// constexpr workarounds
//
#if defined(RTIBOOST_NO_CXX11_CONSTEXPR)
#define RTIBOOST_CONSTEXPR
#define RTIBOOST_CONSTEXPR_OR_CONST const
#else
#define RTIBOOST_CONSTEXPR constexpr
#define RTIBOOST_CONSTEXPR_OR_CONST constexpr
#endif
#if defined(RTIBOOST_NO_CXX14_CONSTEXPR)
#define RTIBOOST_CXX14_CONSTEXPR
#else
#define RTIBOOST_CXX14_CONSTEXPR constexpr
#endif

//
// Unused variable/typedef workarounds:
//
#ifndef RTIBOOST_ATTRIBUTE_UNUSED
#  define RTIBOOST_ATTRIBUTE_UNUSED
#endif

#define RTIBOOST_STATIC_CONSTEXPR  static RTIBOOST_CONSTEXPR_OR_CONST

//
// Set RTIBOOST_HAS_STATIC_ASSERT when RTIBOOST_NO_CXX11_STATIC_ASSERT is not defined
//
#if !defined(RTIBOOST_NO_CXX11_STATIC_ASSERT) && !defined(RTIBOOST_HAS_STATIC_ASSERT)
#  define RTIBOOST_HAS_STATIC_ASSERT
#endif

//
// Set RTIBOOST_HAS_RVALUE_REFS when RTIBOOST_NO_CXX11_RVALUE_REFERENCES is not defined
//
#if !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(RTIBOOST_HAS_RVALUE_REFS)
#define RTIBOOST_HAS_RVALUE_REFS
#endif

//
// Set RTIBOOST_HAS_VARIADIC_TMPL when RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES is not defined
//
#if !defined(RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(RTIBOOST_HAS_VARIADIC_TMPL)
#define RTIBOOST_HAS_VARIADIC_TMPL
#endif
//
// Set RTIBOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS when
// RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES is set:
//
#if defined(RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(RTIBOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS)
#  define RTIBOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#endif

//
// Finish off with checks for macros that are depricated / no longer supported,
// if any of these are set then it's very likely that much of Boost will no
// longer work.  So stop with a #error for now, but give the user a chance
// to continue at their own risk if they really want to:
//
#if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(RTIBOOST_CONFIG_ALLOW_DEPRECATED)
#  error "You are using a compiler which lacks features which are now a minimum requirement in order to use Boost, define RTIBOOST_CONFIG_ALLOW_DEPRECATED if you want to continue at your own risk!!!"
#endif

#endif
