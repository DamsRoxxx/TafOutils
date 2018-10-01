
#ifndef RTIBOOST_MPL_PUSH_BACK_HPP_INCLUDED
#define RTIBOOST_MPL_PUSH_BACK_HPP_INCLUDED

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

#include <rtiboost/mpl/push_back_fwd.hpp>
#include <rtiboost/mpl/aux_/push_back_impl.hpp>
#include <rtiboost/mpl/sequence_tag.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>

namespace rtiboost { namespace mpl {

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_back
    : push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_back,(Sequence,T))
};


template< 
      typename RTIBOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_back
    : has_push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_back,(Sequence))
};


RTIBOOST_MPL_AUX_NA_SPEC(2, push_back)
RTIBOOST_MPL_AUX_NA_SPEC(1, has_push_back)

}}

#endif // RTIBOOST_MPL_PUSH_BACK_HPP_INCLUDED
