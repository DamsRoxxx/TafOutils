//  (C) Copyright Artyom Beilis 2010.  
//  Use, modification and distribution are subject to the  
//  Boost Software License, Version 1.0. (See accompanying file  
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 

#ifndef RTIBOOST_CONFIG_PLATFORM_VMS_HPP 
#define RTIBOOST_CONFIG_PLATFORM_VMS_HPP 

#define RTIBOOST_PLATFORM "OpenVMS" 

#undef  RTIBOOST_HAS_STDINT_H 
#define RTIBOOST_HAS_UNISTD_H 
#define RTIBOOST_HAS_NL_TYPES_H 
#define RTIBOOST_HAS_GETTIMEOFDAY 
#define RTIBOOST_HAS_DIRENT_H 
#define RTIBOOST_HAS_PTHREADS 
#define RTIBOOST_HAS_NANOSLEEP 
#define RTIBOOST_HAS_CLOCK_GETTIME 
#define RTIBOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE 
#define RTIBOOST_HAS_LOG1P 
#define RTIBOOST_HAS_EXPM1 
#define RTIBOOST_HAS_THREADS 
#undef  RTIBOOST_HAS_SCHED_YIELD 

#endif 
