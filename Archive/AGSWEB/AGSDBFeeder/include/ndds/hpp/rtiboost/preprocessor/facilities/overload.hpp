# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef RTIBOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
# define RTIBOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/variadic/size.hpp>
#
# /* RTIBOOST_PP_OVERLOAD */
#
# if RTIBOOST_PP_VARIADICS
#    define RTIBOOST_PP_OVERLOAD(prefix, ...) RTIBOOST_PP_CAT(prefix, RTIBOOST_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
# endif
