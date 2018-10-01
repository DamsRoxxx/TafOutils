// Copyright (C) 2004 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_TEMPLATE_ENCODING_HPP_INCLUDED
#define RTIBOOST_TYPEOF_TEMPLATE_ENCODING_HPP_INCLUDED

#include <rtiboost/preprocessor/cat.hpp>
#include <rtiboost/preprocessor/repetition/enum_trailing.hpp>
#include <rtiboost/preprocessor/control/iif.hpp>
#include <rtiboost/preprocessor/detail/is_unary.hpp>
#include <rtiboost/preprocessor/repetition/repeat.hpp>
#include <rtiboost/preprocessor/tuple/eat.hpp>
#include <rtiboost/preprocessor/seq/transform.hpp>
#include <rtiboost/preprocessor/seq/for_each_i.hpp>
#include <rtiboost/preprocessor/seq/cat.hpp>

#include <rtiboost/typeof/encode_decode.hpp>
#include <rtiboost/typeof/int_encoding.hpp>

#include <rtiboost/typeof/type_template_param.hpp>
#include <rtiboost/typeof/integral_template_param.hpp>
#include <rtiboost/typeof/template_template_param.hpp>

#ifdef __BORLANDC__
#define RTIBOOST_TYPEOF_QUALIFY(P) self_t::P
#else
#define RTIBOOST_TYPEOF_QUALIFY(P) P
#endif
// The template parameter description, entered by the user,
// is converted into a polymorphic "object"
// that is used to generate the code responsible for
// encoding/decoding the parameter, etc.

// make sure to cat the sequence first, and only then add the prefix.
#define RTIBOOST_TYPEOF_MAKE_OBJ(elem) RTIBOOST_PP_CAT(\
    RTIBOOST_TYPEOF_MAKE_OBJ,\
    RTIBOOST_PP_SEQ_CAT((_) RTIBOOST_TYPEOF_TO_SEQ(elem))\
    )

#define RTIBOOST_TYPEOF_TO_SEQ(tokens) RTIBOOST_TYPEOF_ ## tokens ## _RTIBOOST_TYPEOF

// RTIBOOST_TYPEOF_REGISTER_TEMPLATE

#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE_EXPLICIT_ID(Name, Params, Id)\
    RTIBOOST_TYPEOF_REGISTER_TEMPLATE_IMPL(\
        Name,\
        RTIBOOST_TYPEOF_MAKE_OBJS(RTIBOOST_TYPEOF_TOSEQ(Params)),\
        RTIBOOST_PP_SEQ_SIZE(RTIBOOST_TYPEOF_TOSEQ(Params)),\
        Id)

#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE(Name, Params)\
    RTIBOOST_TYPEOF_REGISTER_TEMPLATE_EXPLICIT_ID(Name, Params, RTIBOOST_TYPEOF_UNIQUE_ID())

#define RTIBOOST_TYPEOF_OBJECT_MAKER(s, data, elem)\
    RTIBOOST_TYPEOF_MAKE_OBJ(elem)

#define RTIBOOST_TYPEOF_MAKE_OBJS(Params)\
    RTIBOOST_PP_SEQ_TRANSFORM(RTIBOOST_TYPEOF_OBJECT_MAKER, ~, Params)

// As suggested by Paul Mensonides:

#define RTIBOOST_TYPEOF_TOSEQ(x)\
    RTIBOOST_PP_IIF(\
        RTIBOOST_PP_IS_UNARY(x),\
        x RTIBOOST_PP_TUPLE_EAT(3), RTIBOOST_PP_REPEAT\
    )(x, RTIBOOST_TYPEOF_TOSEQ_2, ~)

#define RTIBOOST_TYPEOF_TOSEQ_2(z, n, _) (class)

// RTIBOOST_TYPEOF_VIRTUAL

#define RTIBOOST_TYPEOF_CAT_4(a, b, c, d) RTIBOOST_TYPEOF_CAT_4_I(a, b, c, d)
#define RTIBOOST_TYPEOF_CAT_4_I(a, b, c, d) a ## b ## c ## d

#define RTIBOOST_TYPEOF_VIRTUAL(Fun, Obj)\
    RTIBOOST_TYPEOF_CAT_4(RTIBOOST_TYPEOF_, RTIBOOST_PP_SEQ_HEAD(Obj), _, Fun)

// RTIBOOST_TYPEOF_SEQ_ENUM[_TRAILING][_1]
// Two versions provided due to reentrancy issue

#define RTIBOOST_TYPEOF_SEQ_EXPAND_ELEMENT(z,n,seq)\
   RTIBOOST_PP_SEQ_ELEM(0,seq) (z,n,RTIBOOST_PP_SEQ_ELEM(n,RTIBOOST_PP_SEQ_ELEM(1,seq)))

#define RTIBOOST_TYPEOF_SEQ_ENUM(seq,macro)\
    RTIBOOST_PP_ENUM(RTIBOOST_PP_SEQ_SIZE(seq),RTIBOOST_TYPEOF_SEQ_EXPAND_ELEMENT,(macro)(seq))

#define RTIBOOST_TYPEOF_SEQ_ENUM_TRAILING(seq,macro)\
    RTIBOOST_PP_ENUM_TRAILING(RTIBOOST_PP_SEQ_SIZE(seq),RTIBOOST_TYPEOF_SEQ_EXPAND_ELEMENT,(macro)(seq))

#define RTIBOOST_TYPEOF_SEQ_EXPAND_ELEMENT_1(z,n,seq)\
    RTIBOOST_PP_SEQ_ELEM(0,seq) (z,n,RTIBOOST_PP_SEQ_ELEM(n,RTIBOOST_PP_SEQ_ELEM(1,seq)))

#define RTIBOOST_TYPEOF_SEQ_ENUM_1(seq,macro)\
    RTIBOOST_PP_ENUM(RTIBOOST_PP_SEQ_SIZE(seq),RTIBOOST_TYPEOF_SEQ_EXPAND_ELEMENT_1,(macro)(seq))

#define RTIBOOST_TYPEOF_SEQ_ENUM_TRAILING_1(seq,macro)\
    RTIBOOST_PP_ENUM_TRAILING(RTIBOOST_PP_SEQ_SIZE(seq),RTIBOOST_TYPEOF_SEQ_EXPAND_ELEMENT_1,(macro)(seq))

//

#define RTIBOOST_TYPEOF_PLACEHOLDER(z, n, elem)\
    RTIBOOST_TYPEOF_VIRTUAL(PLACEHOLDER, elem)(elem)

#define RTIBOOST_TYPEOF_PLACEHOLDER_TYPES(z, n, elem)\
    RTIBOOST_TYPEOF_VIRTUAL(PLACEHOLDER_TYPES, elem)(elem, n)

#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_PARAM(r, data, n, elem)\
    RTIBOOST_TYPEOF_VIRTUAL(ENCODE, elem)(elem, n)

#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_PARAM(r, data, n, elem)\
    RTIBOOST_TYPEOF_VIRTUAL(DECODE, elem)(elem, n)

#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR(z, n, elem) \
    RTIBOOST_TYPEOF_VIRTUAL(EXPANDTYPE, elem)(elem) RTIBOOST_PP_CAT(P, n)

#define RTIBOOST_TYPEOF_REGISTER_DEFAULT_TEMPLATE_TYPE(Name,Params,ID)\
    Name< RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_SEQ_SIZE(Params), P) >

//Since we are creating an internal decode struct, we need to use different template names, T instead of P.
#define RTIBOOST_TYPEOF_REGISTER_DECODER_TYPE_PARAM_PAIR(z,n,elem) \
    RTIBOOST_TYPEOF_VIRTUAL(EXPANDTYPE, elem)(elem) RTIBOOST_PP_CAT(T, n)

//Default template param decoding

#define RTIBOOST_TYPEOF_TYPEDEF_DECODED_TEMPLATE_TYPE(Name,Params)\
    typedef Name<RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_SEQ_SIZE(Params),RTIBOOST_TYPEOF_QUALIFY(P))> type;

//Branch the decoding
#define RTIBOOST_TYPEOF_TYPEDEF_DECODED_TYPE(Name,Params)\
    RTIBOOST_PP_IF(RTIBOOST_TYPEOF_HAS_TEMPLATES(Params),\
        RTIBOOST_TYPEOF_TYPEDEF_DECODED_TEMPLATE_TEMPLATE_TYPE,\
        RTIBOOST_TYPEOF_TYPEDEF_DECODED_TEMPLATE_TYPE)(Name,Params)

#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE_IMPL(Name, Params, Size, ID)\
    RTIBOOST_TYPEOF_BEGIN_ENCODE_NS\
    RTIBOOST_TYPEOF_REGISTER_TEMPLATE_TEMPLATE_IMPL(Name, Params, ID)\
    template<class V\
        RTIBOOST_TYPEOF_SEQ_ENUM_TRAILING(Params, RTIBOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR)\
    >\
    struct encode_type_impl<V, Name<RTIBOOST_PP_ENUM_PARAMS(Size, P)> >\
    {\
        typedef typename rtiboost::type_of::push_back<V, rtiboost::mpl::size_t<ID> >::type V0;\
        RTIBOOST_PP_SEQ_FOR_EACH_I(RTIBOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_PARAM, ~, Params)\
        typedef RTIBOOST_PP_CAT(V, Size) type;\
    };\
    template<class Iter>\
    struct decode_type_impl<rtiboost::mpl::size_t<ID>, Iter>\
    {\
        typedef decode_type_impl<rtiboost::mpl::size_t<ID>, Iter> self_t;\
        typedef rtiboost::mpl::size_t<ID> self_id;\
        typedef Iter iter0;\
        RTIBOOST_PP_SEQ_FOR_EACH_I(RTIBOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_PARAM, ~, Params)\
        RTIBOOST_TYPEOF_TYPEDEF_DECODED_TYPE(Name, Params)\
        typedef RTIBOOST_PP_CAT(iter, Size) iter;\
    };\
    RTIBOOST_TYPEOF_END_ENCODE_NS

#endif//RTIBOOST_TYPEOF_TEMPLATE_ENCODING_HPP_INCLUDED
