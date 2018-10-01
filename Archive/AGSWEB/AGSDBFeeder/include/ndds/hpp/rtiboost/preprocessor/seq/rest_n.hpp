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
# ifndef RTIBOOST_PREPROCESSOR_SEQ_REST_N_HPP
# define RTIBOOST_PREPROCESSOR_SEQ_REST_N_HPP
#
# include <rtiboost/preprocessor/arithmetic/inc.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/facilities/empty.hpp>
# include <rtiboost/preprocessor/seq/detail/split.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
#
# /* RTIBOOST_PP_SEQ_REST_N */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_SEQ_REST_N(n, seq) RTIBOOST_PP_TUPLE_ELEM(2, 1, RTIBOOST_PP_SEQ_SPLIT(RTIBOOST_PP_INC(n), (nil) seq RTIBOOST_PP_EMPTY))()
# else
#    define RTIBOOST_PP_SEQ_REST_N(n, seq) RTIBOOST_PP_SEQ_REST_N_I(n, seq)
#    define RTIBOOST_PP_SEQ_REST_N_I(n, seq) RTIBOOST_PP_TUPLE_ELEM(2, 1, RTIBOOST_PP_SEQ_SPLIT(RTIBOOST_PP_INC(n), (nil) seq RTIBOOST_PP_EMPTY))()
# endif
#
# endif
