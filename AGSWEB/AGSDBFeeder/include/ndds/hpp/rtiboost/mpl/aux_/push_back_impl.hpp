
#ifndef RTIBOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED

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

#include <rtiboost/mpl/push_back_fwd.hpp>
#include <rtiboost/mpl/assert.hpp>
#include <rtiboost/mpl/aux_/has_type.hpp>
#include <rtiboost/mpl/aux_/traits_lambda_spec.hpp>
#include <rtiboost/mpl/aux_/config/forwarding.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>

#include <rtiboost/type_traits/is_same.hpp>

namespace rtiboost { namespace mpl {

struct has_push_back_arg {};

// agurt 05/feb/04: no default implementation; the stub definition is needed 
// to enable the default 'has_push_back' implementation below
template< typename Tag >
struct push_back_impl
{
    template< typename Sequence, typename T > struct apply
    {
        // should be instantiated only in the context of 'has_push_back_impl';
        // if you've got an assert here, you are requesting a 'push_back' 
        // specialization that doesn't exist.
        RTIBOOST_MPL_ASSERT_MSG(
              ( rtiboost::is_same< T, has_push_back_arg >::value )
            , REQUESTED_PUSH_BACK_SPECIALIZATION_FOR_SEQUENCE_DOES_NOT_EXIST
            , ( Sequence )
            );
    };
};

template< typename Tag >
struct has_push_back_impl
{
    template< typename Seq > struct apply
#if !defined(RTIBOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::has_type< push_back< Seq, has_push_back_arg > >
    {
#else
    {
        typedef aux::has_type< push_back< Seq, has_push_back_arg > > type;
        RTIBOOST_STATIC_CONSTANT(bool, value = 
              (aux::has_type< push_back< Seq, has_push_back_arg > >::value)
            );
#endif
    };
};

RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, push_back_impl)
RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, has_push_back_impl)

}}

#endif // RTIBOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED
