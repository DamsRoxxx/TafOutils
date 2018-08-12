
#ifndef RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/lambda.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) /**/
#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(i,name,params) /**/

#else

#   include <rtiboost/mpl/int_fwd.hpp>
#   include <rtiboost/mpl/aux_/yes_no.hpp>
#   include <rtiboost/mpl/aux_/na_fwd.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#   include <rtiboost/mpl/aux_/config/msvc.hpp>
#   include <rtiboost/mpl/aux_/config/workaround.hpp>

#   include <rtiboost/preprocessor/tuple/to_list.hpp>
#   include <rtiboost/preprocessor/list/for_each_i.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC(R,typedef_,i,param) \
    typedef_ param RTIBOOST_PP_CAT(arg,RTIBOOST_PP_INC(i)); \
    /**/

// agurt, 07/mar/03: restore an old revision for the sake of SGI MIPSpro C++
#if RTIBOOST_WORKAROUND(__EDG_VERSION__, <= 238) 

#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    typedef RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    RTIBOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , RTIBOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    struct rebind \
    { \
        template< RTIBOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
            : name< RTIBOOST_MPL_PP_PARAMS(i,U) > \
        { \
        }; \
    }; \
    /**/

#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    /**/

#elif RTIBOOST_WORKAROUND(__EDG_VERSION__, <= 244) && !defined(RTIBOOST_INTEL_CXX_VERSION)
// agurt, 18/jan/03: old EDG-based compilers actually enforce 11.4 para 9
// (in strict mode), so we have to provide an alternative to the 
// MSVC-optimized implementation

#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    typedef RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    RTIBOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , RTIBOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    struct rebind; \
/**/

#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
template< RTIBOOST_MPL_PP_PARAMS(i,typename T) > \
struct name<RTIBOOST_MPL_PP_PARAMS(i,T)>::rebind \
{ \
    template< RTIBOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
        : name< RTIBOOST_MPL_PP_PARAMS(i,U) > \
    { \
    }; \
/**/

#else // __EDG_VERSION__

namespace rtiboost { namespace mpl { namespace aux {
template< typename T > struct has_rebind_tag;
}}}

#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    typedef RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    RTIBOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , RTIBOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    friend class RTIBOOST_PP_CAT(name,_rebind); \
    typedef RTIBOOST_PP_CAT(name,_rebind) rebind; \
/**/

#if RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x610))
#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
template< RTIBOOST_MPL_PP_PARAMS(i,typename T) > \
::rtiboost::mpl::aux::yes_tag operator|( \
      ::rtiboost::mpl::aux::has_rebind_tag<int> \
    , name<RTIBOOST_MPL_PP_PARAMS(i,T)>* \
    ); \
::rtiboost::mpl::aux::no_tag operator|( \
      ::rtiboost::mpl::aux::has_rebind_tag<int> \
    , name< RTIBOOST_MPL_PP_ENUM(i,::rtiboost::mpl::na) >* \
    ); \
/**/
#elif !RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300)
#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
template< RTIBOOST_MPL_PP_PARAMS(i,typename T) > \
::rtiboost::mpl::aux::yes_tag operator|( \
      ::rtiboost::mpl::aux::has_rebind_tag<int> \
    , ::rtiboost::mpl::aux::has_rebind_tag< name<RTIBOOST_MPL_PP_PARAMS(i,T)> >* \
    ); \
/**/
#else
#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) /**/
#endif

#   if !defined(__BORLANDC__)
#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
class RTIBOOST_PP_CAT(name,_rebind) \
{ \
 public: \
    template< RTIBOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
        : name< RTIBOOST_MPL_PP_PARAMS(i,U) > \
    { \
    }; \
/**/
#   else
#   define RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
class RTIBOOST_PP_CAT(name,_rebind) \
{ \
 public: \
    template< RTIBOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
    { \
        typedef typename name< RTIBOOST_MPL_PP_PARAMS(i,U) >::type type; \
    }; \
/**/
#   endif // __BORLANDC__

#endif // __EDG_VERSION__

#endif // RTIBOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif // RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED
