// Copyright (C) 2004 Arkadiy Vertleyb

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// boostinspect:nounnamed

#ifndef RTIBOOST_TYPEOF_ENCODE_DECODE_HPP_INCLUDED
#define RTIBOOST_TYPEOF_ENCODE_DECODE_HPP_INCLUDED

#include <rtiboost/mpl/deref.hpp>
#include <rtiboost/mpl/next.hpp>

#ifndef RTIBOOST_TYPEOF_SUPPRESS_UNNAMED_NAMESPACE

#   define RTIBOOST_TYPEOF_BEGIN_ENCODE_NS namespace { namespace rtiboost_typeof {
#   define RTIBOOST_TYPEOF_END_ENCODE_NS }}
#   define RTIBOOST_TYPEOF_ENCODE_NS_QUALIFIER rtiboost_typeof

#else

#   define RTIBOOST_TYPEOF_BEGIN_ENCODE_NS namespace rtiboost { namespace type_of {
#   define RTIBOOST_TYPEOF_END_ENCODE_NS }}
#   define RTIBOOST_TYPEOF_ENCODE_NS_QUALIFIER rtiboost::type_of

#   define RTIBOOST_TYPEOF_TEXT "unnamed namespace is off"
#   include <rtiboost/typeof/message.hpp>

#endif

RTIBOOST_TYPEOF_BEGIN_ENCODE_NS

template<class V, class Type_Not_Registered_With_Typeof_System>
struct encode_type_impl;

template<class T, class Iter>
struct decode_type_impl
{
    typedef int type;  // MSVC ETI workaround
};

template<class T>
struct decode_nested_template_helper_impl;

RTIBOOST_TYPEOF_END_ENCODE_NS

namespace rtiboost { namespace type_of {

    template<class V, class T>
    struct encode_type : RTIBOOST_TYPEOF_ENCODE_NS_QUALIFIER::encode_type_impl<V, T>
    {};

    template<class Iter>
    struct decode_type : RTIBOOST_TYPEOF_ENCODE_NS_QUALIFIER::decode_type_impl<
        typename Iter::type,
        typename Iter::next
    >
    {};
}}

#endif//RTIBOOST_TYPEOF_ENCODE_DECODE_HPP_INCLUDED
