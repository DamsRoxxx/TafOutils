#ifndef RTIBOOST_TYPE_TRAITS_DETAIL_MP_DEFER_HPP_INCLUDED
#define RTIBOOST_TYPE_TRAITS_DETAIL_MP_DEFER_HPP_INCLUDED

//
//  Copyright 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <rtiboost/type_traits/integral_constant.hpp>
#include <rtiboost/type_traits/conditional.hpp>

namespace rtiboost
{

namespace type_traits_detail
{

// mp_valid
// implementation by Bruno Dutra (by the name is_evaluable)

template<template<class...> class F, class... T>
struct mp_valid_impl
{
    template<template<class...> class G, class = G<T...>>
    static rtiboost::true_type check_s(int);

    template<template<class...> class>
    static rtiboost::false_type check_s(...);

    using type = decltype(check_s<F>(0));
};

template<template<class...> class F, class... T>
using mp_valid = typename mp_valid_impl<F, T...>::type;

// mp_defer

struct mp_empty
{
};

template<template<class...> class F, class... T> struct mp_defer_impl
{
    using type = F<T...>;
};

template<template<class...> class F, class... T> using mp_defer = typename rtiboost::conditional<mp_valid<F, T...>::value, mp_defer_impl<F, T...>, mp_empty>::type;

} // namespace type_traits_detail

} // namespace rtiboost

#endif // #ifndef RTIBOOST_TYPE_TRAITS_DETAIL_MP_DEFER_HPP_INCLUDED
