# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef RTIBOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
# define RTIBOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
#
# /* RTIBOOST_PP_EXPR_IIF */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_EXPR_IIF(bit, expr) RTIBOOST_PP_EXPR_IIF_I(bit, expr)
# else
#    define RTIBOOST_PP_EXPR_IIF(bit, expr) RTIBOOST_PP_EXPR_IIF_OO((bit, expr))
#    define RTIBOOST_PP_EXPR_IIF_OO(par) RTIBOOST_PP_EXPR_IIF_I ## par
# endif
#
# define RTIBOOST_PP_EXPR_IIF_I(bit, expr) RTIBOOST_PP_EXPR_IIF_ ## bit(expr)
#
# define RTIBOOST_PP_EXPR_IIF_0(expr)
# define RTIBOOST_PP_EXPR_IIF_1(expr) expr
#
# endif
