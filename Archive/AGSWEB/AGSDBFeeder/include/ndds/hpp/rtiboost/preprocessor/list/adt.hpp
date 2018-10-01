# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  *
#  * See http://www.boost.org for most recent version.
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# ifndef RTIBOOST_PREPROCESSOR_LIST_ADT_HPP
# define RTIBOOST_PREPROCESSOR_LIST_ADT_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/detail/is_binary.hpp>
# include <rtiboost/preprocessor/logical/compl.hpp>
# include <rtiboost/preprocessor/tuple/eat.hpp>
#
# /* RTIBOOST_PP_LIST_CONS */
#
# define RTIBOOST_PP_LIST_CONS(head, tail) (head, tail)
#
# /* RTIBOOST_PP_LIST_NIL */
#
# define RTIBOOST_PP_LIST_NIL RTIBOOST_PP_NIL
#
# /* RTIBOOST_PP_LIST_FIRST */
#
# define RTIBOOST_PP_LIST_FIRST(list) RTIBOOST_PP_LIST_FIRST_D(list)
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_LIST_FIRST_D(list) RTIBOOST_PP_LIST_FIRST_I list
# else
#    define RTIBOOST_PP_LIST_FIRST_D(list) RTIBOOST_PP_LIST_FIRST_I ## list
# endif
#
# define RTIBOOST_PP_LIST_FIRST_I(head, tail) head
#
# /* RTIBOOST_PP_LIST_REST */
#
# define RTIBOOST_PP_LIST_REST(list) RTIBOOST_PP_LIST_REST_D(list)
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_MWCC()
#    define RTIBOOST_PP_LIST_REST_D(list) RTIBOOST_PP_LIST_REST_I list
# else
#    define RTIBOOST_PP_LIST_REST_D(list) RTIBOOST_PP_LIST_REST_I ## list
# endif
#
# define RTIBOOST_PP_LIST_REST_I(head, tail) tail
#
# /* RTIBOOST_PP_LIST_IS_CONS */
#
# if RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_BCC()
#    define RTIBOOST_PP_LIST_IS_CONS(list) RTIBOOST_PP_LIST_IS_CONS_D(list)
#    define RTIBOOST_PP_LIST_IS_CONS_D(list) RTIBOOST_PP_LIST_IS_CONS_ ## list
#    define RTIBOOST_PP_LIST_IS_CONS_(head, tail) 1
#    define RTIBOOST_PP_LIST_IS_CONS_RTIBOOST_PP_NIL 0
# else
#    define RTIBOOST_PP_LIST_IS_CONS(list) RTIBOOST_PP_IS_BINARY(list)
# endif
#
# /* RTIBOOST_PP_LIST_IS_NIL */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_BCC()
#    define RTIBOOST_PP_LIST_IS_NIL(list) RTIBOOST_PP_COMPL(RTIBOOST_PP_IS_BINARY(list))
# else
#    define RTIBOOST_PP_LIST_IS_NIL(list) RTIBOOST_PP_COMPL(RTIBOOST_PP_LIST_IS_CONS(list))
# endif
#
# endif
