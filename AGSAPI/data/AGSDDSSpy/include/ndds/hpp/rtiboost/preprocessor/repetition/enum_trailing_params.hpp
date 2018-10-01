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
# ifndef RTIBOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_PARAMS_HPP
# define RTIBOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_PARAMS_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/repetition/repeat.hpp>
#
# /* RTIBOOST_PP_ENUM_TRAILING_PARAMS */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ENUM_TRAILING_PARAMS(count, param) RTIBOOST_PP_REPEAT(count, RTIBOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# else
#    define RTIBOOST_PP_ENUM_TRAILING_PARAMS(count, param) RTIBOOST_PP_ENUM_TRAILING_PARAMS_I(count, param)
#    define RTIBOOST_PP_ENUM_TRAILING_PARAMS_I(count, param) RTIBOOST_PP_REPEAT(count, RTIBOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# endif
#
# define RTIBOOST_PP_ENUM_TRAILING_PARAMS_M(z, n, param) , param ## n
#
# /* RTIBOOST_PP_ENUM_TRAILING_PARAMS_Z */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ENUM_TRAILING_PARAMS_Z(z, count, param) RTIBOOST_PP_REPEAT_ ## z(count, RTIBOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# else
#    define RTIBOOST_PP_ENUM_TRAILING_PARAMS_Z(z, count, param) RTIBOOST_PP_ENUM_TRAILING_PARAMS_Z_I(z, count, param)
#    define RTIBOOST_PP_ENUM_TRAILING_PARAMS_Z_I(z, count, param) RTIBOOST_PP_REPEAT_ ## z(count, RTIBOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# endif
#
# endif
