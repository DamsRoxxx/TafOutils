//  (C) Copyright 2009-2011 Frederic Bron.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_HAS_BIT_XOR_HPP_INCLUDED
#define RTIBOOST_TT_HAS_BIT_XOR_HPP_INCLUDED

#define RTIBOOST_TT_TRAIT_NAME has_bit_xor
#define RTIBOOST_TT_TRAIT_OP ^
#define RTIBOOST_TT_FORBIDDEN_IF\
   (\
      /* Lhs==fundamental and Rhs==fundamental and (Lhs!=integral or Rhs!=integral) */\
      (\
         ::rtiboost::is_fundamental< Lhs_nocv >::value && \
         ::rtiboost::is_fundamental< Rhs_nocv >::value && \
         ( \
            (!  ::rtiboost::is_integral< Lhs_noref >::value ) || \
            (!  ::rtiboost::is_integral< Rhs_noref >::value )\
         )\
      )||\
      /* Lhs==fundamental and Rhs==pointer */\
      (\
         ::rtiboost::is_fundamental< Lhs_nocv >::value && \
         ::rtiboost::is_pointer< Rhs_noref >::value\
      )||\
      /* Rhs==fundamental and Lhs==pointer */\
      (\
         ::rtiboost::is_fundamental< Rhs_nocv >::value && \
         ::rtiboost::is_pointer< Lhs_noref >::value\
      )||\
      /* Lhs==pointer and Rhs==pointer */\
      (\
         ::rtiboost::is_pointer< Lhs_noref >::value && \
         ::rtiboost::is_pointer< Rhs_noref >::value\
      )\
      )


#include <rtiboost/type_traits/detail/has_binary_operator.hpp>

#undef RTIBOOST_TT_TRAIT_NAME
#undef RTIBOOST_TT_TRAIT_OP
#undef RTIBOOST_TT_FORBIDDEN_IF

#endif
