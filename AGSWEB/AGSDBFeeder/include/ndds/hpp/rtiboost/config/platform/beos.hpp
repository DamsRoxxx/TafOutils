//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  BeOS specific config options:

#define RTIBOOST_PLATFORM "BeOS"

#define RTIBOOST_NO_CWCHAR
#define RTIBOOST_NO_CWCTYPE
#define RTIBOOST_HAS_UNISTD_H

#define RTIBOOST_HAS_BETHREADS

#ifndef RTIBOOST_DISABLE_THREADS
#  define RTIBOOST_HAS_THREADS
#endif

// boilerplate code:
#include <rtiboost/config/posix_features.hpp>
 


