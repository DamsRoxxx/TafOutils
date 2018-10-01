
#ifndef RTIBOOST_MPL_BOOL_FWD_HPP_INCLUDED
#define RTIBOOST_MPL_BOOL_FWD_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/adl_barrier.hpp>

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_;

// shorcuts
typedef bool_<true> true_;
typedef bool_<false> false_;

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

RTIBOOST_MPL_AUX_ADL_BARRIER_DECL(bool_)
RTIBOOST_MPL_AUX_ADL_BARRIER_DECL(true_)
RTIBOOST_MPL_AUX_ADL_BARRIER_DECL(false_)

#endif // RTIBOOST_MPL_BOOL_FWD_HPP_INCLUDED
