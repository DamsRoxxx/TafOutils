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
# ifndef RTIBOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
# define RTIBOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/detail/check.hpp>
#
# /* RTIBOOST_PP_IS_UNARY */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_IS_UNARY(x) RTIBOOST_PP_CHECK(x, RTIBOOST_PP_IS_UNARY_CHECK)
# else
#    define RTIBOOST_PP_IS_UNARY(x) RTIBOOST_PP_IS_UNARY_I(x)
#    define RTIBOOST_PP_IS_UNARY_I(x) RTIBOOST_PP_CHECK(x, RTIBOOST_PP_IS_UNARY_CHECK)
# endif
#
# define RTIBOOST_PP_IS_UNARY_CHECK(a) 1
# define RTIBOOST_PP_CHECK_RESULT_RTIBOOST_PP_IS_UNARY_CHECK 0, RTIBOOST_PP_NIL
#
# endif
