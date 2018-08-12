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
# ifndef RTIBOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
# define RTIBOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/slot/slot.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
#
# /* RTIBOOST_PP_LOCAL_ITERATE */
#
# define RTIBOOST_PP_LOCAL_ITERATE() <rtiboost/preprocessor/iteration/detail/local.hpp>
#
# define RTIBOOST_PP_LOCAL_C(n) (RTIBOOST_PP_LOCAL_S) <= n && (RTIBOOST_PP_LOCAL_F) >= n
# define RTIBOOST_PP_LOCAL_R(n) (RTIBOOST_PP_LOCAL_F) <= n && (RTIBOOST_PP_LOCAL_S) >= n
#
# endif
