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
# ifndef RTIBOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
# define RTIBOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
#
# /* RTIBOOST_PP_BITOR */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_BITOR(x, y) RTIBOOST_PP_BITOR_I(x, y)
# else
#    define RTIBOOST_PP_BITOR(x, y) RTIBOOST_PP_BITOR_OO((x, y))
#    define RTIBOOST_PP_BITOR_OO(par) RTIBOOST_PP_BITOR_I ## par
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_BITOR_I(x, y) RTIBOOST_PP_BITOR_ ## x ## y
# else
#    define RTIBOOST_PP_BITOR_I(x, y) RTIBOOST_PP_BITOR_ID(RTIBOOST_PP_BITOR_ ## x ## y)
#    define RTIBOOST_PP_BITOR_ID(id) id
# endif
#
# define RTIBOOST_PP_BITOR_00 0
# define RTIBOOST_PP_BITOR_01 1
# define RTIBOOST_PP_BITOR_10 1
# define RTIBOOST_PP_BITOR_11 1
#
# endif
