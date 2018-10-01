
#ifndef RTIBOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
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

#if !defined(RTIBOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <rtiboost/mpl/aux_/preprocessor/tuple.hpp>

#if defined(RTIBOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION)
#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_MPL_PP_ADD(i,j) \
    RTIBOOST_MPL_PP_ADD_DELAY(i,j) \
    /**/

#   define RTIBOOST_MPL_PP_ADD_DELAY(i,j) \
    RTIBOOST_PP_CAT(RTIBOOST_MPL_PP_TUPLE_11_ELEM_##i,RTIBOOST_MPL_PP_ADD_##j) \
    /**/
#else
#   define RTIBOOST_MPL_PP_ADD(i,j) \
    RTIBOOST_MPL_PP_ADD_DELAY(i,j) \
    /**/

#   define RTIBOOST_MPL_PP_ADD_DELAY(i,j) \
    RTIBOOST_MPL_PP_TUPLE_11_ELEM_##i RTIBOOST_MPL_PP_ADD_##j \
    /**/
#endif

#   define RTIBOOST_MPL_PP_ADD_0 (0,1,2,3,4,5,6,7,8,9,10)
#   define RTIBOOST_MPL_PP_ADD_1 (1,2,3,4,5,6,7,8,9,10,0)
#   define RTIBOOST_MPL_PP_ADD_2 (2,3,4,5,6,7,8,9,10,0,0)
#   define RTIBOOST_MPL_PP_ADD_3 (3,4,5,6,7,8,9,10,0,0,0)
#   define RTIBOOST_MPL_PP_ADD_4 (4,5,6,7,8,9,10,0,0,0,0)
#   define RTIBOOST_MPL_PP_ADD_5 (5,6,7,8,9,10,0,0,0,0,0)
#   define RTIBOOST_MPL_PP_ADD_6 (6,7,8,9,10,0,0,0,0,0,0)
#   define RTIBOOST_MPL_PP_ADD_7 (7,8,9,10,0,0,0,0,0,0,0)
#   define RTIBOOST_MPL_PP_ADD_8 (8,9,10,0,0,0,0,0,0,0,0)
#   define RTIBOOST_MPL_PP_ADD_9 (9,10,0,0,0,0,0,0,0,0,0)
#   define RTIBOOST_MPL_PP_ADD_10 (10,0,0,0,0,0,0,0,0,0,0)

#else

#   include <rtiboost/preprocessor/arithmetic/add.hpp>

#   define RTIBOOST_MPL_PP_ADD(i,j) \
    RTIBOOST_PP_ADD(i,j) \
    /**/
    
#endif 

#endif // RTIBOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED
