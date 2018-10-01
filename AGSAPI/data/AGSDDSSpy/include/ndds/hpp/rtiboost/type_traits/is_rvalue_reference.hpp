
//  (C) John Maddock 2010. 
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_IS_RVALUE_REFERENCE_HPP_INCLUDED
#define RTIBOOST_TT_IS_RVALUE_REFERENCE_HPP_INCLUDED

#include <rtiboost/config.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>

namespace rtiboost {

template <class T> struct is_rvalue_reference : public false_type {};
#ifndef RTIBOOST_NO_CXX11_RVALUE_REFERENCES
template <class T> struct is_rvalue_reference<T&&> : public true_type {};
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_REFERENCE_HPP_INCLUDED

