
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_APPLY_WRAP_HPP_INCLUDED
#define RTIBOOST_MPL_APPLY_WRAP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
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
#   include <rtiboost/mpl/aux_/arity.hpp>
#   include <rtiboost/mpl/aux_/has_apply.hpp>
#   include <rtiboost/mpl/aux_/na.hpp>
#   include <rtiboost/mpl/aux_/msvc_never_true.hpp>
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER apply_wrap.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/add.hpp>
#   include <rtiboost/mpl/aux_/config/bcc.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/config/dtp.hpp>
#   include <rtiboost/mpl/aux_/config/eti.hpp>
#   include <rtiboost/mpl/aux_/config/msvc.hpp>
#   include <rtiboost/mpl/aux_/config/workaround.hpp>

#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/logical/and.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>


namespace rtiboost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(n, param) \
    RTIBOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define RTIBOOST_AUX778076_APPLY_WRAP_SPEC_PARAMS(n, param) \
    RTIBOOST_MPL_PP_ENUM(RTIBOOST_PP_INC(n), param) \
    /**/


#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/apply_wrap.hpp>))
#include RTIBOOST_PP_ITERATE()


#   undef RTIBOOST_AUX778076_APPLY_WRAP_SPEC_PARAMS
#   undef RTIBOOST_AUX778076_APPLY_WRAP_PARAMS

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_APPLY_WRAP_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// RTIBOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // RTIBOOST_PP_IS_ITERATING
#if RTIBOOST_PP_ITERATION_DEPTH() == 1

#   define i_ RTIBOOST_PP_FRAME_ITERATION(1)

#   if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
// MSVC version

#define RTIBOOST_AUX778076_MSVC_DTW_NAME RTIBOOST_PP_CAT(msvc_apply,i_)
#define RTIBOOST_AUX778076_MSVC_DTW_ORIGINAL_NAME apply
#define RTIBOOST_AUX778076_MSVC_DTW_ARITY i_
#include <rtiboost/mpl/aux_/msvc_dtw.hpp>

template<
      typename F RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(apply_wrap,i_)
{
    // Metafunction forwarding confuses vc6
    typedef typename RTIBOOST_PP_CAT(msvc_apply,i_)<F>::template result_<
          RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type type;
};

#   elif defined(RTIBOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
// MWCW/Borland version

template<
      int N, typename F RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(apply_wrap_impl,i_);

#define RTIBOOST_PP_ITERATION_PARAMS_2 \
    (3,(0, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY - i_, <rtiboost/mpl/apply_wrap.hpp>))
#include RTIBOOST_PP_ITERATE()

template<
      typename F RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(apply_wrap,i_)
    : RTIBOOST_PP_CAT(apply_wrap_impl,i_)<
          ::rtiboost::mpl::aux::arity<F,i_>::value
        , F
        RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type
{
};

#   else
// ISO98 C++, with minor concession to vc7

template<
      typename F RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
#if i_ == 0
    , typename has_apply_ = typename aux::has_apply<F>::type
#endif
    >
struct RTIBOOST_PP_CAT(apply_wrap,i_)
// metafunction forwarding confuses MSVC 7.0
#if !RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1300)
    : F::template apply< RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, T) >
{
#else
{    
    typedef typename F::template apply<
         RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type type;
#endif
};

#if i_ == 0 && !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename F >
struct RTIBOOST_PP_CAT(apply_wrap,i_)<F,true_>
    : F::apply
{
};
#endif

#   endif // workarounds

#if defined(RTIBOOST_MPL_CFG_MSVC_ETI_BUG)
/// workaround for ETI bug
template<>
struct RTIBOOST_PP_CAT(apply_wrap,i_)<RTIBOOST_AUX778076_APPLY_WRAP_SPEC_PARAMS(i_, int)>
{
    typedef int type;
};
#endif

#   undef i_

///// iteration, depth == 2

#elif RTIBOOST_PP_ITERATION_DEPTH() == 2

#   define j_ RTIBOOST_PP_FRAME_ITERATION(2)

#if i_ == 0 && j_ == 0 \
    && defined(RTIBOOST_MPL_CFG_BCC590_WORKAROUNDS) \
    && !defined(RTIBOOST_MPL_CFG_NO_HAS_APPLY)

template< typename F, bool F_has_apply >
struct apply_wrap_impl0_bcb {
    typedef typename F::template apply< na > type;
};

template< typename F >
struct apply_wrap_impl0_bcb< F, true > {
    typedef typename F::apply type;
};

template<
      typename F RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(apply_wrap_impl,i_)<
          RTIBOOST_MPL_PP_ADD(i_, j_)
        , F
        RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >
{
    typedef apply_wrap_impl0_bcb< F, aux::has_apply< F >::value >::type type;
};
#else

template<
      typename F RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(apply_wrap_impl,i_)<
          RTIBOOST_MPL_PP_ADD(i_, j_)
        , F
        RTIBOOST_PP_COMMA_IF(i_) RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >
{
    typedef typename F::template apply<
          RTIBOOST_AUX778076_APPLY_WRAP_PARAMS(i_, T)
#if i_ == 0 && j_ == 0
/// since the defaults are "lost", we have to pass *something* even for nullary
/// metafunction classes
        na
#else
        RTIBOOST_PP_COMMA_IF(RTIBOOST_PP_AND(i_, j_)) RTIBOOST_MPL_PP_ENUM(j_, na)
#endif
        > type;
};

#endif

#   undef j_

#endif // RTIBOOST_PP_ITERATION_DEPTH()
#endif // RTIBOOST_PP_IS_ITERATING
