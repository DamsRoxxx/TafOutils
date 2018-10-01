
#ifndef RTIBOOST_MPL_NOT_HPP_INCLUDED
#define RTIBOOST_MPL_NOT_HPP_INCLUDED

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

#include <rtiboost/mpl/bool.hpp>
#include <rtiboost/mpl/aux_/nttp_decl.hpp>
#include <rtiboost/mpl/aux_/nested_type_wknd.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/lambda_support.hpp>

namespace rtiboost { namespace mpl {

namespace aux {

template< RTIBOOST_MPL_AUX_NTTP_DECL(long, C_) > // 'long' is intentional here
struct not_impl
    : bool_<!C_>
{
};

} // namespace aux


template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(T)
    >
struct not_
    : aux::not_impl<
          RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(T)::value
        >
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(1,not_,(T))
};

RTIBOOST_MPL_AUX_NA_SPEC(1,not_)

}}

#endif // RTIBOOST_MPL_NOT_HPP_INCLUDED
