
#ifndef RTIBOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED

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

// RTIBOOST_MPL_PP_DEFAULT_PARAMS(0,T,int): <nothing>
// RTIBOOST_MPL_PP_DEFAULT_PARAMS(1,T,int): T1 = int
// RTIBOOST_MPL_PP_DEFAULT_PARAMS(2,T,int): T1 = int, T2 = int
// RTIBOOST_MPL_PP_DEFAULT_PARAMS(n,T,int): T1 = int, T2 = int, .., Tn = int

#if !defined(RTIBOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS(n,p,v) \
    RTIBOOST_PP_CAT(RTIBOOST_MPL_PP_DEFAULT_PARAMS_,n)(p,v) \
    /**/
    
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_0(p,v)
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_1(p,v) p##1=v
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_2(p,v) p##1=v,p##2=v
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_3(p,v) p##1=v,p##2=v,p##3=v
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_4(p,v) p##1=v,p##2=v,p##3=v,p##4=v
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_5(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_6(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_7(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_8(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v,p##8=v
#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS_9(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v,p##8=v,p##9=v

#else

#   include <rtiboost/preprocessor/tuple/elem.hpp>
#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/repeat.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_MPL_PP_AUX_DEFAULT_PARAM_FUNC(unused, i, pv) \
    RTIBOOST_PP_COMMA_IF(i) \
    RTIBOOST_PP_CAT( RTIBOOST_PP_TUPLE_ELEM(2,0,pv), RTIBOOST_PP_INC(i) ) \
        = RTIBOOST_PP_TUPLE_ELEM(2,1,pv) \
    /**/

#   define RTIBOOST_MPL_PP_DEFAULT_PARAMS(n, param, value) \
    RTIBOOST_PP_REPEAT( \
          n \
        , RTIBOOST_MPL_PP_AUX_DEFAULT_PARAM_FUNC \
        , (param,value) \
        ) \
    /**/

#endif

#endif // RTIBOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED
