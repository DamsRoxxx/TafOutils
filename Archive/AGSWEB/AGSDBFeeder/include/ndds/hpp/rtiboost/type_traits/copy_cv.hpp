#ifndef RTIBOOST_TYPE_TRAITS_COPY_CV_HPP_INCLUDED
#define RTIBOOST_TYPE_TRAITS_COPY_CV_HPP_INCLUDED

//
//  Copyright 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <rtiboost/type_traits/is_const.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#include <rtiboost/type_traits/add_const.hpp>
#include <rtiboost/type_traits/add_volatile.hpp>
#include <rtiboost/type_traits/conditional.hpp>

namespace rtiboost
{

template<class T, class U> struct copy_cv
{
private:

    typedef typename rtiboost::conditional<rtiboost::is_const<U>::value, typename rtiboost::add_const<T>::type, T>::type CT;

public:

    typedef typename rtiboost::conditional<rtiboost::is_volatile<U>::value, typename rtiboost::add_volatile<CT>::type, CT>::type type;
};

} // namespace rtiboost

#endif // #ifndef RTIBOOST_TYPE_TRAITS_COPY_CV_HPP_INCLUDED
