#ifndef RTIBOOST_SMART_PTR_DETAIL_SP_INTERLOCKED_HPP_INCLUDED
#define RTIBOOST_SMART_PTR_DETAIL_SP_INTERLOCKED_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/detail/sp_interlocked.hpp
//
//  Copyright 2005, 2014 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <rtiboost/config.hpp>

// RTIBOOST_SP_HAS_INTRIN_H

// VC9 has intrin.h, but it collides with <utility>
#if defined( RTIBOOST_MSVC ) && RTIBOOST_MSVC >= 1600

# define RTIBOOST_SP_HAS_INTRIN_H

// Unlike __MINGW64__, __MINGW64_VERSION_MAJOR is defined by MinGW-w64 for both 32 and 64-bit targets.
#elif defined( __MINGW64_VERSION_MAJOR )

// MinGW-w64 provides intrin.h for both 32 and 64-bit targets.
# define RTIBOOST_SP_HAS_INTRIN_H

// Intel C++ on Windows on VC10+ stdlib
#elif defined( RTIBOOST_INTEL_WIN ) && defined( _CPPLIB_VER ) && _CPPLIB_VER >= 520

# define RTIBOOST_SP_HAS_INTRIN_H

#endif

#if defined( RTIBOOST_USE_WINDOWS_H )

# include <windows.h>

# define RTIBOOST_SP_INTERLOCKED_INCREMENT InterlockedIncrement
# define RTIBOOST_SP_INTERLOCKED_DECREMENT InterlockedDecrement
# define RTIBOOST_SP_INTERLOCKED_COMPARE_EXCHANGE InterlockedCompareExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE InterlockedExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE_ADD InterlockedExchangeAdd

#elif defined( RTIBOOST_USE_INTRIN_H ) || defined( RTIBOOST_SP_HAS_INTRIN_H )

#include <intrin.h>

# define RTIBOOST_SP_INTERLOCKED_INCREMENT _InterlockedIncrement
# define RTIBOOST_SP_INTERLOCKED_DECREMENT _InterlockedDecrement
# define RTIBOOST_SP_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE _InterlockedExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

#elif defined( _WIN32_WCE )

#if _WIN32_WCE >= 0x600

extern "C" long __cdecl _InterlockedIncrement( long volatile * );
extern "C" long __cdecl _InterlockedDecrement( long volatile * );
extern "C" long __cdecl _InterlockedCompareExchange( long volatile *, long, long );
extern "C" long __cdecl _InterlockedExchange( long volatile *, long );
extern "C" long __cdecl _InterlockedExchangeAdd( long volatile *, long );

# define RTIBOOST_SP_INTERLOCKED_INCREMENT _InterlockedIncrement
# define RTIBOOST_SP_INTERLOCKED_DECREMENT _InterlockedDecrement
# define RTIBOOST_SP_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE _InterlockedExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

#else

// under Windows CE we still have old-style Interlocked* functions

extern "C" long __cdecl InterlockedIncrement( long* );
extern "C" long __cdecl InterlockedDecrement( long* );
extern "C" long __cdecl InterlockedCompareExchange( long*, long, long );
extern "C" long __cdecl InterlockedExchange( long*, long );
extern "C" long __cdecl InterlockedExchangeAdd( long*, long );

# define RTIBOOST_SP_INTERLOCKED_INCREMENT InterlockedIncrement
# define RTIBOOST_SP_INTERLOCKED_DECREMENT InterlockedDecrement
# define RTIBOOST_SP_INTERLOCKED_COMPARE_EXCHANGE InterlockedCompareExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE InterlockedExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE_ADD InterlockedExchangeAdd

#endif

#elif defined( RTIBOOST_MSVC ) || defined( RTIBOOST_INTEL_WIN )

#if defined( __CLRCALL_PURE_OR_CDECL )

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

# if defined( RTIBOOST_MSVC ) && RTIBOOST_MSVC == 1310
//From MSDN, Visual Studio .NET 2003 spedific: To declare one of the interlocked functions
//for use as an intrinsic, the function must be declared with the leading underscore and
//the new function must appear in a #pragma intrinsic statement.
#  pragma intrinsic( _InterlockedIncrement )
#  pragma intrinsic( _InterlockedDecrement )
#  pragma intrinsic( _InterlockedCompareExchange )
#  pragma intrinsic( _InterlockedExchange )
#  pragma intrinsic( _InterlockedExchangeAdd )
# endif

#endif

# define RTIBOOST_SP_INTERLOCKED_INCREMENT _InterlockedIncrement
# define RTIBOOST_SP_INTERLOCKED_DECREMENT _InterlockedDecrement
# define RTIBOOST_SP_INTERLOCKED_COMPARE_EXCHANGE _InterlockedCompareExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE _InterlockedExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE_ADD _InterlockedExchangeAdd

#elif defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __CYGWIN__ )

namespace rtiboost
{

namespace detail
{

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile * );
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile * );
extern "C" __declspec(dllimport) long __stdcall InterlockedCompareExchange( long volatile *, long, long );
extern "C" __declspec(dllimport) long __stdcall InterlockedExchange( long volatile *, long );
extern "C" __declspec(dllimport) long __stdcall InterlockedExchangeAdd( long volatile *, long );

} // namespace detail

} // namespace rtiboost

# define RTIBOOST_SP_INTERLOCKED_INCREMENT ::rtiboost::detail::InterlockedIncrement
# define RTIBOOST_SP_INTERLOCKED_DECREMENT ::rtiboost::detail::InterlockedDecrement
# define RTIBOOST_SP_INTERLOCKED_COMPARE_EXCHANGE ::rtiboost::detail::InterlockedCompareExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE ::rtiboost::detail::InterlockedExchange
# define RTIBOOST_SP_INTERLOCKED_EXCHANGE_ADD ::rtiboost::detail::InterlockedExchangeAdd

#else

# error "Interlocked intrinsics not available"

#endif

#endif // #ifndef RTIBOOST_SMART_PTR_DETAIL_SP_INTERLOCKED_HPP_INCLUDED
