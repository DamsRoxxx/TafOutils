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
# ifndef RTIBOOST_PREPROCESSOR_ITERATION_ITERATE_HPP
# define RTIBOOST_PREPROCESSOR_ITERATION_ITERATE_HPP
#
# include <rtiboost/preprocessor/arithmetic/dec.hpp>
# include <rtiboost/preprocessor/arithmetic/inc.hpp>
# include <rtiboost/preprocessor/array/elem.hpp>
# include <rtiboost/preprocessor/array/size.hpp>
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/slot/slot.hpp>
# include <rtiboost/preprocessor/tuple/elem.hpp>
#
# /* RTIBOOST_PP_ITERATION_DEPTH */
#
# define RTIBOOST_PP_ITERATION_DEPTH() 0
#
# /* RTIBOOST_PP_ITERATION */
#
# define RTIBOOST_PP_ITERATION() RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATION_, RTIBOOST_PP_ITERATION_DEPTH())
#
# /* RTIBOOST_PP_ITERATION_START && RTIBOOST_PP_ITERATION_FINISH */
#
# define RTIBOOST_PP_ITERATION_START() RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATION_START_, RTIBOOST_PP_ITERATION_DEPTH())
# define RTIBOOST_PP_ITERATION_FINISH() RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATION_FINISH_, RTIBOOST_PP_ITERATION_DEPTH())
#
# /* RTIBOOST_PP_ITERATION_FLAGS */
#
# define RTIBOOST_PP_ITERATION_FLAGS() (RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATION_FLAGS_, RTIBOOST_PP_ITERATION_DEPTH())())
#
# /* RTIBOOST_PP_FRAME_ITERATION */
#
# define RTIBOOST_PP_FRAME_ITERATION(i) RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATION_, i)
#
# /* RTIBOOST_PP_FRAME_START && RTIBOOST_PP_FRAME_FINISH */
#
# define RTIBOOST_PP_FRAME_START(i) RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATION_START_, i)
# define RTIBOOST_PP_FRAME_FINISH(i) RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATION_FINISH_, i)
#
# /* RTIBOOST_PP_FRAME_FLAGS */
#
# define RTIBOOST_PP_FRAME_FLAGS(i) (RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATION_FLAGS_, i)())
#
# /* RTIBOOST_PP_RELATIVE_ITERATION */
#
# define RTIBOOST_PP_RELATIVE_ITERATION(i) RTIBOOST_PP_CAT(RTIBOOST_PP_RELATIVE_, i)(RTIBOOST_PP_ITERATION_)
#
# define RTIBOOST_PP_RELATIVE_0(m) RTIBOOST_PP_CAT(m, RTIBOOST_PP_ITERATION_DEPTH())
# define RTIBOOST_PP_RELATIVE_1(m) RTIBOOST_PP_CAT(m, RTIBOOST_PP_DEC(RTIBOOST_PP_ITERATION_DEPTH()))
# define RTIBOOST_PP_RELATIVE_2(m) RTIBOOST_PP_CAT(m, RTIBOOST_PP_DEC(RTIBOOST_PP_DEC(RTIBOOST_PP_ITERATION_DEPTH())))
# define RTIBOOST_PP_RELATIVE_3(m) RTIBOOST_PP_CAT(m, RTIBOOST_PP_DEC(RTIBOOST_PP_DEC(RTIBOOST_PP_DEC(RTIBOOST_PP_ITERATION_DEPTH()))))
# define RTIBOOST_PP_RELATIVE_4(m) RTIBOOST_PP_CAT(m, RTIBOOST_PP_DEC(RTIBOOST_PP_DEC(RTIBOOST_PP_DEC(RTIBOOST_PP_DEC(RTIBOOST_PP_ITERATION_DEPTH())))))
#
# /* RTIBOOST_PP_RELATIVE_START && RTIBOOST_PP_RELATIVE_FINISH */
#
# define RTIBOOST_PP_RELATIVE_START(i) RTIBOOST_PP_CAT(RTIBOOST_PP_RELATIVE_, i)(RTIBOOST_PP_ITERATION_START_)
# define RTIBOOST_PP_RELATIVE_FINISH(i) RTIBOOST_PP_CAT(RTIBOOST_PP_RELATIVE_, i)(RTIBOOST_PP_ITERATION_FINISH_)
#
# /* RTIBOOST_PP_RELATIVE_FLAGS */
#
# define RTIBOOST_PP_RELATIVE_FLAGS(i) (RTIBOOST_PP_CAT(RTIBOOST_PP_RELATIVE_, i)(RTIBOOST_PP_ITERATION_FLAGS_)())
#
# /* RTIBOOST_PP_ITERATE */
#
# define RTIBOOST_PP_ITERATE() RTIBOOST_PP_CAT(RTIBOOST_PP_ITERATE_, RTIBOOST_PP_INC(RTIBOOST_PP_ITERATION_DEPTH()))
#
# define RTIBOOST_PP_ITERATE_1 <rtiboost/preprocessor/iteration/detail/iter/forward1.hpp>
# define RTIBOOST_PP_ITERATE_2 <rtiboost/preprocessor/iteration/detail/iter/forward2.hpp>
# define RTIBOOST_PP_ITERATE_3 <rtiboost/preprocessor/iteration/detail/iter/forward3.hpp>
# define RTIBOOST_PP_ITERATE_4 <rtiboost/preprocessor/iteration/detail/iter/forward4.hpp>
# define RTIBOOST_PP_ITERATE_5 <rtiboost/preprocessor/iteration/detail/iter/forward5.hpp>
#
# endif
