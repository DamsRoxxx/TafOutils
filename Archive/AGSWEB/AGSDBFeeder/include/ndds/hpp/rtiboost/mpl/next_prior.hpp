
#ifndef RTIBOOST_MPL_NEXT_PRIOR_HPP_INCLUDED
#define RTIBOOST_MPL_NEXT_PRIOR_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/common_name_wknd.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>

namespace rtiboost { namespace mpl {

RTIBOOST_MPL_AUX_COMMON_NAME_WKND(next)
RTIBOOST_MPL_AUX_COMMON_NAME_WKND(prior)

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(T)
    >
struct next
{
    typedef typename T::next type;
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1,next,(T))
};

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(T)
    >
struct prior
{
    typedef typename T::prior type;
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1,prior,(T))
};

RTIBOOST_MPL_AUX_NA_SPEC(1, next)
RTIBOOST_MPL_AUX_NA_SPEC(1, prior)

}}

#endif // RTIBOOST_MPL_NEXT_PRIOR_HPP_INCLUDED
