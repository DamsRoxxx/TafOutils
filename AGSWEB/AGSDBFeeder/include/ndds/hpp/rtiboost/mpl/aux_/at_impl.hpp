
#ifndef RTIBOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

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

#include <rtiboost/mpl/begin_end.hpp>
#include <rtiboost/mpl/advance.hpp>
#include <rtiboost/mpl/deref.hpp>
#include <rtiboost/mpl/aux_/traits_lambda_spec.hpp>

namespace rtiboost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'at_impl' or the primary 'at' template

template< typename Tag >
struct at_impl
{
    template< typename Sequence, typename N > struct apply
    {
        typedef typename advance<
              typename begin<Sequence>::type
            , N
            >::type iter_;

        typedef typename deref<iter_>::type type;
    };
};

RTIBOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, at_impl)

}}

#endif // RTIBOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED
