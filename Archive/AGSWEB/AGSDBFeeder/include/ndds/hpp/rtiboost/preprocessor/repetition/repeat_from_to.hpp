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
# ifndef RTIBOOST_PREPROCESSOR_REPETITION_REPEAT_FROM_TO_HPP
# define RTIBOOST_PREPROCESSOR_REPETITION_REPEAT_FROM_TO_HPP
#
# include <rtiboost/preprocessor/arithmetic/add.hpp>
# include <rtiboost/preprocessor/arithmetic/sub.hpp>
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/control/while.hpp>
# include <rtiboost/preprocessor/debug/error.hpp>
# include <rtiboost/preprocessor/detail/auto_rec.hpp>
# include <rtiboost/preprocessor/repetition/repeat.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
# include <rtiboost/preprocessor/tuple/rem.hpp>
#
# /* RTIBOOST_PP_REPEAT_FROM_TO */
#
# if 0
#    define RTIBOOST_PP_REPEAT_FROM_TO(first, last, macro, data)
# endif
#
# define RTIBOOST_PP_REPEAT_FROM_TO RTIBOOST_PP_CAT(RTIBOOST_PP_REPEAT_FROM_TO_, RTIBOOST_PP_AUTO_REC(RTIBOOST_PP_REPEAT_P, 4))
#
# define RTIBOOST_PP_REPEAT_FROM_TO_1(f, l, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_D_1(RTIBOOST_PP_AUTO_REC(RTIBOOST_PP_WHILE_P, 256), f, l, m, dt)
# define RTIBOOST_PP_REPEAT_FROM_TO_2(f, l, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_D_2(RTIBOOST_PP_AUTO_REC(RTIBOOST_PP_WHILE_P, 256), f, l, m, dt)
# define RTIBOOST_PP_REPEAT_FROM_TO_3(f, l, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_D_3(RTIBOOST_PP_AUTO_REC(RTIBOOST_PP_WHILE_P, 256), f, l, m, dt)
# define RTIBOOST_PP_REPEAT_FROM_TO_4(f, l, m, dt) RTIBOOST_PP_ERROR(0x0003)
#
# define RTIBOOST_PP_REPEAT_FROM_TO_1ST RTIBOOST_PP_REPEAT_FROM_TO_1
# define RTIBOOST_PP_REPEAT_FROM_TO_2ND RTIBOOST_PP_REPEAT_FROM_TO_2
# define RTIBOOST_PP_REPEAT_FROM_TO_3RD RTIBOOST_PP_REPEAT_FROM_TO_3
#
# /* RTIBOOST_PP_REPEAT_FROM_TO_D */
#
# if 0
#    define RTIBOOST_PP_REPEAT_FROM_TO_D(d, first, last, macro, data)
# endif
#
# define RTIBOOST_PP_REPEAT_FROM_TO_D RTIBOOST_PP_CAT(RTIBOOST_PP_REPEAT_FROM_TO_D_, RTIBOOST_PP_AUTO_REC(RTIBOOST_PP_REPEAT_P, 4))
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_1(d, f, l, m, dt) RTIBOOST_PP_REPEAT_1(RTIBOOST_PP_SUB_D(d, l, f), RTIBOOST_PP_REPEAT_FROM_TO_M_1, (d, f, m, dt))
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_2(d, f, l, m, dt) RTIBOOST_PP_REPEAT_2(RTIBOOST_PP_SUB_D(d, l, f), RTIBOOST_PP_REPEAT_FROM_TO_M_2, (d, f, m, dt))
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_3(d, f, l, m, dt) RTIBOOST_PP_REPEAT_3(RTIBOOST_PP_SUB_D(d, l, f), RTIBOOST_PP_REPEAT_FROM_TO_M_3, (d, f, m, dt))
# else
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_1(d, f, l, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_D_1_I(d, f, l, m, dt)
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_2(d, f, l, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_D_2_I(d, f, l, m, dt)
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_3(d, f, l, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_D_3_I(d, f, l, m, dt)
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_1_I(d, f, l, m, dt) RTIBOOST_PP_REPEAT_1(RTIBOOST_PP_SUB_D(d, l, f), RTIBOOST_PP_REPEAT_FROM_TO_M_1, (d, f, m, dt))
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_2_I(d, f, l, m, dt) RTIBOOST_PP_REPEAT_2(RTIBOOST_PP_SUB_D(d, l, f), RTIBOOST_PP_REPEAT_FROM_TO_M_2, (d, f, m, dt))
#    define RTIBOOST_PP_REPEAT_FROM_TO_D_3_I(d, f, l, m, dt) RTIBOOST_PP_REPEAT_3(RTIBOOST_PP_SUB_D(d, l, f), RTIBOOST_PP_REPEAT_FROM_TO_M_3, (d, f, m, dt))
# endif
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_STRICT()
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_1(z, n, dfmd) RTIBOOST_PP_REPEAT_FROM_TO_M_1_IM(z, n, RTIBOOST_PP_TUPLE_REM_4 dfmd)
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_2(z, n, dfmd) RTIBOOST_PP_REPEAT_FROM_TO_M_2_IM(z, n, RTIBOOST_PP_TUPLE_REM_4 dfmd)
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_3(z, n, dfmd) RTIBOOST_PP_REPEAT_FROM_TO_M_3_IM(z, n, RTIBOOST_PP_TUPLE_REM_4 dfmd)
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_1_IM(z, n, im) RTIBOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, im)
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_2_IM(z, n, im) RTIBOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, im)
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_3_IM(z, n, im) RTIBOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, im)
# else
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_1(z, n, dfmd) RTIBOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, RTIBOOST_PP_TUPLE_ELEM(4, 0, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 1, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 2, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 3, dfmd))
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_2(z, n, dfmd) RTIBOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, RTIBOOST_PP_TUPLE_ELEM(4, 0, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 1, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 2, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 3, dfmd))
#    define RTIBOOST_PP_REPEAT_FROM_TO_M_3(z, n, dfmd) RTIBOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, RTIBOOST_PP_TUPLE_ELEM(4, 0, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 1, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 2, dfmd), RTIBOOST_PP_TUPLE_ELEM(4, 3, dfmd))
# endif
#
# define RTIBOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, d, f, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_M_1_II(z, RTIBOOST_PP_ADD_D(d, n, f), m, dt)
# define RTIBOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, d, f, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_M_2_II(z, RTIBOOST_PP_ADD_D(d, n, f), m, dt)
# define RTIBOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, d, f, m, dt) RTIBOOST_PP_REPEAT_FROM_TO_M_3_II(z, RTIBOOST_PP_ADD_D(d, n, f), m, dt)
#
# define RTIBOOST_PP_REPEAT_FROM_TO_M_1_II(z, n, m, dt) m(z, n, dt)
# define RTIBOOST_PP_REPEAT_FROM_TO_M_2_II(z, n, m, dt) m(z, n, dt)
# define RTIBOOST_PP_REPEAT_FROM_TO_M_3_II(z, n, m, dt) m(z, n, dt)
#
# endif
