
#ifndef RTIBOOST_MPL_SIZE_HPP_INCLUDED
#define RTIBOOST_MPL_SIZE_HPP_INCLUDED

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

#include <rtiboost/mpl/size_fwd.hpp>
#include <rtiboost/mpl/sequence_tag.hpp>
#include <rtiboost/mpl/aux_/size_impl.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>
#include <rtiboost/mpl/aux_/msvc_eti_base.hpp>

namespace rtiboost { namespace mpl {

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct size
    : aux::msvc_eti_base<
        typename size_impl< typename sequence_tag<Sequence>::type >
            ::template apply< Sequence >::type
      >::type
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1, size, (Sequence))
};

RTIBOOST_MPL_AUX_NA_SPEC(1, size)

}}

#endif // RTIBOOST_MPL_SIZE_HPP_INCLUDED
