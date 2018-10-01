
#ifndef RTIBOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1300)

namespace rtiboost { namespace mpl { namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

}}}

#endif // RTIBOOST_MSVC

#endif // RTIBOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
