
//  Copyright (c) 2014 Agustin Berge
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef RTIBOOST_TT_IS_FINAL_HPP_INCLUDED
#define RTIBOOST_TT_IS_FINAL_HPP_INCLUDED

#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>
#ifdef RTIBOOST_IS_FINAL
#include <rtiboost/type_traits/remove_cv.hpp>
#endif

namespace rtiboost {

#ifdef RTIBOOST_IS_FINAL
template <class T> struct is_final : public integral_constant<bool, RTIBOOST_IS_FINAL(typename remove_cv<T>::type)> {};
#else
template <class T> struct is_final : public integral_constant<bool, false> {};
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_FINAL_HPP_INCLUDED
