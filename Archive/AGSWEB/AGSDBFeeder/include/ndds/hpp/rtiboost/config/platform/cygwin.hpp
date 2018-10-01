//  (C) Copyright John Maddock 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  cygwin specific config options:

#define RTIBOOST_PLATFORM "Cygwin"
#define RTIBOOST_HAS_DIRENT_H
#define RTIBOOST_HAS_LOG1P
#define RTIBOOST_HAS_EXPM1

//
// Threading API:
// See if we have POSIX threads, if we do use them, otherwise
// revert to native Win threads.
#define RTIBOOST_HAS_UNISTD_H
#include <unistd.h>
#if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(RTIBOOST_HAS_WINTHREADS)
#  define RTIBOOST_HAS_PTHREADS
#  define RTIBOOST_HAS_SCHED_YIELD
#  define RTIBOOST_HAS_GETTIMEOFDAY
#  define RTIBOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  define RTIBOOST_HAS_SIGACTION
#else
#  if !defined(RTIBOOST_HAS_WINTHREADS)
#     define RTIBOOST_HAS_WINTHREADS
#  endif
#  define RTIBOOST_HAS_FTIME
#endif

//
// find out if we have a stdint.h, there should be a better way to do this:
//
#include <sys/types.h>
#ifdef _STDINT_H
#define RTIBOOST_HAS_STDINT_H
#endif

/// Cygwin has no fenv.h
#define RTIBOOST_NO_FENV_H

// boilerplate code:
#include <rtiboost/config/posix_features.hpp>

//
// Cygwin lies about XSI conformance, there is no nl_types.h:
//
#ifdef RTIBOOST_HAS_NL_TYPES_H
#  undef RTIBOOST_HAS_NL_TYPES_H
#endif
 




