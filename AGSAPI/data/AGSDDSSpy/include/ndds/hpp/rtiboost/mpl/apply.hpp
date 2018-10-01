
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_APPLY_HPP_INCLUDED
#define RTIBOOST_MPL_APPLY_HPP_INCLUDED

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
#   include <rtiboost/mpl/apply_fwd.hpp>
#   include <rtiboost/mpl/apply_wrap.hpp>
#   include <rtiboost/mpl/placeholders.hpp>
#   include <rtiboost/mpl/lambda.hpp>
#   include <rtiboost/mpl/aux_/na.hpp>
#   include <rtiboost/mpl/aux_/lambda_support.hpp>
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER apply.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#   include <rtiboost/mpl/aux_/config/lambda.hpp>
#   include <rtiboost/mpl/aux_/config/dtp.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>
#   include <rtiboost/mpl/aux_/config/eti.hpp>
#   include <rtiboost/mpl/aux_/config/msvc.hpp>
#   include <rtiboost/mpl/aux_/config/workaround.hpp>

#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

namespace rtiboost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define RTIBOOST_AUX778076_APPLY_PARAMS(param) \
    RTIBOOST_MPL_PP_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define RTIBOOST_AUX778076_APPLY_DEF_PARAMS(param, value) \
    RTIBOOST_MPL_PP_DEFAULT_PARAMS( \
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define RTIBOOST_AUX778076_APPLY_N_PARAMS(n, param) \
    RTIBOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(n, param) \
    RTIBOOST_PP_COMMA_IF(n) \
    RTIBOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define RTIBOOST_AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS(n, param, def) \
    RTIBOOST_PP_COMMA_IF(n) \
    RTIBOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
    /**/
    
#   define RTIBOOST_AUX778076_APPLY_N_SPEC_PARAMS(n, param) \
    RTIBOOST_MPL_PP_ENUM(RTIBOOST_PP_INC(n), param) \
    /**/


#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/apply.hpp>))
#include RTIBOOST_PP_ITERATE()

#   if !defined(RTIBOOST_MPL_CFG_NO_APPLY_TEMPLATE)
// real C++ version is already taken care of
#   if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// apply_count_args
#define RTIBOOST_AUX778076_COUNT_ARGS_PREFIX apply
#define RTIBOOST_AUX778076_COUNT_ARGS_DEFAULT na
#define RTIBOOST_AUX778076_COUNT_ARGS_ARITY RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
#include <rtiboost/mpl/aux_/count_args.hpp>
}


template<
      typename F, RTIBOOST_AUX778076_APPLY_DEF_PARAMS(typename T, na)
    >
struct apply
    : aux::apply_chooser< 
          aux::apply_count_args< RTIBOOST_AUX778076_APPLY_PARAMS(T) >::value
        >::template result_< F, RTIBOOST_AUX778076_APPLY_PARAMS(T) >::type
{
};

#   endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // RTIBOOST_MPL_CFG_NO_APPLY_TEMPLATE

#   undef RTIBOOST_AUX778076_APPLY_N_SPEC_PARAMS
#   undef RTIBOOST_AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS
#   undef RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS
#   undef RTIBOOST_AUX778076_APPLY_N_PARAMS
#   undef RTIBOOST_AUX778076_APPLY_DEF_PARAMS
#   undef RTIBOOST_AUX778076_APPLY_PARAMS

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_APPLY_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// RTIBOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // RTIBOOST_PP_IS_ITERATING
#if RTIBOOST_PP_ITERATION_DEPTH() == 1

#   define i_ RTIBOOST_PP_FRAME_ITERATION(1)

template<
      typename F RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(apply,i_)
#if !RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
    : RTIBOOST_PP_CAT(apply_wrap,i_)< 
          typename lambda<F>::type
        RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
        >
{
#else
{
    typedef typename RTIBOOST_PP_CAT(apply_wrap,i_)< 
          typename lambda<F>::type
        RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
        >::type type;
#endif
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(
          RTIBOOST_PP_INC(i_)
        , RTIBOOST_PP_CAT(apply,i_)
        , (F RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_,T))
        )
};


#if defined(RTIBOOST_MPL_CFG_MSVC_ETI_BUG)
/// workaround for ETI bug
template<>
struct RTIBOOST_PP_CAT(apply,i_)<RTIBOOST_AUX778076_APPLY_N_SPEC_PARAMS(i_, int)>
{
    typedef int type;
};
#endif

#   if !defined(RTIBOOST_MPL_CFG_NO_APPLY_TEMPLATE)
#   if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
/// primary template (not a specialization!)
template<
      typename F RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct apply
    : RTIBOOST_PP_CAT(apply,i_)< F RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, T) >
{
};
#else
template<
      typename F RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct apply< F RTIBOOST_AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS(i_, T, na) >
    : RTIBOOST_PP_CAT(apply,i_)< F RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, T) >
{
};
#endif

#   else // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if !defined(RTIBOOST_MPL_CFG_NO_APPLY_TEMPLATE)
namespace aux {

template<>
struct apply_chooser<i_>
{
    template<
          typename F, RTIBOOST_AUX778076_APPLY_PARAMS(typename T)
        >
    struct result_
    {
        typedef RTIBOOST_PP_CAT(apply,i_)<
              F RTIBOOST_AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
            > type;
    };
};

} // namespace aux
#endif

#   endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // RTIBOOST_MPL_CFG_NO_APPLY_TEMPLATE

#   undef i_

#endif // RTIBOOST_PP_ITERATION_DEPTH()
#endif // RTIBOOST_PP_IS_ITERATING
