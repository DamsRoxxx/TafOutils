
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

#include <rtiboost/preprocessor/expr_if.hpp>
#include <rtiboost/preprocessor/inc.hpp>
#include <rtiboost/preprocessor/cat.hpp>

#if !defined(RTIBOOST_AUX778076_COUNT_ARGS_PARAM_NAME)
#   define RTIBOOST_AUX778076_COUNT_ARGS_PARAM_NAME T
#endif

#if !defined(RTIBOOST_AUX778076_COUNT_ARGS_TEMPLATE_PARAM)
#   define RTIBOOST_AUX778076_COUNT_ARGS_TEMPLATE_PARAM typename RTIBOOST_AUX778076_COUNT_ARGS_PARAM_NAME
#endif

// local macros, #undef-ined at the end of the header

#if !defined(RTIBOOST_AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES)

#   include <rtiboost/mpl/aux_/preprocessor/repeat.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>

#   define RTIBOOST_AUX778076_COUNT_ARGS_REPEAT RTIBOOST_MPL_PP_REPEAT
#   define RTIBOOST_AUX778076_COUNT_ARGS_PARAMS(param) \
    RTIBOOST_MPL_PP_PARAMS( \
          RTIBOOST_AUX778076_COUNT_ARGS_ARITY \
        , param \
        ) \
    /**/

#else

#   include <rtiboost/preprocessor/enum_shifted_params.hpp>
#   include <rtiboost/preprocessor/repeat.hpp>
#   include <rtiboost/preprocessor/inc.hpp>

#   define RTIBOOST_AUX778076_COUNT_ARGS_REPEAT RTIBOOST_PP_REPEAT
#   define RTIBOOST_AUX778076_COUNT_ARGS_PARAMS(param) \
    RTIBOOST_PP_ENUM_SHIFTED_PARAMS( \
          RTIBOOST_PP_INC(RTIBOOST_AUX778076_COUNT_ARGS_ARITY) \
        , param \
        ) \
    /**/

#endif // RTIBOOST_AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES


#define RTIBOOST_AUX778076_IS_ARG_TEMPLATE_NAME \
    RTIBOOST_PP_CAT(is_,RTIBOOST_PP_CAT(RTIBOOST_AUX778076_COUNT_ARGS_PREFIX,_arg)) \
/**/

#define RTIBOOST_AUX778076_COUNT_ARGS_FUNC(unused, i, param) \
    RTIBOOST_PP_EXPR_IF(i, +) \
    RTIBOOST_AUX778076_IS_ARG_TEMPLATE_NAME<RTIBOOST_PP_CAT(param,RTIBOOST_PP_INC(i))>::value \
/**/

// is_<xxx>_arg
template< RTIBOOST_AUX778076_COUNT_ARGS_TEMPLATE_PARAM >
struct RTIBOOST_AUX778076_IS_ARG_TEMPLATE_NAME
{
    RTIBOOST_STATIC_CONSTANT(bool, value = true);
};

template<>
struct RTIBOOST_AUX778076_IS_ARG_TEMPLATE_NAME<RTIBOOST_AUX778076_COUNT_ARGS_DEFAULT>
{
    RTIBOOST_STATIC_CONSTANT(bool, value = false);
};

// <xxx>_count_args
template<
      RTIBOOST_AUX778076_COUNT_ARGS_PARAMS(RTIBOOST_AUX778076_COUNT_ARGS_TEMPLATE_PARAM)
    >
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_COUNT_ARGS_PREFIX,_count_args)
{
    RTIBOOST_STATIC_CONSTANT(int, value = RTIBOOST_AUX778076_COUNT_ARGS_REPEAT(
          RTIBOOST_AUX778076_COUNT_ARGS_ARITY
        , RTIBOOST_AUX778076_COUNT_ARGS_FUNC
        , RTIBOOST_AUX778076_COUNT_ARGS_PARAM_NAME
        ));
};

#undef RTIBOOST_AUX778076_COUNT_ARGS_FUNC
#undef RTIBOOST_AUX778076_IS_ARG_TEMPLATE_NAME
#undef RTIBOOST_AUX778076_COUNT_ARGS_PARAMS
#undef RTIBOOST_AUX778076_COUNT_ARGS_REPEAT

#undef RTIBOOST_AUX778076_COUNT_ARGS_ARITY
#undef RTIBOOST_AUX778076_COUNT_ARGS_DEFAULT
#undef RTIBOOST_AUX778076_COUNT_ARGS_PREFIX
#undef RTIBOOST_AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES
#undef RTIBOOST_AUX778076_COUNT_ARGS_TEMPLATE_PARAM
#undef RTIBOOST_AUX778076_COUNT_ARGS_PARAM_NAME
