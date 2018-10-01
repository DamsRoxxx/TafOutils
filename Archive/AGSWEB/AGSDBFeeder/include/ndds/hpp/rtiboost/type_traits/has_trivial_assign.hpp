
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_HAS_TRIVIAL_ASSIGN_HPP_INCLUDED
#define RTIBOOST_TT_HAS_TRIVIAL_ASSIGN_HPP_INCLUDED

#include <rtiboost/type_traits/detail/config.hpp>
#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>

#if !defined(RTIBOOST_HAS_TRIVIAL_ASSIGN) || defined(RTIBOOST_MSVC) || defined(__GNUC__) || defined(RTIBOOST_INTEL) || defined(__SUNPRO_CC) || defined(__clang__)
#include <rtiboost/type_traits/is_pod.hpp>
#include <rtiboost/type_traits/is_const.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#include <rtiboost/type_traits/is_assignable.hpp>
#endif

namespace rtiboost {

   template <typename T>
   struct has_trivial_assign : public integral_constant < bool,
#ifdef RTIBOOST_HAS_TRIVIAL_ASSIGN
      RTIBOOST_HAS_TRIVIAL_ASSIGN(T)
#else
      ::rtiboost::is_pod<T>::value && !::rtiboost::is_const<T>::value && !::rtiboost::is_volatile<T>::value
#endif
   > {};

   template<> struct has_trivial_assign<void> : public false_type{};
#ifndef RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
   template<> struct has_trivial_assign<void const> : public false_type{};
   template<> struct has_trivial_assign<void const volatile> : public false_type{};
   template<> struct has_trivial_assign<void volatile> : public false_type{};
#endif
   template <class T> struct has_trivial_assign<T volatile> : public false_type{};
   template <class T> struct has_trivial_assign<T&> : public false_type{};
#if !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES)
   template <class T> struct has_trivial_assign<T&&> : public false_type{};
#endif
   // Arrays are not explictly assignable:
   template <typename T, std::size_t N> struct has_trivial_assign<T[N]> : public false_type{};
   template <typename T> struct has_trivial_assign<T[]> : public false_type{};

} // namespace rtiboost

#endif // RTIBOOST_TT_HAS_TRIVIAL_ASSIGN_HPP_INCLUDED
