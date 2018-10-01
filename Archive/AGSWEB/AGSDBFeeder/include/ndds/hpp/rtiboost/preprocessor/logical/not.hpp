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
# ifndef RTIBOOST_PREPROCESSOR_LOGICAL_NOT_HPP
# define RTIBOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/logical/bool.hpp>
# include <rtiboost/preprocessor/logical/compl.hpp>
#
# /* RTIBOOST_PP_NOT */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_NOT(x) RTIBOOST_PP_COMPL(RTIBOOST_PP_BOOL(x))
# else
#    define RTIBOOST_PP_NOT(x) RTIBOOST_PP_NOT_I(x)
#    define RTIBOOST_PP_NOT_I(x) RTIBOOST_PP_COMPL(RTIBOOST_PP_BOOL(x))
# endif
#
# endif
