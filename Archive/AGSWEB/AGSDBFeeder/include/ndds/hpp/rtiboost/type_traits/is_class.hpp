//  (C) Copyright Dave Abrahams, Steve Cleary, Beman Dawes, Howard
//  Hinnant & John Maddock 2000-2003.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef RTIBOOST_TT_IS_CLASS_HPP_INCLUDED
#define RTIBOOST_TT_IS_CLASS_HPP_INCLUDED

#include <rtiboost/type_traits/detail/config.hpp>
#include <rtiboost/type_traits/intrinsics.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>
#ifndef RTIBOOST_IS_CLASS
#   include <rtiboost/type_traits/is_union.hpp>

#ifdef RTIBOOST_TT_HAS_CONFORMING_IS_CLASS_IMPLEMENTATION
#   include <rtiboost/type_traits/detail/yes_no_type.hpp>
#else
#   include <rtiboost/type_traits/is_scalar.hpp>
#   include <rtiboost/type_traits/is_array.hpp>
#   include <rtiboost/type_traits/is_reference.hpp>
#   include <rtiboost/type_traits/is_void.hpp>
#   include <rtiboost/type_traits/is_function.hpp>
#endif

#endif // RTIBOOST_IS_CLASS

namespace rtiboost {

namespace detail {

#ifndef RTIBOOST_IS_CLASS
#ifdef RTIBOOST_TT_HAS_CONFORMING_IS_CLASS_IMPLEMENTATION

// This is actually the conforming implementation which works with
// abstract classes.  However, enough compilers have trouble with
// it that most will use the one in
// boost/type_traits/object_traits.hpp. This implementation
// actually works with VC7.0, but other interactions seem to fail
// when we use it.

// is_class<> metafunction due to Paul Mensonides
// (leavings@attbi.com). For more details:
// http://groups.google.com/groups?hl=en&selm=000001c1cc83%24e154d5e0%247772e50c%40c161550a&rnum=1
#if defined(__GNUC__)  && !defined(__EDG_VERSION__)

template <class U> ::rtiboost::type_traits::yes_type is_class_tester(void(U::*)(void));
template <class U> ::rtiboost::type_traits::no_type is_class_tester(...);

template <typename T>
struct is_class_impl
{

    RTIBOOST_STATIC_CONSTANT(bool, value =
            sizeof(is_class_tester<T>(0)) == sizeof(::rtiboost::type_traits::yes_type)
            && ! ::rtiboost::is_union<T>::value
        );
};

#else

template <typename T>
struct is_class_impl
{
    template <class U> static ::rtiboost::type_traits::yes_type is_class_tester(void(U::*)(void));
    template <class U> static ::rtiboost::type_traits::no_type is_class_tester(...);

    RTIBOOST_STATIC_CONSTANT(bool, value =
            sizeof(is_class_tester<T>(0)) == sizeof(::rtiboost::type_traits::yes_type)
            && ! ::rtiboost::is_union<T>::value
        );
};

#endif

#else

template <typename T>
struct is_class_impl
{
    RTIBOOST_STATIC_CONSTANT(bool, value =
        ! ::rtiboost::is_union<T>::value >::value
        && ! ::rtiboost::is_scalar<T>::value
        && ! ::rtiboost::is_array<T>::value
        && ! ::rtiboost::is_reference<T>::value
        && ! ::rtiboost::is_void<T>::value
        && ! ::rtiboost::is_function<T>::value
        );
};

# endif // RTIBOOST_TT_HAS_CONFORMING_IS_CLASS_IMPLEMENTATION
# else // RTIBOOST_IS_CLASS
template <typename T>
struct is_class_impl
{
    RTIBOOST_STATIC_CONSTANT(bool, value = RTIBOOST_IS_CLASS(T));
};
# endif // RTIBOOST_IS_CLASS

} // namespace detail

template <class T> struct is_class : public integral_constant<bool, ::rtiboost::detail::is_class_impl<T>::value> {};
# ifdef __EDG_VERSION__
template <class T> struct is_class<const T> : public is_class<T>{};
template <class T> struct is_class<const volatile T> : public is_class<T>{};
template <class T> struct is_class<volatile T> : public is_class<T>{};
# endif
    
} // namespace rtiboost

#endif // RTIBOOST_TT_IS_CLASS_HPP_INCLUDED
