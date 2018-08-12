
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED

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

#if !defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   include <rtiboost/mpl/next.hpp>
#   include <rtiboost/mpl/apply_wrap.hpp>
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if    !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER advance_forward.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/unrolling.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>
#   include <rtiboost/mpl/aux_/config/eti.hpp>

#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/cat.hpp>
#   include <rtiboost/preprocessor/inc.hpp>

namespace rtiboost { namespace mpl { namespace aux {

// forward declaration
template< RTIBOOST_MPL_AUX_NTTP_DECL(long, N) > struct advance_forward;

#   define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_UNROLLING, <rtiboost/mpl/aux_/advance_forward.hpp>))
#   include RTIBOOST_PP_ITERATE()

// implementation for N that exceeds RTIBOOST_MPL_LIMIT_UNROLLING
template< RTIBOOST_MPL_AUX_NTTP_DECL(long, N) > 
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<RTIBOOST_MPL_LIMIT_UNROLLING>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - RTIBOOST_MPL_LIMIT_UNROLLING) < 0
                    ? 0
                    : N - RTIBOOST_MPL_LIMIT_UNROLLING
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// RTIBOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // RTIBOOST_PP_IS_ITERATING
#if RTIBOOST_PP_ITERATION_DEPTH() == 1
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

template<>
struct advance_forward< RTIBOOST_PP_FRAME_ITERATION(1) >
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;

#if i_ > 0
#   define RTIBOOST_PP_ITERATION_PARAMS_2 \
    (3,(1, i_, <rtiboost/mpl/aux_/advance_forward.hpp>))
#   include RTIBOOST_PP_ITERATE()
#endif
        typedef RTIBOOST_PP_CAT(iter,i_) type;
    };

#if defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };
#endif
};

#undef i_

///// iteration, depth == 2

#elif RTIBOOST_PP_ITERATION_DEPTH() == 2

#   define RTIBOOST_AUX778076_ITER_0 RTIBOOST_PP_CAT(iter,RTIBOOST_PP_DEC(RTIBOOST_PP_FRAME_ITERATION(2)))
#   define RTIBOOST_AUX778076_ITER_1 RTIBOOST_PP_CAT(iter,RTIBOOST_PP_FRAME_ITERATION(2))

        typedef typename next<RTIBOOST_AUX778076_ITER_0>::type RTIBOOST_AUX778076_ITER_1;
        
#   undef RTIBOOST_AUX778076_ITER_1
#   undef RTIBOOST_AUX778076_ITER_0

#endif // RTIBOOST_PP_ITERATION_DEPTH()
#endif // RTIBOOST_PP_IS_ITERATING
