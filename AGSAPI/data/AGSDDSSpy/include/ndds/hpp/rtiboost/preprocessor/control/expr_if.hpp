# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef RTIBOOST_PREPROCESSOR_CONTROL_EXPR_IF_HPP
# define RTIBOOST_PREPROCESSOR_CONTROL_EXPR_IF_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/control/expr_iif.hpp>
# include <rtiboost/preprocessor/logical/bool.hpp>
#
# /* RTIBOOST_PP_EXPR_IF */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_EXPR_IF(cond, expr) RTIBOOST_PP_EXPR_IIF(RTIBOOST_PP_BOOL(cond), expr)
# else
#    define RTIBOOST_PP_EXPR_IF(cond, expr) RTIBOOST_PP_EXPR_IF_I(cond, expr)
#    define RTIBOOST_PP_EXPR_IF_I(cond, expr) RTIBOOST_PP_EXPR_IIF(RTIBOOST_PP_BOOL(cond), expr)
# endif
#
# endif
