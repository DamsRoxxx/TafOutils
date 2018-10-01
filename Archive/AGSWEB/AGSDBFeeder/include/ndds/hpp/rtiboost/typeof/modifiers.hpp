// Copyright (C) 2004 Arkadiy Vertleyb
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_MODIFIERS_HPP_INCLUDED
#define RTIBOOST_TYPEOF_MODIFIERS_HPP_INCLUDED

#include <rtiboost/typeof/encode_decode.hpp>
#include <rtiboost/preprocessor/facilities/identity.hpp>

#include RTIBOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

// modifiers

#define RTIBOOST_TYPEOF_modifier_support(ID, Fun)\
    template<class V, class T> struct encode_type_impl<V, Fun(T)>\
    {\
        typedef\
            typename rtiboost::type_of::encode_type<\
            typename rtiboost::type_of::push_back<\
            V\
            , rtiboost::mpl::size_t<ID> >::type\
            , T>::type\
            type;\
    };\
    template<class Iter> struct decode_type_impl<rtiboost::mpl::size_t<ID>, Iter>\
    {\
        typedef rtiboost::type_of::decode_type<Iter> d1;\
        typedef Fun(typename d1::type) type;\
        typedef typename d1::iter iter;\
    }


#define RTIBOOST_TYPEOF_const_fun(T) const T
#define RTIBOOST_TYPEOF_volatile_fun(T) volatile T
#define RTIBOOST_TYPEOF_volatile_const_fun(T) volatile const T
#define RTIBOOST_TYPEOF_pointer_fun(T) T*
#define RTIBOOST_TYPEOF_reference_fun(T) T&

#if defined(__BORLANDC__) && (__BORLANDC__ < 0x600)
//Borland incorrectly handles T const, T const volatile and T volatile.
//It drops the decoration no matter what, so we need to try to handle T* const etc. without loosing the top modifier.
#define RTIBOOST_TYPEOF_const_pointer_fun(T) T const *
#define RTIBOOST_TYPEOF_const_reference_fun(T) T const &
#define RTIBOOST_TYPEOF_volatile_pointer_fun(T) T volatile*
#define RTIBOOST_TYPEOF_volatile_reference_fun(T) T volatile&
#define RTIBOOST_TYPEOF_volatile_const_pointer_fun(T) T volatile const *
#define RTIBOOST_TYPEOF_volatile_const_reference_fun(T) T volatile const &
#endif

RTIBOOST_TYPEOF_BEGIN_ENCODE_NS

RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_const_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_volatile_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_volatile_const_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_pointer_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_reference_fun);

#if defined(__BORLANDC__) && (__BORLANDC__ < 0x600)
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_const_pointer_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_const_reference_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_volatile_pointer_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_volatile_reference_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_volatile_const_pointer_fun);
RTIBOOST_TYPEOF_modifier_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_TYPEOF_volatile_const_reference_fun);
#endif

RTIBOOST_TYPEOF_END_ENCODE_NS

#undef RTIBOOST_TYPEOF_modifier_support
#undef RTIBOOST_TYPEOF_const_fun
#undef RTIBOOST_TYPEOF_volatile_fun
#undef RTIBOOST_TYPEOF_volatile_const_fun
#undef RTIBOOST_TYPEOF_pointer_fun
#undef RTIBOOST_TYPEOF_reference_fun

#if defined(__BORLANDC__) && (__BORLANDC__ < 0x600)
#undef RTIBOOST_TYPEOF_const_pointer_fun
#undef RTIBOOST_TYPEOF_const_reference_fun
#undef RTIBOOST_TYPEOF_volatile_pointer_fun
#undef RTIBOOST_TYPEOF_volatile_reference_fun
#undef RTIBOOST_TYPEOF_volatile_const_pointer_fun
#undef RTIBOOST_TYPEOF_volatile_const_reference_fun
#endif

// arrays

#define RTIBOOST_TYPEOF_array_support(ID, Qualifier)\
    template<class V, class T, int N>\
    struct encode_type_impl<V, Qualifier() T[N]>\
    {\
        typedef\
            typename rtiboost::type_of::encode_type<\
            typename rtiboost::type_of::push_back<\
            typename rtiboost::type_of::push_back<\
            V\
            , rtiboost::mpl::size_t<ID> >::type\
            , rtiboost::mpl::size_t<N> >::type\
            , T>::type\
        type;\
    };\
    template<class Iter>\
    struct decode_type_impl<rtiboost::mpl::size_t<ID>, Iter>\
    {\
        enum{n = Iter::type::value};\
        typedef rtiboost::type_of::decode_type<typename Iter::next> d;\
        typedef typename d::type Qualifier() type[n];\
        typedef typename d::iter iter;\
    }

RTIBOOST_TYPEOF_BEGIN_ENCODE_NS

RTIBOOST_TYPEOF_array_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_PP_EMPTY);
RTIBOOST_TYPEOF_array_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_PP_IDENTITY(const));
RTIBOOST_TYPEOF_array_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_PP_IDENTITY(volatile));
RTIBOOST_TYPEOF_array_support(RTIBOOST_TYPEOF_UNIQUE_ID(), RTIBOOST_PP_IDENTITY(volatile const));
RTIBOOST_TYPEOF_END_ENCODE_NS

#undef RTIBOOST_TYPEOF_array_support

#endif//RTIBOOST_TYPEOF_MODIFIERS_HPP_INCLUDED
