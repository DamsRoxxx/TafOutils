
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_HAS_NOTHROW_COPY_HPP_INCLUDED
#define RTIBOOST_TT_HAS_NOTHROW_COPY_HPP_INCLUDED

#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>

#ifdef RTIBOOST_HAS_NOTHROW_COPY

#if defined(RTIBOOST_CLANG) || defined(__GNUC__) || defined(__ghs__) || defined(__CODEGEARC__) || defined(__SUNPRO_CC)
#include <rtiboost/type_traits/is_volatile.hpp>
#include <rtiboost/type_traits/is_copy_constructible.hpp>
#include <rtiboost/type_traits/is_reference.hpp>
#include <rtiboost/type_traits/is_array.hpp>
#ifdef RTIBOOST_INTEL
#include <rtiboost/type_traits/is_pod.hpp>
#endif
#elif defined(RTIBOOST_MSVC) || defined(RTIBOOST_INTEL)
#include <rtiboost/type_traits/has_trivial_copy.hpp>
#include <rtiboost/type_traits/is_array.hpp>
#ifdef RTIBOOST_INTEL
#include <rtiboost/type_traits/add_lvalue_reference.hpp>
#include <rtiboost/type_traits/add_const.hpp>
#endif
#endif

namespace rtiboost {

template <class T> struct has_nothrow_copy_constructor : public integral_constant<bool, RTIBOOST_HAS_NOTHROW_COPY(T)>{};

#elif !defined(RTIBOOST_NO_CXX11_NOEXCEPT)

#include <rtiboost/type_traits/declval.hpp>
#include <rtiboost/type_traits/is_copy_constructible.hpp>

namespace rtiboost{

namespace detail{

template <class T, bool b>
struct has_nothrow_copy_constructor_imp : public rtiboost::integral_constant<bool, false>{};
template <class T>
struct has_nothrow_copy_constructor_imp<T, true> : public rtiboost::integral_constant<bool, noexcept(T(rtiboost::declval<const T&>()))>{};

}

template <class T> struct has_nothrow_copy_constructor : public detail::has_nothrow_copy_constructor_imp<T, rtiboost::is_copy_constructible<T>::value>{};

#else

#include <rtiboost/type_traits/has_trivial_copy.hpp>

namespace rtiboost{

template <class T> struct has_nothrow_copy_constructor : public integral_constant<bool, ::rtiboost::has_trivial_copy<T>::value>{};

#endif

template <> struct has_nothrow_copy_constructor<void> : public false_type{};
template <class T> struct has_nothrow_copy_constructor<T volatile> : public false_type{};
template <class T> struct has_nothrow_copy_constructor<T&> : public false_type{};
#if !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES) 
template <class T> struct has_nothrow_copy_constructor<T&&> : public false_type{};
#endif
#ifndef RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct has_nothrow_copy_constructor<void const> : public false_type{};
template <> struct has_nothrow_copy_constructor<void volatile> : public false_type{};
template <> struct has_nothrow_copy_constructor<void const volatile> : public false_type{};
#endif

template <class T> struct has_nothrow_copy : public has_nothrow_copy_constructor<T>{};

} // namespace rtiboost

#endif // RTIBOOST_TT_HAS_NOTHROW_COPY_HPP_INCLUDED
