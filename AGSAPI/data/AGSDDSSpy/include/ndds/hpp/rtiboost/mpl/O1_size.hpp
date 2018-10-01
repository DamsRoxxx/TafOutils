
#ifndef RTIBOOST_MPL_O1_SIZE_HPP_INCLUDED
#define RTIBOOST_MPL_O1_SIZE_HPP_INCLUDED

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

#include <rtiboost/mpl/O1_size_fwd.hpp>
#include <rtiboost/mpl/sequence_tag.hpp>
#include <rtiboost/mpl/aux_/O1_size_impl.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>

namespace rtiboost { namespace mpl {

// returns sequence size if it's an O(1) operation; otherwise returns -1
template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct O1_size
    : O1_size_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1, O1_size, (Sequence))
};

RTIBOOST_MPL_AUX_NA_SPEC(1, O1_size)

}}

#endif // RTIBOOST_MPL_O1_SIZE_HPP_INCLUDED
