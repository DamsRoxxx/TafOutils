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
# ifndef RTIBOOST_PREPROCESSOR_REPETITION_ENUM_BINARY_PARAMS_HPP
# define RTIBOOST_PREPROCESSOR_REPETITION_ENUM_BINARY_PARAMS_HPP
#
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/punctuation/comma_if.hpp>
# include <rtiboost/preprocessor/repetition/repeat.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
# include <rtiboost/preprocessor/tuple/rem.hpp>
#
# /* RTIBOOST_PP_ENUM_BINARY_PARAMS */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS(count, p1, p2) RTIBOOST_PP_REPEAT(count, RTIBOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# else
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS(count, p1, p2) RTIBOOST_PP_ENUM_BINARY_PARAMS_I(count, p1, p2)
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_I(count, p1, p2) RTIBOOST_PP_REPEAT(count, RTIBOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# endif
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_STRICT()
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_M(z, n, pp) RTIBOOST_PP_ENUM_BINARY_PARAMS_M_IM(z, n, RTIBOOST_PP_TUPLE_REM_2 pp)
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_M_IM(z, n, im) RTIBOOST_PP_ENUM_BINARY_PARAMS_M_I(z, n, im)
# else
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_M(z, n, pp) RTIBOOST_PP_ENUM_BINARY_PARAMS_M_I(z, n, RTIBOOST_PP_TUPLE_ELEM(2, 0, pp), RTIBOOST_PP_TUPLE_ELEM(2, 1, pp))
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_M_I(z, n, p1, p2) RTIBOOST_PP_ENUM_BINARY_PARAMS_M_II(z, n, p1, p2)
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_M_II(z, n, p1, p2) RTIBOOST_PP_COMMA_IF(n) p1 ## n p2 ## n
# else
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_M_I(z, n, p1, p2) RTIBOOST_PP_COMMA_IF(n) RTIBOOST_PP_CAT(p1, n) RTIBOOST_PP_CAT(p2, n)
# endif
#
# /* RTIBOOST_PP_ENUM_BINARY_PARAMS_Z */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_Z(z, count, p1, p2) RTIBOOST_PP_REPEAT_ ## z(count, RTIBOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# else
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_Z(z, count, p1, p2) RTIBOOST_PP_ENUM_BINARY_PARAMS_Z_I(z, count, p1, p2)
#    define RTIBOOST_PP_ENUM_BINARY_PARAMS_Z_I(z, count, p1, p2) RTIBOOST_PP_REPEAT_ ## z(count, RTIBOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# endif
#
# endif
