
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
#   include <rtiboost/mpl/bool.hpp>
#   include <rtiboost/mpl/aux_/value_wknd.hpp>
#endif

#if !defined(RTIBOOST_AUX778076_OP_PREFIX)
#   define RTIBOOST_AUX778076_OP_PREFIX RTIBOOST_AUX778076_OP_NAME
#endif

#define RTIBOOST_AUX778076_OP_ARITY 2

#include <rtiboost/mpl/aux_/numeric_op.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER RTIBOOST_AUX778076_OP_PREFIX.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/aux_/config/integral.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

namespace rtiboost { namespace mpl {

// MSVC workaround: implement less in terms of greater
#if 0 RTIBOOST_AUX778076_OP_TOKEN 1 && !(1 RTIBOOST_AUX778076_OP_TOKEN 0) && !(0 RTIBOOST_AUX778076_OP_TOKEN 0)
#   define RTIBOOST_AUX778076_OP(N1, N2) \
    ( RTIBOOST_MPL_AUX_VALUE_WKND(N2)::value > RTIBOOST_MPL_AUX_VALUE_WKND(N1)::value ) \
/**/
#else
#   define RTIBOOST_AUX778076_OP(N1, N2) \
    ( RTIBOOST_MPL_AUX_VALUE_WKND(N1)::value \
          RTIBOOST_AUX778076_OP_TOKEN RTIBOOST_MPL_AUX_VALUE_WKND(N2)::value \
        ) \
/**/
#endif

template<>
struct RTIBOOST_AUX778076_OP_IMPL_NAME<rtiboost_integral_c_tag,rtiboost_integral_c_tag>
{
    template< typename N1, typename N2 > struct apply
#if !defined(RTIBOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
        : bool_< RTIBOOST_AUX778076_OP(N1, N2) >
    {
#else
    {
        RTIBOOST_STATIC_CONSTANT(bool, value = RTIBOOST_AUX778076_OP(N1, N2));
        typedef bool_<value> type;
#endif
    };
};

#undef RTIBOOST_AUX778076_OP

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#undef RTIBOOST_AUX778076_OP_TAG_NAME
#undef RTIBOOST_AUX778076_OP_IMPL_NAME
#undef RTIBOOST_AUX778076_OP_ARITY
#undef RTIBOOST_AUX778076_OP_PREFIX
#undef RTIBOOST_AUX778076_OP_NAME
#undef RTIBOOST_AUX778076_OP_TOKEN
