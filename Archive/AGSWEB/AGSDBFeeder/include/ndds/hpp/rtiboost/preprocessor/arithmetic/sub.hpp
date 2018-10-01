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
# ifndef RTIBOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
# define RTIBOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#
# include <rtiboost/preprocessor/arithmetic/dec.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/control/while.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
#
# /* RTIBOOST_PP_SUB */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SUB(x, y) RTIBOOST_PP_TUPLE_ELEM(2, 0, RTIBOOST_PP_WHILE(RTIBOOST_PP_SUB_P, RTIBOOST_PP_SUB_O, (x, y)))
# else
#    define RTIBOOST_PP_SUB(x, y) RTIBOOST_PP_SUB_I(x, y)
#    define RTIBOOST_PP_SUB_I(x, y) RTIBOOST_PP_TUPLE_ELEM(2, 0, RTIBOOST_PP_WHILE(RTIBOOST_PP_SUB_P, RTIBOOST_PP_SUB_O, (x, y)))
# endif
#
# define RTIBOOST_PP_SUB_P(d, xy) RTIBOOST_PP_TUPLE_ELEM(2, 1, xy)
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_SUB_O(d, xy) RTIBOOST_PP_SUB_O_I xy
# else
#    define RTIBOOST_PP_SUB_O(d, xy) RTIBOOST_PP_SUB_O_I(RTIBOOST_PP_TUPLE_ELEM(2, 0, xy), RTIBOOST_PP_TUPLE_ELEM(2, 1, xy))
# endif
#
# define RTIBOOST_PP_SUB_O_I(x, y) (RTIBOOST_PP_DEC(x), RTIBOOST_PP_DEC(y))
#
# /* RTIBOOST_PP_SUB_D */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SUB_D(d, x, y) RTIBOOST_PP_TUPLE_ELEM(2, 0, RTIBOOST_PP_WHILE_ ## d(RTIBOOST_PP_SUB_P, RTIBOOST_PP_SUB_O, (x, y)))
# else
#    define RTIBOOST_PP_SUB_D(d, x, y) RTIBOOST_PP_SUB_D_I(d, x, y)
#    define RTIBOOST_PP_SUB_D_I(d, x, y) RTIBOOST_PP_TUPLE_ELEM(2, 0, RTIBOOST_PP_WHILE_ ## d(RTIBOOST_PP_SUB_P, RTIBOOST_PP_SUB_O, (x, y)))
# endif
#
# endif
