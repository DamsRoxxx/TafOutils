// Copyright 2005 Alexander Nasonov.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_type_traits_floating_point_promotion_hpp_INCLUDED
#define RTIBOOST_type_traits_floating_point_promotion_hpp_INCLUDED

namespace rtiboost {

   template<class T> struct floating_point_promotion { typedef T type; };
   template<> struct floating_point_promotion<float> { typedef double type; };
   template<> struct floating_point_promotion<float const> { typedef double const type; };
   template<> struct floating_point_promotion<float volatile>{ typedef double volatile type; };
   template<> struct floating_point_promotion<float const volatile> { typedef double const volatile type; };

}

#endif // #ifndef RTIBOOST_type_traits_floating_point_promotion_hpp_INCLUDED

