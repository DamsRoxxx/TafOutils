
#ifndef RTIBOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED
#define RTIBOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

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

#include <rtiboost/mpl/back_fwd.hpp>
#include <rtiboost/mpl/next_prior.hpp>
#include <rtiboost/mpl/vector/aux_/at.hpp>
#include <rtiboost/mpl/vector/aux_/tag.hpp>
#include <rtiboost/mpl/aux_/config/typeof.hpp>
#include <rtiboost/mpl/aux_/config/ctps.hpp>

namespace rtiboost { namespace mpl {

#if defined(RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<
              Vector
            , prior<typename Vector::size>::type::value
            >
    {
    };
};

#else

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long n_ >
struct back_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // RTIBOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED
