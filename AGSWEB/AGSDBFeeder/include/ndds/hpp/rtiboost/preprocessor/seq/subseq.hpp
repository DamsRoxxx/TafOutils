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
# ifndef RTIBOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
# define RTIBOOST_PREPROCESSOR_SEQ_SUBSEQ_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/seq/first_n.hpp>
# include <rtiboost/preprocessor/seq/rest_n.hpp>
#
# /* RTIBOOST_PP_SEQ_SUBSEQ */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_SUBSEQ(seq, i, len) RTIBOOST_PP_SEQ_FIRST_N(len, RTIBOOST_PP_SEQ_REST_N(i, seq))
# else
#    define RTIBOOST_PP_SEQ_SUBSEQ(seq, i, len) RTIBOOST_PP_SEQ_SUBSEQ_I(seq, i, len)
#    define RTIBOOST_PP_SEQ_SUBSEQ_I(seq, i, len) RTIBOOST_PP_SEQ_FIRST_N(len, RTIBOOST_PP_SEQ_REST_N(i, seq))
# endif
#
# endif
