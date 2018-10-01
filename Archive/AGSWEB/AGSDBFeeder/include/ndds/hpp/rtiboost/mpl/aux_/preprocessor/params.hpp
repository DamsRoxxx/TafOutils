
#ifndef RTIBOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/preprocessor.hpp>

// RTIBOOST_MPL_PP_PARAMS(0,T): <nothing>
// RTIBOOST_MPL_PP_PARAMS(1,T): T1
// RTIBOOST_MPL_PP_PARAMS(2,T): T1, T2
// RTIBOOST_MPL_PP_PARAMS(n,T): T1, T2, .., Tn

#if !defined(RTIBOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_MPL_PP_PARAMS(n,p) \
    RTIBOOST_PP_CAT(RTIBOOST_MPL_PP_PARAMS_,n)(p) \
    /**/

#   define RTIBOOST_MPL_PP_PARAMS_0(p)
#   define RTIBOOST_MPL_PP_PARAMS_1(p) p##1
#   define RTIBOOST_MPL_PP_PARAMS_2(p) p##1,p##2
#   define RTIBOOST_MPL_PP_PARAMS_3(p) p##1,p##2,p##3
#   define RTIBOOST_MPL_PP_PARAMS_4(p) p##1,p##2,p##3,p##4
#   define RTIBOOST_MPL_PP_PARAMS_5(p) p##1,p##2,p##3,p##4,p##5
#   define RTIBOOST_MPL_PP_PARAMS_6(p) p##1,p##2,p##3,p##4,p##5,p##6
#   define RTIBOOST_MPL_PP_PARAMS_7(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7
#   define RTIBOOST_MPL_PP_PARAMS_8(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8
#   define RTIBOOST_MPL_PP_PARAMS_9(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9

#else

#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/repeat.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_MPL_PP_AUX_PARAM_FUNC(unused, i, param) \
    RTIBOOST_PP_COMMA_IF(i) \
    RTIBOOST_PP_CAT(param, RTIBOOST_PP_INC(i)) \
    /**/

#   define RTIBOOST_MPL_PP_PARAMS(n, param) \
    RTIBOOST_PP_REPEAT( \
          n \
        , RTIBOOST_MPL_PP_AUX_PARAM_FUNC \
        , param \
        ) \
    /**/

#endif 

#endif // RTIBOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED
