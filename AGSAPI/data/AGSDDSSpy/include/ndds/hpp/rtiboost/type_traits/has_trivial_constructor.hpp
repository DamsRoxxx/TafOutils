
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_HAS_TRIVIAL_CONSTRUCTOR_HPP_INCLUDED
#define RTIBOOST_TT_HAS_TRIVIAL_CONSTRUCTOR_HPP_INCLUDED

#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/is_pod.hpp>
#include <rtiboost/type_traits/is_default_constructible.hpp>

#ifdef RTIBOOST_HAS_TRIVIAL_CONSTRUCTOR
#ifdef RTIBOOST_HAS_SGI_TYPE_TRAITS
#include <rtiboost/type_traits/is_same.hpp>
#elif defined(__GNUC__) || defined(__SUNPRO_CC)
#include <rtiboost/type_traits/is_volatile.hpp>
#ifdef RTIBOOST_INTEL
#include <rtiboost/type_traits/is_pod.hpp>
#endif
#endif
#endif


#if (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ >= 409)) || defined(RTIBOOST_CLANG) || (defined(__SUNPRO_CC) && defined(RTIBOOST_HAS_TRIVIAL_CONSTRUCTOR))
#include <rtiboost/type_traits/is_default_constructible.hpp>
#define RTIBOOST_TT_TRIVIAL_CONSTRUCT_FIX && is_default_constructible<T>::value
#else
//
// Mot all compilers, particularly older GCC versions can handle the fix above.
#define RTIBOOST_TT_TRIVIAL_CONSTRUCT_FIX
#endif

namespace rtiboost {

template <typename T> struct has_trivial_constructor
#ifdef RTIBOOST_HAS_TRIVIAL_CONSTRUCTOR
   : public integral_constant <bool, ((::rtiboost::is_pod<T>::value || RTIBOOST_HAS_TRIVIAL_CONSTRUCTOR(T)) RTIBOOST_TT_TRIVIAL_CONSTRUCT_FIX)>{};
#else
   : public integral_constant <bool, ::rtiboost::is_pod<T>::value>{};
#endif

template <> struct has_trivial_constructor<void> : public rtiboost::false_type{};
template <> struct has_trivial_constructor<void const> : public rtiboost::false_type{};
template <> struct has_trivial_constructor<void const volatile> : public rtiboost::false_type{};
template <> struct has_trivial_constructor<void volatile> : public rtiboost::false_type{};

template <class T> struct has_trivial_default_constructor : public has_trivial_constructor<T> {};

#undef RTIBOOST_TT_TRIVIAL_CONSTRUCT_FIX

} // namespace rtiboost

#endif // RTIBOOST_TT_HAS_TRIVIAL_CONSTRUCTOR_HPP_INCLUDED
