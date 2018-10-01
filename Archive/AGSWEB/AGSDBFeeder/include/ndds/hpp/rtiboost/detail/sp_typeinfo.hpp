#ifndef RTIBOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED
#define RTIBOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/sp_typeinfo.hpp
//
//  Deprecated, please use boost/core/typeinfo.hpp
//
//  Copyright 2007 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <rtiboost/core/typeinfo.hpp>

namespace rtiboost
{

namespace detail
{

typedef rtiboost::core::typeinfo sp_typeinfo;

} // namespace detail

} // namespace rtiboost

#define RTIBOOST_SP_TYPEID(T) RTIBOOST_CORE_TYPEID(T)

#endif  // #ifndef RTIBOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED
