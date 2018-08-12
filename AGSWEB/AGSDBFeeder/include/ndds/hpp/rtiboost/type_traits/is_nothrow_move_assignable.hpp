
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  (C) Copyright Eric Friedman 2002-2003.
//  (C) Copyright Antony Polukhin 2013.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_IS_NOTHROW_MOVE_ASSIGNABLE_HPP_INCLUDED
#define RTIBOOST_TT_IS_NOTHROW_MOVE_ASSIGNABLE_HPP_INCLUDED

#include <rtiboost/config.hpp>
#include <rtiboost/type_traits/has_trivial_move_assign.hpp>
#include <rtiboost/type_traits/has_nothrow_assign.hpp>
#include <rtiboost/type_traits/is_array.hpp>
#include <rtiboost/type_traits/is_reference.hpp>
#include <rtiboost/utility/enable_if.hpp>
#include <rtiboost/type_traits/declval.hpp>

namespace rtiboost {

#ifdef RTIBOOST_IS_NOTHROW_MOVE_ASSIGN

template <class T>
struct is_nothrow_move_assignable : public integral_constant<bool, RTIBOOST_IS_NOTHROW_MOVE_ASSIGN(T)>{};
template <class T> struct is_nothrow_move_assignable<T const> : public false_type{};
template <class T> struct is_nothrow_move_assignable<T volatile> : public false_type{};
template <class T> struct is_nothrow_move_assignable<T const volatile> : public false_type{};
template <class T> struct is_nothrow_move_assignable<T&> : public false_type{};
#if !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES) 
template <class T> struct is_nothrow_move_assignable<T&&> : public false_type{};
#endif

#elif !defined(RTIBOOST_NO_CXX11_NOEXCEPT) && !defined(RTIBOOST_NO_SFINAE_EXPR) && !RTIBOOST_WORKAROUND(RTIBOOST_GCC_VERSION, < 40700)

namespace detail{

template <class T, class Enable = void>
struct false_or_cpp11_noexcept_move_assignable: public ::rtiboost::false_type {};

template <class T>
struct false_or_cpp11_noexcept_move_assignable <
        T,
        typename ::rtiboost::enable_if_c<sizeof(T) && RTIBOOST_NOEXCEPT_EXPR(::rtiboost::declval<T&>() = ::rtiboost::declval<T>())>::type
    > : public ::rtiboost::integral_constant<bool, RTIBOOST_NOEXCEPT_EXPR(::rtiboost::declval<T&>() = ::rtiboost::declval<T>())>
{};

}

template <class T>
struct is_nothrow_move_assignable : public integral_constant<bool, ::rtiboost::detail::false_or_cpp11_noexcept_move_assignable<T>::value>{};

template <class T> struct is_nothrow_move_assignable<T const> : public ::rtiboost::false_type {};
template <class T> struct is_nothrow_move_assignable<T const volatile> : public ::rtiboost::false_type{};
template <class T> struct is_nothrow_move_assignable<T volatile> : public ::rtiboost::false_type{};
template <class T> struct is_nothrow_move_assignable<T&> : public ::rtiboost::false_type{};
#ifndef RTIBOOST_NO_CXX11_RVALUE_REFERENCES
template <class T> struct is_nothrow_move_assignable<T&&> : public ::rtiboost::false_type{};
#endif

#else

template <class T>
struct is_nothrow_move_assignable : public integral_constant<bool,
   (::rtiboost::has_trivial_move_assign<T>::value || ::rtiboost::has_nothrow_assign<T>::value) &&  ! ::rtiboost::is_array<T>::value>{};

#endif


template <> struct is_nothrow_move_assignable<void> : public false_type{};
#ifndef RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct is_nothrow_move_assignable<void const> : public false_type{};
template <> struct is_nothrow_move_assignable<void const volatile> : public false_type{};
template <> struct is_nothrow_move_assignable<void volatile> : public false_type{};
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_NOTHROW_MOVE_ASSIGNABLE_HPP_INCLUDED
