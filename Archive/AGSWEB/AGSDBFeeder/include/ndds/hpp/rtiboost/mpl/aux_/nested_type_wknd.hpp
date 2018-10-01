
#ifndef RTIBOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/gcc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if RTIBOOST_WORKAROUND(RTIBOOST_MPL_CFG_GCC, RTIBOOST_TESTED_AT(0x0302)) \
    || RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x561)) \
    || RTIBOOST_WORKAROUND(__SUNPRO_CC, RTIBOOST_TESTED_AT(0x530)) \
    || RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840))

namespace rtiboost { namespace mpl { namespace aux {
template< typename T > struct nested_type_wknd
    : T::type
{
};
}}}

#if RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840))
#   define RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    aux::nested_type_wknd<T> \
/**/
#else
#   define RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    ::rtiboost::mpl::aux::nested_type_wknd<T> \
/**/
#endif

#else // !RTIBOOST_MPL_CFG_GCC et al.

#   define RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(T) T::type

#endif 

#endif // RTIBOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED
