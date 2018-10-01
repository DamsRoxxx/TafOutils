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
# ifndef RTIBOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
# define RTIBOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
#
# /* RTIBOOST_PP_COMPL */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_COMPL(x) RTIBOOST_PP_COMPL_I(x)
# else
#    define RTIBOOST_PP_COMPL(x) RTIBOOST_PP_COMPL_OO((x))
#    define RTIBOOST_PP_COMPL_OO(par) RTIBOOST_PP_COMPL_I ## par
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_COMPL_I(x) RTIBOOST_PP_COMPL_ ## x
# else
#    define RTIBOOST_PP_COMPL_I(x) RTIBOOST_PP_COMPL_ID(RTIBOOST_PP_COMPL_ ## x)
#    define RTIBOOST_PP_COMPL_ID(id) id
# endif
#
# define RTIBOOST_PP_COMPL_0 1
# define RTIBOOST_PP_COMPL_1 0
#
# endif
