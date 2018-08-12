// Copyright (C) 2004 Arkadiy Vertleyb
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_TYPEOF_HPP_INCLUDED
#define RTIBOOST_TYPEOF_TYPEOF_HPP_INCLUDED

#if defined(RTIBOOST_TYPEOF_COMPLIANT)
#   define RTIBOOST_TYPEOF_EMULATION
#endif

#if defined(RTIBOOST_TYPEOF_EMULATION) && defined(RTIBOOST_TYPEOF_NATIVE)
#   error both typeof emulation and native mode requested
#endif

#if defined(__COMO__)
#   ifdef __GNUG__
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           ifndef RTIBOOST_TYPEOF_NATIVE
#               define RTIBOOST_TYPEOF_NATIVE
#           endif
#           define RTIBOOST_TYPEOF_KEYWORD typeof
#       endif
#   else
#       ifndef RTIBOOST_TYPEOF_NATIVE
#           ifndef RTIBOOST_TYPEOF_EMULATION
#               define RTIBOOST_TYPEOF_EMULATION
#           endif
#       else
#           error native typeof is not supported
#       endif
#   endif

#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#   ifdef __GNUC__
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           ifndef RTIBOOST_TYPEOF_NATIVE
#               define RTIBOOST_TYPEOF_NATIVE
#           endif
#           define RTIBOOST_TYPEOF_KEYWORD __typeof__
#       endif
#   else
#       ifndef RTIBOOST_TYPEOF_NATIVE
#           ifndef RTIBOOST_TYPEOF_EMULATION
#               define RTIBOOST_TYPEOF_EMULATION
#           endif
#       else
#           error native typeof is not supported
#       endif
#   endif

#elif defined(__GNUC__)
#   ifndef RTIBOOST_TYPEOF_EMULATION
#       ifndef RTIBOOST_TYPEOF_NATIVE
#           define RTIBOOST_TYPEOF_NATIVE
#       endif
#       define RTIBOOST_TYPEOF_KEYWORD __typeof__
#   endif

#elif defined(__MWERKS__)
#   if(__MWERKS__ <= 0x3003)  // 8.x
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           ifndef RTIBOOST_TYPEOF_NATIVE
#               define RTIBOOST_TYPEOF_NATIVE
#           endif
#           define RTIBOOST_TYPEOF_KEYWORD __typeof__
#       else
#           define RTIBOOST_TYPEOF_EMULATION_UNSUPPORTED
#       endif
#   else // 9.x
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           ifndef RTIBOOST_TYPEOF_NATIVE
#               define RTIBOOST_TYPEOF_NATIVE
#           endif
#           define RTIBOOST_TYPEOF_KEYWORD __typeof__
#       endif
#   endif
#elif defined __CODEGEARC__
#   ifndef RTIBOOST_TYPEOF_EMULATION
#       ifndef RTIBOOST_TYPEOF_NATIVE
#           define RTIBOOST_TYPEOF_EMULATION_UNSUPPORTED
#       endif
#   else
#       define RTIBOOST_TYPEOF_EMULATION_UNSUPPORTED
#   endif
#elif defined __BORLANDC__
#   ifndef RTIBOOST_TYPEOF_EMULATION
#       ifndef RTIBOOST_TYPEOF_NATIVE
#           define RTIBOOST_TYPEOF_EMULATION_UNSUPPORTED
#       endif
#   else
#       define RTIBOOST_TYPEOF_EMULATION_UNSUPPORTED
#   endif
#elif defined __DMC__
#   ifndef RTIBOOST_TYPEOF_EMULATION
#       ifndef RTIBOOST_TYPEOF_NATIVE
#           define RTIBOOST_TYPEOF_NATIVE
#       endif
#       include <rtiboost/typeof/dmc/typeof_impl.hpp>
#       define MSVC_TYPEOF_HACK
#   endif
#elif defined(_MSC_VER)
#   if (_MSC_VER <= 1300)  // 6.5, 7.0
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           ifndef RTIBOOST_TYPEOF_NATIVE
#               define RTIBOOST_TYPEOF_NATIVE
#           endif
#           include <rtiboost/typeof/msvc/typeof_impl.hpp>
#           define MSVC_TYPEOF_HACK
#       else
#           error typeof emulation is not supported
#       endif
#   elif (_MSC_VER >= 1310)  // 7.1 ->
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           ifndef RTIBOOST_TYPEOF_NATIVE
#               ifndef _MSC_EXTENSIONS
#                   define RTIBOOST_TYPEOF_EMULATION
#               else
#                   define RTIBOOST_TYPEOF_NATIVE
#               endif
#           endif
#       endif
#       ifdef RTIBOOST_TYPEOF_NATIVE
#           include <rtiboost/typeof/msvc/typeof_impl.hpp>
#           define MSVC_TYPEOF_HACK
#       endif
#   endif
#elif defined(__HP_aCC)
#   ifndef RTIBOOST_TYPEOF_NATIVE
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           define RTIBOOST_TYPEOF_EMULATION
#       endif
#   else
#       error native typeof is not supported
#   endif

#elif defined(__DECCXX)
#   ifndef RTIBOOST_TYPEOF_NATIVE
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           define RTIBOOST_TYPEOF_EMULATION
#       endif
#   else
#       error native typeof is not supported
#   endif

#elif defined(__BORLANDC__)
#   if (__BORLANDC__ < 0x590)
#       define RTIBOOST_TYPEOF_NO_FUNCTION_TYPES
#       define RTIBOOST_TYPEOF_NO_MEMBER_FUNCTION_TYPES
#   endif
#   ifndef RTIBOOST_TYPEOF_NATIVE
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           define RTIBOOST_TYPEOF_EMULATION
#       endif
#   else
#       error native typeof is not supported
#   endif
#elif defined(__SUNPRO_CC)
#   if (__SUNPRO_CC < 0x590 )
#     ifdef RTIBOOST_TYPEOF_NATIVE
#         error native typeof is not supported
#     endif
#     ifndef RTIBOOST_TYPEOF_EMULATION
#         define RTIBOOST_TYPEOF_EMULATION
#     endif
#   else
#     ifndef RTIBOOST_TYPEOF_EMULATION
#         ifndef RTIBOOST_TYPEOF_NATIVE
#             define RTIBOOST_TYPEOF_NATIVE
#         endif
#         define RTIBOOST_TYPEOF_KEYWORD __typeof__
#     endif
#   endif
#else //unknown compiler
#   ifndef RTIBOOST_TYPEOF_NATIVE
#       ifndef RTIBOOST_TYPEOF_EMULATION
#           define RTIBOOST_TYPEOF_EMULATION
#       endif
#   else
#       ifndef RTIBOOST_TYPEOF_KEYWORD
#           define RTIBOOST_TYPEOF_KEYWORD typeof
#       endif
#   endif

#endif

#define RTIBOOST_TYPEOF_UNIQUE_ID()\
     RTIBOOST_TYPEOF_REGISTRATION_GROUP * 0x10000 + __LINE__

#define RTIBOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()\
     <rtiboost/typeof/incr_registration_group.hpp>

#ifdef RTIBOOST_TYPEOF_EMULATION_UNSUPPORTED
#   include <rtiboost/typeof/unsupported.hpp>
#elif defined RTIBOOST_TYPEOF_EMULATION
#   define RTIBOOST_TYPEOF_TEXT "using typeof emulation"
#   include <rtiboost/typeof/message.hpp>
#   include <rtiboost/typeof/typeof_impl.hpp>
#   include <rtiboost/typeof/type_encoding.hpp>
#   include <rtiboost/typeof/template_encoding.hpp>
#   include <rtiboost/typeof/modifiers.hpp>
#   include <rtiboost/typeof/pointers_data_members.hpp>
#   include <rtiboost/typeof/register_functions.hpp>
#   include <rtiboost/typeof/register_fundamental.hpp>

#elif defined(RTIBOOST_TYPEOF_NATIVE)
#   define RTIBOOST_TYPEOF_TEXT "using native typeof"
#   include <rtiboost/typeof/message.hpp>
#   include <rtiboost/typeof/native.hpp>
#else
#   error typeof configuration error
#endif

// auto
#define RTIBOOST_AUTO(Var, Expr) RTIBOOST_TYPEOF(Expr) Var = Expr
#define RTIBOOST_AUTO_TPL(Var, Expr) RTIBOOST_TYPEOF_TPL(Expr) Var = Expr

#endif//RTIBOOST_TYPEOF_TYPEOF_HPP_INCLUDED
