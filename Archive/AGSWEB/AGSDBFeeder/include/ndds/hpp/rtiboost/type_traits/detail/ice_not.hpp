//  (C) Copyright John Maddock and Steve Cleary 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_DETAIL_ICE_NOT_HPP_INCLUDED
#define RTIBOOST_TT_DETAIL_ICE_NOT_HPP_INCLUDED

#include <rtiboost/config.hpp>

namespace rtiboost {
namespace type_traits {

template <bool b>
struct ice_not
{
    RTIBOOST_STATIC_CONSTANT(bool, value = true);
};

template <>
struct ice_not<true>
{
    RTIBOOST_STATIC_CONSTANT(bool, value = false);
};

} // namespace type_traits
} // namespace rtiboost

#endif // RTIBOOST_TT_DETAIL_ICE_NOT_HPP_INCLUDED
