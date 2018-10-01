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
# ifndef RTIBOOST_PREPROCESSOR_LIST_LIST_FOR_EACH_I_HPP
# define RTIBOOST_PREPROCESSOR_LIST_LIST_FOR_EACH_I_HPP
#
# include <rtiboost/preprocessor/arithmetic/inc.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/list/adt.hpp>
# include <rtiboost/preprocessor/repetition/for.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
# include <rtiboost/preprocessor/tuple/rem.hpp>
#
# /* RTIBOOST_PP_LIST_FOR_EACH_I */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG() && ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_LIST_FOR_EACH_I(macro, data, list) RTIBOOST_PP_FOR((macro, data, list, 0), RTIBOOST_PP_LIST_FOR_EACH_I_P, RTIBOOST_PP_LIST_FOR_EACH_I_O, RTIBOOST_PP_LIST_FOR_EACH_I_M)
# else
#    define RTIBOOST_PP_LIST_FOR_EACH_I(macro, data, list) RTIBOOST_PP_LIST_FOR_EACH_I_I(macro, data, list)
#    define RTIBOOST_PP_LIST_FOR_EACH_I_I(macro, data, list) RTIBOOST_PP_FOR((macro, data, list, 0), RTIBOOST_PP_LIST_FOR_EACH_I_P, RTIBOOST_PP_LIST_FOR_EACH_I_O, RTIBOOST_PP_LIST_FOR_EACH_I_M)
# endif
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_STRICT()
#    define RTIBOOST_PP_LIST_FOR_EACH_I_P(r, x) RTIBOOST_PP_LIST_FOR_EACH_I_P_D x
#    define RTIBOOST_PP_LIST_FOR_EACH_I_P_D(m, d, l, i) RTIBOOST_PP_LIST_IS_CONS(l)
# else
#    define RTIBOOST_PP_LIST_FOR_EACH_I_P(r, x) RTIBOOST_PP_LIST_IS_CONS(RTIBOOST_PP_TUPLE_ELEM(4, 2, x))
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_LIST_FOR_EACH_I_O(r, x) RTIBOOST_PP_LIST_FOR_EACH_I_O_D x
#    define RTIBOOST_PP_LIST_FOR_EACH_I_O_D(m, d, l, i) (m, d, RTIBOOST_PP_LIST_REST(l), RTIBOOST_PP_INC(i))
# else
#    define RTIBOOST_PP_LIST_FOR_EACH_I_O(r, x) (RTIBOOST_PP_TUPLE_ELEM(4, 0, x), RTIBOOST_PP_TUPLE_ELEM(4, 1, x), RTIBOOST_PP_LIST_REST(RTIBOOST_PP_TUPLE_ELEM(4, 2, x)), RTIBOOST_PP_INC(RTIBOOST_PP_TUPLE_ELEM(4, 3, x)))
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_FOR_EACH_I_M(r, x) RTIBOOST_PP_LIST_FOR_EACH_I_M_D(r, RTIBOOST_PP_TUPLE_ELEM(4, 0, x), RTIBOOST_PP_TUPLE_ELEM(4, 1, x), RTIBOOST_PP_TUPLE_ELEM(4, 2, x), RTIBOOST_PP_TUPLE_ELEM(4, 3, x))
# else
#    define RTIBOOST_PP_LIST_FOR_EACH_I_M(r, x) RTIBOOST_PP_LIST_FOR_EACH_I_M_I(r, RTIBOOST_PP_TUPLE_REM_4 x)
#    define RTIBOOST_PP_LIST_FOR_EACH_I_M_I(r, x_e) RTIBOOST_PP_LIST_FOR_EACH_I_M_D(r, x_e)
# endif
#
# define RTIBOOST_PP_LIST_FOR_EACH_I_M_D(r, m, d, l, i) m(r, d, i, RTIBOOST_PP_LIST_FIRST(l))
#
# /* RTIBOOST_PP_LIST_FOR_EACH_I_R */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_FOR_EACH_I_R(r, macro, data, list) RTIBOOST_PP_FOR_ ## r((macro, data, list, 0), RTIBOOST_PP_LIST_FOR_EACH_I_P, RTIBOOST_PP_LIST_FOR_EACH_I_O, RTIBOOST_PP_LIST_FOR_EACH_I_M)
# else
#    define RTIBOOST_PP_LIST_FOR_EACH_I_R(r, macro, data, list) RTIBOOST_PP_LIST_FOR_EACH_I_R_I(r, macro, data, list)
#    define RTIBOOST_PP_LIST_FOR_EACH_I_R_I(r, macro, data, list) RTIBOOST_PP_FOR_ ## r((macro, data, list, 0), RTIBOOST_PP_LIST_FOR_EACH_I_P, RTIBOOST_PP_LIST_FOR_EACH_I_O, RTIBOOST_PP_LIST_FOR_EACH_I_M)
# endif
#
# endif
