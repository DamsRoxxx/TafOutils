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
# ifndef RTIBOOST_PREPROCESSOR_CAT_HPP
# define RTIBOOST_PREPROCESSOR_CAT_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
#
# /* RTIBOOST_PP_CAT */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_CAT(a, b) RTIBOOST_PP_CAT_I(a, b)
# else
#    define RTIBOOST_PP_CAT(a, b) RTIBOOST_PP_CAT_OO((a, b))
#    define RTIBOOST_PP_CAT_OO(par) RTIBOOST_PP_CAT_I ## par
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_CAT_I(a, b) a ## b
# else
#    define RTIBOOST_PP_CAT_I(a, b) RTIBOOST_PP_CAT_II(~, a ## b)
#    define RTIBOOST_PP_CAT_II(p, res) res
# endif
#
# endif
