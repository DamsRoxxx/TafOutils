
#ifndef RTIBOOST_MPL_AUX_ADL_BARRIER_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_ADL_BARRIER_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/adl.hpp>
#include <rtiboost/mpl/aux_/config/gcc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE)

#   define RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE rtiboost_mpl_
#   define RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN namespace rtiboost_mpl_ {
#   define RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE }
#   define RTIBOOST_MPL_AUX_ADL_BARRIER_DECL(type) \
    namespace rtiboost { namespace mpl { \
    using ::RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::type; \
    } } \
/**/

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
namespace RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE { namespace rtiboost_aux {} }
namespace rtiboost { namespace mpl { using namespace RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE; 
namespace rtiboost_aux { using namespace RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::rtiboost_aux; }
}}
#endif

#else // RTIBOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE

#   define RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE rtiboost::mpl
#   define RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN namespace rtiboost { namespace mpl {
#   define RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE }}
#   define RTIBOOST_MPL_AUX_ADL_BARRIER_DECL(type) /**/

#endif

#endif // RTIBOOST_MPL_AUX_ADL_BARRIER_HPP_INCLUDED
