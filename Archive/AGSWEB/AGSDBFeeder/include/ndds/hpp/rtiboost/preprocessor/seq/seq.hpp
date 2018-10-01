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
# ifndef RTIBOOST_PREPROCESSOR_SEQ_SEQ_HPP
# define RTIBOOST_PREPROCESSOR_SEQ_SEQ_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/seq/elem.hpp>
#
# /* RTIBOOST_PP_SEQ_HEAD */
#
# define RTIBOOST_PP_SEQ_HEAD(seq) RTIBOOST_PP_SEQ_ELEM(0, seq)
#
# /* RTIBOOST_PP_SEQ_TAIL */
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_SEQ_TAIL(seq) RTIBOOST_PP_SEQ_TAIL_1((seq))
#    define RTIBOOST_PP_SEQ_TAIL_1(par) RTIBOOST_PP_SEQ_TAIL_2 ## par
#    define RTIBOOST_PP_SEQ_TAIL_2(seq) RTIBOOST_PP_SEQ_TAIL_I ## seq
# elif RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_SEQ_TAIL(seq) RTIBOOST_PP_SEQ_TAIL_ID(RTIBOOST_PP_SEQ_TAIL_I seq)
#    define RTIBOOST_PP_SEQ_TAIL_ID(id) id
# elif RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_TAIL(seq) RTIBOOST_PP_SEQ_TAIL_D(seq)
#    define RTIBOOST_PP_SEQ_TAIL_D(seq) RTIBOOST_PP_SEQ_TAIL_I seq
# else
#    define RTIBOOST_PP_SEQ_TAIL(seq) RTIBOOST_PP_SEQ_TAIL_I seq
# endif
#
# define RTIBOOST_PP_SEQ_TAIL_I(x)
#
# /* RTIBOOST_PP_SEQ_NIL */
#
# define RTIBOOST_PP_SEQ_NIL(x) (x)
#
# endif
