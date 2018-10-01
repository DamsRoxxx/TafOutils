
//  (C) Copyright Dave Abrahams, Steve Cleary, Beman Dawes, Howard
//  Hinnant & John Maddock 2000.  
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef RTIBOOST_TT_IS_UNION_HPP_INCLUDED
#define RTIBOOST_TT_IS_UNION_HPP_INCLUDED

#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>

namespace rtiboost {

#ifdef RTIBOOST_IS_UNION
template <class T> struct is_union : public integral_constant<bool, RTIBOOST_IS_UNION(T)> {};
#else
template <class T> struct is_union : public integral_constant<bool, false> {};
#endif

template <class T> struct is_union<T const> : public is_union<T>{};
template <class T> struct is_union<T volatile const> : public is_union<T>{};
template <class T> struct is_union<T volatile> : public is_union<T>{};

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_UNION_HPP_INCLUDED
