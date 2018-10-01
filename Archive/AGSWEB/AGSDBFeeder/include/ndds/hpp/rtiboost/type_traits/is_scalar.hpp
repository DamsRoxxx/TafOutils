
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_IS_SCALAR_HPP_INCLUDED
#define RTIBOOST_TT_IS_SCALAR_HPP_INCLUDED

#include <rtiboost/type_traits/is_arithmetic.hpp>
#include <rtiboost/type_traits/is_enum.hpp>
#include <rtiboost/type_traits/is_pointer.hpp>
#include <rtiboost/type_traits/is_member_pointer.hpp>
#include <rtiboost/config.hpp>

namespace rtiboost {

template <typename T>
struct is_scalar
   : public integral_constant<bool, ::rtiboost::is_arithmetic<T>::value || ::rtiboost::is_enum<T>::value || ::rtiboost::is_pointer<T>::value || ::rtiboost::is_member_pointer<T>::value>
{};

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_SCALAR_HPP_INCLUDED
