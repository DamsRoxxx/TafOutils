#ifndef RTIBOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_PT_HPP_INCLUDED
#define RTIBOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_PT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_pt.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <rtiboost/detail/sp_typeinfo.hpp>
#include <rtiboost/assert.hpp>
#include <pthread.h>

namespace rtiboost
{

namespace detail
{

class sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    long use_count_;        // #shared
    long weak_count_;       // #weak + (#shared != 0)

    mutable pthread_mutex_t m_;

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
// HPUX 10.20 / DCE has a nonstandard pthread_mutex_init

#if defined(__hpux) && defined(_DECTHREADS_)
        RTIBOOST_VERIFY( pthread_mutex_init( &m_, pthread_mutexattr_default ) == 0 );
#else
        RTIBOOST_VERIFY( pthread_mutex_init( &m_, 0 ) == 0 );
#endif
    }

    virtual ~sp_counted_base() // nothrow
    {
        RTIBOOST_VERIFY( pthread_mutex_destroy( &m_ ) == 0 );
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() // nothrow
    {
        delete this;
    }

    virtual void * get_deleter( sp_typeinfo const & ti ) = 0;
    virtual void * get_untyped_deleter() = 0;

    void add_ref_copy()
    {
        RTIBOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        ++use_count_;
        RTIBOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
    }

    bool add_ref_lock() // true on success
    {
        RTIBOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        bool r = use_count_ == 0? false: ( ++use_count_, true );
        RTIBOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
        return r;
    }

    void release() // nothrow
    {
        RTIBOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        long new_use_count = --use_count_;
        RTIBOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );

        if( new_use_count == 0 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        RTIBOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        ++weak_count_;
        RTIBOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
    }

    void weak_release() // nothrow
    {
        RTIBOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        long new_weak_count = --weak_count_;
        RTIBOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );

        if( new_weak_count == 0 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        RTIBOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        long r = use_count_;
        RTIBOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );

        return r;
    }
};

} // namespace detail

} // namespace rtiboost

#endif  // #ifndef RTIBOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_PT_HPP_INCLUDED
