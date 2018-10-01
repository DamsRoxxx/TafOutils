
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_ADD_REFERENCE_HPP_INCLUDED
#define RTIBOOST_TT_ADD_REFERENCE_HPP_INCLUDED

#include <rtiboost/detail/workaround.hpp>
#include <rtiboost/config.hpp>

namespace rtiboost {

namespace detail {

//
// We can't filter out rvalue_references at the same level as
// references or we get ambiguities from msvc:
//

template <typename T>
struct add_reference_impl
{
    typedef T& type;
};

#ifndef RTIBOOST_NO_CXX11_RVALUE_REFERENCES
template <typename T>
struct add_reference_impl<T&&>
{
    typedef T&& type;
};
#endif

} // namespace detail

template <class T> struct add_reference
{
   typedef typename rtiboost::detail::add_reference_impl<T>::type type;
};
template <class T> struct add_reference<T&>
{
   typedef T& type;
};

// these full specialisations are always required:
template <> struct add_reference<void> { typedef void type; };
#ifndef RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct add_reference<const void> { typedef const void type; };
template <> struct add_reference<const volatile void> { typedef const volatile void type; };
template <> struct add_reference<volatile void> { typedef volatile void type; };
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_ADD_REFERENCE_HPP_INCLUDED
