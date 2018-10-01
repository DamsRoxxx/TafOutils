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
# ifndef RTIBOOST_PREPROCESSOR_ARRAY_SIZE_HPP
# define RTIBOOST_PREPROCESSOR_ARRAY_SIZE_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
#
# /* RTIBOOST_PP_ARRAY_SIZE */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ARRAY_SIZE(array) RTIBOOST_PP_TUPLE_ELEM(2, 0, array)
# else
#    define RTIBOOST_PP_ARRAY_SIZE(array) RTIBOOST_PP_ARRAY_SIZE_I(array)
#    define RTIBOOST_PP_ARRAY_SIZE_I(array) RTIBOOST_PP_ARRAY_SIZE_II array
#    define RTIBOOST_PP_ARRAY_SIZE_II(size, data) size
# endif
#
# endif
