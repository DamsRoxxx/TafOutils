
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

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   include <rtiboost/mpl/bool.hpp>
#   include <rtiboost/mpl/aux_/nested_type_wknd.hpp>
#   include <rtiboost/mpl/aux_/na_spec.hpp>
#   include <rtiboost/mpl/aux_/lambda_support.hpp>
#endif

#include <rtiboost/mpl/limits/arity.hpp>
#include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#include <rtiboost/mpl/aux_/preprocessor/ext_params.hpp>
#include <rtiboost/mpl/aux_/preprocessor/def_params_tail.hpp>
#include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#include <rtiboost/mpl/aux_/preprocessor/sub.hpp>
#include <rtiboost/mpl/aux_/config/ctps.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#include <rtiboost/preprocessor/dec.hpp>
#include <rtiboost/preprocessor/inc.hpp>
#include <rtiboost/preprocessor/cat.hpp>

namespace rtiboost { namespace mpl {

#   define RTIBOOST_AUX778076_PARAMS(param, sub) \
    RTIBOOST_MPL_PP_PARAMS( \
          RTIBOOST_MPL_PP_SUB(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, sub) \
        , param \
        ) \
    /**/

#   define RTIBOOST_AUX778076_SHIFTED_PARAMS(param, sub) \
    RTIBOOST_MPL_PP_EXT_PARAMS( \
          2, RTIBOOST_MPL_PP_SUB(RTIBOOST_PP_INC(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY), sub) \
        , param \
        ) \
    /**/

#   define RTIBOOST_AUX778076_SPEC_PARAMS(param) \
    RTIBOOST_MPL_PP_ENUM( \
          RTIBOOST_PP_DEC(RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY) \
        , param \
        ) \
    /**/

namespace aux {

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< bool C_, RTIBOOST_AUX778076_PARAMS(typename T, 1) >
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)
    : RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE1,_)
{
};

template< RTIBOOST_AUX778076_PARAMS(typename T, 1) >
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)< RTIBOOST_AUX778076_OP_VALUE2,RTIBOOST_AUX778076_PARAMS(T, 1) >
    : RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)<
          RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , RTIBOOST_AUX778076_SHIFTED_PARAMS(T, 1)
        , RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_)
        >
{
};

template<>
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)<
          RTIBOOST_AUX778076_OP_VALUE2
        , RTIBOOST_AUX778076_SPEC_PARAMS(RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_))
        >
    : RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_)
{
};

#else

template< bool C_ > struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)
{
    template< RTIBOOST_AUX778076_PARAMS(typename T, 1) > struct result_
        : RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE1,_)
    {
    };
};

template<> struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)<RTIBOOST_AUX778076_OP_VALUE2>
{
    template< RTIBOOST_AUX778076_PARAMS(typename T, 1) > struct result_
        : RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)< 
              RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< RTIBOOST_AUX778076_SHIFTED_PARAMS(T,1),RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_) >
    {
    };

#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1300)
    template<> struct result_<RTIBOOST_AUX778076_SPEC_PARAMS(RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_))>
        : RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_)
    {
    };
};
#else
};

template<>
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)<RTIBOOST_AUX778076_OP_VALUE2>
    ::result_< RTIBOOST_AUX778076_SPEC_PARAMS(RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_)) >
        : RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_)
{
};
#endif // RTIBOOST_MSVC == 1300

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(T1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(T2)
    RTIBOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename T, RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_VALUE2,_))
    >
struct RTIBOOST_AUX778076_OP_NAME
#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    : aux::RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)<
          RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , RTIBOOST_AUX778076_SHIFTED_PARAMS(T,0)
        >
#else
    : aux::RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,impl)< 
          RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        >::template result_< RTIBOOST_AUX778076_SHIFTED_PARAMS(T,0) >
#endif
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(
          RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
        , RTIBOOST_AUX778076_OP_NAME
        , (RTIBOOST_AUX778076_PARAMS(T, 0))
        )
};

RTIBOOST_MPL_AUX_NA_SPEC2(
      2
    , RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
    , RTIBOOST_AUX778076_OP_NAME
    )

}}

#undef RTIBOOST_AUX778076_SPEC_PARAMS
#undef RTIBOOST_AUX778076_SHIFTED_PARAMS
#undef RTIBOOST_AUX778076_PARAMS
#undef RTIBOOST_AUX778076_OP_NAME
#undef RTIBOOST_AUX778076_OP_VALUE1
#undef RTIBOOST_AUX778076_OP_VALUE2
