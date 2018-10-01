
#ifndef RTIBOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED
#define RTIBOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

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

#include <rtiboost/mpl/empty_fwd.hpp>
#include <rtiboost/mpl/bool.hpp>
#include <rtiboost/mpl/vector/aux_/tag.hpp>
#include <rtiboost/mpl/aux_/config/typeof.hpp>
#include <rtiboost/mpl/aux_/config/ctps.hpp>
#include <rtiboost/type_traits/is_same.hpp>

namespace rtiboost { namespace mpl {

#if defined(RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct empty_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : is_same<
              typename Vector::lower_bound_
            , typename Vector::upper_bound_
            >
    {
    };
};

#else

template<>
struct empty_impl< aux::vector_tag<0> >
{
    template< typename Vector > struct apply
        : true_
    {
    };
};

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct empty_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // RTIBOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED
