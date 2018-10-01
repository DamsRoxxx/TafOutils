
//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_MAKE_UNSIGNED_HPP_INCLUDED
#define RTIBOOST_TT_MAKE_UNSIGNED_HPP_INCLUDED

#include <rtiboost/type_traits/conditional.hpp>
#include <rtiboost/type_traits/is_integral.hpp>
#include <rtiboost/type_traits/is_signed.hpp>
#include <rtiboost/type_traits/is_unsigned.hpp>
#include <rtiboost/type_traits/is_enum.hpp>
#include <rtiboost/type_traits/is_same.hpp>
#include <rtiboost/type_traits/remove_cv.hpp>
#include <rtiboost/type_traits/is_const.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#include <rtiboost/type_traits/add_const.hpp>
#include <rtiboost/type_traits/add_volatile.hpp>
#include <rtiboost/static_assert.hpp>

namespace rtiboost {

template <class T>
struct make_unsigned
{
private:
   RTIBOOST_STATIC_ASSERT_MSG((::rtiboost::is_integral<T>::value || ::rtiboost::is_enum<T>::value), "The template argument to make_unsigned must be an integer or enum type.");
   RTIBOOST_STATIC_ASSERT_MSG((! ::rtiboost::is_same<typename remove_cv<T>::type, bool>::value), "The template argument to make_unsigned must not be the type bool");

   typedef typename remove_cv<T>::type t_no_cv;
   typedef typename conditional<
      (::rtiboost::is_unsigned<T>::value && ::rtiboost::is_integral<T>::value 
      && ! ::rtiboost::is_same<t_no_cv, char>::value
      && ! ::rtiboost::is_same<t_no_cv, wchar_t>::value
      && ! ::rtiboost::is_same<t_no_cv, bool>::value),
      T,
      typename conditional<
         (::rtiboost::is_integral<T>::value 
         && ! ::rtiboost::is_same<t_no_cv, char>::value
         && ! ::rtiboost::is_same<t_no_cv, wchar_t>::value
         && ! ::rtiboost::is_same<t_no_cv, bool>::value),
         typename conditional<
            is_same<t_no_cv, signed char>::value,
            unsigned char,
            typename conditional<
               is_same<t_no_cv, short>::value,
               unsigned short,
               typename conditional<
                  is_same<t_no_cv, int>::value,
                  unsigned int,
                  typename conditional<
                     is_same<t_no_cv, long>::value,
                     unsigned long,
#if defined(RTIBOOST_HAS_LONG_LONG)
#ifdef RTIBOOST_HAS_INT128
                     typename conditional<
                        sizeof(t_no_cv) == sizeof(rtiboost::ulong_long_type), 
                        rtiboost::ulong_long_type, 
                        rtiboost::uint128_type
                     >::type
#else
                     rtiboost::ulong_long_type
#endif
#elif defined(RTIBOOST_HAS_MS_INT64)
                     unsigned __int64
#else
                     unsigned long
#endif
                  >::type
               >::type
            >::type
         >::type,
         // Not a regular integer type:
         typename conditional<
            sizeof(t_no_cv) == sizeof(unsigned char),
            unsigned char,
            typename conditional<
               sizeof(t_no_cv) == sizeof(unsigned short),
               unsigned short,
               typename conditional<
                  sizeof(t_no_cv) == sizeof(unsigned int),
                  unsigned int,
                  typename conditional<
                     sizeof(t_no_cv) == sizeof(unsigned long),
                     unsigned long,
#if defined(RTIBOOST_HAS_LONG_LONG)
#ifdef RTIBOOST_HAS_INT128
                     typename conditional<
                        sizeof(t_no_cv) == sizeof(rtiboost::ulong_long_type), 
                        rtiboost::ulong_long_type, 
                        rtiboost::uint128_type
                     >::type
#else
                     rtiboost::ulong_long_type
#endif
#elif defined(RTIBOOST_HAS_MS_INT64)
                     unsigned __int64
#else
                     unsigned long
#endif
                  >::type
               >::type
            >::type
         >::type
      >::type
   >::type base_integer_type;
   
   // Add back any const qualifier:
   typedef typename conditional<
      is_const<T>::value,
      typename add_const<base_integer_type>::type,
      base_integer_type
   >::type const_base_integer_type;
public:
   // Add back any volatile qualifier:
   typedef typename conditional<
      is_volatile<T>::value,
      typename add_volatile<const_base_integer_type>::type,
      const_base_integer_type
   >::type type;
};

} // namespace rtiboost

#endif // RTIBOOST_TT_ADD_REFERENCE_HPP_INCLUDED

