
#ifndef RTIBOOST_MPL_IDENTITY_HPP_INCLUDED
#define RTIBOOST_MPL_IDENTITY_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>

namespace rtiboost { namespace mpl {

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(T)
    >
struct identity
{
    typedef T type;
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1, identity, (T))
};

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(T)
    >
struct make_identity
{
    typedef identity<T> type;
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_identity, (T))
};

RTIBOOST_MPL_AUX_NA_SPEC_NO_ETI(1, identity)
RTIBOOST_MPL_AUX_NA_SPEC_NO_ETI(1, make_identity)

}}

#endif // RTIBOOST_MPL_IDENTITY_HPP_INCLUDED
