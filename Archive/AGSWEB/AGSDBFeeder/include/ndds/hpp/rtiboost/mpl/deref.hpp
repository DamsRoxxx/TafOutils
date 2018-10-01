
#ifndef RTIBOOST_MPL_DEREF_HPP_INCLUDED
#define RTIBOOST_MPL_DEREF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/aux_/msvc_type.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>
#include <rtiboost/mpl/aux_/config/eti.hpp>

namespace rtiboost { namespace mpl {

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct deref
{
#if !defined(RTIBOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename Iterator::type type;
#else
    typedef typename aux::msvc_type<Iterator>::type type;
#endif
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1,deref,(Iterator))
};

RTIBOOST_MPL_AUX_NA_SPEC(1, deref)

}}

#endif // RTIBOOST_MPL_DEREF_HPP_INCLUDED
