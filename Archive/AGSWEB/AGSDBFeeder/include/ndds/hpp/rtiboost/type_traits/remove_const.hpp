
//  (C) Copyright Dave Abrahams, Steve Cleary, Beman Dawes, Howard
//  Hinnant & John Maddock 2000.  
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef RTIBOOST_TT_REMOVE_CONST_HPP_INCLUDED
#define RTIBOOST_TT_REMOVE_CONST_HPP_INCLUDED

#include <rtiboost/config.hpp>
#include <cstddef>
#include <rtiboost/detail/workaround.hpp>

namespace rtiboost {

   //  convert a type T to a non-cv-qualified type - remove_const<T>
   template <class T> struct remove_const{ typedef T type; };
   template <class T> struct remove_const<T const>{ typedef T type; };

#if !defined(RTIBOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
   template <class T, std::size_t N> struct remove_const<T const[N]>{ typedef T type[N]; };
#if !RTIBOOST_WORKAROUND(__BORLANDC__, < 0x600) && !defined(__IBMCPP__) &&  !RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840))
   template <class T> struct remove_const<T const[]>{ typedef T type[]; };
#endif
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_REMOVE_CONST_HPP_INCLUDED
