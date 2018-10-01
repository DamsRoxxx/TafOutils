
#ifndef RTIBOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED

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

#include <rtiboost/mpl/aux_/config/nttp.hpp>

#if defined(RTIBOOST_MPL_CFG_NTTP_BUG)

typedef bool        _mpl_nttp_bool;
typedef int         _mpl_nttp_int;
typedef unsigned    _mpl_nttp_unsigned;
typedef long        _mpl_nttp_long;

#   include <rtiboost/preprocessor/cat.hpp>
#   define RTIBOOST_MPL_AUX_NTTP_DECL(T, x) RTIBOOST_PP_CAT(_mpl_nttp_,T) x /**/

#else

#   define RTIBOOST_MPL_AUX_NTTP_DECL(T, x) T x /**/

#endif

#endif // RTIBOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED
