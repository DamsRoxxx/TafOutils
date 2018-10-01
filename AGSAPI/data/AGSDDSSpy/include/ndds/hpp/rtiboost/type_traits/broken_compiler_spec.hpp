
//  Copyright 2001-2003 Aleksey Gurtovoy.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_BROKEN_COMPILER_SPEC_HPP_INCLUDED
#define RTIBOOST_TT_BROKEN_COMPILER_SPEC_HPP_INCLUDED

#include <rtiboost/mpl/aux_/lambda_support.hpp>
#include <rtiboost/config.hpp>

// these are needed regardless of RTIBOOST_TT_NO_BROKEN_COMPILER_SPEC 
#if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
namespace rtiboost { namespace detail {
template< typename T > struct remove_const_impl     { typedef T type; };
template< typename T > struct remove_volatile_impl  { typedef T type; };
template< typename T > struct remove_pointer_impl   { typedef T type; };
template< typename T > struct remove_reference_impl { typedef T type; };
typedef int invoke_RTIBOOST_TT_BROKEN_COMPILER_SPEC_outside_all_namespaces;
}}
#endif

// agurt, 27/jun/03: disable the workaround if user defined 
// RTIBOOST_TT_NO_BROKEN_COMPILER_SPEC
#if    !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    || defined(RTIBOOST_TT_NO_BROKEN_COMPILER_SPEC)

#   define RTIBOOST_TT_BROKEN_COMPILER_SPEC(T) /**/

#else

// same as RTIBOOST_TT_AUX_TYPE_TRAIT_IMPL_SPEC1 macro, except that it
// never gets #undef-ined
#   define RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(trait,spec,result) \
template<> struct trait##_impl<spec> \
{ \
    typedef result type; \
}; \
/**/

#   define RTIBOOST_TT_AUX_REMOVE_CONST_VOLATILE_RANK1_SPEC(T)                         \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_const,T const,T)                    \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_const,T const volatile,T volatile)  \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_volatile,T volatile,T)              \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_volatile,T const volatile,T const)  \
    /**/

#   define RTIBOOST_TT_AUX_REMOVE_PTR_REF_RANK_1_SPEC(T)                               \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_pointer,T*,T)                       \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_pointer,T*const,T)                  \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_pointer,T*volatile,T)               \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_pointer,T*const volatile,T)         \
    RTIBOOST_TT_AUX_BROKEN_TYPE_TRAIT_SPEC1(remove_reference,T&,T)                     \
    /**/

#   define RTIBOOST_TT_AUX_REMOVE_PTR_REF_RANK_2_SPEC(T)                               \
    RTIBOOST_TT_AUX_REMOVE_PTR_REF_RANK_1_SPEC(T)                                      \
    RTIBOOST_TT_AUX_REMOVE_PTR_REF_RANK_1_SPEC(T const)                                \
    RTIBOOST_TT_AUX_REMOVE_PTR_REF_RANK_1_SPEC(T volatile)                             \
    RTIBOOST_TT_AUX_REMOVE_PTR_REF_RANK_1_SPEC(T const volatile)                       \
    /**/

#   define RTIBOOST_TT_AUX_REMOVE_ALL_RANK_1_SPEC(T)                                   \
    RTIBOOST_TT_AUX_REMOVE_PTR_REF_RANK_2_SPEC(T)                                      \
    RTIBOOST_TT_AUX_REMOVE_CONST_VOLATILE_RANK1_SPEC(T)                                \
    /**/

#   define RTIBOOST_TT_AUX_REMOVE_ALL_RANK_2_SPEC(T)                                   \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_1_SPEC(T*)                                         \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_1_SPEC(T const*)                                   \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_1_SPEC(T volatile*)                                \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_1_SPEC(T const volatile*)                          \
    /**/

#   define RTIBOOST_TT_BROKEN_COMPILER_SPEC(T)                                         \
    namespace rtiboost { namespace detail {                                            \
    typedef invoke_RTIBOOST_TT_BROKEN_COMPILER_SPEC_outside_all_namespaces             \
      please_invoke_RTIBOOST_TT_BROKEN_COMPILER_SPEC_outside_all_namespaces;           \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_1_SPEC(T)                                          \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_2_SPEC(T)                                          \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_2_SPEC(T*)                                         \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_2_SPEC(T const*)                                   \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_2_SPEC(T volatile*)                                \
    RTIBOOST_TT_AUX_REMOVE_ALL_RANK_2_SPEC(T const volatile*)                          \
    }}                                                                              \
    /**/

#   include <rtiboost/type_traits/detail/type_trait_undef.hpp>

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

RTIBOOST_TT_BROKEN_COMPILER_SPEC(bool)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(char)
#ifndef RTIBOOST_NO_INTRINSIC_WCHAR_T
RTIBOOST_TT_BROKEN_COMPILER_SPEC(wchar_t)
#endif
RTIBOOST_TT_BROKEN_COMPILER_SPEC(signed char)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(unsigned char)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(signed short)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(unsigned short)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(signed int)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(unsigned int)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(signed long)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(unsigned long)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(float)
RTIBOOST_TT_BROKEN_COMPILER_SPEC(double)
//RTIBOOST_TT_BROKEN_COMPILER_SPEC(long double)

// for backward compatibility
#define RTIBOOST_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION(T) \
    RTIBOOST_TT_BROKEN_COMPILER_SPEC(T) \
/**/

#endif // RTIBOOST_TT_BROKEN_COMPILER_SPEC_HPP_INCLUDED
