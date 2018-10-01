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
# ifndef RTIBOOST_PREPROCESSOR_SEQ_FOR_EACH_I_HPP
# define RTIBOOST_PREPROCESSOR_SEQ_FOR_EACH_I_HPP
#
# include <rtiboost/preprocessor/arithmetic/dec.hpp>
# include <rtiboost/preprocessor/arithmetic/inc.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/repetition/for.hpp>
# include <rtiboost/preprocessor/seq/seq.hpp>
# include <rtiboost/preprocessor/seq/size.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
# include <rtiboost/preprocessor/tuple/rem.hpp>
#
# /* RTIBOOST_PP_SEQ_FOR_EACH_I */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_FOR_EACH_I(macro, data, seq) RTIBOOST_PP_FOR((macro, data, seq (nil), 0), RTIBOOST_PP_SEQ_FOR_EACH_I_P, RTIBOOST_PP_SEQ_FOR_EACH_I_O, RTIBOOST_PP_SEQ_FOR_EACH_I_M)
# else
#    define RTIBOOST_PP_SEQ_FOR_EACH_I(macro, data, seq) RTIBOOST_PP_SEQ_FOR_EACH_I_I(macro, data, seq)
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_I(macro, data, seq) RTIBOOST_PP_FOR((macro, data, seq (nil), 0), RTIBOOST_PP_SEQ_FOR_EACH_I_P, RTIBOOST_PP_SEQ_FOR_EACH_I_O, RTIBOOST_PP_SEQ_FOR_EACH_I_M)
# endif
#
# define RTIBOOST_PP_SEQ_FOR_EACH_I_P(r, x) RTIBOOST_PP_DEC(RTIBOOST_PP_SEQ_SIZE(RTIBOOST_PP_TUPLE_ELEM(4, 2, x)))
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_STRICT()
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_O(r, x) RTIBOOST_PP_SEQ_FOR_EACH_I_O_I x
# else
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_O(r, x) RTIBOOST_PP_SEQ_FOR_EACH_I_O_I(RTIBOOST_PP_TUPLE_ELEM(4, 0, x), RTIBOOST_PP_TUPLE_ELEM(4, 1, x), RTIBOOST_PP_TUPLE_ELEM(4, 2, x), RTIBOOST_PP_TUPLE_ELEM(4, 3, x))
# endif
#
# define RTIBOOST_PP_SEQ_FOR_EACH_I_O_I(macro, data, seq, i) (macro, data, RTIBOOST_PP_SEQ_TAIL(seq), RTIBOOST_PP_INC(i))
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_STRICT()
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_M(r, x) RTIBOOST_PP_SEQ_FOR_EACH_I_M_IM(r, RTIBOOST_PP_TUPLE_REM_4 x)
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_M_IM(r, im) RTIBOOST_PP_SEQ_FOR_EACH_I_M_I(r, im)
# else
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_M(r, x) RTIBOOST_PP_SEQ_FOR_EACH_I_M_I(r, RTIBOOST_PP_TUPLE_ELEM(4, 0, x), RTIBOOST_PP_TUPLE_ELEM(4, 1, x), RTIBOOST_PP_TUPLE_ELEM(4, 2, x), RTIBOOST_PP_TUPLE_ELEM(4, 3, x))
# endif
#
# define RTIBOOST_PP_SEQ_FOR_EACH_I_M_I(r, macro, data, seq, i) macro(r, data, i, RTIBOOST_PP_SEQ_HEAD(seq))
#
# /* RTIBOOST_PP_SEQ_FOR_EACH_I_R */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_R(r, macro, data, seq) RTIBOOST_PP_FOR_ ## r((macro, data, seq (nil), 0), RTIBOOST_PP_SEQ_FOR_EACH_I_P, RTIBOOST_PP_SEQ_FOR_EACH_I_O, RTIBOOST_PP_SEQ_FOR_EACH_I_M)
# else
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_R(r, macro, data, seq) RTIBOOST_PP_SEQ_FOR_EACH_I_R_I(r, macro, data, seq)
#    define RTIBOOST_PP_SEQ_FOR_EACH_I_R_I(r, macro, data, seq) RTIBOOST_PP_FOR_ ## r((macro, data, seq (nil), 0), RTIBOOST_PP_SEQ_FOR_EACH_I_P, RTIBOOST_PP_SEQ_FOR_EACH_I_O, RTIBOOST_PP_SEQ_FOR_EACH_I_M)
# endif
#
# endif
