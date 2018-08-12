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
# ifndef RTIBOOST_PREPROCESSOR_STRINGIZE_HPP
# define RTIBOOST_PREPROCESSOR_STRINGIZE_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
#
# /* RTIBOOST_PP_STRINGIZE */
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_STRINGIZE(text) RTIBOOST_PP_STRINGIZE_A((text))
#    define RTIBOOST_PP_STRINGIZE_A(arg) RTIBOOST_PP_STRINGIZE_I arg
# elif RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_STRINGIZE(text) RTIBOOST_PP_STRINGIZE_OO((text))
#    define RTIBOOST_PP_STRINGIZE_OO(par) RTIBOOST_PP_STRINGIZE_I ## par
# else
#    define RTIBOOST_PP_STRINGIZE(text) RTIBOOST_PP_STRINGIZE_I(text)
# endif
#
# define RTIBOOST_PP_STRINGIZE_I(text) #text
#
# endif
