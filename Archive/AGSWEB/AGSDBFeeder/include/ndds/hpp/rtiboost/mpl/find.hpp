
#ifndef RTIBOOST_MPL_FIND_HPP_INCLUDED
#define RTIBOOST_MPL_FIND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/find_if.hpp>
#include <rtiboost/mpl/same_as.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>

namespace rtiboost { namespace mpl {

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(T)
    >
struct find
    : find_if< Sequence,same_as<T> >
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2,find,(Sequence,T))
};

RTIBOOST_MPL_AUX_NA_SPEC(2, find)

}}

#endif // RTIBOOST_MPL_FIND_HPP_INCLUDED
