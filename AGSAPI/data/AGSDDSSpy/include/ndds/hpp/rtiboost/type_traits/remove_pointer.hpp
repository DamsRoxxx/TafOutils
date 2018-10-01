
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_REMOVE_POINTER_HPP_INCLUDED
#define RTIBOOST_TT_REMOVE_POINTER_HPP_INCLUDED

#include <rtiboost/config.hpp>

#if defined(RTIBOOST_MSVC)
#include <rtiboost/type_traits/remove_cv.hpp>
#include <rtiboost/type_traits/is_pointer.hpp>
#endif

namespace rtiboost {

#ifdef RTIBOOST_MSVC

namespace detail{

   //
   // We need all this crazy indirection because a type such as:
   //
   // T (*const)(U)
   //
   // Does not bind to a <T*> or <T*const> partial specialization with VC10 and earlier
   //
   template <class T> 
   struct remove_pointer_imp
   {
      typedef T type;
   };

   template <class T> 
   struct remove_pointer_imp<T*>
   {
      typedef T type;
   };

   template <class T, bool b> 
   struct remove_pointer_imp3
   {
      typedef typename remove_pointer_imp<typename rtiboost::remove_cv<T>::type>::type type;
   };

   template <class T> 
   struct remove_pointer_imp3<T, false>
   {
      typedef T type;
   };

   template <class T> 
   struct remove_pointer_imp2
   {
      typedef typename remove_pointer_imp3<T, ::rtiboost::is_pointer<T>::value>::type type;
   };
}

template <class T> struct remove_pointer{ typedef typename rtiboost::detail::remove_pointer_imp2<T>::type type; };

#else

template <class T> struct remove_pointer{ typedef T type; };
template <class T> struct remove_pointer<T*>{ typedef T type; };
template <class T> struct remove_pointer<T*const>{ typedef T type; };
template <class T> struct remove_pointer<T*volatile>{ typedef T type; };
template <class T> struct remove_pointer<T*const volatile>{ typedef T type; };

#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_REMOVE_POINTER_HPP_INCLUDED
