
#ifndef RTIBOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

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

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   include <rtiboost/mpl/next_prior.hpp>
#   include <rtiboost/mpl/apply.hpp>
#   include <rtiboost/mpl/deref.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <rtiboost/mpl/if.hpp>
#       include <rtiboost/type_traits/is_same.hpp>
#   endif
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER fold_impl.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   define RTIBOOST_AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX fold
#   include <rtiboost/mpl/aux_/fold_impl_body.hpp>

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED
