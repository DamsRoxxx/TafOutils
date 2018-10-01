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
# ifndef RTIBOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
# define RTIBOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/control/if.hpp>
# include <rtiboost/preprocessor/facilities/empty.hpp>
# include <rtiboost/preprocessor/punctuation/comma.hpp>
#
# /* RTIBOOST_PP_COMMA_IF */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_COMMA_IF(cond) RTIBOOST_PP_IF(cond, RTIBOOST_PP_COMMA, RTIBOOST_PP_EMPTY)()
# else
#    define RTIBOOST_PP_COMMA_IF(cond) RTIBOOST_PP_COMMA_IF_I(cond)
#    define RTIBOOST_PP_COMMA_IF_I(cond) RTIBOOST_PP_IF(cond, RTIBOOST_PP_COMMA, RTIBOOST_PP_EMPTY)()
# endif
#
# endif
