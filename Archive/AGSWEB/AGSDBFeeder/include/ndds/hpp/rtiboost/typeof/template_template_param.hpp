// Copyright (C) 2005 Peder Holt
// Copyright (C) 2005 Arkadiy Vertleyb
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_TEMPLATE_TEMPLATE_PARAM_HPP_INCLUDED
#define RTIBOOST_TYPEOF_TEMPLATE_TEMPLATE_PARAM_HPP_INCLUDED

#include <rtiboost/preprocessor/logical/or.hpp>
#include <rtiboost/preprocessor/seq/fold_left.hpp>
#include <rtiboost/preprocessor/seq/enum.hpp>

#define RTIBOOST_TYPEOF_MAKE_OBJ_template(x)   RTIBOOST_TYPEOF_TEMPLATE_PARAM(x)
#define RTIBOOST_TYPEOF_TEMPLATE(X) template(X) RTIBOOST_TYPEOF_EAT
#define RTIBOOST_TYPEOF_template(X) (template(X))

#define RTIBOOST_TYPEOF_TEMPLATE_PARAM(Params)\
    (TEMPLATE_PARAM)\
    (Params)

#define RTIBOOST_TYPEOF_TEMPLATE_PARAM_GETPARAMS(This)\
    RTIBOOST_TYPEOF_TOSEQ(RTIBOOST_PP_SEQ_ELEM(1, This))

//Encode / decode this
#define RTIBOOST_TYPEOF_TEMPLATE_PARAM_ENCODE(This, n)\
   typedef typename rtiboost::type_of::encode_template<RTIBOOST_PP_CAT(V, n),\
       RTIBOOST_PP_CAT(P, n)<RTIBOOST_TYPEOF_SEQ_ENUM(RTIBOOST_TYPEOF_MAKE_OBJS(RTIBOOST_TYPEOF_TEMPLATE_PARAM_GETPARAMS(This)),RTIBOOST_TYPEOF_PLACEHOLDER) >\
   >::type RTIBOOST_PP_CAT(V, RTIBOOST_PP_INC(n));

#define RTIBOOST_TYPEOF_TEMPLATE_PARAM_DECODE(This, n)\
   typedef rtiboost::type_of::decode_template< RTIBOOST_PP_CAT(iter, n) > RTIBOOST_PP_CAT(d, n);\
   typedef typename RTIBOOST_PP_CAT(d, n)::type RTIBOOST_PP_CAT(P, n);\
   typedef typename RTIBOOST_PP_CAT(d, n)::iter RTIBOOST_PP_CAT(iter,RTIBOOST_PP_INC(n));

// template<class, unsigned int, ...> class
#define RTIBOOST_TYPEOF_TEMPLATE_PARAM_EXPANDTYPE(This) \
    template <RTIBOOST_PP_SEQ_ENUM(RTIBOOST_TYPEOF_TEMPLATE_PARAM_GETPARAMS(This)) > class

#define RTIBOOST_TYPEOF_TEMPLATE_PARAM_PLACEHOLDER(Param)\
    Nested_Template_Template_Arguments_Not_Supported

//'template<class,int> class' is reduced to 'class'
#define RTIBOOST_TYPEOF_TEMPLATE_PARAM_DECLARATION_TYPE(Param) class

// T3<int, (unsigned int)0, ...>
#define RTIBOOST_TYPEOF_TEMPLATE_PARAM_PLACEHOLDER_TYPES(Param, n)\
    RTIBOOST_PP_CAT(T,n)<RTIBOOST_TYPEOF_SEQ_ENUM_1(RTIBOOST_TYPEOF_MAKE_OBJS(RTIBOOST_TYPEOF_TEMPLATE_PARAM_GETPARAMS(Param)),RTIBOOST_TYPEOF_PLACEHOLDER) >

#define RTIBOOST_TYPEOF_TEMPLATE_PARAM_ISTEMPLATE 1

////////////////////////////
// move to encode_decode?

RTIBOOST_TYPEOF_BEGIN_ENCODE_NS

template<class V, class Type_Not_Registered_With_Typeof_System> struct encode_template_impl;
template<class T, class Iter> struct decode_template_impl;

RTIBOOST_TYPEOF_END_ENCODE_NS

namespace rtiboost { namespace type_of {

    template<class V, class T> struct encode_template
        : RTIBOOST_TYPEOF_ENCODE_NS_QUALIFIER::encode_template_impl<V, T>
    {};

    template<class Iter> struct decode_template
        : RTIBOOST_TYPEOF_ENCODE_NS_QUALIFIER::decode_template_impl<typename Iter::type, typename Iter::next>
    {};
}}

////////////////////////////
// move to template_encoding.hpp?

//Template template registration
#define RTIBOOST_TYPEOF_REGISTER_TYPE_FOR_TEMPLATE_TEMPLATE(Name,Params,ID)\
    template<class V\
        RTIBOOST_TYPEOF_SEQ_ENUM_TRAILING(Params,RTIBOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR)\
    >\
    struct encode_template_impl<V,Name<\
        RTIBOOST_PP_ENUM_PARAMS(\
        RTIBOOST_PP_SEQ_SIZE(Params),\
        P)> >\
        : rtiboost::type_of::push_back<V, rtiboost::mpl::size_t<ID> >\
    {\
    };\
    template<class Iter> struct decode_template_impl<rtiboost::mpl::size_t<ID>, Iter>\
    {\
        RTIBOOST_PP_REPEAT(RTIBOOST_PP_SEQ_SIZE(Params),RTIBOOST_TYPEOF_TYPEDEF_INT_PN,_)\
        typedef Name<RTIBOOST_TYPEOF_SEQ_ENUM(Params,RTIBOOST_TYPEOF_PLACEHOLDER) > type;\
        typedef Iter iter;\
    };

#define RTIBOOST_TYPEOF_TYPEDEF_INT_PN(z,n,Params) typedef int RTIBOOST_PP_CAT(P,n);

#ifdef __BORLANDC__
#define RTIBOOST_TYPEOF_DECODE_NESTED_TEMPLATE_HELPER_NAME RTIBOOST_PP_CAT(\
        RTIBOOST_PP_CAT(\
            RTIBOOST_PP_CAT(\
                decode_nested_template_helper,\
                RTIBOOST_TYPEOF_REGISTRATION_GROUP\
            ),0x10000\
        ),__LINE__\
    )
#define RTIBOOST_TYPEOF_REGISTER_DECODE_NESTED_TEMPLATE_HELPER_IMPL(Name,Params,ID)\
    struct RTIBOOST_TYPEOF_DECODE_NESTED_TEMPLATE_HELPER_NAME {\
        template<RTIBOOST_TYPEOF_SEQ_ENUM(Params,RTIBOOST_TYPEOF_REGISTER_DECLARE_DECODER_TYPE_PARAM_PAIR) >\
        struct decode_params;\
        template<RTIBOOST_TYPEOF_SEQ_ENUM(Params,RTIBOOST_TYPEOF_REGISTER_DECODER_TYPE_PARAM_PAIR) >\
        struct decode_params<RTIBOOST_TYPEOF_SEQ_ENUM(Params,RTIBOOST_TYPEOF_PLACEHOLDER_TYPES) >\
        {\
            typedef Name<RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_SEQ_SIZE(Params),T)> type;\
        };\
    };
//Template template param decoding
#define RTIBOOST_TYPEOF_TYPEDEF_DECODED_TEMPLATE_TEMPLATE_TYPE(Name,Params)\
    typedef typename RTIBOOST_TYPEOF_DECODE_NESTED_TEMPLATE_HELPER_NAME::decode_params<RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_SEQ_SIZE(Params),P)>::type type;

#else
#define RTIBOOST_TYPEOF_REGISTER_DECODE_NESTED_TEMPLATE_HELPER_IMPL(Name,Params,ID)

//Template template param decoding
#define RTIBOOST_TYPEOF_TYPEDEF_DECODED_TEMPLATE_TEMPLATE_TYPE(Name,Params)\
    template<RTIBOOST_TYPEOF_SEQ_ENUM(Params,RTIBOOST_TYPEOF_REGISTER_DECLARE_DECODER_TYPE_PARAM_PAIR) >\
    struct decode_params;\
    template<RTIBOOST_TYPEOF_SEQ_ENUM(Params,RTIBOOST_TYPEOF_REGISTER_DECODER_TYPE_PARAM_PAIR) >\
    struct decode_params<RTIBOOST_TYPEOF_SEQ_ENUM(Params,RTIBOOST_TYPEOF_PLACEHOLDER_TYPES) >\
    {\
        typedef Name<RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_SEQ_SIZE(Params),T)> type;\
    };\
    typedef typename decode_params<RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_SEQ_SIZE(Params),P)>::type type;
#endif
#define RTIBOOST_TYPEOF_REGISTER_DECLARE_DECODER_TYPE_PARAM_PAIR(z,n,elem) \
    RTIBOOST_TYPEOF_VIRTUAL(DECLARATION_TYPE, elem)(elem) RTIBOOST_PP_CAT(T, n)

// RTIBOOST_TYPEOF_HAS_TEMPLATES
#define RTIBOOST_TYPEOF_HAS_TEMPLATES(Params)\
    RTIBOOST_PP_SEQ_FOLD_LEFT(RTIBOOST_TYPEOF_HAS_TEMPLATES_OP, 0, Params)

#define RTIBOOST_TYPEOF_HAS_TEMPLATES_OP(s, state, elem)\
    RTIBOOST_PP_OR(state, RTIBOOST_TYPEOF_VIRTUAL(ISTEMPLATE, elem))

//Define template template arguments
#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE_TEMPLATE_IMPL(Name,Params,ID)\
    RTIBOOST_PP_IF(RTIBOOST_TYPEOF_HAS_TEMPLATES(Params),\
        RTIBOOST_TYPEOF_REGISTER_DECODE_NESTED_TEMPLATE_HELPER_IMPL,\
        RTIBOOST_TYPEOF_REGISTER_TYPE_FOR_TEMPLATE_TEMPLATE)(Name,Params,ID)

#endif //RTIBOOST_TYPEOF_TEMPLATE_TEMPLATE_PARAM_HPP_INCLUDED
