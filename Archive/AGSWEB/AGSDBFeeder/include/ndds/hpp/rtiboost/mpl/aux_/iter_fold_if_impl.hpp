
#ifndef RTIBOOST_MPL_AUX_ITER_FOLD_IF_IMPL_HPP_INCLUDED
#define RTIBOOST_MPL_AUX_ITER_FOLD_IF_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
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
#   include <rtiboost/mpl/identity.hpp>
#   include <rtiboost/mpl/next.hpp>
#   include <rtiboost/mpl/if.hpp>
#   include <rtiboost/mpl/apply.hpp>
#   include <rtiboost/mpl/aux_/value_wknd.hpp>
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER iter_fold_if_impl.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/unrolling.hpp>
#   include <rtiboost/preprocessor/arithmetic/sub.hpp>
#   include <rtiboost/preprocessor/repeat.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/dec.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

namespace rtiboost { namespace mpl { namespace aux {

template< typename Iterator, typename State >
struct iter_fold_if_null_step
{
    typedef State state;
    typedef Iterator iterator;
};

template< bool >
struct iter_fold_if_step_impl
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef typename apply2<StateOp,State,Iterator>::type state;
        typedef typename IteratorOp::type iterator;
    };
};

template<>
struct iter_fold_if_step_impl<false>
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef State state;
        typedef Iterator iterator;
    };
};

// agurt, 25/jun/02: MSVC 6.5 workaround, had to get rid of inheritance 
// here and in 'iter_fold_if_backward_step', because sometimes it interfered 
// with the "early template instantiation bug" in _really_ ugly ways
template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename Predicate
    >
struct iter_fold_if_forward_step
{
    typedef typename apply2<Predicate,State,Iterator>::type not_last;
    typedef typename iter_fold_if_step_impl<
          RTIBOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,ForwardOp,mpl::next<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename BackwardOp
    , typename Predicate
    >
struct iter_fold_if_backward_step
{
    typedef typename apply2<Predicate,State,Iterator>::type not_last;
    typedef typename iter_fold_if_step_impl<
          RTIBOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,BackwardOp,identity<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};


// local macros, #undef-ined at the end of the header

#   define RTIBOOST_AUX_ITER_FOLD_FORWARD_STEP(unused, i, unused2) \
    typedef iter_fold_if_forward_step< \
          typename RTIBOOST_PP_CAT(forward_step,i)::iterator \
        , typename RTIBOOST_PP_CAT(forward_step,i)::state \
        , ForwardOp \
        , ForwardPredicate \
        > RTIBOOST_PP_CAT(forward_step, RTIBOOST_PP_INC(i)); \
    /**/

#   define RTIBOOST_AUX_ITER_FOLD_BACKWARD_STEP_FUNC(i) \
    typedef iter_fold_if_backward_step< \
          typename RTIBOOST_PP_CAT(forward_step,RTIBOOST_PP_DEC(i))::iterator \
        , typename RTIBOOST_PP_CAT(backward_step,i)::state \
        , BackwardOp \
        , BackwardPredicate \
        > RTIBOOST_PP_CAT(backward_step,RTIBOOST_PP_DEC(i)); \
    /**/

#   define RTIBOOST_AUX_ITER_FOLD_BACKWARD_STEP(unused, i, unused2) \
    RTIBOOST_AUX_ITER_FOLD_BACKWARD_STEP_FUNC( \
        RTIBOOST_PP_SUB_D(1,RTIBOOST_MPL_LIMIT_UNROLLING,i) \
        ) \
    /**/

#   define RTIBOOST_AUX_LAST_FORWARD_STEP \
    RTIBOOST_PP_CAT(forward_step, RTIBOOST_MPL_LIMIT_UNROLLING) \
    /**/

#   define RTIBOOST_AUX_LAST_BACKWARD_STEP \
    RTIBOOST_PP_CAT(backward_step, RTIBOOST_MPL_LIMIT_UNROLLING) \
    /**/

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename ForwardPredicate
    , typename BackwardOp
    , typename BackwardPredicate
    >
struct iter_fold_if_impl
{
 private:
    typedef iter_fold_if_null_step<Iterator,State> forward_step0;
    RTIBOOST_PP_REPEAT(
          RTIBOOST_MPL_LIMIT_UNROLLING
        , RTIBOOST_AUX_ITER_FOLD_FORWARD_STEP
        , unused
        )
    
    typedef typename if_<
          typename RTIBOOST_AUX_LAST_FORWARD_STEP::not_last
        , iter_fold_if_impl<
              typename RTIBOOST_AUX_LAST_FORWARD_STEP::iterator
            , typename RTIBOOST_AUX_LAST_FORWARD_STEP::state
            , ForwardOp
            , ForwardPredicate
            , BackwardOp
            , BackwardPredicate
            >
        , iter_fold_if_null_step<
              typename RTIBOOST_AUX_LAST_FORWARD_STEP::iterator
            , typename RTIBOOST_AUX_LAST_FORWARD_STEP::state
            >
        >::type RTIBOOST_AUX_LAST_BACKWARD_STEP;

    RTIBOOST_PP_REPEAT(
          RTIBOOST_MPL_LIMIT_UNROLLING
        , RTIBOOST_AUX_ITER_FOLD_BACKWARD_STEP
        , unused
        )

 public:
    typedef typename backward_step0::state state;
    typedef typename RTIBOOST_AUX_LAST_BACKWARD_STEP::iterator iterator;
};

#   undef RTIBOOST_AUX_LAST_BACKWARD_STEP
#   undef RTIBOOST_AUX_LAST_FORWARD_STEP
#   undef RTIBOOST_AUX_ITER_FOLD_BACKWARD_STEP
#   undef RTIBOOST_AUX_ITER_FOLD_BACKWARD_STEP_FUNC
#   undef RTIBOOST_AUX_ITER_FOLD_FORWARD_STEP

}}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_AUX_ITER_FOLD_IF_IMPL_HPP_INCLUDED
