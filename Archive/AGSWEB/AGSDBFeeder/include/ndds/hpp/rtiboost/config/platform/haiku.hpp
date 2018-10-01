//  (C) Copyright Jessica Hamilton 2014.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Haiku specific config options:

#define RTIBOOST_PLATFORM "Haiku"

#define RTIBOOST_HAS_UNISTD_H
#define RTIBOOST_HAS_STDINT_H

#ifndef RTIBOOST_DISABLE_THREADS
#  define RTIBOOST_HAS_THREADS
#endif

#define RTIBOOST_NO_CXX11_HDR_TYPE_TRAITS
#define RTIBOOST_NO_CXX11_ATOMIC_SMART_PTR
#define RTIBOOST_NO_CXX11_STATIC_ASSERT
#define RTIBOOST_NO_CXX11_VARIADIC_MACROS

//
// thread API's not auto detected:
//
#define RTIBOOST_HAS_SCHED_YIELD
#define RTIBOOST_HAS_GETTIMEOFDAY

// boilerplate code:
#include <rtiboost/config/posix_features.hpp>
