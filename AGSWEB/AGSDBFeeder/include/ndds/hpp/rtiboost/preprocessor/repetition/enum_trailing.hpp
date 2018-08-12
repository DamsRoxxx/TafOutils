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
# ifndef RTIBOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_HPP
# define RTIBOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_HPP
#
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/debug/error.hpp>
# include <rtiboost/preprocessor/detail/auto_rec.hpp>
# include <rtiboost/preprocessor/repetition/repeat.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
# include <rtiboost/preprocessor/tuple/rem.hpp>
#
# /* RTIBOOST_PP_ENUM_TRAILING */
#
# if 0
#    define RTIBOOST_PP_ENUM_TRAILING(count, macro, data)
# endif
#
# define RTIBOOST_PP_ENUM_TRAILING RTIBOOST_PP_CAT(RTIBOOST_PP_ENUM_TRAILING_, RTIBOOST_PP_AUTO_REC(RTIBOOST_PP_REPEAT_P, 4))
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ENUM_TRAILING_1(c, m, d) RTIBOOST_PP_REPEAT_1(c, RTIBOOST_PP_ENUM_TRAILING_M_1, (m, d))
#    define RTIBOOST_PP_ENUM_TRAILING_2(c, m, d) RTIBOOST_PP_REPEAT_2(c, RTIBOOST_PP_ENUM_TRAILING_M_2, (m, d))
#    define RTIBOOST_PP_ENUM_TRAILING_3(c, m, d) RTIBOOST_PP_REPEAT_3(c, RTIBOOST_PP_ENUM_TRAILING_M_3, (m, d))
# else
#    define RTIBOOST_PP_ENUM_TRAILING_1(c, m, d) RTIBOOST_PP_ENUM_TRAILING_1_I(c, m, d)
#    define RTIBOOST_PP_ENUM_TRAILING_2(c, m, d) RTIBOOST_PP_ENUM_TRAILING_2_I(c, m, d)
#    define RTIBOOST_PP_ENUM_TRAILING_3(c, m, d) RTIBOOST_PP_ENUM_TRAILING_3_I(c, m, d)
#    define RTIBOOST_PP_ENUM_TRAILING_1_I(c, m, d) RTIBOOST_PP_REPEAT_1(c, RTIBOOST_PP_ENUM_TRAILING_M_1, (m, d))
#    define RTIBOOST_PP_ENUM_TRAILING_2_I(c, m, d) RTIBOOST_PP_REPEAT_2(c, RTIBOOST_PP_ENUM_TRAILING_M_2, (m, d))
#    define RTIBOOST_PP_ENUM_TRAILING_3_I(c, m, d) RTIBOOST_PP_REPEAT_3(c, RTIBOOST_PP_ENUM_TRAILING_M_3, (m, d))
# endif
#
# define RTIBOOST_PP_ENUM_TRAILING_4(c, m, d) RTIBOOST_PP_ERROR(0x0003)
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_STRICT()
#    define RTIBOOST_PP_ENUM_TRAILING_M_1(z, n, md) RTIBOOST_PP_ENUM_TRAILING_M_1_IM(z, n, RTIBOOST_PP_TUPLE_REM_2 md)
#    define RTIBOOST_PP_ENUM_TRAILING_M_2(z, n, md) RTIBOOST_PP_ENUM_TRAILING_M_2_IM(z, n, RTIBOOST_PP_TUPLE_REM_2 md)
#    define RTIBOOST_PP_ENUM_TRAILING_M_3(z, n, md) RTIBOOST_PP_ENUM_TRAILING_M_3_IM(z, n, RTIBOOST_PP_TUPLE_REM_2 md)
#    define RTIBOOST_PP_ENUM_TRAILING_M_1_IM(z, n, im) RTIBOOST_PP_ENUM_TRAILING_M_1_I(z, n, im)
#    define RTIBOOST_PP_ENUM_TRAILING_M_2_IM(z, n, im) RTIBOOST_PP_ENUM_TRAILING_M_2_I(z, n, im)
#    define RTIBOOST_PP_ENUM_TRAILING_M_3_IM(z, n, im) RTIBOOST_PP_ENUM_TRAILING_M_3_I(z, n, im)
# else
#    define RTIBOOST_PP_ENUM_TRAILING_M_1(z, n, md) RTIBOOST_PP_ENUM_TRAILING_M_1_I(z, n, RTIBOOST_PP_TUPLE_ELEM(2, 0, md), RTIBOOST_PP_TUPLE_ELEM(2, 1, md))
#    define RTIBOOST_PP_ENUM_TRAILING_M_2(z, n, md) RTIBOOST_PP_ENUM_TRAILING_M_2_I(z, n, RTIBOOST_PP_TUPLE_ELEM(2, 0, md), RTIBOOST_PP_TUPLE_ELEM(2, 1, md))
#    define RTIBOOST_PP_ENUM_TRAILING_M_3(z, n, md) RTIBOOST_PP_ENUM_TRAILING_M_3_I(z, n, RTIBOOST_PP_TUPLE_ELEM(2, 0, md), RTIBOOST_PP_TUPLE_ELEM(2, 1, md))
# endif
#
# define RTIBOOST_PP_ENUM_TRAILING_M_1_I(z, n, m, d) , m(z, n, d)
# define RTIBOOST_PP_ENUM_TRAILING_M_2_I(z, n, m, d) , m(z, n, d)
# define RTIBOOST_PP_ENUM_TRAILING_M_3_I(z, n, m, d) , m(z, n, d)
#
# endif
