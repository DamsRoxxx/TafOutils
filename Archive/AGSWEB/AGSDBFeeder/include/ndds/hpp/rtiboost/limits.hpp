
//  (C) Copyright John maddock 1999. 
//  (C) David Abrahams 2002.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// use this header as a workaround for missing <limits>

//  See http://www.boost.org/libs/compatibility/index.html for documentation.

#ifndef RTIBOOST_LIMITS
#define RTIBOOST_LIMITS

#include <rtiboost/config.hpp>

#ifdef RTIBOOST_NO_LIMITS
#  error "There is no std::numeric_limits suppport available."
#else
# include <limits>
#endif

#if (defined(RTIBOOST_HAS_LONG_LONG) && defined(RTIBOOST_NO_LONG_LONG_NUMERIC_LIMITS)) \
      || (defined(RTIBOOST_HAS_MS_INT64) && defined(RTIBOOST_NO_MS_INT64_NUMERIC_LIMITS))
// Add missing specializations for numeric_limits:
#ifdef RTIBOOST_HAS_MS_INT64
#  define RTIBOOST_LLT __int64
#  define RTIBOOST_ULLT unsigned __int64
#else
#  define RTIBOOST_LLT  ::rtiboost::long_long_type
#  define RTIBOOST_ULLT  ::rtiboost::ulong_long_type
#endif

#include <climits>  // for CHAR_BIT

namespace std
{
  template<>
  class numeric_limits<RTIBOOST_LLT> 
  {
   public:

      RTIBOOST_STATIC_CONSTANT(bool, is_specialized = true);
#ifdef RTIBOOST_HAS_MS_INT64
      static RTIBOOST_LLT min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0x8000000000000000i64; }
      static RTIBOOST_LLT max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0x7FFFFFFFFFFFFFFFi64; }
#elif defined(LLONG_MAX)
      static RTIBOOST_LLT min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return LLONG_MIN; }
      static RTIBOOST_LLT max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return LLONG_MAX; }
#elif defined(LONGLONG_MAX)
      static RTIBOOST_LLT min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return LONGLONG_MIN; }
      static RTIBOOST_LLT max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return LONGLONG_MAX; }
#else
      static RTIBOOST_LLT min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return 1LL << (sizeof(RTIBOOST_LLT) * CHAR_BIT - 1); }
      static RTIBOOST_LLT max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return ~(min)(); }
#endif
      RTIBOOST_STATIC_CONSTANT(int, digits = sizeof(RTIBOOST_LLT) * CHAR_BIT -1);
      RTIBOOST_STATIC_CONSTANT(int, digits10 = (CHAR_BIT * sizeof (RTIBOOST_LLT) - 1) * 301L / 1000);
      RTIBOOST_STATIC_CONSTANT(bool, is_signed = true);
      RTIBOOST_STATIC_CONSTANT(bool, is_integer = true);
      RTIBOOST_STATIC_CONSTANT(bool, is_exact = true);
      RTIBOOST_STATIC_CONSTANT(int, radix = 2);
      static RTIBOOST_LLT epsilon() throw() { return 0; };
      static RTIBOOST_LLT round_error() throw() { return 0; };

      RTIBOOST_STATIC_CONSTANT(int, min_exponent = 0);
      RTIBOOST_STATIC_CONSTANT(int, min_exponent10 = 0);
      RTIBOOST_STATIC_CONSTANT(int, max_exponent = 0);
      RTIBOOST_STATIC_CONSTANT(int, max_exponent10 = 0);

      RTIBOOST_STATIC_CONSTANT(bool, has_infinity = false);
      RTIBOOST_STATIC_CONSTANT(bool, has_quiet_NaN = false);
      RTIBOOST_STATIC_CONSTANT(bool, has_signaling_NaN = false);
      RTIBOOST_STATIC_CONSTANT(bool, has_denorm = false);
      RTIBOOST_STATIC_CONSTANT(bool, has_denorm_loss = false);
      static RTIBOOST_LLT infinity() throw() { return 0; };
      static RTIBOOST_LLT quiet_NaN() throw() { return 0; };
      static RTIBOOST_LLT signaling_NaN() throw() { return 0; };
      static RTIBOOST_LLT denorm_min() throw() { return 0; };

      RTIBOOST_STATIC_CONSTANT(bool, is_iec559 = false);
      RTIBOOST_STATIC_CONSTANT(bool, is_bounded = true);
      RTIBOOST_STATIC_CONSTANT(bool, is_modulo = true);

      RTIBOOST_STATIC_CONSTANT(bool, traps = false);
      RTIBOOST_STATIC_CONSTANT(bool, tinyness_before = false);
      RTIBOOST_STATIC_CONSTANT(float_round_style, round_style = round_toward_zero);
      
  };

  template<>
  class numeric_limits<RTIBOOST_ULLT> 
  {
   public:

      RTIBOOST_STATIC_CONSTANT(bool, is_specialized = true);
#ifdef RTIBOOST_HAS_MS_INT64
      static RTIBOOST_ULLT min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0ui64; }
      static RTIBOOST_ULLT max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0xFFFFFFFFFFFFFFFFui64; }
#elif defined(ULLONG_MAX) && defined(ULLONG_MIN)
      static RTIBOOST_ULLT min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return ULLONG_MIN; }
      static RTIBOOST_ULLT max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return ULLONG_MAX; }
#elif defined(ULONGLONG_MAX) && defined(ULONGLONG_MIN)
      static RTIBOOST_ULLT min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return ULONGLONG_MIN; }
      static RTIBOOST_ULLT max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return ULONGLONG_MAX; }
#else
      static RTIBOOST_ULLT min RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return 0uLL; }
      static RTIBOOST_ULLT max RTIBOOST_PREVENT_MACRO_SUBSTITUTION (){ return ~0uLL; }
#endif
      RTIBOOST_STATIC_CONSTANT(int, digits = sizeof(RTIBOOST_LLT) * CHAR_BIT);
      RTIBOOST_STATIC_CONSTANT(int, digits10 = (CHAR_BIT * sizeof (RTIBOOST_LLT)) * 301L / 1000);
      RTIBOOST_STATIC_CONSTANT(bool, is_signed = false);
      RTIBOOST_STATIC_CONSTANT(bool, is_integer = true);
      RTIBOOST_STATIC_CONSTANT(bool, is_exact = true);
      RTIBOOST_STATIC_CONSTANT(int, radix = 2);
      static RTIBOOST_ULLT epsilon() throw() { return 0; };
      static RTIBOOST_ULLT round_error() throw() { return 0; };

      RTIBOOST_STATIC_CONSTANT(int, min_exponent = 0);
      RTIBOOST_STATIC_CONSTANT(int, min_exponent10 = 0);
      RTIBOOST_STATIC_CONSTANT(int, max_exponent = 0);
      RTIBOOST_STATIC_CONSTANT(int, max_exponent10 = 0);

      RTIBOOST_STATIC_CONSTANT(bool, has_infinity = false);
      RTIBOOST_STATIC_CONSTANT(bool, has_quiet_NaN = false);
      RTIBOOST_STATIC_CONSTANT(bool, has_signaling_NaN = false);
      RTIBOOST_STATIC_CONSTANT(bool, has_denorm = false);
      RTIBOOST_STATIC_CONSTANT(bool, has_denorm_loss = false);
      static RTIBOOST_ULLT infinity() throw() { return 0; };
      static RTIBOOST_ULLT quiet_NaN() throw() { return 0; };
      static RTIBOOST_ULLT signaling_NaN() throw() { return 0; };
      static RTIBOOST_ULLT denorm_min() throw() { return 0; };

      RTIBOOST_STATIC_CONSTANT(bool, is_iec559 = false);
      RTIBOOST_STATIC_CONSTANT(bool, is_bounded = true);
      RTIBOOST_STATIC_CONSTANT(bool, is_modulo = true);

      RTIBOOST_STATIC_CONSTANT(bool, traps = false);
      RTIBOOST_STATIC_CONSTANT(bool, tinyness_before = false);
      RTIBOOST_STATIC_CONSTANT(float_round_style, round_style = round_toward_zero);
      
  };
}
#endif 

#endif

