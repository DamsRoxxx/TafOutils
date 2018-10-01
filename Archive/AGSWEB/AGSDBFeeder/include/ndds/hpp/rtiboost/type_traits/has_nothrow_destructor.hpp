
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_HAS_NOTHROW_DESTRUCTOR_HPP_INCLUDED
#define RTIBOOST_TT_HAS_NOTHROW_DESTRUCTOR_HPP_INCLUDED

#include <rtiboost/type_traits/has_trivial_destructor.hpp>

#if !defined(RTIBOOST_NO_CXX11_NOEXCEPT) && !defined(__SUNPRO_CC) && !defined(RTIBOOST_MSVC)

#include <rtiboost/type_traits/declval.hpp>
#include <rtiboost/type_traits/is_destructible.hpp>

namespace rtiboost{

   namespace detail{

      template <class T, bool b>
      struct has_nothrow_destructor_imp : public rtiboost::integral_constant<bool, false>{};
      template <class T>
      struct has_nothrow_destructor_imp<T, true> : public rtiboost::integral_constant<bool, noexcept(rtiboost::declval<T*&>()->~T())>{};

   }

   template <class T> struct has_nothrow_destructor : public detail::has_nothrow_destructor_imp<T, rtiboost::is_destructible<T>::value>{};
   template <class T, std::size_t N> struct has_nothrow_destructor<T[N]> : public has_nothrow_destructor<T>{};
   template <class T> struct has_nothrow_destructor<T&> : public integral_constant<bool, false>{};
#if !defined(RTIBOOST_NO_CXX11_RVALUE_REFERENCES) 
   template <class T> struct has_nothrow_destructor<T&&> : public integral_constant<bool, false>{};
#endif
}
#else

namespace rtiboost {

template <class T> struct has_nothrow_destructor : public ::rtiboost::has_trivial_destructor<T> {};

} // namespace rtiboost

#endif

#endif // RTIBOOST_TT_HAS_NOTHROW_DESTRUCTOR_HPP_INCLUDED
