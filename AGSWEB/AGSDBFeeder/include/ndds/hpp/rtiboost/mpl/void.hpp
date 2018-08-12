
#ifndef RTIBOOST_MPL_VOID_HPP_INCLUDED
#define RTIBOOST_MPL_VOID_HPP_INCLUDED

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

#include <rtiboost/mpl/void_fwd.hpp>
#include <rtiboost/mpl/bool.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

//  [JDG Feb-4-2003] made void_ a complete type to allow it to be
//  instantiated so that it can be passed in as an object that can be
//  used to select an overloaded function. Possible use includes signaling
//  a zero arity functor evaluation call.
struct void_ { typedef void_ type; };

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace rtiboost { namespace mpl {

template< typename T >
struct is_void_
    : false_
{
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_void_<void_>
    : true_
{
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template< typename T >
struct is_not_void_
    : true_
{
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template<>
struct is_not_void_<void_>
    : false_
{
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
    using false_::value;
#endif
};

RTIBOOST_MPL_AUX_NA_SPEC(1, is_void_)
RTIBOOST_MPL_AUX_NA_SPEC(1, is_not_void_)

}}

#endif // RTIBOOST_MPL_VOID_HPP_INCLUDED
