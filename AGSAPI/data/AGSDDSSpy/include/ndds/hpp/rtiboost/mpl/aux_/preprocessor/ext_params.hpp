
#ifndef RTIBOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED

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

// RTIBOOST_MPL_PP_EXT_PARAMS(2,2,T): <nothing>
// RTIBOOST_MPL_PP_EXT_PARAMS(2,3,T): T2
// RTIBOOST_MPL_PP_EXT_PARAMS(2,4,T): T2, T3
// RTIBOOST_MPL_PP_EXT_PARAMS(2,n,T): T2, T3, .., Tn-1

#if !defined(RTIBOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <rtiboost/mpl/aux_/preprocessor/filter_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/sub.hpp>

#   define RTIBOOST_MPL_PP_EXT_PARAMS(i,j,p) \
    RTIBOOST_MPL_PP_EXT_PARAMS_DELAY_1(i,RTIBOOST_MPL_PP_SUB(j,i),p) \
    /**/

#   define RTIBOOST_MPL_PP_EXT_PARAMS_DELAY_1(i,n,p) \
    RTIBOOST_MPL_PP_EXT_PARAMS_DELAY_2(i,n,p) \
    /**/

#   define RTIBOOST_MPL_PP_EXT_PARAMS_DELAY_2(i,n,p) \
    RTIBOOST_MPL_PP_EXT_PARAMS_##i(n,p) \
    /**/

#   define RTIBOOST_MPL_PP_EXT_PARAMS_1(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9)
#   define RTIBOOST_MPL_PP_EXT_PARAMS_2(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9,p1)
#   define RTIBOOST_MPL_PP_EXT_PARAMS_3(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##3,p##4,p##5,p##6,p##7,p##8,p##9,p1,p2)
#   define RTIBOOST_MPL_PP_EXT_PARAMS_4(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##4,p##5,p##6,p##7,p##8,p##9,p1,p2,p3)
#   define RTIBOOST_MPL_PP_EXT_PARAMS_5(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##5,p##6,p##7,p##8,p##9,p1,p2,p3,p4)
#   define RTIBOOST_MPL_PP_EXT_PARAMS_6(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##6,p##7,p##8,p##9,p1,p2,p3,p4,p5)
#   define RTIBOOST_MPL_PP_EXT_PARAMS_7(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##7,p##8,p##9,p1,p2,p3,p4,p5,p6)
#   define RTIBOOST_MPL_PP_EXT_PARAMS_8(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##8,p##9,p1,p2,p3,p4,p5,p6,p7)
#   define RTIBOOST_MPL_PP_EXT_PARAMS_9(i,p) RTIBOOST_MPL_PP_FILTER_PARAMS_##i(p##9,p1,p2,p3,p4,p5,p6,p7,p8)

#else

#   include <rtiboost/preprocessor/arithmetic/add.hpp>
#   include <rtiboost/preprocessor/arithmetic/sub.hpp>
#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/repeat.hpp>
#   include <rtiboost/preprocessor/tuple/elem.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_MPL_PP_AUX_EXT_PARAM_FUNC(unused, i, op) \
    RTIBOOST_PP_COMMA_IF(i) \
    RTIBOOST_PP_CAT( \
          RTIBOOST_PP_TUPLE_ELEM(2,1,op) \
        , RTIBOOST_PP_ADD_D(1, i, RTIBOOST_PP_TUPLE_ELEM(2,0,op)) \
        ) \
    /**/

#   define RTIBOOST_MPL_PP_EXT_PARAMS(i, j, param) \
    RTIBOOST_PP_REPEAT( \
          RTIBOOST_PP_SUB_D(1,j,i) \
        , RTIBOOST_MPL_PP_AUX_EXT_PARAM_FUNC \
        , (i,param) \
        ) \
    /**/

#endif

#endif // RTIBOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED
