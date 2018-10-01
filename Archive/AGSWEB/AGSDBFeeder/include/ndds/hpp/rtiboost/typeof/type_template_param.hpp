// Copyright (C) 2005 Arkadiy Vertleyb
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_TYPE_TEMPLATE_PARAM_HPP_INCLUDED
#define RTIBOOST_TYPEOF_TYPE_TEMPLATE_PARAM_HPP_INCLUDED

#define RTIBOOST_TYPEOF_class_RTIBOOST_TYPEOF (class)
#define RTIBOOST_TYPEOF_typename_RTIBOOST_TYPEOF (typename)

#define RTIBOOST_TYPEOF_MAKE_OBJ_class RTIBOOST_TYPEOF_TYPE_PARAM
#define RTIBOOST_TYPEOF_MAKE_OBJ_typename RTIBOOST_TYPEOF_TYPE_PARAM

#define RTIBOOST_TYPEOF_TYPE_PARAM\
    (TYPE_PARAM)

#define RTIBOOST_TYPEOF_TYPE_PARAM_EXPANDTYPE(Param) class

// TYPE_PARAM "virtual functions" implementation

#define RTIBOOST_TYPEOF_TYPE_PARAM_ENCODE(This, n)\
    typedef typename rtiboost::type_of::encode_type<\
        RTIBOOST_PP_CAT(V, n),\
        RTIBOOST_PP_CAT(P, n)\
    >::type RTIBOOST_PP_CAT(V, RTIBOOST_PP_INC(n)); 

#define RTIBOOST_TYPEOF_TYPE_PARAM_DECODE(This, n)\
    typedef rtiboost::type_of::decode_type< RTIBOOST_PP_CAT(iter, n) > RTIBOOST_PP_CAT(d, n);\
    typedef typename RTIBOOST_PP_CAT(d, n)::type RTIBOOST_PP_CAT(P, n);\
    typedef typename RTIBOOST_PP_CAT(d, n)::iter RTIBOOST_PP_CAT(iter, RTIBOOST_PP_INC(n));

#define RTIBOOST_TYPEOF_TYPE_PARAM_PLACEHOLDER(Param) int
#define RTIBOOST_TYPEOF_TYPE_PARAM_DECLARATION_TYPE(Param) class
#define RTIBOOST_TYPEOF_TYPE_PARAM_PLACEHOLDER_TYPES(Param, n) RTIBOOST_PP_CAT(T,n)
#define RTIBOOST_TYPEOF_TYPE_PARAM_ISTEMPLATE 0

#endif//RTIBOOST_TYPEOF_TYPE_TEMPLATE_PARAM_HPP_INCLUDED
