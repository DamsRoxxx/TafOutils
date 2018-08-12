
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  (C) Copyright Eric Friedman 2002-2003.
//  (C) Copyright Antony Polukhin 2013.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_INCLUDED
#define RTIBOOST_TT_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_INCLUDED

#include <rtiboost/config.hpp>
#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>
#include <rtiboost/detail/workaround.hpp>

#ifdef RTIBOOST_IS_NOTHROW_MOVE_CONSTRUCT

namespace rtiboost {

template <class T>
struct is_nothrow_move_constructible : public integral_constant<bool, RTIBOOST_IS_NOTHROW_MOVE_CONSTRUCT(T)>{};

template <class T> struct is_nothrow_move_constructible<volatile T> : public ::rtiboost::false_type {};
template <class T> struct is_nothrow_move_constructible<const volatile T> : public ::rtiboost::false_type{};

#elif !defined(RTIBOOST_NO_CXX11_NOEXCEPT) && !defined(RTIBOOST_NO_SFINAE_EXPR) && !RTIBOOST_WORKAROUND(RTIBOOST_GCC_VERSION, < 40800)

#include <rtiboost/type_traits/declval.hpp>
#include <rtiboost/utility/enable_if.hpp>

namespace rtiboost{ namespace detail{

template <class T, class Enable = void>
struct false_or_cpp11_noexcept_move_constructible: public ::rtiboost::false_type {};

template <class T>
struct false_or_cpp11_noexcept_move_constructible <
        T,
        typename ::rtiboost::enable_if_c<sizeof(T) && RTIBOOST_NOEXCEPT_EXPR(T(::rtiboost::declval<T>()))>::type
    > : public ::rtiboost::integral_constant<bool, RTIBOOST_NOEXCEPT_EXPR(T(::rtiboost::declval<T>()))>
{};

}

template <class T> struct is_nothrow_move_constructible
   : public integral_constant<bool, ::rtiboost::detail::false_or_cpp11_noexcept_move_constructible<T>::value>{};

template <class T> struct is_nothrow_move_constructible<volatile T> : public ::rtiboost::false_type {};
template <class T> struct is_nothrow_move_constructible<const volatile T> : public ::rtiboost::false_type{};
template <class T, std::size_t N> struct is_nothrow_move_constructible<T[N]> : public ::rtiboost::false_type{};
template <class T> struct is_nothrow_move_constructible<T[]> : public ::rtiboost::false_type{};

#else

#include <rtiboost/type_traits/has_trivial_move_constructor.hpp>
#include <rtiboost/type_traits/has_nothrow_copy.hpp>
#include <rtiboost/type_traits/is_array.hpp>

namespace rtiboost{

template <class T>
struct is_nothrow_move_constructible
   : public integral_constant<bool,
   (::rtiboost::has_trivial_move_constructor<T>::value || ::rtiboost::has_nothrow_copy<T>::value) && !::rtiboost::is_array<T>::value>
{};

#endif

template <> struct is_nothrow_move_constructible<void> : false_type{};
#ifndef RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct is_nothrow_move_constructible<void const> : false_type{};
template <> struct is_nothrow_move_constructible<void volatile> : false_type{};
template <> struct is_nothrow_move_constructible<void const volatile> : false_type{};
#endif
// References are always trivially constructible, even if the thing they reference is not:
template <class T> struct is_nothrow_move_constructible<T&> : public ::rtiboost::true_type{};
#ifndef RTIBOOST_NO_CXX11_RVALUE_REFERENCES
template <class T> struct is_nothrow_move_constructible<T&&> : public ::rtiboost::true_type{};
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_INCLUDED
