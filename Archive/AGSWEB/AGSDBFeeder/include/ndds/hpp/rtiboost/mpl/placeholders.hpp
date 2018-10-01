
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_PLACEHOLDERS_HPP_INCLUDED
#define RTIBOOST_MPL_PLACEHOLDERS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright Peter Dimov 2001-2003
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
#   include <rtiboost/mpl/arg.hpp>
#   include <rtiboost/mpl/aux_/adl_barrier.hpp>

#   if !defined(RTIBOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE)
#       define RTIBOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(type) \
        using ::RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::type; \
        /**/
#   else
#       define RTIBOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(type) /**/
#   endif

#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
 && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER placeholders.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/aux_/nttp_decl.hpp>
#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

// watch out for GNU gettext users, who #define _(x)
#if !defined(_) || defined(RTIBOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)
RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
typedef arg<-1> _;
RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace rtiboost { namespace mpl { 

RTIBOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(_)

namespace placeholders {
using RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::_;
}

}}
#endif

/// agurt, 17/mar/02: one more placeholder for the last 'apply#' 
/// specialization
#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY + 1, <rtiboost/mpl/placeholders.hpp>))
#include RTIBOOST_PP_ITERATE()

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_PLACEHOLDERS_HPP_INCLUDED

///// iteration

#else
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

typedef arg<i_> RTIBOOST_PP_CAT(_,i_);

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace rtiboost { namespace mpl { 

RTIBOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(RTIBOOST_PP_CAT(_,i_))

namespace placeholders {
using RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::RTIBOOST_PP_CAT(_,i_);
}

}}

#undef i_
#endif // RTIBOOST_PP_IS_ITERATING
