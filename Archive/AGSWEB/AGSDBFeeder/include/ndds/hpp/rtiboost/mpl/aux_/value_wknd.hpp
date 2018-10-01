
#ifndef RTIBOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/aux_/static_cast.hpp>
#include <rtiboost/mpl/aux_/config/integral.hpp>
#include <rtiboost/mpl/aux_/config/eti.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if defined(RTIBOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS) \
    || defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG)

#   include <rtiboost/mpl/int.hpp>

namespace rtiboost { namespace mpl { namespace aux {
template< typename C_ > struct value_wknd
    : C_
{
};

#if defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct value_wknd<int>
    : int_<1>
{
    using int_<1>::value;
};
#endif
}}}


#if !defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG)
#   define RTIBOOST_MPL_AUX_VALUE_WKND(C) \
    ::RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::aux::value_wknd< C > \
/**/
#    define RTIBOOST_MPL_AUX_MSVC_VALUE_WKND(C) RTIBOOST_MPL_AUX_VALUE_WKND(C)
#else
#   define RTIBOOST_MPL_AUX_VALUE_WKND(C) C
#   define RTIBOOST_MPL_AUX_MSVC_VALUE_WKND(C) \
    ::rtiboost::mpl::aux::value_wknd< C > \
/**/
#endif

#else // RTIBOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS

#   define RTIBOOST_MPL_AUX_VALUE_WKND(C) C
#   define RTIBOOST_MPL_AUX_MSVC_VALUE_WKND(C) C

#endif

#if RTIBOOST_WORKAROUND(__EDG_VERSION__, <= 238)
#   define RTIBOOST_MPL_AUX_NESTED_VALUE_WKND(T, C) \
    RTIBOOST_MPL_AUX_STATIC_CAST(T, C::value) \
/**/
#else
#   define RTIBOOST_MPL_AUX_NESTED_VALUE_WKND(T, C) \
    RTIBOOST_MPL_AUX_VALUE_WKND(C)::value \
/**/
#endif


namespace rtiboost { namespace mpl { namespace aux {

template< typename T > struct value_type_wknd
{
    typedef typename T::value_type type;
};

#if defined(RTIBOOST_MPL_CFG_MSVC_ETI_BUG)
template<> struct value_type_wknd<int>
{
    typedef int type;
};
#endif

}}}

#endif // RTIBOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
