
#ifndef RTIBOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED

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

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   include <rtiboost/mpl/lambda_fwd.hpp>
#   include <rtiboost/mpl/int.hpp>
#   include <rtiboost/mpl/bool.hpp>
#   include <rtiboost/mpl/aux_/na.hpp>
#   include <rtiboost/mpl/aux_/arity.hpp>
#   include <rtiboost/mpl/aux_/template_arity_fwd.hpp>
#endif

#include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#include <rtiboost/mpl/aux_/preprocessor/def_params_tail.hpp>
#include <rtiboost/mpl/aux_/lambda_arity_param.hpp>
#include <rtiboost/mpl/aux_/config/dtp.hpp>
#include <rtiboost/mpl/aux_/config/eti.hpp>
#include <rtiboost/mpl/aux_/nttp_decl.hpp>
#include <rtiboost/mpl/aux_/config/ttp.hpp>
#include <rtiboost/mpl/aux_/config/lambda.hpp>
#include <rtiboost/mpl/aux_/config/overload_resolution.hpp>


#define RTIBOOST_MPL_AUX_NA_PARAMS(i) \
    RTIBOOST_MPL_PP_ENUM(i, na) \
/**/

#if defined(RTIBOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define RTIBOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
namespace aux { \
template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N) > \
struct arity< \
          name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > \
        , N \
        > \
    : int_< RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY > \
{ \
}; \
} \
/**/
#else
#   define RTIBOOST_MPL_AUX_NA_SPEC_ARITY(i, name) /**/
#endif

#define RTIBOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
template<> \
struct name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > \
{ \
    template< \
          RTIBOOST_MPL_PP_PARAMS(i, typename T) \
        RTIBOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(i, typename T, na) \
        > \
    struct apply \
        : name< RTIBOOST_MPL_PP_PARAMS(i, T) > \
    { \
    }; \
}; \
/**/

#if defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   define RTIBOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
template<> \
struct lambda< \
      name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > \
    , void_ \
    , true_ \
    > \
{ \
    typedef false_ is_le; \
    typedef name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
template<> \
struct lambda< \
      name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > \
    , void_ \
    , false_ \
    > \
{ \
    typedef false_ is_le; \
    typedef name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
/**/
#else
#   define RTIBOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
template< typename Tag > \
struct lambda< \
      name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > \
    , Tag \
    RTIBOOST_MPL_AUX_LAMBDA_ARITY_PARAM(int_<-1>) \
    > \
{ \
    typedef false_ is_le; \
    typedef name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > result_; \
    typedef name< RTIBOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
/**/
#endif

#if defined(RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    || defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
        && defined(RTIBOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION)
#   define RTIBOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) \
namespace aux { \
template< RTIBOOST_MPL_PP_PARAMS(j, typename T) > \
struct template_arity< \
          name< RTIBOOST_MPL_PP_PARAMS(j, T) > \
        > \
    : int_<j> \
{ \
}; \
\
template<> \
struct template_arity< \
          name< RTIBOOST_MPL_PP_ENUM(i, na) > \
        > \
    : int_<-1> \
{ \
}; \
} \
/**/
#else
#   define RTIBOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) /**/
#endif

#if defined(RTIBOOST_MPL_CFG_MSVC_ETI_BUG)
#   define RTIBOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
template<> \
struct name< RTIBOOST_MPL_PP_ENUM(i, int) > \
{ \
    typedef int type; \
    enum { value = 0 }; \
}; \
/**/
#else
#   define RTIBOOST_MPL_AUX_NA_SPEC_ETI(i, name) /**/
#endif

#define RTIBOOST_MPL_AUX_NA_PARAM(param) param = na

#define RTIBOOST_MPL_AUX_NA_SPEC_NO_ETI(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, i, name) \
/**/

#define RTIBOOST_MPL_AUX_NA_SPEC(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_NO_ETI(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
/**/

#define RTIBOOST_MPL_AUX_NA_SPEC2(i, j, name) \
RTIBOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
RTIBOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) \
/**/


#endif // RTIBOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED
