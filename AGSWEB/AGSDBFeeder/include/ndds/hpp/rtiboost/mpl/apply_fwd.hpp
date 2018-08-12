
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_APPLY_FWD_HPP_INCLUDED
#define RTIBOOST_MPL_APPLY_FWD_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER apply_fwd.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>

#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

// agurt, 15/jan/02: top-level 'apply' template gives an ICE on MSVC
// (for known reasons)
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
#   define RTIBOOST_MPL_CFG_NO_APPLY_TEMPLATE
#endif

namespace rtiboost { namespace mpl {

// local macro, #undef-ined at the end of the header
#   define RTIBOOST_AUX778076_APPLY_DEF_PARAMS(param, value) \
    RTIBOOST_MPL_PP_DEFAULT_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(n, param) \
    RTIBOOST_PP_COMMA_IF(n) \
    RTIBOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   if !defined(RTIBOOST_MPL_CFG_NO_APPLY_TEMPLATE)

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// forward declaration
template<
      typename F, RTIBOOST_AUX778076_APPLY_DEF_PARAMS(typename T, na)
    >
struct apply;
#else
namespace aux {
template< RTIBOOST_AUX_NTTP_DECL(int, arity_) > struct apply_chooser;
}
#endif

#   endif // RTIBOOST_MPL_CFG_NO_APPLY_TEMPLATE

#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/apply_fwd.hpp>))
#include RTIBOOST_PP_ITERATE()


#   undef RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS
#   undef RTIBOOST_AUX778076_APPLY_DEF_PARAMS

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_APPLY_FWD_HPP_INCLUDED

///// iteration

#else
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

template<
      typename F RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(apply,i_);

#undef i_
#endif // RTIBOOST_PP_IS_ITERATING
