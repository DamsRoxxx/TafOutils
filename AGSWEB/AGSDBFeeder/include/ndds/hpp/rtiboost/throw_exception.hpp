#ifndef RTI_UUID_AA15E74A856F11E08B8D93F24824019B
#define RTI_UUID_AA15E74A856F11E08B8D93F24824019B
#if (__GNUC__*100+__GNUC_MINOR__>301) && !defined(RTIBOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma GCC system_header
#endif
#if defined(_MSC_VER) && !defined(RTIBOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(push,1)
#endif

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/throw_exception.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2008-2009 Emil Dotchevski and Reverge Studios, Inc.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  http://www.boost.org/libs/utility/throw_exception.html
//

#include <rtiboost/detail/workaround.hpp>
#include <rtiboost/config.hpp>
#include <exception>

#if !defined( RTIBOOST_EXCEPTION_DISABLE ) && defined( __BORLANDC__ ) && RTIBOOST_WORKAROUND( __BORLANDC__, RTIBOOST_TESTED_AT(0x593) )
# define RTIBOOST_EXCEPTION_DISABLE
#endif

#if !defined( RTIBOOST_EXCEPTION_DISABLE ) && defined( RTIBOOST_MSVC ) && RTIBOOST_WORKAROUND( RTIBOOST_MSVC, < 1310 )
# define RTIBOOST_EXCEPTION_DISABLE
#endif

#if !defined( RTIBOOST_EXCEPTION_DISABLE )
# include <rtiboost/exception/exception.hpp>
#if !defined(RTIBOOST_THROW_EXCEPTION_CURRENT_FUNCTION)
# include <rtiboost/current_function.hpp>
# define RTIBOOST_THROW_EXCEPTION_CURRENT_FUNCTION RTIBOOST_CURRENT_FUNCTION
#endif
# define RTIBOOST_THROW_EXCEPTION(x) ::rtiboost::exception_detail::throw_exception_(x,RTIBOOST_THROW_EXCEPTION_CURRENT_FUNCTION,__FILE__,__LINE__)
#else
# define RTIBOOST_THROW_EXCEPTION(x) ::rtiboost::throw_exception(x)
#endif

namespace rtiboost
{
#ifdef RTIBOOST_NO_EXCEPTIONS

void throw_exception( std::exception const & e ); // user defined

#else

inline void throw_exception_assert_compatibility( std::exception const & ) { }

template<class E> RTIBOOST_NORETURN inline void throw_exception( E const & e )
{
    //All boost exceptions are required to derive from std::exception,
    //to ensure compatibility with RTIBOOST_NO_EXCEPTIONS.
    throw_exception_assert_compatibility(e);

#ifndef RTIBOOST_EXCEPTION_DISABLE
    throw enable_current_exception(enable_error_info(e));
#else
    throw e;
#endif
}

#endif

#if !defined( RTIBOOST_EXCEPTION_DISABLE )
    namespace
    exception_detail
    {
        template <class E>
        RTIBOOST_NORETURN
        void
        throw_exception_( E const & x, char const * current_function, char const * file, int line )
        {
            rtiboost::throw_exception(
                set_info(
                    set_info(
                        set_info(
                            enable_error_info(x),
                            throw_function(current_function)),
                        throw_file(file)),
                    throw_line(line)));
        }
    }
#endif
} // namespace rtiboost

#if defined(_MSC_VER) && !defined(RTIBOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif
