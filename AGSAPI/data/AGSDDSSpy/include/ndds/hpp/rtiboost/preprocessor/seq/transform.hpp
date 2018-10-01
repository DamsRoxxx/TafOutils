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
# ifndef RTIBOOST_PREPROCESSOR_SEQ_TRANSFORM_HPP
# define RTIBOOST_PREPROCESSOR_SEQ_TRANSFORM_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/seq/fold_left.hpp>
# include <rtiboost/preprocessor/seq/seq.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
# include <rtiboost/preprocessor/tuple/rem.hpp>
#
# /* RTIBOOST_PP_SEQ_TRANSFORM */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_TRANSFORM(op, data, seq) RTIBOOST_PP_SEQ_TAIL(RTIBOOST_PP_TUPLE_ELEM(3, 2, RTIBOOST_PP_SEQ_FOLD_LEFT(RTIBOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# else
#    define RTIBOOST_PP_SEQ_TRANSFORM(op, data, seq) RTIBOOST_PP_SEQ_TRANSFORM_I(op, data, seq)
#    define RTIBOOST_PP_SEQ_TRANSFORM_I(op, data, seq) RTIBOOST_PP_SEQ_TAIL(RTIBOOST_PP_TUPLE_ELEM(3, 2, RTIBOOST_PP_SEQ_FOLD_LEFT(RTIBOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# endif
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_STRICT()
#    define RTIBOOST_PP_SEQ_TRANSFORM_O(s, state, elem) RTIBOOST_PP_SEQ_TRANSFORM_O_IM(s, RTIBOOST_PP_TUPLE_REM_3 state, elem)
#    define RTIBOOST_PP_SEQ_TRANSFORM_O_IM(s, im, elem) RTIBOOST_PP_SEQ_TRANSFORM_O_I(s, im, elem)
# else
#    define RTIBOOST_PP_SEQ_TRANSFORM_O(s, state, elem) RTIBOOST_PP_SEQ_TRANSFORM_O_I(s, RTIBOOST_PP_TUPLE_ELEM(3, 0, state), RTIBOOST_PP_TUPLE_ELEM(3, 1, state), RTIBOOST_PP_TUPLE_ELEM(3, 2, state), elem)
# endif
#
# define RTIBOOST_PP_SEQ_TRANSFORM_O_I(s, op, data, res, elem) (op, data, res (op(s, data, elem)))
#
# /* RTIBOOST_PP_SEQ_TRANSFORM_S */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_TRANSFORM_S(s, op, data, seq) RTIBOOST_PP_SEQ_TAIL(RTIBOOST_PP_TUPLE_ELEM(3, 2, RTIBOOST_PP_SEQ_FOLD_LEFT_ ## s(RTIBOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# else
#    define RTIBOOST_PP_SEQ_TRANSFORM_S(s, op, data, seq) RTIBOOST_PP_SEQ_TRANSFORM_S_I(s, op, data, seq)
#    define RTIBOOST_PP_SEQ_TRANSFORM_S_I(s, op, data, seq) RTIBOOST_PP_SEQ_TAIL(RTIBOOST_PP_TUPLE_ELEM(3, 2, RTIBOOST_PP_SEQ_FOLD_LEFT_ ## s(RTIBOOST_PP_SEQ_TRANSFORM_O, (op, data, (nil)), seq)))
# endif
#
# endif
