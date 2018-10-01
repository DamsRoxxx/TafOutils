
#ifndef RTIBOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED

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

#include <rtiboost/mpl/int.hpp>
#include <rtiboost/mpl/limits/arity.hpp>
#include <rtiboost/mpl/aux_/config/dtp.hpp>
#include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#include <rtiboost/mpl/aux_/arity.hpp>
#include <rtiboost/mpl/aux_/template_arity_fwd.hpp>
#include <rtiboost/mpl/aux_/config/ttp.hpp>
#include <rtiboost/mpl/aux_/config/lambda.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>

#if defined(RTIBOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define RTIBOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,type,name) \
namespace aux { \
template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N), RTIBOOST_MPL_PP_PARAMS(i,type T) > \
struct arity< \
      name< RTIBOOST_MPL_PP_PARAMS(i,T) > \
    , N \
    > \
{ \
    RTIBOOST_STATIC_CONSTANT(int \
        , value = RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        ); \
}; \
} \
/**/
#else
#   define RTIBOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,type,name) /**/
#endif

#   define RTIBOOST_MPL_AUX_ARITY_SPEC(i,name) \
    RTIBOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,typename,name) \
/**/


#if defined(RTIBOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   define RTIBOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(i, name) \
namespace aux { \
template< RTIBOOST_MPL_PP_PARAMS(i,typename T) > \
struct template_arity< name<RTIBOOST_MPL_PP_PARAMS(i,T)> > \
    : int_<i> \
{ \
}; \
} \
/**/
#else
#   define RTIBOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(i, name) /**/
#endif


#endif // RTIBOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED
