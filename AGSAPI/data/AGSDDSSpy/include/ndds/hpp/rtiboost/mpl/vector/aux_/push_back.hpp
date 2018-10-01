
#ifndef RTIBOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
#define RTIBOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

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
#include <rtiboost/mpl/aux_/config/typeof.hpp>

#if defined(RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <rtiboost/mpl/vector/aux_/item.hpp>
#   include <rtiboost/mpl/vector/aux_/tag.hpp>

namespace rtiboost { namespace mpl {

template<>
struct push_back_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,0> type;
    };
};

}}

#endif 

#endif // RTIBOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
