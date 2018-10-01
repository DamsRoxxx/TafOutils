
#ifndef RTIBOOST_MPL_AT_HPP_INCLUDED
#define RTIBOOST_MPL_AT_HPP_INCLUDED

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

#include <rtiboost/mpl/at_fwd.hpp>
#include <rtiboost/mpl/aux_/at_impl.hpp>
#include <rtiboost/mpl/long.hpp>
#include <rtiboost/mpl/sequence_tag.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>
#include <rtiboost/mpl/aux_/nttp_decl.hpp>

namespace rtiboost { namespace mpl {

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N)
    >
struct at
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,N >
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2,at,(Sequence,N))
};

template<
      typename Sequence
    , RTIBOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct at_c
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,mpl::long_<N> >
{
};

RTIBOOST_MPL_AUX_NA_SPEC(2, at)

}}

#endif // RTIBOOST_MPL_AT_HPP_INCLUDED
