#ifndef RTIBOOST_CORE_DEMANGLE_HPP_INCLUDED
#define RTIBOOST_CORE_DEMANGLE_HPP_INCLUDED

// core::demangle
//
// Copyright 2014 Peter Dimov
// Copyright 2014 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <rtiboost/config.hpp>
#include <string>

#if defined(RTIBOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

// __has_include is currently supported by GCC and Clang. However GCC 4.9 may have issues and
// returns 1 for 'defined( __has_include )', while '__has_include' is actually not supported:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63662
#if defined( __has_include ) && (!defined( RTIBOOST_GCC ) || (__GNUC__ + 0) >= 5)
# if __has_include(<cxxabi.h>)
#  define RTIBOOST_CORE_HAS_CXXABI_H
# endif
#elif defined( __GLIBCXX__ ) || defined( __GLIBCPP__ )
# define RTIBOOST_CORE_HAS_CXXABI_H
#endif

#if defined( RTIBOOST_CORE_HAS_CXXABI_H )
# include <cxxabi.h>
// For some archtectures (mips, mips64, x86, x86_64) cxxabi.h in Android NDK is implemented by gabi++ library
// (https://android.googlesource.com/platform/ndk/+/master/sources/cxx-stl/gabi++/), which does not implement
// abi::__cxa_demangle(). We detect this implementation by checking the include guard here.
# if defined( __GABIXX_CXXABI_H__ )
#  undef RTIBOOST_CORE_HAS_CXXABI_H
# else
#  include <cstdlib>
#  include <cstddef>
# endif
#endif

namespace rtiboost
{

namespace core
{

inline char const * demangle_alloc( char const * name ) RTIBOOST_NOEXCEPT;
inline void demangle_free( char const * name ) RTIBOOST_NOEXCEPT;

class scoped_demangled_name
{
private:
    char const * m_p;

public:
    explicit scoped_demangled_name( char const * name ) RTIBOOST_NOEXCEPT :
        m_p( demangle_alloc( name ) )
    {
    }

    ~scoped_demangled_name() RTIBOOST_NOEXCEPT
    {
        demangle_free( m_p );
    }

    char const * get() const RTIBOOST_NOEXCEPT
    {
        return m_p;
    }

    RTIBOOST_DELETED_FUNCTION(scoped_demangled_name( scoped_demangled_name const& ))
    RTIBOOST_DELETED_FUNCTION(scoped_demangled_name& operator= ( scoped_demangled_name const& ))
};


#if defined( RTIBOOST_CORE_HAS_CXXABI_H )

inline char const * demangle_alloc( char const * name ) RTIBOOST_NOEXCEPT
{
    int status = 0;
    std::size_t size = 0;
    return abi::__cxa_demangle( name, NULL, &size, &status );
}

inline void demangle_free( char const * name ) RTIBOOST_NOEXCEPT
{
    std::free( const_cast< char* >( name ) );
}

inline std::string demangle( char const * name )
{
    scoped_demangled_name demangled_name( name );
    char const * const p = demangled_name.get();
    if( p )
    {
        return p;
    }
    else
    {
        return name;
    }
}

#else

inline char const * demangle_alloc( char const * name ) RTIBOOST_NOEXCEPT
{
    return name;
}

inline void demangle_free( char const * ) RTIBOOST_NOEXCEPT
{
}

inline std::string demangle( char const * name )
{
    return name;
}

#endif

} // namespace core

} // namespace rtiboost

#undef RTIBOOST_CORE_HAS_CXXABI_H

#endif // #ifndef RTIBOOST_CORE_DEMANGLE_HPP_INCLUDED
