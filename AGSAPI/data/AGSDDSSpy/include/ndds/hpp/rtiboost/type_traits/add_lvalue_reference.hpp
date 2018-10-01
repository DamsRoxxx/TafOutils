//  Copyright 2010 John Maddock

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef RTIBOOST_TYPE_TRAITS_EXT_ADD_LVALUE_REFERENCE__HPP
#define RTIBOOST_TYPE_TRAITS_EXT_ADD_LVALUE_REFERENCE__HPP

#include <rtiboost/type_traits/add_reference.hpp>

namespace rtiboost{

template <class T> struct add_lvalue_reference
{
   typedef typename rtiboost::add_reference<T>::type type; 
};

#ifndef RTIBOOST_NO_CXX11_RVALUE_REFERENCES
template <class T> struct add_lvalue_reference<T&&>
{
   typedef T& type;
};
#endif

}

#endif  // RTIBOOST_TYPE_TRAITS_EXT_ADD_LVALUE_REFERENCE__HPP
