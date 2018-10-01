
#ifndef RTIBOOST_MPL_BACK_INSERTER_HPP_INCLUDED
#define RTIBOOST_MPL_BACK_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/push_back.hpp>
#include <rtiboost/mpl/inserter.hpp>

namespace rtiboost {
namespace mpl {

template<
      typename Sequence
    >
struct back_inserter
    : inserter< Sequence,push_back<> >
{
};

}}

#endif // RTIBOOST_MPL_BACK_INSERTER_HPP_INCLUDED
