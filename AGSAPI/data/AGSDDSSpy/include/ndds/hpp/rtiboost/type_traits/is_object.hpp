
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_IS_OBJECT_HPP_INCLUDED
#define RTIBOOST_TT_IS_OBJECT_HPP_INCLUDED

#include <rtiboost/config.hpp>
#include <rtiboost/type_traits/is_reference.hpp>
#include <rtiboost/type_traits/is_void.hpp>
#include <rtiboost/type_traits/is_function.hpp>

namespace rtiboost {

template <class T> struct is_object
   : public 
      integral_constant<
         bool, 
         ! ::rtiboost::is_reference<T>::value && ! ::rtiboost::is_void<T>::value && ! ::rtiboost::is_function<T>::value > 
{};

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_OBJECT_HPP_INCLUDED
