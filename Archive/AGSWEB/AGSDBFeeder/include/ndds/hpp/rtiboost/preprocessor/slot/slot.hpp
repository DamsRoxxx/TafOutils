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
# ifndef RTIBOOST_PREPROCESSOR_SLOT_SLOT_HPP
# define RTIBOOST_PREPROCESSOR_SLOT_SLOT_HPP
#
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/slot/detail/def.hpp>
#
# /* RTIBOOST_PP_ASSIGN_SLOT */
#
# define RTIBOOST_PP_ASSIGN_SLOT(i) RTIBOOST_PP_CAT(RTIBOOST_PP_ASSIGN_SLOT_, i)
#
# define RTIBOOST_PP_ASSIGN_SLOT_1 <rtiboost/preprocessor/slot/detail/slot1.hpp>
# define RTIBOOST_PP_ASSIGN_SLOT_2 <rtiboost/preprocessor/slot/detail/slot2.hpp>
# define RTIBOOST_PP_ASSIGN_SLOT_3 <rtiboost/preprocessor/slot/detail/slot3.hpp>
# define RTIBOOST_PP_ASSIGN_SLOT_4 <rtiboost/preprocessor/slot/detail/slot4.hpp>
# define RTIBOOST_PP_ASSIGN_SLOT_5 <rtiboost/preprocessor/slot/detail/slot5.hpp>
#
# /* RTIBOOST_PP_SLOT */
#
# define RTIBOOST_PP_SLOT(i) RTIBOOST_PP_CAT(RTIBOOST_PP_SLOT_, i)()
#
# endif
