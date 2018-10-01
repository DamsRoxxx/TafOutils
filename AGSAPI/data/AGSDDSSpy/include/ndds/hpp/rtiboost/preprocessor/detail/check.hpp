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
# ifndef RTIBOOST_PREPROCESSOR_DETAIL_CHECK_HPP
# define RTIBOOST_PREPROCESSOR_DETAIL_CHECK_HPP
#
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
#
# /* RTIBOOST_PP_CHECK */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_CHECK(x, type) RTIBOOST_PP_CHECK_D(x, type)
# else
#    define RTIBOOST_PP_CHECK(x, type) RTIBOOST_PP_CHECK_OO((x, type))
#    define RTIBOOST_PP_CHECK_OO(par) RTIBOOST_PP_CHECK_D ## par
# endif
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC() && ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_DMC()
#    define RTIBOOST_PP_CHECK_D(x, type) RTIBOOST_PP_CHECK_1(RTIBOOST_PP_CAT(RTIBOOST_PP_CHECK_RESULT_, type x))
#    define RTIBOOST_PP_CHECK_1(chk) RTIBOOST_PP_CHECK_2(chk)
#    define RTIBOOST_PP_CHECK_2(res, _) res
# elif RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MSVC()
#    define RTIBOOST_PP_CHECK_D(x, type) RTIBOOST_PP_CHECK_1(type x)
#    define RTIBOOST_PP_CHECK_1(chk) RTIBOOST_PP_CHECK_2(chk)
#    define RTIBOOST_PP_CHECK_2(chk) RTIBOOST_PP_CHECK_3((RTIBOOST_PP_CHECK_RESULT_ ## chk))
#    define RTIBOOST_PP_CHECK_3(im) RTIBOOST_PP_CHECK_5(RTIBOOST_PP_CHECK_4 im)
#    define RTIBOOST_PP_CHECK_4(res, _) res
#    define RTIBOOST_PP_CHECK_5(res) res
# else /* DMC */
#    define RTIBOOST_PP_CHECK_D(x, type) RTIBOOST_PP_CHECK_OO((type x))
#    define RTIBOOST_PP_CHECK_OO(par) RTIBOOST_PP_CHECK_0 ## par
#    define RTIBOOST_PP_CHECK_0(chk) RTIBOOST_PP_CHECK_1(RTIBOOST_PP_CAT(RTIBOOST_PP_CHECK_RESULT_, chk))
#    define RTIBOOST_PP_CHECK_1(chk) RTIBOOST_PP_CHECK_2(chk)
#    define RTIBOOST_PP_CHECK_2(res, _) res
# endif
#
# define RTIBOOST_PP_CHECK_RESULT_1 1, RTIBOOST_PP_NIL
#
# endif
