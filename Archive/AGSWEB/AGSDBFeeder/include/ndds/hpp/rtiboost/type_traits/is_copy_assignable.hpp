//  (C) Copyright Ion Gaztanaga 2014.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_IS_COPY_ASSIGNABLE_HPP_INCLUDED
#define RTIBOOST_TT_IS_COPY_ASSIGNABLE_HPP_INCLUDED

#include <rtiboost/config.hpp>
#include <rtiboost/type_traits/detail/yes_no_type.hpp>
#include <rtiboost/type_traits/is_base_and_derived.hpp>
#include <rtiboost/noncopyable.hpp>

#if !defined(RTIBOOST_NO_CXX11_DELETED_FUNCTIONS) && !defined(RTIBOOST_NO_CXX11_DECLTYPE) \
   && !defined(RTIBOOST_INTEL_CXX_VERSION) && \
      !(defined(RTIBOOST_MSVC) && _MSC_VER == 1800)
#define RTIBOOST_TT_CXX11_IS_COPY_ASSIGNABLE
#include <rtiboost/type_traits/declval.hpp>
#else
   //For compilers without decltype
   #include <rtiboost/type_traits/is_const.hpp>
   #include <rtiboost/type_traits/is_array.hpp>
   #include <rtiboost/type_traits/add_reference.hpp>
   #include <rtiboost/type_traits/remove_reference.hpp>
#endif

namespace rtiboost {

namespace detail{

template <bool DerivedFromNoncopyable, class T>
struct is_copy_assignable_impl2 {

// Intel compiler has problems with SFINAE for copy constructors and deleted functions:
//
// error: function *function_name* cannot be referenced -- it is a deleted function
// static rtiboost::type_traits::yes_type test(T1&, decltype(T1(rtiboost::declval<T1&>()))* = 0);
//                                                        ^ 
//
// MSVC 12.0 (Visual 2013) has problems when the copy constructor has been deleted. See:
// https://connect.microsoft.com/VisualStudio/feedback/details/800328/std-is-copy-constructible-is-broken
#if defined(RTIBOOST_TT_CXX11_IS_COPY_ASSIGNABLE)
    typedef rtiboost::type_traits::yes_type yes_type;
    typedef rtiboost::type_traits::no_type  no_type;

    template <class U>
    static decltype(::rtiboost::declval<U&>() = ::rtiboost::declval<const U&>(), yes_type() ) test(int);

    template <class>
    static no_type test(...);

    static const bool value = sizeof(test<T>(0)) == sizeof(yes_type);

#else
    static RTIBOOST_DEDUCED_TYPENAME rtiboost::add_reference<T>::type produce();

    template <class T1>
    static rtiboost::type_traits::no_type test(T1&, typename T1::boost_move_no_copy_constructor_or_assign* = 0);

    static rtiboost::type_traits::yes_type test(...);
    // If you see errors like this:
    //
    //      `'T::operator=(const T&)' is private`
    //      `boost/type_traits/is_copy_assignable.hpp:NN:M: error: within this context`
    //
    // then you are trying to call that macro for a structure defined like that:
    //
    //      struct T {
    //          ...
    //      private:
    //          T & operator=(const T &);
    //          ...
    //      };
    //
    // To fix that you must modify your structure:
    //
    //      // C++03 and C++11 version
    //      struct T: private rtiboost::noncopyable {
    //          ...
    //      private:
    //          T & operator=(const T &);
    //          ...
    //      };
    //
    //      // C++11 version
    //      struct T {
    //          ...
    //      private:
    //          T& operator=(const T &) = delete;
    //          ...
    //      };
    RTIBOOST_STATIC_CONSTANT(bool, value = (
            sizeof(test(produce())) == sizeof(rtiboost::type_traits::yes_type)
    ));
   #endif
};

template <class T>
struct is_copy_assignable_impl2<true, T> {
    RTIBOOST_STATIC_CONSTANT(bool, value = false);
};

template <class T>
struct is_copy_assignable_impl {

#if !defined(RTIBOOST_TT_CXX11_IS_COPY_ASSIGNABLE)
    //For compilers without decltype, at least return false on const types, arrays
    //types derived from rtiboost::noncopyable and types defined as RTIBOOST_MOVEABLE_BUT_NOT_COPYABLE
    typedef RTIBOOST_DEDUCED_TYPENAME rtiboost::remove_reference<T>::type unreferenced_t;
    RTIBOOST_STATIC_CONSTANT(bool, value = (
        rtiboost::detail::is_copy_assignable_impl2<
            rtiboost::is_base_and_derived<rtiboost::noncopyable, T>::value
            || rtiboost::is_const<unreferenced_t>::value || rtiboost::is_array<unreferenced_t>::value
            ,T
        >::value
    ));
    #else
    RTIBOOST_STATIC_CONSTANT(bool, value = (
        rtiboost::detail::is_copy_assignable_impl2<
            rtiboost::is_base_and_derived<rtiboost::noncopyable, T>::value,T
        >::value
    ));
    #endif
};

} // namespace detail

template <class T> struct is_copy_assignable : public integral_constant<bool, ::rtiboost::detail::is_copy_assignable_impl<T>::value>{};
template <> struct is_copy_assignable<void> : public false_type{};
#ifndef RTIBOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct is_copy_assignable<void const> : public false_type{};
template <> struct is_copy_assignable<void const volatile> : public false_type{};
template <> struct is_copy_assignable<void volatile> : public false_type{};
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_COPY_ASSIGNABLE_HPP_INCLUDED
