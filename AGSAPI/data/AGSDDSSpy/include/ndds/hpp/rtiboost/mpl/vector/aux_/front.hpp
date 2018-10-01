
#ifndef RTIBOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED
#define RTIBOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/front_fwd.hpp>
#include <rtiboost/mpl/vector/aux_/at.hpp>
#include <rtiboost/mpl/vector/aux_/tag.hpp>
#include <rtiboost/mpl/aux_/nttp_decl.hpp>
#include <rtiboost/mpl/aux_/config/typeof.hpp>
#include <rtiboost/mpl/aux_/config/ctps.hpp>

namespace rtiboost { namespace mpl {

#if defined(RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<Vector,0>
    {
    };
};

#else

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< RTIBOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct front_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // RTIBOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED
