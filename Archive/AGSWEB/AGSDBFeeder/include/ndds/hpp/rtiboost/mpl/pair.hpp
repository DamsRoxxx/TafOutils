
#ifndef RTIBOOST_MPL_PAIR_HPP_INCLUDED
#define RTIBOOST_MPL_PAIR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/aux_/msvc_eti_base.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>
#include <rtiboost/mpl/aux_/config/eti.hpp>

namespace rtiboost { namespace mpl {

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(T1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(T2)
    >
struct pair
{
    typedef pair type;
    typedef T1 first;
    typedef T2 second;

    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2,pair,(T1,T2))
};

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(P)
    >
struct first
{
#if !defined(RTIBOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::first type;
#else
    typedef typename aux::msvc_eti_base<P>::first type;
#endif
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1,first,(P))
};

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(P)
    >
struct second
{
#if !defined(RTIBOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::second type;
#else
    typedef typename aux::msvc_eti_base<P>::second type;
#endif
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1,second,(P))
};


RTIBOOST_MPL_AUX_NA_SPEC_NO_ETI(2, pair)
RTIBOOST_MPL_AUX_NA_SPEC(1, first)
RTIBOOST_MPL_AUX_NA_SPEC(1, second)

}}

#endif // RTIBOOST_MPL_PAIR_HPP_INCLUDED
