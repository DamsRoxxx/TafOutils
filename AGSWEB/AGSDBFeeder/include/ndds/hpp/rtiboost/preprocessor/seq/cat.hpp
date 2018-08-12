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
# ifndef RTIBOOST_PREPROCESSOR_SEQ_CAT_HPP
# define RTIBOOST_PREPROCESSOR_SEQ_CAT_HPP
#
# include <rtiboost/preprocessor/arithmetic/dec.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/control/if.hpp>
# include <rtiboost/preprocessor/seq/fold_left.hpp>
# include <rtiboost/preprocessor/seq/seq.hpp>
# include <rtiboost/preprocessor/seq/size.hpp>
# include <rtiboost/preprocessor/tuple/eat.hpp>
#
# /* RTIBOOST_PP_SEQ_CAT */
#
# define RTIBOOST_PP_SEQ_CAT(seq) \
    RTIBOOST_PP_IF( \
        RTIBOOST_PP_DEC(RTIBOOST_PP_SEQ_SIZE(seq)), \
        RTIBOOST_PP_SEQ_CAT_I, \
        RTIBOOST_PP_SEQ_HEAD \
    )(seq) \
    /**/
# define RTIBOOST_PP_SEQ_CAT_I(seq) RTIBOOST_PP_SEQ_FOLD_LEFT(RTIBOOST_PP_SEQ_CAT_O, RTIBOOST_PP_SEQ_HEAD(seq), RTIBOOST_PP_SEQ_TAIL(seq))
#
# define RTIBOOST_PP_SEQ_CAT_O(s, st, elem) RTIBOOST_PP_SEQ_CAT_O_I(st, elem)
# define RTIBOOST_PP_SEQ_CAT_O_I(a, b) a ## b
#
# /* RTIBOOST_PP_SEQ_CAT_S */
#
# define RTIBOOST_PP_SEQ_CAT_S(s, seq) \
    RTIBOOST_PP_IF( \
        RTIBOOST_PP_DEC(RTIBOOST_PP_SEQ_SIZE(seq)), \
        RTIBOOST_PP_SEQ_CAT_S_I_A, \
        RTIBOOST_PP_SEQ_CAT_S_I_B \
    )(s, seq) \
    /**/
# define RTIBOOST_PP_SEQ_CAT_S_I_A(s, seq) RTIBOOST_PP_SEQ_FOLD_LEFT_ ## s(RTIBOOST_PP_SEQ_CAT_O, RTIBOOST_PP_SEQ_HEAD(seq), RTIBOOST_PP_SEQ_TAIL(seq))
# define RTIBOOST_PP_SEQ_CAT_S_I_B(s, seq) RTIBOOST_PP_SEQ_HEAD(seq)
#
# endif
