
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_IS_STATELESS_HPP_INCLUDED
#define RTIBOOST_TT_IS_STATELESS_HPP_INCLUDED

#include <rtiboost/type_traits/has_trivial_constructor.hpp>
#include <rtiboost/type_traits/has_trivial_copy.hpp>
#include <rtiboost/type_traits/has_trivial_destructor.hpp>
#include <rtiboost/type_traits/is_class.hpp>
#include <rtiboost/type_traits/is_empty.hpp>
#include <rtiboost/config.hpp>

namespace rtiboost {

template <typename T>
struct is_stateless
 : public integral_constant<bool,  
      (::rtiboost::has_trivial_constructor<T>::value
      && ::rtiboost::has_trivial_copy<T>::value
      && ::rtiboost::has_trivial_destructor<T>::value
      && ::rtiboost::is_class<T>::value
      && ::rtiboost::is_empty<T>::value)>
{};

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_STATELESS_HPP_INCLUDED
