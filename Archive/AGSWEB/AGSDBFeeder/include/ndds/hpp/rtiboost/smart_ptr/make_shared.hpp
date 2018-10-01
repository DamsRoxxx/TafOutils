#ifndef RTIBOOST_SMART_PTR_MAKE_SHARED_HPP_INCLUDED
#define RTIBOOST_SMART_PTR_MAKE_SHARED_HPP_INCLUDED

//  make_shared.hpp
//
//  Copyright (c) 2007, 2008, 2012 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/smart_ptr/make_shared.html
//  for documentation.

#include <rtiboost/smart_ptr/make_shared_object.hpp>

#if !defined( RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION ) && !defined( RTIBOOST_NO_SFINAE )
# include <rtiboost/smart_ptr/make_shared_array.hpp>
# include <rtiboost/smart_ptr/allocate_shared_array.hpp>
#endif

#endif // #ifndef RTIBOOST_SMART_PTR_MAKE_SHARED_HPP_INCLUDED
