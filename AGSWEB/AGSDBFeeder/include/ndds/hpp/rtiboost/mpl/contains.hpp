
#ifndef RTIBOOST_MPL_CONTAINS_HPP_INCLUDED
#define RTIBOOST_MPL_CONTAINS_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/contains_fwd.hpp>
#include <rtiboost/mpl/sequence_tag.hpp>
#include <rtiboost/mpl/aux_/contains_impl.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>

namespace rtiboost { namespace mpl {

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(T)
    >
struct contains
    : contains_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2,contains,(Sequence,T))
};

RTIBOOST_MPL_AUX_NA_SPEC(2, contains)

}}

#endif // RTIBOOST_MPL_CONTAINS_HPP_INCLUDED
