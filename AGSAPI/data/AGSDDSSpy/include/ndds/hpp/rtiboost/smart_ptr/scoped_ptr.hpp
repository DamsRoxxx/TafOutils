#ifndef RTIBOOST_SMART_PTR_SCOPED_PTR_HPP_INCLUDED
#define RTIBOOST_SMART_PTR_SCOPED_PTR_HPP_INCLUDED

//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  http://www.boost.org/libs/smart_ptr/scoped_ptr.htm
//

#include <rtiboost/config.hpp>
#include <rtiboost/assert.hpp>
#include <rtiboost/checked_delete.hpp>
#include <rtiboost/smart_ptr/detail/sp_nullptr_t.hpp>
#include <rtiboost/smart_ptr/detail/sp_disable_deprecated.hpp>
#include <rtiboost/detail/workaround.hpp>

#ifndef RTIBOOST_NO_AUTO_PTR
# include <memory>          // for std::auto_ptr
#endif

#if defined( RTIBOOST_SP_DISABLE_DEPRECATED )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace rtiboost
{

// Debug hooks

#if defined(RTIBOOST_SP_ENABLE_DEBUG_HOOKS)

void sp_scalar_constructor_hook(void * p);
void sp_scalar_destructor_hook(void * p);

#endif

//  scoped_ptr mimics a built-in pointer except that it guarantees deletion
//  of the object pointed to, either on destruction of the scoped_ptr or via
//  an explicit reset(). scoped_ptr is a simple solution for simple needs;
//  use shared_ptr or std::auto_ptr if your needs are more complex.

template<class T> class scoped_ptr // noncopyable
{
private:

    T * px;

    scoped_ptr(scoped_ptr const &);
    scoped_ptr & operator=(scoped_ptr const &);

    typedef scoped_ptr<T> this_type;

    void operator==( scoped_ptr const& ) const;
    void operator!=( scoped_ptr const& ) const;

public:

    typedef T element_type;

    explicit scoped_ptr( T * p = 0 ): px( p ) // never throws
    {
#if defined(RTIBOOST_SP_ENABLE_DEBUG_HOOKS)
        rtiboost::sp_scalar_constructor_hook( px );
#endif
    }

#ifndef RTIBOOST_NO_AUTO_PTR

    explicit scoped_ptr( std::auto_ptr<T> p ) RTIBOOST_NOEXCEPT : px( p.release() )
    {
#if defined(RTIBOOST_SP_ENABLE_DEBUG_HOOKS)
        rtiboost::sp_scalar_constructor_hook( px );
#endif
    }

#endif

    ~scoped_ptr() // never throws
    {
#if defined(RTIBOOST_SP_ENABLE_DEBUG_HOOKS)
        rtiboost::sp_scalar_destructor_hook( px );
#endif
        rtiboost::checked_delete( px );
    }

    void reset(T * p = 0) // never throws
    {
        RTIBOOST_ASSERT( p == 0 || p != px ); // catch self-reset errors
        this_type(p).swap(*this);
    }

    T & operator*() const // never throws
    {
        RTIBOOST_ASSERT( px != 0 );
        return *px;
    }

    T * operator->() const // never throws
    {
        RTIBOOST_ASSERT( px != 0 );
        return px;
    }

    T * get() const RTIBOOST_NOEXCEPT
    {
        return px;
    }

// implicit conversion to "bool"
#include <rtiboost/smart_ptr/detail/operator_bool.hpp>

    void swap(scoped_ptr & b) RTIBOOST_NOEXCEPT
    {
        T * tmp = b.px;
        b.px = px;
        px = tmp;
    }
};

#if !defined( RTIBOOST_NO_CXX11_NULLPTR )

template<class T> inline bool operator==( scoped_ptr<T> const & p, rtiboost::detail::sp_nullptr_t ) RTIBOOST_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator==( rtiboost::detail::sp_nullptr_t, scoped_ptr<T> const & p ) RTIBOOST_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator!=( scoped_ptr<T> const & p, rtiboost::detail::sp_nullptr_t ) RTIBOOST_NOEXCEPT
{
    return p.get() != 0;
}

template<class T> inline bool operator!=( rtiboost::detail::sp_nullptr_t, scoped_ptr<T> const & p ) RTIBOOST_NOEXCEPT
{
    return p.get() != 0;
}

#endif

template<class T> inline void swap(scoped_ptr<T> & a, scoped_ptr<T> & b) RTIBOOST_NOEXCEPT
{
    a.swap(b);
}

// get_pointer(p) is a generic way to say p.get()

template<class T> inline T * get_pointer(scoped_ptr<T> const & p) RTIBOOST_NOEXCEPT
{
    return p.get();
}

} // namespace rtiboost

#if defined( RTIBOOST_SP_DISABLE_DEPRECATED )
#pragma GCC diagnostic pop
#endif

#endif // #ifndef RTIBOOST_SMART_PTR_SCOPED_PTR_HPP_INCLUDED
