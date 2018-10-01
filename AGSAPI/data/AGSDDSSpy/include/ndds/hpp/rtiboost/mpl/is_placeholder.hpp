
#ifndef RTIBOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED
#define RTIBOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/arg_fwd.hpp>
#include <rtiboost/mpl/bool.hpp>
#include <rtiboost/mpl/aux_/yes_no.hpp>
#include <rtiboost/mpl/aux_/type_wrapper.hpp>
#include <rtiboost/mpl/aux_/nttp_decl.hpp>
#include <rtiboost/mpl/aux_/config/ctps.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>

namespace rtiboost { namespace mpl {

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T >
struct is_placeholder
    : bool_<false>
{
};

template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N) >
struct is_placeholder< arg<N> >
    : bool_<true>
{
};

#else

namespace aux {

aux::no_tag is_placeholder_helper(...);

template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N) >
aux::yes_tag is_placeholder_helper(aux::type_wrapper< arg<N> >*);

} // namespace aux

template< typename T >
struct is_placeholder
{
    static aux::type_wrapper<T>* get();
    RTIBOOST_STATIC_CONSTANT(bool, value = 
          sizeof(aux::is_placeholder_helper(get())) == sizeof(aux::yes_tag)
        );
    
    typedef bool_<value> type;
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // RTIBOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED
