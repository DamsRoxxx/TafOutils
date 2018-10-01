// Copyright 2005 Alexander Nasonov.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_type_traits_promote_hpp_INCLUDED
#define RTIBOOST_type_traits_promote_hpp_INCLUDED

#include <rtiboost/config.hpp>
#include <rtiboost/type_traits/integral_promotion.hpp>
#include <rtiboost/type_traits/floating_point_promotion.hpp>

namespace rtiboost {

template<class T> struct promote : public integral_promotion<typename floating_point_promotion<T>::type>{};

}

#endif // #ifndef RTIBOOST_type_traits_promote_hpp_INCLUDED

