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
# ifndef RTIBOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
# define RTIBOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/control/if.hpp>
# include <rtiboost/preprocessor/seq/detail/split.hpp>
# include <rtiboost/preprocessor/tuple/eat.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
#
# /* RTIBOOST_PP_SEQ_FIRST_N */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_FIRST_N(n, seq) RTIBOOST_PP_IF(n, RTIBOOST_PP_TUPLE_ELEM, RTIBOOST_PP_TUPLE_EAT_3)(2, 0, RTIBOOST_PP_SEQ_SPLIT(n, seq (nil)))
# else
#    define RTIBOOST_PP_SEQ_FIRST_N(n, seq) RTIBOOST_PP_SEQ_FIRST_N_I(n, seq)
#    define RTIBOOST_PP_SEQ_FIRST_N_I(n, seq) RTIBOOST_PP_IF(n, RTIBOOST_PP_TUPLE_ELEM, RTIBOOST_PP_TUPLE_EAT_3)(2, 0, RTIBOOST_PP_SEQ_SPLIT(n, seq (nil)))
# endif
#
# endif
