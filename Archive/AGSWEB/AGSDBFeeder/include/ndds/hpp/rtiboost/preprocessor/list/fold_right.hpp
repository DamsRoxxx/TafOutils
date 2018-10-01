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
# ifndef RTIBOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
# define RTIBOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
#
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/control/while.hpp>
# include <rtiboost/preprocessor/debug/error.hpp>
# include <rtiboost/preprocessor/detail/auto_rec.hpp>
#
# if 0
#    define RTIBOOST_PP_LIST_FOLD_RIGHT(op, state, list)
# endif
#
# define RTIBOOST_PP_LIST_FOLD_RIGHT RTIBOOST_PP_CAT(RTIBOOST_PP_LIST_FOLD_RIGHT_, RTIBOOST_PP_AUTO_REC(RTIBOOST_PP_WHILE_P, 256))
#
# define RTIBOOST_PP_LIST_FOLD_RIGHT_257(o, s, l) RTIBOOST_PP_ERROR(0x0004)
#
# define RTIBOOST_PP_LIST_FOLD_RIGHT_D(d, o, s, l) RTIBOOST_PP_LIST_FOLD_RIGHT_ ## d(o, s, l)
# define RTIBOOST_PP_LIST_FOLD_RIGHT_2ND RTIBOOST_PP_LIST_FOLD_RIGHT
# define RTIBOOST_PP_LIST_FOLD_RIGHT_2ND_D RTIBOOST_PP_LIST_FOLD_RIGHT_D
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    include <rtiboost/preprocessor/list/detail/edg/fold_right.hpp>
# else
#    include <rtiboost/preprocessor/list/detail/fold_right.hpp>
# endif
#
# endif
