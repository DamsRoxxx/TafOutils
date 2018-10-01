
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <rtiboost/mpl/aux_/preprocessor/params.hpp>

// local macros, #undef-ined at the end of the header
#define RTIBOOST_AUX778076_DTW_PARAMS(param) \
    RTIBOOST_MPL_PP_PARAMS(RTIBOOST_AUX778076_MSVC_DTW_ARITY, param) \
/**/

#define RTIBOOST_AUX778076_DTW_ORIGINAL_NAME \
    RTIBOOST_AUX778076_MSVC_DTW_ORIGINAL_NAME \
/**/

// warning: not a well-formed C++
// workaround for MSVC 6.5's "dependent template typedef bug"

template< typename F>
struct RTIBOOST_AUX778076_MSVC_DTW_NAME
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
#if RTIBOOST_AUX778076_MSVC_DTW_ARITY > 0
        template< RTIBOOST_AUX778076_DTW_PARAMS(typename P) > struct RTIBOOST_AUX778076_DTW_ORIGINAL_NAME
        {
            typedef int type;
        };
    };

    template< RTIBOOST_AUX778076_DTW_PARAMS(typename T) > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template RTIBOOST_AUX778076_DTW_ORIGINAL_NAME< RTIBOOST_AUX778076_DTW_PARAMS(T) >
    {
    };
#else
        template< typename P = int > struct RTIBOOST_AUX778076_DTW_ORIGINAL_NAME
        {
            typedef int type;
        };
    };

    template< typename T = int > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template RTIBOOST_AUX778076_DTW_ORIGINAL_NAME<>
    {
    };
#endif
};

#undef RTIBOOST_AUX778076_DTW_ORIGINAL_NAME
#undef RTIBOOST_AUX778076_DTW_PARAMS

#undef RTIBOOST_AUX778076_MSVC_DTW_NAME
#undef RTIBOOST_AUX778076_MSVC_DTW_ORIGINAL_NAME
#undef RTIBOOST_AUX778076_MSVC_DTW_ARITY
