
#ifndef RTIBOOST_MPL_BOOL_HPP_INCLUDED
#define RTIBOOST_MPL_BOOL_HPP_INCLUDED

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

#include <rtiboost/mpl/bool_fwd.hpp>
#include <rtiboost/mpl/integral_c_tag.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_
{
    RTIBOOST_STATIC_CONSTANT(bool, value = C_);
    typedef rtiboost_integral_c_tag tag;
    typedef bool_ type;
    typedef bool value_type;
    operator bool() const { return this->value; }
};

#if !defined(RTIBOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< bool C_ >
bool const bool_<C_>::value;
#endif

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // RTIBOOST_MPL_BOOL_HPP_INCLUDED
