
#ifndef RTIBOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
#define RTIBOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

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
#include <rtiboost/mpl/aux_/na.hpp>
#include <rtiboost/mpl/aux_/config/lambda.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   include <rtiboost/mpl/int.hpp>
#   include <rtiboost/mpl/aux_/lambda_arity_param.hpp>
#   include <rtiboost/mpl/aux_/template_arity_fwd.hpp>

namespace rtiboost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    RTIBOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = int_< aux::template_arity<T>::value >
        )
    >
struct lambda;

}}

#else // RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <rtiboost/mpl/bool.hpp>

namespace rtiboost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    , typename Protect = true_
    > 
struct lambda;

}}

#endif

#endif // RTIBOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
