
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_HAS_NOTHROW_ASSIGN_HPP_INCLUDED
#define RTIBOOST_TT_HAS_NOTHROW_ASSIGN_HPP_INCLUDED

#include <rtiboost/type_traits/integral_constant.hpp>
#include <rtiboost/type_traits/intrinsics.hpp>

#if !defined(RTIBOOST_HAS_NOTHROW_ASSIGN) || defined(RTIBOOST_MSVC) || defined(RTIBOOST_INTEL)
#include <rtiboost/type_traits/has_trivial_assign.hpp>
#if !defined(RTIBOOST_NO_CXX11_NOEXCEPT) && !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES)
#include <rtiboost/type_traits/declval.hpp>
#include <rtiboost/type_traits/is_const.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#include <rtiboost/type_traits/is_reference.hpp>
#include <rtiboost/type_traits/is_assignable.hpp>
#include <rtiboost/type_traits/add_reference.hpp>
#include <rtiboost/type_traits/remove_reference.hpp>
#endif
#endif
#if defined(__GNUC__) || defined(__SUNPRO_CC) || defined(__clang__)
#include <rtiboost/type_traits/is_const.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#include <rtiboost/type_traits/is_assignable.hpp>
#include <rtiboost/type_traits/is_array.hpp>
#ifdef RTIBOOST_INTEL
#include <rtiboost/type_traits/is_pod.hpp>
#endif
#endif

namespace rtiboost {

#if !defined(RTIBOOST_HAS_NOTHROW_ASSIGN) && !defined(RTIBOOST_NO_CXX11_NOEXCEPT) && !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES)

   namespace detail
   {
      template <class T, bool b1, bool b2> struct has_nothrow_assign_imp{ static const bool value = false; };
      template <class T>          struct has_nothrow_assign_imp<T, false, true>{ static const bool value = noexcept(rtiboost::declval<typename add_reference<T>::type>() = rtiboost::declval<typename add_reference<T const>::type>()); };
      template <class T, std::size_t N> struct has_nothrow_assign_imp<T[N], false, true>{ static const bool value = has_nothrow_assign_imp<T, false, true>::value; };
      template <class T>          struct has_nothrow_assign_imp<T[], false, true>{ static const bool value = has_nothrow_assign_imp<T, false, true>::value; };
   }

#endif

   template <class T>
   struct has_nothrow_assign : public integral_constant < bool,
#ifndef RTIBOOST_HAS_NOTHROW_ASSIGN
#if !defined(RTIBOOST_NO_CXX11_NOEXCEPT) && !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES)
      // Portable C++11 version:
      detail::has_nothrow_assign_imp<T, 
      (is_const<typename remove_reference<T>::type>::value || is_volatile<typename remove_reference<T>::type>::value || is_reference<T>::value), 
      is_assignable<typename add_reference<T>::type, typename add_reference<const T>::type>::value
      >::value
#else
      ::rtiboost::has_trivial_assign<T>::value
#endif
#else
      RTIBOOST_HAS_NOTHROW_ASSIGN(T)
#endif
   > {};

template <class T, std::size_t N> struct has_nothrow_assign <T[N]> : public has_nothrow_assign<T> {};
template <> struct has_nothrow_assign<void> : public false_type{};
template <class T> struct has_nothrow_assign<T volatile> : public false_type{};
template <class T> struct has_nothrow_assign<T&> : public false_type{};
#if !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES)
template <class T> struct has_nothrow_assign<T&&> : public false_type{};
#endif
#ifndef RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct has_nothrow_assign<void const> : public false_type{};
template <> struct has_nothrow_assign<void const volatile> : public false_type{};
template <> struct has_nothrow_assign<void volatile> : public false_type{};
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_HAS_NOTHROW_ASSIGN_HPP_INCLUDED
