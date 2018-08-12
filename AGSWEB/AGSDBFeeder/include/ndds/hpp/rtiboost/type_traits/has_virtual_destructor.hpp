
//  (C) Copyright John Maddock 2005.  
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef RTIBOOST_TT_HAS_VIRTUAL_DESTRUCTOR_HPP_INCLUDED
#define RTIBOOST_TT_HAS_VIRTUAL_DESTRUCTOR_HPP_INCLUDED

#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>

namespace rtiboost {

#ifdef RTIBOOST_HAS_VIRTUAL_DESTRUCTOR
   template <class T> struct has_virtual_destructor : public integral_constant<bool, RTIBOOST_HAS_VIRTUAL_DESTRUCTOR(T)>{};
#else
   template <class T> struct has_virtual_destructor : public integral_constant<bool, false>{};
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
