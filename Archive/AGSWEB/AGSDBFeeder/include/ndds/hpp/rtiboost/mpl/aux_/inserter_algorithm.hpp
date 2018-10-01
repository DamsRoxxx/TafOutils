
#ifndef RTIBOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/back_inserter.hpp>
#include <rtiboost/mpl/front_inserter.hpp>
#include <rtiboost/mpl/push_back.hpp>
#include <rtiboost/mpl/push_front.hpp>
#include <rtiboost/mpl/back_inserter.hpp>
#include <rtiboost/mpl/front_inserter.hpp>
#include <rtiboost/mpl/clear.hpp>
#include <rtiboost/mpl/eval_if.hpp>
#include <rtiboost/mpl/if.hpp>
#include <rtiboost/mpl/aux_/na.hpp>
#include <rtiboost/mpl/aux_/common_name_wknd.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#include <rtiboost/mpl/aux_/preprocessor/default_params.hpp>
#include <rtiboost/mpl/aux_/config/ctps.hpp>

#include <rtiboost/preprocessor/arithmetic/dec.hpp>

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define RTIBOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(arity, name) \
RTIBOOST_MPL_AUX_COMMON_NAME_WKND(name) \
template< \
      RTIBOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct name \
    : aux::name##_impl<RTIBOOST_MPL_PP_PARAMS(arity, P)> \
{ \
}; \
\
template< \
      RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), typename P) \
    > \
struct name< RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P),na > \
    : if_< has_push_back< typename clear<P1>::type> \
        , aux::name##_impl< \
              RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::reverse_##name##_impl< \
              RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
\
template< \
      RTIBOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct reverse_##name \
    : aux::reverse_##name##_impl<RTIBOOST_MPL_PP_PARAMS(arity, P)> \
{ \
}; \
\
template< \
      RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), typename P) \
    > \
struct reverse_##name< RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P),na > \
    : if_< has_push_back<P1> \
        , aux::reverse_##name##_impl< \
              RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::name##_impl< \
              RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
RTIBOOST_MPL_AUX_NA_SPEC(arity, name) \
RTIBOOST_MPL_AUX_NA_SPEC(arity, reverse_##name) \
/**/

#else

#   define RTIBOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(arity, name) \
RTIBOOST_MPL_AUX_COMMON_NAME_WKND(name) \
template< \
      RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), typename P) \
    > \
struct def_##name##_impl \
    : if_< has_push_back<P1> \
        , aux::name##_impl< \
              RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::reverse_##name##_impl< \
              RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
\
template< \
      RTIBOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct name \
{ \
    typedef typename eval_if< \
          is_na<RTIBOOST_PP_CAT(P, arity)> \
        , def_##name##_impl<RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P)> \
        , aux::name##_impl<RTIBOOST_MPL_PP_PARAMS(arity, P)> \
        >::type type; \
}; \
\
template< \
      RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), typename P) \
    > \
struct def_reverse_##name##_impl \
    : if_< has_push_back<P1> \
        , aux::reverse_##name##_impl< \
              RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::name##_impl< \
              RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
template< \
      RTIBOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct reverse_##name \
{ \
    typedef typename eval_if< \
          is_na<RTIBOOST_PP_CAT(P, arity)> \
        , def_reverse_##name##_impl<RTIBOOST_MPL_PP_PARAMS(RTIBOOST_PP_DEC(arity), P)> \
        , aux::reverse_##name##_impl<RTIBOOST_MPL_PP_PARAMS(arity, P)> \
        >::type type; \
}; \
RTIBOOST_MPL_AUX_NA_SPEC(arity, name) \
RTIBOOST_MPL_AUX_NA_SPEC(arity, reverse_##name) \
/**/

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // RTIBOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED
