
#ifndef RTIBOOST_MPL_DISTANCE_HPP_INCLUDED
#define RTIBOOST_MPL_DISTANCE_HPP_INCLUDED

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

#include <rtiboost/mpl/distance_fwd.hpp>
#include <rtiboost/mpl/iter_fold.hpp>
#include <rtiboost/mpl/iterator_range.hpp>
#include <rtiboost/mpl/long.hpp>
#include <rtiboost/mpl/next.hpp>
#include <rtiboost/mpl/tag.hpp>
#include <rtiboost/mpl/apply_wrap.hpp>
#include <rtiboost/mpl/aux_/msvc_eti_base.hpp>
#include <rtiboost/mpl/aux_/value_wknd.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/config/forwarding.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>


namespace rtiboost { namespace mpl {

// default implementation for forward/bidirectional iterators
template< typename Tag > struct distance_impl
{
    template< typename First, typename Last > struct apply
#if !defined(RTIBOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::msvc_eti_base< typename iter_fold<
              iterator_range<First,Last>
            , mpl::long_<0>
            , next<>
            >::type >
    {
#else
    {
        typedef typename iter_fold<
              iterator_range<First,Last>
            , mpl::long_<0>
            , next<>
            >::type type;
        
        RTIBOOST_STATIC_CONSTANT(long, value =
              (iter_fold<
                  iterator_range<First,Last>
                , mpl::long_<0>
                , next<>
                >::type::value)
            );
#endif
    };
};

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(First)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(Last)
    >
struct distance
    : distance_impl< typename tag<First>::type >
        ::template apply<First, Last>
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2, distance, (First, Last))
};

RTIBOOST_MPL_AUX_NA_SPEC(2, distance)

}}

#endif // RTIBOOST_MPL_DISTANCE_HPP_INCLUDED
