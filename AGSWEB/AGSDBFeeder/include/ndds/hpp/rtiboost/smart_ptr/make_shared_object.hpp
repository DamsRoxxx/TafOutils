#ifndef RTIBOOST_SMART_PTR_MAKE_SHARED_OBJECT_HPP_INCLUDED
#define RTIBOOST_SMART_PTR_MAKE_SHARED_OBJECT_HPP_INCLUDED

//  make_shared_object.hpp
//
//  Copyright (c) 2007, 2008, 2012 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/smart_ptr/make_shared.html
//  for documentation.

#include <rtiboost/config.hpp>
#include <rtiboost/smart_ptr/shared_ptr.hpp>
#include <rtiboost/smart_ptr/detail/sp_forward.hpp>
#include <rtiboost/type_traits/type_with_alignment.hpp>
#include <rtiboost/type_traits/alignment_of.hpp>
#include <cstddef>
#include <new>

namespace rtiboost
{

namespace detail
{

template< std::size_t N, std::size_t A > struct sp_aligned_storage
{
    union type
    {
        char data_[ N ];
        typename rtiboost::type_with_alignment< A >::type align_;
    };
};

template< class T > class sp_ms_deleter
{
private:

    typedef typename sp_aligned_storage< sizeof( T ), ::rtiboost::alignment_of< T >::value >::type storage_type;

    bool initialized_;
    storage_type storage_;

private:

    void destroy()
    {
        if( initialized_ )
        {
#if defined( __GNUC__ )

            // fixes incorrect aliasing warning
            T * p = reinterpret_cast< T* >( storage_.data_ );
            p->~T();

#else

            reinterpret_cast< T* >( storage_.data_ )->~T();

#endif

            initialized_ = false;
        }
    }

public:

    sp_ms_deleter() RTIBOOST_NOEXCEPT : initialized_( false )
    {
    }

    template<class A> explicit sp_ms_deleter( A const & ) RTIBOOST_NOEXCEPT : initialized_( false )
    {
    }

    // optimization: do not copy storage_
    sp_ms_deleter( sp_ms_deleter const & ) RTIBOOST_NOEXCEPT : initialized_( false )
    {
    }

    ~sp_ms_deleter()
    {
        destroy();
    }

    void operator()( T * )
    {
        destroy();
    }

    static void operator_fn( T* ) // operator() can't be static
    {
    }

    void * address() RTIBOOST_NOEXCEPT
    {
        return storage_.data_;
    }

    void set_initialized() RTIBOOST_NOEXCEPT
    {
        initialized_ = true;
    }
};

template< class T, class A > class sp_as_deleter
{
private:

    typedef typename sp_aligned_storage< sizeof( T ), ::rtiboost::alignment_of< T >::value >::type storage_type;

    storage_type storage_;
    A a_;
    bool initialized_;

private:

    void destroy()
    {
        if( initialized_ )
        {
            T * p = reinterpret_cast< T* >( storage_.data_ );

#if !defined( RTIBOOST_NO_CXX11_ALLOCATOR )

            std::allocator_traits<A>::destroy( a_, p );

#else

            p->~T();

#endif

            initialized_ = false;
        }
    }

public:

    sp_as_deleter( A const & a ) RTIBOOST_NOEXCEPT : a_( a ), initialized_( false )
    {
    }

    // optimization: do not copy storage_
    sp_as_deleter( sp_as_deleter const & r ) RTIBOOST_NOEXCEPT : a_( r.a_), initialized_( false )
    {
    }

    ~sp_as_deleter()
    {
        destroy();
    }

    void operator()( T * )
    {
        destroy();
    }

    static void operator_fn( T* ) // operator() can't be static
    {
    }

    void * address() RTIBOOST_NOEXCEPT
    {
        return storage_.data_;
    }

    void set_initialized() RTIBOOST_NOEXCEPT
    {
        initialized_ = true;
    }
};

template< class T > struct sp_if_not_array
{
    typedef rtiboost::shared_ptr< T > type;
};

#if !defined( RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template< class T > struct sp_if_not_array< T[] >
{
};

#if !defined( __BORLANDC__ ) || !RTIBOOST_WORKAROUND( __BORLANDC__, < 0x600 )

template< class T, std::size_t N > struct sp_if_not_array< T[N] >
{
};

#endif

#endif

} // namespace detail

#if !defined( RTIBOOST_NO_FUNCTION_TEMPLATE_ORDERING )
# define RTIBOOST_SP_MSD( T ) rtiboost::detail::sp_inplace_tag< rtiboost::detail::sp_ms_deleter< T > >()
#else
# define RTIBOOST_SP_MSD( T ) rtiboost::detail::sp_ms_deleter< T >()
#endif

// _noinit versions

template< class T > typename rtiboost::detail::sp_if_not_array< T >::type make_shared_noinit()
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T;
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A > typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared_noinit( A const & a )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T;
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

#if !defined( RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES ) && !defined( RTIBOOST_NO_CXX11_RVALUE_REFERENCES )

// Variadic templates, rvalue reference

template< class T, class... Args > typename rtiboost::detail::sp_if_not_array< T >::type make_shared( Args && ... args )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( rtiboost::detail::sp_forward<Args>( args )... );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class... Args > typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, Args && ... args )
{
#if !defined( RTIBOOST_NO_CXX11_ALLOCATOR )

    typedef typename std::allocator_traits<A>::template rebind_alloc<T> A2;
    A2 a2( a );

    typedef rtiboost::detail::sp_as_deleter< T, A2 > D;

    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), rtiboost::detail::sp_inplace_tag<D>(), a2 );

#else

    typedef rtiboost::detail::sp_ms_deleter< T > D;

    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), rtiboost::detail::sp_inplace_tag<D>(), a );

#endif

    D * pd = static_cast< D* >( pt._internal_get_untyped_deleter() );
    void * pv = pd->address();

#if !defined( RTIBOOST_NO_CXX11_ALLOCATOR )

    std::allocator_traits<A2>::construct( a2, static_cast< T* >( pv ), rtiboost::detail::sp_forward<Args>( args )... );

#else

    ::new( pv ) T( rtiboost::detail::sp_forward<Args>( args )... );

#endif

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

#else // !defined( RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES ) && !defined( RTIBOOST_NO_CXX11_RVALUE_REFERENCES )

// Common zero-argument versions

template< class T > typename rtiboost::detail::sp_if_not_array< T >::type make_shared()
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T();
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A > typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T();
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

#if !defined( RTIBOOST_NO_CXX11_RVALUE_REFERENCES )

// For example MSVC 10.0

template< class T, class A1 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1, A2 && a2 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1, A2 && a2 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1, A2 && a2, A3 && a3 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1, A2 && a2, A3 && a3 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1, A2 && a2, A3 && a3, A4 && a4 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1, A2 && a2, A3 && a3, A4 && a4 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 ), 
        rtiboost::detail::sp_forward<A6>( a6 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5, class A6 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 ), 
        rtiboost::detail::sp_forward<A6>( a6 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 ), 
        rtiboost::detail::sp_forward<A6>( a6 ), 
        rtiboost::detail::sp_forward<A7>( a7 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 ), 
        rtiboost::detail::sp_forward<A6>( a6 ), 
        rtiboost::detail::sp_forward<A7>( a7 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7, A8 && a8 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 ), 
        rtiboost::detail::sp_forward<A6>( a6 ), 
        rtiboost::detail::sp_forward<A7>( a7 ), 
        rtiboost::detail::sp_forward<A8>( a8 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7, A8 && a8 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 ), 
        rtiboost::detail::sp_forward<A6>( a6 ), 
        rtiboost::detail::sp_forward<A7>( a7 ), 
        rtiboost::detail::sp_forward<A8>( a8 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7, A8 && a8, A9 && a9 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T(
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 ), 
        rtiboost::detail::sp_forward<A6>( a6 ), 
        rtiboost::detail::sp_forward<A7>( a7 ), 
        rtiboost::detail::sp_forward<A8>( a8 ), 
        rtiboost::detail::sp_forward<A9>( a9 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 && a1, A2 && a2, A3 && a3, A4 && a4, A5 && a5, A6 && a6, A7 && a7, A8 && a8, A9 && a9 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( 
        rtiboost::detail::sp_forward<A1>( a1 ), 
        rtiboost::detail::sp_forward<A2>( a2 ), 
        rtiboost::detail::sp_forward<A3>( a3 ), 
        rtiboost::detail::sp_forward<A4>( a4 ), 
        rtiboost::detail::sp_forward<A5>( a5 ), 
        rtiboost::detail::sp_forward<A6>( a6 ), 
        rtiboost::detail::sp_forward<A7>( a7 ), 
        rtiboost::detail::sp_forward<A8>( a8 ), 
        rtiboost::detail::sp_forward<A9>( a9 )
        );

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

#else // !defined( RTIBOOST_NO_CXX11_RVALUE_REFERENCES )

// C++03 version

template< class T, class A1 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1, A2 const & a2 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1, A2 const & a2 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1, A2 const & a2, A3 const & a3 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1, A2 const & a2, A3 const & a3 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5, a6 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5, class A6 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5, a6 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5, a6, a7 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5, a6, a7 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5, a6, a7, a8 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5, a6, a7, a8 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 >
typename rtiboost::detail::sp_if_not_array< T >::type make_shared( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ) );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5, a6, a7, a8, a9 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

template< class T, class A, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 >
typename rtiboost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9 )
{
    rtiboost::shared_ptr< T > pt( static_cast< T* >( 0 ), RTIBOOST_SP_MSD( T ), a );

    rtiboost::detail::sp_ms_deleter< T > * pd = static_cast<rtiboost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( a1, a2, a3, a4, a5, a6, a7, a8, a9 );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    rtiboost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return rtiboost::shared_ptr< T >( pt, pt2 );
}

#endif // !defined( RTIBOOST_NO_CXX11_RVALUE_REFERENCES )

#endif // !defined( RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES ) && !defined( RTIBOOST_NO_CXX11_RVALUE_REFERENCES )

#undef RTIBOOST_SP_MSD

} // namespace rtiboost

#endif // #ifndef RTIBOOST_SMART_PTR_MAKE_SHARED_OBJECT_HPP_INCLUDED
