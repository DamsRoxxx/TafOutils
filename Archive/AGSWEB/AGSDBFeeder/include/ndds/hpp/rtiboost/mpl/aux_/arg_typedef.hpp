
#ifndef RTIBOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/lambda.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    || RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840))
    
#   define RTIBOOST_MPL_AUX_ARG_TYPEDEF(T, name) typedef T name;

#else

#   define RTIBOOST_MPL_AUX_ARG_TYPEDEF(T, name) /**/

#endif

#endif // RTIBOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED
