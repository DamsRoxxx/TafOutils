// Copyright (C) 2005 Arkadiy Vertleyb
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_ENCODE_DECODE_PARAMS_HPP_INCLUDED
#define RTIBOOST_TYPEOF_ENCODE_DECODE_PARAMS_HPP_INCLUDED

#include <rtiboost/preprocessor/cat.hpp>
#include <rtiboost/preprocessor/repetition/repeat.hpp>

// Assumes iter0 contains initial iterator

#define RTIBOOST_TYPEOF_DECODE_PARAM(z, n, text)   \
    typedef rtiboost::type_of::decode_type<iter##n> decode##n;     \
    typedef typename decode##n::type p##n;      \
    typedef typename decode##n::iter RTIBOOST_PP_CAT(iter, RTIBOOST_PP_INC(n));

#define RTIBOOST_TYPEOF_DECODE_PARAMS(n)\
    RTIBOOST_PP_REPEAT(n, RTIBOOST_TYPEOF_DECODE_PARAM, ~)

// The P0, P1, ... PN are encoded and added to V 

#define RTIBOOST_TYPEOF_ENCODE_PARAMS_BEGIN(z, n, text)\
    typename rtiboost::type_of::encode_type<

#define RTIBOOST_TYPEOF_ENCODE_PARAMS_END(z, n, text)\
    , RTIBOOST_PP_CAT(P, n)>::type

#define RTIBOOST_TYPEOF_ENCODE_PARAMS(n, ID)                   \
    RTIBOOST_PP_REPEAT(n, RTIBOOST_TYPEOF_ENCODE_PARAMS_BEGIN, ~) \
    typename rtiboost::type_of::push_back<V, rtiboost::mpl::size_t<ID> >::type      \
    RTIBOOST_PP_REPEAT(n, RTIBOOST_TYPEOF_ENCODE_PARAMS_END, ~)

#endif//RTIBOOST_TYPEOF_ENCODE_DECODE_PARAMS_HPP_INCLUDED
