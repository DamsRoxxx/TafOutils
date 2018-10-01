
//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_REMOVE_ALL_EXTENTS_HPP_INCLUDED
#define RTIBOOST_TT_REMOVE_ALL_EXTENTS_HPP_INCLUDED

#include <rtiboost/config.hpp>
#include <cstddef>
#include <rtiboost/detail/workaround.hpp>

namespace rtiboost {

template <class T> struct remove_all_extents{ typedef T type; };

#if !defined(RTIBOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
template <class T, std::size_t N> struct remove_all_extents<T[N]> : public remove_all_extents<T>{};
template <class T, std::size_t N> struct remove_all_extents<T const[N]> : public remove_all_extents<T const>{};
template <class T, std::size_t N> struct remove_all_extents<T volatile[N]> : public remove_all_extents<T volatile>{};
template <class T, std::size_t N> struct remove_all_extents<T const volatile[N]> : public remove_all_extents<T const volatile>{};
#if !RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x610)) && !defined(__IBMCPP__) &&  !RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840))
template <class T> struct remove_all_extents<T[]> : public remove_all_extents<T>{};
template <class T> struct remove_all_extents<T const[]> : public remove_all_extents<T const>{};
template <class T> struct remove_all_extents<T volatile[]> : public remove_all_extents<T volatile>{};
template <class T> struct remove_all_extents<T const volatile[]> : public remove_all_extents<T const volatile>{};
#endif
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_REMOVE_BOUNDS_HPP_INCLUDED
