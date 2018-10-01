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
# ifndef RTIBOOST_PREPROCESSOR_LIST_REVERSE_HPP
# define RTIBOOST_PREPROCESSOR_LIST_REVERSE_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/list/fold_left.hpp>
#
# /* RTIBOOST_PP_LIST_REVERSE */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_REVERSE(list) RTIBOOST_PP_LIST_FOLD_LEFT(RTIBOOST_PP_LIST_REVERSE_O, RTIBOOST_PP_NIL, list)
# else
#    define RTIBOOST_PP_LIST_REVERSE(list) RTIBOOST_PP_LIST_REVERSE_I(list)
#    define RTIBOOST_PP_LIST_REVERSE_I(list) RTIBOOST_PP_LIST_FOLD_LEFT(RTIBOOST_PP_LIST_REVERSE_O, RTIBOOST_PP_NIL, list)
# endif
#
# define RTIBOOST_PP_LIST_REVERSE_O(d, s, x) (x, s)
#
# /* RTIBOOST_PP_LIST_REVERSE_D */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_REVERSE_D(d, list) RTIBOOST_PP_LIST_FOLD_LEFT_ ## d(RTIBOOST_PP_LIST_REVERSE_O, RTIBOOST_PP_NIL, list)
# else
#    define RTIBOOST_PP_LIST_REVERSE_D(d, list) RTIBOOST_PP_LIST_REVERSE_D_I(d, list)
#    define RTIBOOST_PP_LIST_REVERSE_D_I(d, list) RTIBOOST_PP_LIST_FOLD_LEFT_ ## d(RTIBOOST_PP_LIST_REVERSE_O, RTIBOOST_PP_NIL, list)
# endif
#
# endif
