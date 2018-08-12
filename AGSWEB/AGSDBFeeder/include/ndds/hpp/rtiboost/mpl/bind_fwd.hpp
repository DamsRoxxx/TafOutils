
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_BIND_FWD_HPP_INCLUDED
#define RTIBOOST_MPL_BIND_FWD_HPP_INCLUDED

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
#   include <rtiboost/mpl/aux_/na.hpp>
#endif

#include <rtiboost/mpl/aux_/config/bind.hpp>
#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER bind_fwd.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <rtiboost/mpl/aux_/config/dmc_ambiguous_ctps.hpp>

#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

namespace rtiboost { namespace mpl {

// local macros, #undef-ined at the end of the header

#   if defined(RTIBOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)
#       define RTIBOOST_AUX778076_DMC_PARAM() , int dummy_ = 0
#   else
#       define RTIBOOST_AUX778076_DMC_PARAM()
#   endif

#   define RTIBOOST_AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    RTIBOOST_MPL_PP_DEFAULT_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    RTIBOOST_AUX778076_DMC_PARAM() \
    /**/

#   define RTIBOOST_AUX778076_BIND_N_PARAMS(n, param) \
    RTIBOOST_PP_COMMA_IF(n) RTIBOOST_MPL_PP_PARAMS(n, param) \
    RTIBOOST_AUX778076_DMC_PARAM() \
    /**/

#if !defined(RTIBOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, RTIBOOST_AUX778076_BIND_DEFAULT_PARAMS(typename T, na)
    >
struct bind;
#endif

#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/bind_fwd.hpp>))
#include RTIBOOST_PP_ITERATE()

#   undef RTIBOOST_AUX778076_BIND_N_PARAMS
#   undef RTIBOOST_AUX778076_BIND_DEFAULT_PARAMS
#   undef RTIBOOST_AUX778076_DMC_PARAM
}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_BIND_FWD_HPP_INCLUDED

///// iteration

#else
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

template<
      typename F RTIBOOST_AUX778076_BIND_N_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(bind,i_);

#undef i_
#endif // RTIBOOST_PP_IS_ITERATING
