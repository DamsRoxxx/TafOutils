
//  (C) Copyright John Maddock 2005.  
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef RTIBOOST_TT_RANK_HPP_INCLUDED
#define RTIBOOST_TT_RANK_HPP_INCLUDED

#include <rtiboost/type_traits/integral_constant.hpp>

namespace rtiboost {

#if !defined( __CODEGEARC__ )

namespace detail{

template <class T, std::size_t N>
struct rank_imp
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = N);
};
#if !defined(RTIBOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
template <class T, std::size_t R, std::size_t N>
struct rank_imp<T[R], N>
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = (::rtiboost::detail::rank_imp<T, N+1>::value));
};

template <class T, std::size_t R, std::size_t N>
struct rank_imp<T const[R], N>
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = (::rtiboost::detail::rank_imp<T, N+1>::value));
};

template <class T, std::size_t R, std::size_t N>
struct rank_imp<T volatile[R], N>
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = (::rtiboost::detail::rank_imp<T, N+1>::value));
};

template <class T, std::size_t R, std::size_t N>
struct rank_imp<T const volatile[R], N>
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = (::rtiboost::detail::rank_imp<T, N+1>::value));
};

#if !RTIBOOST_WORKAROUND(__BORLANDC__, < 0x600) && !defined(__IBMCPP__) &&  !RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840))
template <class T, std::size_t N>
struct rank_imp<T[], N>
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = (::rtiboost::detail::rank_imp<T, N+1>::value));
};
template <class T, std::size_t N>
struct rank_imp<T const[], N>
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = (::rtiboost::detail::rank_imp<T, N+1>::value));
};
template <class T, std::size_t N>
struct rank_imp<T volatile[], N>
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = (::rtiboost::detail::rank_imp<T, N+1>::value));
};
template <class T, std::size_t N>
struct rank_imp<T const volatile[], N>
{
   RTIBOOST_STATIC_CONSTANT(std::size_t, value = (::rtiboost::detail::rank_imp<T, N+1>::value));
};
#endif
#endif
}

#endif // !defined( __CODEGEARC__ )

#if defined( __CODEGEARC__ )
template <class T> struct rank : public integral_constant<std::size_t, __array_rank(T)>{};
#else
template <class T> struct rank : public integral_constant<std::size_t, (::rtiboost::detail::rank_imp<T, 0>::value)>{};
#endif

} // namespace rtiboost

#endif // RTIBOOST_TT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
