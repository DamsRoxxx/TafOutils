
#ifndef RTIBOOST_MPL_AUX_ARITY_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_ARITY_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/dtp.hpp>

#if defined(RTIBOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)

#   include <rtiboost/mpl/aux_/nttp_decl.hpp>
#   include <rtiboost/mpl/aux_/config/static_constant.hpp>

namespace rtiboost { namespace mpl { namespace aux {

// agurt, 15/mar/02: it's possible to implement the template so that it will 
// "just work" and do not require any specialization, but not on the compilers
// that require the arity workaround in the first place
template< typename F, RTIBOOST_MPL_AUX_NTTP_DECL(int, N) >
struct arity
{
    RTIBOOST_STATIC_CONSTANT(int, value = N);
};

}}}

#endif // RTIBOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif // RTIBOOST_MPL_AUX_ARITY_HPP_INCLUDED
