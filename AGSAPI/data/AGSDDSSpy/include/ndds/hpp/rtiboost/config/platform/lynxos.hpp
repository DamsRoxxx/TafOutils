//  (C) Copyright Real-Time Innovations, Inc 2015

// Note: this configuration file is not part of boost. It has been added
// by RTI to support LynxOS. This doesn't fully configure all possible features
// availabe on LynxOS, it simply enables certain posix features, most notably
// pthreads.

//  LynxOS specific config options:

#define RTIBOOST_PLATFORM "LynxOS"

#  ifndef RTIBOOST_HAS_UNISTD_H
#    define RTIBOOST_HAS_UNISTD_H
#  endif

#  include <rtiboost/config/posix_features.hpp>

#ifdef RTIBOOST_HAS_PTHREADS
#  define RTIBOOST_HAS_THREADS
#endif
