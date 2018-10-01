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
# ifndef RTIBOOST_PREPROCESSOR_CONTROL_IF_HPP
# define RTIBOOST_PREPROCESSOR_CONTROL_IF_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/control/iif.hpp>
# include <rtiboost/preprocessor/logical/bool.hpp>
#
# /* RTIBOOST_PP_IF */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_IF(cond, t, f) RTIBOOST_PP_IIF(RTIBOOST_PP_BOOL(cond), t, f)
# else
#    define RTIBOOST_PP_IF(cond, t, f) RTIBOOST_PP_IF_I(cond, t, f)
#    define RTIBOOST_PP_IF_I(cond, t, f) RTIBOOST_PP_IIF(RTIBOOST_PP_BOOL(cond), t, f)
# endif
#
# endif
