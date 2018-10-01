
#ifndef RTIBOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED
#define RTIBOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/O1_size_fwd.hpp>
#include <rtiboost/mpl/long.hpp>
#include <rtiboost/mpl/if.hpp>
#include <rtiboost/mpl/aux_/has_size.hpp>
#include <rtiboost/mpl/aux_/config/forwarding.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

namespace rtiboost { namespace mpl {

// default implementation - returns 'Sequence::size' if sequence has a 'size'
// member, and -1 otherwise; conrete sequences might override it by 
// specializing either the 'O1_size_impl' or the primary 'O1_size' template

#   if !RTIBOOST_WORKAROUND(RTIBOOST_MSVC, < 1300) \
    && !RTIBOOST_WORKAROUND(__MWERKS__, RTIBOOST_TESTED_AT(0x3003))

namespace aux {
template< typename Sequence > struct O1_size_impl
    : Sequence::size
{
};
}

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
#if !defined(RTIBOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              aux::has_size<Sequence>
            , aux::O1_size_impl<Sequence>
            , long_<-1>
            >::type
    {
#else
    {
        typedef typename if_<
              aux::has_size<Sequence>
            , aux::O1_size_impl<Sequence>
            , long_<-1>
            >::type type;

        RTIBOOST_STATIC_CONSTANT(long, value =
              (if_<
                  aux::has_size<Sequence>
                , aux::O1_size_impl<Sequence>
                , long_<-1>
                >::type::value)
            );
#endif
    };
};

#   else // RTIBOOST_MSVC

template< typename Tag >
struct O1_size_impl
{
    template< typename Sequence > struct apply
        : long_<-1>
        {
        };
};

#   endif

}}

#endif // RTIBOOST_MPL_O1_SIZE_IMPL_HPP_INCLUDED
