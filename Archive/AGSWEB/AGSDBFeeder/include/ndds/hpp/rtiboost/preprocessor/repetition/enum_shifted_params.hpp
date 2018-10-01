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
# ifndef RTIBOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_PARAMS_HPP
# define RTIBOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_PARAMS_HPP
#
# include <rtiboost/preprocessor/arithmetic/dec.hpp>
# include <rtiboost/preprocessor/arithmetic/inc.hpp>
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/punctuation/comma_if.hpp>
# include <rtiboost/preprocessor/repetition/repeat.hpp>
#
# /* RTIBOOST_PP_ENUM_SHIFTED_PARAMS */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ENUM_SHIFTED_PARAMS(count, param) RTIBOOST_PP_REPEAT(RTIBOOST_PP_DEC(count), RTIBOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# else
#    define RTIBOOST_PP_ENUM_SHIFTED_PARAMS(count, param) RTIBOOST_PP_ENUM_SHIFTED_PARAMS_I(count, param)
#    define RTIBOOST_PP_ENUM_SHIFTED_PARAMS_I(count, param) RTIBOOST_PP_REPEAT(RTIBOOST_PP_DEC(count), RTIBOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# endif
#
# define RTIBOOST_PP_ENUM_SHIFTED_PARAMS_M(z, n, param) RTIBOOST_PP_COMMA_IF(n) RTIBOOST_PP_CAT(param, RTIBOOST_PP_INC(n))
#
# /* RTIBOOST_PP_ENUM_SHIFTED_PARAMS_Z */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, count, param) RTIBOOST_PP_REPEAT_ ## z(RTIBOOST_PP_DEC(count), RTIBOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# else
#    define RTIBOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, count, param) RTIBOOST_PP_ENUM_SHIFTED_PARAMS_Z_I(z, count, param)
#    define RTIBOOST_PP_ENUM_SHIFTED_PARAMS_Z_I(z, count, param) RTIBOOST_PP_REPEAT_ ## z(RTIBOOST_PP_DEC(count), RTIBOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# endif
#
# endif
