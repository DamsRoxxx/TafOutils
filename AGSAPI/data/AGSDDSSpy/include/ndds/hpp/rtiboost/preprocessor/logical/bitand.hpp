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
# ifndef RTIBOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
# define RTIBOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
#
# /* RTIBOOST_PP_BITAND */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_BITAND(x, y) RTIBOOST_PP_BITAND_I(x, y)
# else
#    define RTIBOOST_PP_BITAND(x, y) RTIBOOST_PP_BITAND_OO((x, y))
#    define RTIBOOST_PP_BITAND_OO(par) RTIBOOST_PP_BITAND_I ## par
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_BITAND_I(x, y) RTIBOOST_PP_BITAND_ ## x ## y
# else
#    define RTIBOOST_PP_BITAND_I(x, y) RTIBOOST_PP_BITAND_ID(RTIBOOST_PP_BITAND_ ## x ## y)
#    define RTIBOOST_PP_BITAND_ID(res) res
# endif
#
# define RTIBOOST_PP_BITAND_00 0
# define RTIBOOST_PP_BITAND_01 0
# define RTIBOOST_PP_BITAND_10 0
# define RTIBOOST_PP_BITAND_11 1
#
# endif
