//
//  boost/assert.hpp - RTIBOOST_ASSERT(expr)
//                     RTIBOOST_ASSERT_MSG(expr, msg)
//                     RTIBOOST_VERIFY(expr)
//                     RTIBOOST_VERIFY_MSG(expr, msg)
//                     RTIBOOST_ASSERT_IS_VOID
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2007, 2014 Peter Dimov
//  Copyright (c) Beman Dawes 2011
//  Copyright (c) 2015 Ion Gaztanaga
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  Note: There are no include guards. This is intentional.
//
//  See http://www.boost.org/libs/assert/assert.html for documentation.
//

//
// Stop inspect complaining about use of 'assert':
//
// boostinspect:naassert_macro
//

//
// RTIBOOST_ASSERT, RTIBOOST_ASSERT_MSG, RTIBOOST_ASSERT_IS_VOID
//

#undef RTIBOOST_ASSERT
#undef RTIBOOST_ASSERT_MSG
#undef RTIBOOST_ASSERT_IS_VOID

#if defined(RTIBOOST_DISABLE_ASSERTS) || ( defined(RTIBOOST_ENABLE_ASSERT_DEBUG_HANDLER) && defined(NDEBUG) )

# define RTIBOOST_ASSERT(expr) ((void)0)
# define RTIBOOST_ASSERT_MSG(expr, msg) ((void)0)
# define RTIBOOST_ASSERT_IS_VOID

#elif defined(RTIBOOST_ENABLE_ASSERT_HANDLER) || ( defined(RTIBOOST_ENABLE_ASSERT_DEBUG_HANDLER) && !defined(NDEBUG) )

#include <rtiboost/config.hpp> // for RTIBOOST_LIKELY
#include <rtiboost/current_function.hpp>

namespace rtiboost
{
    void assertion_failed(char const * expr, char const * function, char const * file, long line); // user defined
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line); // user defined
} // namespace rtiboost

#define RTIBOOST_ASSERT(expr) (RTIBOOST_LIKELY(!!(expr))? ((void)0): ::rtiboost::assertion_failed(#expr, RTIBOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define RTIBOOST_ASSERT_MSG(expr, msg) (RTIBOOST_LIKELY(!!(expr))? ((void)0): ::rtiboost::assertion_failed_msg(#expr, msg, RTIBOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

# include <assert.h> // .h to support old libraries w/o <cassert> - effect is the same

# define RTIBOOST_ASSERT(expr) assert(expr)
# define RTIBOOST_ASSERT_MSG(expr, msg) assert((expr)&&(msg))
#if defined(NDEBUG)
# define RTIBOOST_ASSERT_IS_VOID
#endif

#endif

//
// RTIBOOST_VERIFY, RTIBOOST_VERIFY_MSG
//

#undef RTIBOOST_VERIFY
#undef RTIBOOST_VERIFY_MSG

#if defined(RTIBOOST_DISABLE_ASSERTS) || ( !defined(RTIBOOST_ENABLE_ASSERT_HANDLER) && defined(NDEBUG) )

# define RTIBOOST_VERIFY(expr) ((void)(expr))
# define RTIBOOST_VERIFY_MSG(expr, msg) ((void)(expr))

#else

# define RTIBOOST_VERIFY(expr) RTIBOOST_ASSERT(expr)
# define RTIBOOST_VERIFY_MSG(expr, msg) RTIBOOST_ASSERT_MSG(expr,msg)

#endif
