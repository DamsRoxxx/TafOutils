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
# ifndef RTIBOOST_PREPROCESSOR_CONTROL_IIF_HPP
# define RTIBOOST_PREPROCESSOR_CONTROL_IIF_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_IIF(bit, t, f) RTIBOOST_PP_IIF_I(bit, t, f)
# else
#    define RTIBOOST_PP_IIF(bit, t, f) RTIBOOST_PP_IIF_OO((bit, t, f))
#    define RTIBOOST_PP_IIF_OO(par) RTIBOOST_PP_IIF_I ## par
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_IIF_I(bit, t, f) RTIBOOST_PP_IIF_ ## bit(t, f)
# else
#    define RTIBOOST_PP_IIF_I(bit, t, f) RTIBOOST_PP_IIF_II(RTIBOOST_PP_IIF_ ## bit(t, f))
#    define RTIBOOST_PP_IIF_II(id) id
# endif
#
# define RTIBOOST_PP_IIF_0(t, f) f
# define RTIBOOST_PP_IIF_1(t, f) t
#
# endif
