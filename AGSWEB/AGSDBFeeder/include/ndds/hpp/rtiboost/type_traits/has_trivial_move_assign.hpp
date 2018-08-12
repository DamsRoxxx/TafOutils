
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  (C) Copyright Eric Friedman 2002-2003.
//  (C) Copyright Antony Polukhin 2013.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_HAS_TRIVIAL_MOVE_ASSIGN_HPP_INCLUDED
#define RTIBOOST_TT_HAS_TRIVIAL_MOVE_ASSIGN_HPP_INCLUDED

#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>

#if !defined(RTIBOOST_HAS_TRIVIAL_MOVE_ASSIGN) || defined(RTIBOOST_MSVC) || defined(RTIBOOST_INTEL)
#include <rtiboost/type_traits/is_pod.hpp>
#include <rtiboost/type_traits/is_const.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#ifdef RTIBOOST_MSVC
#include <rtiboost/type_traits/is_reference.hpp>
#endif
#endif

#if defined(__GNUC__) || defined(__clang)
#include <rtiboost/type_traits/is_assignable.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#endif

#ifdef __SUNPRO_CC
#include <rtiboost/type_traits/is_assignable.hpp>
#include <rtiboost/type_traits/remove_const.hpp>
#if __cplusplus >= 201103
#define SOLARIS_EXTRA_CHECK && is_assignable<typename remove_const<T>::type&, typename remove_const<T>::type&&>::value
#endif
#endif

#ifndef SOLARIS_EXTRA_CHECK
#define SOLARIS_EXTRA_CHECK
#endif

namespace rtiboost{

template <typename T>
struct has_trivial_move_assign : public integral_constant<bool,
#ifdef RTIBOOST_HAS_TRIVIAL_MOVE_ASSIGN
   RTIBOOST_HAS_TRIVIAL_MOVE_ASSIGN(T)
#else
   ::rtiboost::is_pod<T>::value && !::rtiboost::is_const<T>::value && !::rtiboost::is_volatile<T>::value SOLARIS_EXTRA_CHECK
#endif
   > {};

template <> struct has_trivial_move_assign<void> : public false_type{};
#ifndef RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct has_trivial_move_assign<void const> : public false_type{};
template <> struct has_trivial_move_assign<void const volatile> : public false_type{};
template <> struct has_trivial_move_assign<void volatile> : public false_type{};
#endif
template <class T> struct has_trivial_move_assign<T&> : public false_type{};
#ifndef RTIBOOST_NO_CXX11_RVALUE_REFERENCES
template <class T> struct has_trivial_move_assign<T&&> : public false_type{};
#endif
// Array types are not assignable:
template <class T, std::size_t N> struct has_trivial_move_assign<T[N]> : public false_type{};
template <class T> struct has_trivial_move_assign<T[]> : public false_type{};

} // namespace rtiboost

#undef SOLARIS_EXTRA_CHECK

#endif // RTIBOOST_TT_HAS_TRIVIAL_MOVE_ASSIGN_HPP_INCLUDED
