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
# ifndef RTIBOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
# define RTIBOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/list/fold_right.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
# include <rtiboost/preprocessor/tuple/rem.hpp>
#
# /* RTIBOOST_PP_LIST_TRANSFORM */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_TRANSFORM(op, data, list) RTIBOOST_PP_TUPLE_ELEM(3, 2, RTIBOOST_PP_LIST_FOLD_RIGHT(RTIBOOST_PP_LIST_TRANSFORM_O, (op, data, RTIBOOST_PP_NIL), list))
# else
#    define RTIBOOST_PP_LIST_TRANSFORM(op, data, list) RTIBOOST_PP_LIST_TRANSFORM_I(op, data, list)
#    define RTIBOOST_PP_LIST_TRANSFORM_I(op, data, list) RTIBOOST_PP_TUPLE_ELEM(3, 2, RTIBOOST_PP_LIST_FOLD_RIGHT(RTIBOOST_PP_LIST_TRANSFORM_O, (op, data, RTIBOOST_PP_NIL), list))
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_TRANSFORM_O(d, odr, elem) RTIBOOST_PP_LIST_TRANSFORM_O_D(d, RTIBOOST_PP_TUPLE_ELEM(3, 0, odr), RTIBOOST_PP_TUPLE_ELEM(3, 1, odr), RTIBOOST_PP_TUPLE_ELEM(3, 2, odr), elem)
# else
#    define RTIBOOST_PP_LIST_TRANSFORM_O(d, odr, elem) RTIBOOST_PP_LIST_TRANSFORM_O_I(d, RTIBOOST_PP_TUPLE_REM_3 odr, elem)
#    define RTIBOOST_PP_LIST_TRANSFORM_O_I(d, im, elem) RTIBOOST_PP_LIST_TRANSFORM_O_D(d, im, elem)
# endif
#
# define RTIBOOST_PP_LIST_TRANSFORM_O_D(d, op, data, res, elem) (op, data, (op(d, data, elem), res))
#
# /* RTIBOOST_PP_LIST_TRANSFORM_D */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_LIST_TRANSFORM_D(d, op, data, list) RTIBOOST_PP_TUPLE_ELEM(3, 2, RTIBOOST_PP_LIST_FOLD_RIGHT_ ## d(RTIBOOST_PP_LIST_TRANSFORM_O, (op, data, RTIBOOST_PP_NIL), list))
# else
#    define RTIBOOST_PP_LIST_TRANSFORM_D(d, op, data, list) RTIBOOST_PP_LIST_TRANSFORM_D_I(d, op, data, list)
#    define RTIBOOST_PP_LIST_TRANSFORM_D_I(d, op, data, list) RTIBOOST_PP_TUPLE_ELEM(3, 2, RTIBOOST_PP_LIST_FOLD_RIGHT_ ## d(RTIBOOST_PP_LIST_TRANSFORM_O, (op, data, RTIBOOST_PP_NIL), list))
# endif
#
# endif
