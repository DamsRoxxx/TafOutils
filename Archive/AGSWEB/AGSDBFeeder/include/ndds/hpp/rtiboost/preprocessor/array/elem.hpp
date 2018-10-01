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
# ifndef RTIBOOST_PREPROCESSOR_ARRAY_ELEM_HPP
# define RTIBOOST_PREPROCESSOR_ARRAY_ELEM_HPP
#
# include <rtiboost/preprocessor/array/data.hpp>
# include <rtiboost/preprocessor/array/size.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
#
# /* RTIBOOST_PP_ARRAY_ELEM */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ARRAY_ELEM(i, array) RTIBOOST_PP_TUPLE_ELEM(RTIBOOST_PP_ARRAY_SIZE(array), i, RTIBOOST_PP_ARRAY_DATA(array))
# else
#    define RTIBOOST_PP_ARRAY_ELEM(i, array) RTIBOOST_PP_ARRAY_ELEM_I(i, array)
#    define RTIBOOST_PP_ARRAY_ELEM_I(i, array) RTIBOOST_PP_TUPLE_ELEM(RTIBOOST_PP_ARRAY_SIZE(array), i, RTIBOOST_PP_ARRAY_DATA(array))
# endif
#
# endif
