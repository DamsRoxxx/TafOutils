// Copyright (C) 2004, 2005 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

// Inclusion of this file increments RTIBOOST_TYPEOF_REGISTRATION_GROUP 
// This method was suggested by Paul Mensonides

#ifdef RTIBOOST_TYPEOF_EMULATION
#   undef RTIBOOST_TYPEOF_REGISTRATION_GROUP

#   include <rtiboost/preprocessor/slot/counter.hpp>
#   include RTIBOOST_PP_UPDATE_COUNTER()
#   define RTIBOOST_TYPEOF_REGISTRATION_GROUP RTIBOOST_PP_COUNTER
#endif
