#ifndef RTIBOOST_DETAIL_INTERLOCKED_HPP_INCLUDED
#define RTIBOOST_DETAIL_INTERLOCKED_HPP_INCLUDED

//
//  boost/detail/interlocked.hpp
//
//  Copyright 2005 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <rtiboost/config.hpp>

// MS compatible compilers support #pragma once
#ifdef RTIBOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined( RTIBOOST_USE_WINDOWS_H )

# include <windows.h>

# define RTIBOOST_INTERLOCKED_INCREMENT InterlockedIncrement
# define RTIBOOST_INTERLOCKED_DECREMENT InterlockedDecrement
# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE InterlockedCompareExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE InterlockedExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE_ADD InterlockedExchangeAdd
# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER InterlockedCompareExchangePointer
# define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER InterlockedExchangePointer

#elif defined( RTIBOOST_USE_INTRIN_H )

#include <intrin.h>

# define RTIBOOST_INTERLOCKED_INCREMENT _InterlockedIncrement
# define RTIBOOST_INTERLOCKED_DECREMENT _InterlockedDecrement
# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE _InterlockedExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

# if defined(_M_IA64) || defined(_M_AMD64) || defined(__x86_64__) || defined(__x86_64)

#  define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER _InterlockedCompareExchangePointer
#  define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER _InterlockedExchangePointer

# else

#  define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest,exchange,compare) \
    ((void*)RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE((long volatile*)(dest),(long)(exchange),(long)(compare)))
#  define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER(dest,exchange) \
    ((void*)RTIBOOST_INTERLOCKED_EXCHANGE((long volatile*)(dest),(long)(exchange)))

# endif

#elif defined(_WIN32_WCE)

#if _WIN32_WCE >= 0x600

extern "C" long __cdecl _InterlockedIncrement( long volatile * );
extern "C" long __cdecl _InterlockedDecrement( long volatile * );
extern "C" long __cdecl _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __cdecl _InterlockedExchange( long volatile *, long );
extern "C" long __cdecl _InterlockedExchangeAdd( long volatile *, long );

# define RTIBOOST_INTERLOCKED_INCREMENT _InterlockedIncrement
# define RTIBOOST_INTERLOCKED_DECREMENT _InterlockedDecrement
# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE _InterlockedExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

#else
// under Windows CE we still have old-style Interlocked* functions

extern "C" long __cdecl InterlockedIncrement( long* );
extern "C" long __cdecl InterlockedDecrement( long* );
extern "C" long __cdecl InterlockedCompareExchange( long*, long, long );
extern "C" long __cdecl InterlockedExchange( long*, long );
extern "C" long __cdecl InterlockedExchangeAdd( long*, long );

# define RTIBOOST_INTERLOCKED_INCREMENT InterlockedIncrement
# define RTIBOOST_INTERLOCKED_DECREMENT InterlockedDecrement
# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE InterlockedCompareExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE InterlockedExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE_ADD InterlockedExchangeAdd

#endif

# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest,exchange,compare) \
    ((void*)RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE((long*)(dest),(long)(exchange),(long)(compare)))
# define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER(dest,exchange) \
    ((void*)RTIBOOST_INTERLOCKED_EXCHANGE((long*)(dest),(long)(exchange)))

#elif defined( RTIBOOST_MSVC ) || defined( RTIBOOST_INTEL_WIN )

#if defined( RTIBOOST_MSVC ) && RTIBOOST_MSVC >= 1500

#include <intrin.h>

#elif defined( __CLRCALL_PURE_OR_CDECL )

extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedIncrement( long volatile * );
extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedDecrement( long volatile * );
extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedExchange( long volatile *, long );
extern "C" long __CLRCALL_PURE_OR_CDECL _InterlockedExchangeAdd( long volatile *, long );

#else

extern "C" long __cdecl _InterlockedIncrement( long volatile * );
extern "C" long __cdecl _InterlockedDecrement( long volatile * );
extern "C" long __cdecl _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __cdecl _InterlockedExchange( long volatile *, long );
extern "C" long __cdecl _InterlockedExchangeAdd( long volatile *, long );

#endif

# if defined(_M_IA64) || defined(_M_AMD64)

extern "C" void* __cdecl _InterlockedCompareExchangePointer( void* volatile *, void*, void* );
extern "C" void* __cdecl _InterlockedExchangePointer( void* volatile *, void* );

#  define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER _InterlockedCompareExchangePointer
#  define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER _InterlockedExchangePointer

# else

#  define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest,exchange,compare) \
    ((void*)RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE((long volatile*)(dest),(long)(exchange),(long)(compare)))
#  define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER(dest,exchange) \
    ((void*)RTIBOOST_INTERLOCKED_EXCHANGE((long volatile*)(dest),(long)(exchange)))

# endif

# define RTIBOOST_INTERLOCKED_INCREMENT _InterlockedIncrement
# define RTIBOOST_INTERLOCKED_DECREMENT _InterlockedDecrement
# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE _InterlockedExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

// Unlike __MINGW64__, __MINGW64_VERSION_MAJOR is defined by MinGW-w64 for both 32 and 64-bit targets.
#elif defined(__MINGW64_VERSION_MAJOR)

// MinGW-w64 provides intrin.h for both 32 and 64-bit targets.
#include <intrin.h>

# define RTIBOOST_INTERLOCKED_INCREMENT _InterlockedIncrement
# define RTIBOOST_INTERLOCKED_DECREMENT _InterlockedDecrement
# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE _InterlockedExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd
# if defined(__x86_64__) || defined(__x86_64)
#  define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER _InterlockedCompareExchangePointer
#  define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER _InterlockedExchangePointer
# else
#  define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest,exchange,compare) \
    ((void*)RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE((long volatile*)(dest),(long)(exchange),(long)(compare)))
#  define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER(dest,exchange) \
    ((void*)RTIBOOST_INTERLOCKED_EXCHANGE((long volatile*)(dest),(long)(exchange)))
# endif

#elif defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )

#define RTIBOOST_INTERLOCKED_IMPORT __declspec(dllimport)

namespace rtiboost
{

namespace detail
{

extern "C" RTIBOOST_INTERLOCKED_IMPORT long __stdcall InterlockedIncrement( long volatile * );
extern "C" RTIBOOST_INTERLOCKED_IMPORT long __stdcall InterlockedDecrement( long volatile * );
extern "C" RTIBOOST_INTERLOCKED_IMPORT long __stdcall InterlockedCompareExchange( long volatile *, long, long );
extern "C" RTIBOOST_INTERLOCKED_IMPORT long __stdcall InterlockedExchange( long volatile *, long );
extern "C" RTIBOOST_INTERLOCKED_IMPORT long __stdcall InterlockedExchangeAdd( long volatile *, long );

# if defined(_M_IA64) || defined(_M_AMD64)
extern "C" RTIBOOST_INTERLOCKED_IMPORT void* __stdcall InterlockedCompareExchangePointer( void* volatile *, void*, void* );
extern "C" RTIBOOST_INTERLOCKED_IMPORT void* __stdcall InterlockedExchangePointer( void* volatile *, void* );
# endif

} // namespace detail

} // namespace rtiboost

# define RTIBOOST_INTERLOCKED_INCREMENT ::rtiboost::detail::InterlockedIncrement
# define RTIBOOST_INTERLOCKED_DECREMENT ::rtiboost::detail::InterlockedDecrement
# define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE ::rtiboost::detail::InterlockedCompareExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE ::rtiboost::detail::InterlockedExchange
# define RTIBOOST_INTERLOCKED_EXCHANGE_ADD ::rtiboost::detail::InterlockedExchangeAdd

# if defined(_M_IA64) || defined(_M_AMD64)
#  define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER ::rtiboost::detail::InterlockedCompareExchangePointer
#  define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER ::rtiboost::detail::InterlockedExchangePointer
# else
#  define RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(dest,exchange,compare) \
    ((void*)RTIBOOST_INTERLOCKED_COMPARE_EXCHANGE((long volatile*)(dest),(long)(exchange),(long)(compare)))
#  define RTIBOOST_INTERLOCKED_EXCHANGE_POINTER(dest,exchange) \
    ((void*)RTIBOOST_INTERLOCKED_EXCHANGE((long volatile*)(dest),(long)(exchange)))
# endif

#else

# error "Interlocked intrinsics not available"

#endif

#endif // #ifndef RTIBOOST_DETAIL_INTERLOCKED_HPP_INCLUDED
