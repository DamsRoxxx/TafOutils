
#ifndef RTIBOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

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
#include <rtiboost/mpl/begin_end.hpp>
#include <rtiboost/mpl/find.hpp>
#include <rtiboost/mpl/not.hpp>
#include <rtiboost/mpl/aux_/traits_lambda_spec.hpp>
#include <rtiboost/mpl/aux_/config/forwarding.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>

#include <rtiboost/type_traits/is_same.hpp>

namespace rtiboost { namespace mpl {

template< typename Tag >
struct contains_impl
{
    template< typename Sequence, typename T > struct apply
#if !defined(RTIBOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > >
    {
#else
    {
        typedef not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > > type;

        RTIBOOST_STATIC_CONSTANT(bool, value = 
              (not_< is_same<
                  typename find<Sequence,T>::type
                , typename end<Sequence>::type
                > >::value)
            );
#endif
    };
};

RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,contains_impl)

}}

#endif // RTIBOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED
