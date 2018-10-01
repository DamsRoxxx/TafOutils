
// (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_IS_EMPTY_HPP_INCLUDED
#define RTIBOOST_TT_IS_EMPTY_HPP_INCLUDED

#include <rtiboost/type_traits/is_convertible.hpp>
#include <rtiboost/type_traits/detail/config.hpp>
#include <rtiboost/type_traits/intrinsics.hpp>

#include <rtiboost/type_traits/remove_cv.hpp>
#include <rtiboost/type_traits/is_class.hpp>
#include <rtiboost/type_traits/add_reference.hpp>

#ifndef RTIBOOST_INTERNAL_IS_EMPTY
#define RTIBOOST_INTERNAL_IS_EMPTY(T) false
#else
#define RTIBOOST_INTERNAL_IS_EMPTY(T) RTIBOOST_IS_EMPTY(T)
#endif

namespace rtiboost {

namespace detail {


#ifdef RTIBOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4624) // destructor could not be generated
#endif

template <typename T>
struct empty_helper_t1 : public T
{
    empty_helper_t1();  // hh compiler bug workaround
    int i[256];
private:
   // suppress compiler warnings:
   empty_helper_t1(const empty_helper_t1&);
   empty_helper_t1& operator=(const empty_helper_t1&);
};

#ifdef RTIBOOST_MSVC
#pragma warning(pop)
#endif

struct empty_helper_t2 { int i[256]; };

#if !RTIBOOST_WORKAROUND(__BORLANDC__, < 0x600)

template <typename T, bool is_a_class = false>
struct empty_helper
{
    RTIBOOST_STATIC_CONSTANT(bool, value = false);
};

template <typename T>
struct empty_helper<T, true>
{
    RTIBOOST_STATIC_CONSTANT(
        bool, value = (sizeof(empty_helper_t1<T>) == sizeof(empty_helper_t2))
        );
};

template <typename T>
struct is_empty_impl
{
    typedef typename remove_cv<T>::type cvt;
    RTIBOOST_STATIC_CONSTANT(
        bool, 
        value = ( ::rtiboost::detail::empty_helper<cvt,::rtiboost::is_class<T>::value>::value || RTIBOOST_INTERNAL_IS_EMPTY(cvt)));
};

#else // __BORLANDC__

template <typename T, bool is_a_class, bool convertible_to_int>
struct empty_helper
{
    RTIBOOST_STATIC_CONSTANT(bool, value = false);
};

template <typename T>
struct empty_helper<T, true, false>
{
    RTIBOOST_STATIC_CONSTANT(bool, value = (
        sizeof(empty_helper_t1<T>) == sizeof(empty_helper_t2)
        ));
};

template <typename T>
struct is_empty_impl
{
   typedef typename remove_cv<T>::type cvt;
   typedef typename add_reference<T>::type r_type;

   RTIBOOST_STATIC_CONSTANT(
       bool, value = (
              ::rtiboost::detail::empty_helper<
                  cvt
                , ::rtiboost::is_class<T>::value
                , ::rtiboost::is_convertible< r_type,int>::value
              >::value || RTIBOOST_INTERNAL_IS_EMPTY(cvt));
};

#endif // __BORLANDC__

} // namespace detail

template <class T> struct is_empty : integral_constant<bool, ::rtiboost::detail::is_empty_impl<T>::value> {};

} // namespace rtiboost

#undef RTIBOOST_INTERNAL_IS_EMPTY

#endif // RTIBOOST_TT_IS_EMPTY_HPP_INCLUDED

