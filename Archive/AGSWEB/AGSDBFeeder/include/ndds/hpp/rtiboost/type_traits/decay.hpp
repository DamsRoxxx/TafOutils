//  (C) Copyright John Maddock & Thorsten Ottosen 2005.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef RTIBOOST_TT_DECAY_HPP_INCLUDED
#define RTIBOOST_TT_DECAY_HPP_INCLUDED

#include <rtiboost/type_traits/is_array.hpp>
#include <rtiboost/type_traits/is_function.hpp>
#include <rtiboost/type_traits/remove_bounds.hpp>
#include <rtiboost/type_traits/add_pointer.hpp>
#include <rtiboost/type_traits/remove_reference.hpp>
#include <rtiboost/type_traits/remove_cv.hpp>

namespace rtiboost 
{

   namespace detail
   {

      template <class T, bool Array, bool Function> struct decay_imp { typedef typename remove_cv<T>::type type; };
      template <class T> struct decay_imp<T, true, false> { typedef typename remove_bounds<T>::type* type; };
      template <class T> struct decay_imp<T, false, true> { typedef T* type; };

   }

    template< class T >
    struct decay
    {
    private:
        typedef typename remove_reference<T>::type Ty;
    public:
       typedef typename rtiboost::detail::decay_imp<Ty, rtiboost::is_array<Ty>::value, rtiboost::is_function<Ty>::value>::type type;
    };
    
} // namespace rtiboost


#endif // RTIBOOST_TT_DECAY_HPP_INCLUDED
