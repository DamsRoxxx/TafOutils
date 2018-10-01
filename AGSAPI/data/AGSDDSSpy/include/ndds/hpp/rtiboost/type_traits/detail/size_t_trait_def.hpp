
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

// $Source$
// $Date$
// $Revision$

#include <rtiboost/type_traits/detail/template_arity_spec.hpp>
#include <rtiboost/type_traits/integral_constant.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>
#include <rtiboost/mpl/size_t.hpp>

#include <cstddef>

#if !defined(RTIBOOST_MSVC) || RTIBOOST_MSVC >= 1300
#   define RTIBOOST_TT_AUX_SIZE_T_BASE(C) public ::rtiboost::integral_constant<std::size_t,C>
#   define RTIBOOST_TT_AUX_SIZE_T_TRAIT_VALUE_DECL(C) /**/
#else
#   define RTIBOOST_TT_AUX_SIZE_T_BASE(C) public ::rtiboost::mpl::size_t<C>
#   define RTIBOOST_TT_AUX_SIZE_T_TRAIT_VALUE_DECL(C) \
    typedef ::rtiboost::mpl::size_t<C> base_; \
    using base_::value; \
    /**/
#endif


#define RTIBOOST_TT_AUX_SIZE_T_TRAIT_DEF1(trait,T,C) \
template< typename T > struct trait \
    : RTIBOOST_TT_AUX_SIZE_T_BASE(C) \
{ \
public:\
    RTIBOOST_TT_AUX_SIZE_T_TRAIT_VALUE_DECL(C) \
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1,trait,(T)) \
}; \
\
RTIBOOST_TT_AUX_TEMPLATE_ARITY_SPEC(1,trait) \
/**/

#define RTIBOOST_TT_AUX_SIZE_T_TRAIT_SPEC1(trait,spec,C) \
template<> struct trait<spec> \
    : RTIBOOST_TT_AUX_SIZE_T_BASE(C) \
{ \
public:\
    RTIBOOST_TT_AUX_SIZE_T_TRAIT_VALUE_DECL(C) \
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,trait,(spec)) \
}; \
/**/

#define RTIBOOST_TT_AUX_SIZE_T_TRAIT_PARTIAL_SPEC1_1(param,trait,spec,C) \
template< param > struct trait<spec> \
    : RTIBOOST_TT_AUX_SIZE_T_BASE(C) \
{ \
}; \
/**/
