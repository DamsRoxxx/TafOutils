
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(RTIBOOST_PP_IS_ITERATING)

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

#include <rtiboost/preprocessor/enum_params.hpp>
#include <rtiboost/preprocessor/enum_shifted_params.hpp>
#include <rtiboost/preprocessor/comma_if.hpp>
#include <rtiboost/preprocessor/repeat.hpp>
#include <rtiboost/preprocessor/dec.hpp>
#include <rtiboost/preprocessor/cat.hpp>

#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

#if defined(RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   define RTIBOOST_AUX778076_VECTOR_TAIL(vector, i_, C) \
    RTIBOOST_PP_CAT(RTIBOOST_PP_CAT(vector,i_),_c)<T \
          RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_PP_ENUM_PARAMS(i_, C) \
        > \
    /**/

#if i_ > 0
template<
      typename T
    , RTIBOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct RTIBOOST_PP_CAT(RTIBOOST_PP_CAT(vector,i_),_c)
    : v_item<
          integral_c<T,RTIBOOST_PP_CAT(C,RTIBOOST_PP_DEC(i_))>
        , RTIBOOST_AUX778076_VECTOR_TAIL(vector,RTIBOOST_PP_DEC(i_),C)
        >
{
    typedef RTIBOOST_PP_CAT(RTIBOOST_PP_CAT(vector,i_),_c) type;
    typedef T value_type;
};
#endif

#   undef RTIBOOST_AUX778076_VECTOR_TAIL

#else // "brute force" implementation

#   define RTIBOOST_AUX778076_VECTOR_C_PARAM_FUNC(unused, i_, param) \
    RTIBOOST_PP_COMMA_IF(i_) \
    integral_c<T,RTIBOOST_PP_CAT(param,i_)> \
    /**/

template<
      typename T
    , RTIBOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct RTIBOOST_PP_CAT(RTIBOOST_PP_CAT(vector,i_),_c)
    : RTIBOOST_PP_CAT(vector,i_)< RTIBOOST_PP_REPEAT(i_,RTIBOOST_AUX778076_VECTOR_C_PARAM_FUNC,C) >
{
    typedef RTIBOOST_PP_CAT(RTIBOOST_PP_CAT(vector,i_),_c) type;
    typedef T value_type;
};

#   undef RTIBOOST_AUX778076_VECTOR_C_PARAM_FUNC

#endif // RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#undef i_

#endif // RTIBOOST_PP_IS_ITERATING
