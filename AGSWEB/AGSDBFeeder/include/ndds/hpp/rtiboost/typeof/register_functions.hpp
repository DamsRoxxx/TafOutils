// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_REGISTER_FUNCTIONS_HPP_INCLUDED
#define RTIBOOST_TYPEOF_REGISTER_FUNCTIONS_HPP_INCLUDED

#include <rtiboost/preprocessor/repetition/enum.hpp>
#include <rtiboost/preprocessor/repetition/enum_params.hpp>
#include <rtiboost/preprocessor/repetition/enum_trailing_params.hpp>
#include <rtiboost/preprocessor/cat.hpp>
#include <rtiboost/preprocessor/inc.hpp>
#include <rtiboost/preprocessor/dec.hpp>
#include <rtiboost/preprocessor/if.hpp>
#include <rtiboost/preprocessor/arithmetic/add.hpp>
#include <rtiboost/preprocessor/iteration/iterate.hpp>

#include RTIBOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

#ifndef RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY
#define RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY 10
#endif

enum 
{
    FUN_ID                          = RTIBOOST_TYPEOF_UNIQUE_ID(),
    FUN_PTR_ID                      = FUN_ID +  1 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    FUN_REF_ID                      = FUN_ID +  2 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    MEM_FUN_ID                      = FUN_ID +  3 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    CONST_MEM_FUN_ID                = FUN_ID +  4 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    VOLATILE_MEM_FUN_ID             = FUN_ID +  5 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    VOLATILE_CONST_MEM_FUN_ID       = FUN_ID +  6 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    FUN_VAR_ID                      = FUN_ID +  7 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    FUN_VAR_PTR_ID                  = FUN_ID +  8 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    FUN_VAR_REF_ID                  = FUN_ID +  9 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    MEM_FUN_VAR_ID                  = FUN_ID + 10 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    CONST_MEM_FUN_VAR_ID            = FUN_ID + 11 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    VOLATILE_MEM_FUN_VAR_ID         = FUN_ID + 12 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY),
    VOLATILE_CONST_MEM_FUN_VAR_ID   = FUN_ID + 13 * RTIBOOST_PP_INC(RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY)
};

RTIBOOST_TYPEOF_BEGIN_ENCODE_NS

# define RTIBOOST_PP_ITERATION_LIMITS (0, RTIBOOST_TYPEOF_LIMIT_FUNCTION_ARITY)
# define RTIBOOST_PP_FILENAME_1 <rtiboost/typeof/register_functions_iterate.hpp>
# include RTIBOOST_PP_ITERATE()

RTIBOOST_TYPEOF_END_ENCODE_NS

#endif//RTIBOOST_TYPEOF_REGISTER_FUNCTIONS_HPP_INCLUDED
