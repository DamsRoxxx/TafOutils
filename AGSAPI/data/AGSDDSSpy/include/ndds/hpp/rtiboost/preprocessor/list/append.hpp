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
# ifndef RTIBOOST_PREPROCESSOR_LIST_APPEND_HPP
# define RTIBOOST_PREPROCESSOR_LIST_APPEND_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/list/fold_right.hpp>
#
# /* RTIBOOST_PP_LIST_APPEND */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_APPEND(a, b) RTIBOOST_PP_LIST_FOLD_RIGHT(RTIBOOST_PP_LIST_APPEND_O, b, a)
# else
#    define RTIBOOST_PP_LIST_APPEND(a, b) RTIBOOST_PP_LIST_APPEND_I(a, b)
#    define RTIBOOST_PP_LIST_APPEND_I(a, b) RTIBOOST_PP_LIST_FOLD_RIGHT(RTIBOOST_PP_LIST_APPEND_O, b, a)
# endif
#
# define RTIBOOST_PP_LIST_APPEND_O(d, s, x) (x, s)
#
# /* RTIBOOST_PP_LIST_APPEND_D */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_APPEND_D(d, a, b) RTIBOOST_PP_LIST_FOLD_RIGHT_ ## d(RTIBOOST_PP_LIST_APPEND_O, b, a)
# else
#    define RTIBOOST_PP_LIST_APPEND_D(d, a, b) RTIBOOST_PP_LIST_APPEND_D_I(d, a, b)
#    define RTIBOOST_PP_LIST_APPEND_D_I(d, a, b) RTIBOOST_PP_LIST_FOLD_RIGHT_ ## d(RTIBOOST_PP_LIST_APPEND_O, b, a)
# endif
#
# endif
