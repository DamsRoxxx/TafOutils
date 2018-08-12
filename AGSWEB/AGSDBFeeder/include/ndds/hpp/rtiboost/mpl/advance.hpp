
#ifndef RTIBOOST_MPL_ADVANCE_HPP_INCLUDED
#define RTIBOOST_MPL_ADVANCE_HPP_INCLUDED

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

#include <rtiboost/mpl/advance_fwd.hpp>
#include <rtiboost/mpl/less.hpp>
#include <rtiboost/mpl/negate.hpp>
#include <rtiboost/mpl/long.hpp>
#include <rtiboost/mpl/if.hpp>
#include <rtiboost/mpl/tag.hpp>
#include <rtiboost/mpl/apply_wrap.hpp>
#include <rtiboost/mpl/aux_/advance_forward.hpp>
#include <rtiboost/mpl/aux_/advance_backward.hpp>
#include <rtiboost/mpl/aux_/value_wknd.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/nttp_decl.hpp>

namespace rtiboost { namespace mpl {

// default implementation for forward/bidirectional iterators
template< typename Tag >
struct advance_impl
{
    template< typename Iterator, typename N > struct apply
    {
        typedef typename less< N,long_<0> >::type backward_;
        typedef typename if_< backward_, negate<N>, N >::type offset_;

        typedef typename if_<
              backward_
            , aux::advance_backward< RTIBOOST_MPL_AUX_VALUE_WKND(offset_)::value >
            , aux::advance_forward< RTIBOOST_MPL_AUX_VALUE_WKND(offset_)::value >
            >::type f_;

        typedef typename apply_wrap1<f_,Iterator>::type type;
    };
};


template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(Iterator)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N)
    >
struct advance
    : advance_impl< typename tag<Iterator>::type >
        ::template apply<Iterator,N>
{
};

template<
      typename Iterator
    , RTIBOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct advance_c
    : advance_impl< typename tag<Iterator>::type >
        ::template apply<Iterator,long_<N> >
{
};

RTIBOOST_MPL_AUX_NA_SPEC(2, advance)

}}

#endif // RTIBOOST_MPL_ADVANCE_HPP_INCLUDED
