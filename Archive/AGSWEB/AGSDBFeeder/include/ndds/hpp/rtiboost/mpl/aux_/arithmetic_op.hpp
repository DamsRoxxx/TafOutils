
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

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
#   include <rtiboost/mpl/integral_c.hpp>
#   include <rtiboost/mpl/aux_/largest_int.hpp>
#   include <rtiboost/mpl/aux_/value_wknd.hpp>
#endif

#if !defined(RTIBOOST_AUX778076_OP_PREFIX)
#   define RTIBOOST_AUX778076_OP_PREFIX RTIBOOST_AUX778076_OP_NAME
#endif

#include <rtiboost/mpl/aux_/numeric_op.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER RTIBOOST_AUX778076_OP_PREFIX.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/aux_/config/workaround.hpp>
#   include <rtiboost/preprocessor/cat.hpp>


namespace rtiboost { namespace mpl {

#if defined(RTIBOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
namespace aux {
template< typename T, T n1, T n2 >
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_PREFIX,_wknd)
{
    RTIBOOST_STATIC_CONSTANT(T, value = (n1 RTIBOOST_AUX778076_OP_TOKEN n2));
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct RTIBOOST_AUX778076_OP_IMPL_NAME<rtiboost_integral_c_tag,rtiboost_integral_c_tag>
{
    template< typename N1, typename N2 > struct apply
#if !defined(RTIBOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( RTIBOOST_MPL_AUX_VALUE_WKND(N1)::value
                  RTIBOOST_AUX778076_OP_TOKEN RTIBOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
#else
        : aux::RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_PREFIX,_wknd)<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type
#endif
    {
    };
};

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#undef RTIBOOST_AUX778076_OP_TAG_NAME
#undef RTIBOOST_AUX778076_OP_IMPL_NAME
#undef RTIBOOST_AUX778076_OP_ARITY
#undef RTIBOOST_AUX778076_OP_PREFIX
#undef RTIBOOST_AUX778076_OP_NAME
#undef RTIBOOST_AUX778076_OP_TOKEN
