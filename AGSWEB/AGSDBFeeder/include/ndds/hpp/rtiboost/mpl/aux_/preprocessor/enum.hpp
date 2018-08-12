
#ifndef RTIBOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

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

// RTIBOOST_MPL_PP_ENUM(0,int): <nothing>
// RTIBOOST_MPL_PP_ENUM(1,int): int
// RTIBOOST_MPL_PP_ENUM(2,int): int, int
// RTIBOOST_MPL_PP_ENUM(n,int): int, int, .., int

#if !defined(RTIBOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_MPL_PP_ENUM(n, param) \
    RTIBOOST_PP_CAT(RTIBOOST_MPL_PP_ENUM_,n)(param) \
    /**/
    
#   define RTIBOOST_MPL_PP_ENUM_0(p)
#   define RTIBOOST_MPL_PP_ENUM_1(p) p
#   define RTIBOOST_MPL_PP_ENUM_2(p) p,p
#   define RTIBOOST_MPL_PP_ENUM_3(p) p,p,p
#   define RTIBOOST_MPL_PP_ENUM_4(p) p,p,p,p
#   define RTIBOOST_MPL_PP_ENUM_5(p) p,p,p,p,p
#   define RTIBOOST_MPL_PP_ENUM_6(p) p,p,p,p,p,p
#   define RTIBOOST_MPL_PP_ENUM_7(p) p,p,p,p,p,p,p
#   define RTIBOOST_MPL_PP_ENUM_8(p) p,p,p,p,p,p,p,p
#   define RTIBOOST_MPL_PP_ENUM_9(p) p,p,p,p,p,p,p,p,p

#else

#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/repeat.hpp>

#   define RTIBOOST_MPL_PP_AUX_ENUM_FUNC(unused, i, param) \
    RTIBOOST_PP_COMMA_IF(i) param \
    /**/

#   define RTIBOOST_MPL_PP_ENUM(n, param) \
    RTIBOOST_PP_REPEAT( \
          n \
        , RTIBOOST_MPL_PP_AUX_ENUM_FUNC \
        , param \
        ) \
    /**/

#endif

#endif // RTIBOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED
