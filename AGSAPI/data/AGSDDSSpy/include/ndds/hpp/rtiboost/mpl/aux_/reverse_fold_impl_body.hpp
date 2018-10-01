
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#if !defined(RTIBOOST_PP_IS_ITERATING)

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

#   include <rtiboost/mpl/limits/unrolling.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/repeat.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>

#   include <rtiboost/preprocessor/arithmetic/sub.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/dec.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

// local macros, #undef-ined at the end of the header

#   define RTIBOOST_AUX778076_ITER_FOLD_FORWARD_STEP(unused, n_, unused2) \
    typedef typename apply2< \
          ForwardOp \
        , RTIBOOST_PP_CAT(fwd_state,n_) \
        , RTIBOOST_AUX778076_FOLD_IMPL_OP(RTIBOOST_PP_CAT(iter,n_)) \
        >::type RTIBOOST_PP_CAT(fwd_state,RTIBOOST_PP_INC(n_)); \
    typedef typename mpl::next<RTIBOOST_PP_CAT(iter,n_)>::type \
        RTIBOOST_PP_CAT(iter,RTIBOOST_PP_INC(n_)); \
    /**/

#   define RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC(n_) \
    typedef typename apply2< \
          BackwardOp \
        , RTIBOOST_PP_CAT(bkwd_state,n_) \
        , RTIBOOST_AUX778076_FOLD_IMPL_OP(RTIBOOST_PP_CAT(iter,RTIBOOST_PP_DEC(n_))) \
        >::type RTIBOOST_PP_CAT(bkwd_state,RTIBOOST_PP_DEC(n_)); \
    /**/

#   define RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP(unused, n_, j) \
    RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC( \
          RTIBOOST_PP_SUB_D(1,j,n_) \
        ) \
    /**/

#   define RTIBOOST_AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(n_) \
    typedef typename nested_chunk::state RTIBOOST_PP_CAT(bkwd_state,n_);
    /**/

#   define RTIBOOST_AUX778076_FOLD_IMPL_NAME \
    RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_impl) \
    /**/

#   define RTIBOOST_AUX778076_FOLD_CHUNK_NAME \
    RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_chunk) \
    /**/

namespace rtiboost { namespace mpl { namespace aux {

/// forward declaration
template<
      RTIBOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME;

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(RTIBOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

#   define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_UNROLLING, <rtiboost/mpl/aux_/reverse_fold_impl_body.hpp>))
#   include RTIBOOST_PP_ITERATE()

// implementation for N that exceeds RTIBOOST_MPL_LIMIT_UNROLLING
template<
      RTIBOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME
{
    typedef First iter0;
    typedef State fwd_state0;

    RTIBOOST_MPL_PP_REPEAT(
          RTIBOOST_MPL_LIMIT_UNROLLING
        , RTIBOOST_AUX778076_ITER_FOLD_FORWARD_STEP
        , unused
        )

    typedef RTIBOOST_AUX778076_FOLD_IMPL_NAME<
          ( (N - RTIBOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - RTIBOOST_MPL_LIMIT_UNROLLING )
        , RTIBOOST_PP_CAT(iter,RTIBOOST_MPL_LIMIT_UNROLLING)
        , Last
        , RTIBOOST_PP_CAT(fwd_state,RTIBOOST_MPL_LIMIT_UNROLLING)
        , BackwardOp
        , ForwardOp
        > nested_chunk;
        
    RTIBOOST_AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(RTIBOOST_MPL_LIMIT_UNROLLING)

    RTIBOOST_MPL_PP_REPEAT(
          RTIBOOST_MPL_LIMIT_UNROLLING
        , RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP
        , RTIBOOST_MPL_LIMIT_UNROLLING
        )

    typedef bkwd_state0 state;
    typedef typename nested_chunk::iterator iterator;
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME<-1,First,Last,State,BackwardOp,ForwardOp>
{
    typedef RTIBOOST_AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,RTIBOOST_AUX778076_FOLD_IMPL_OP(First)>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , RTIBOOST_AUX778076_FOLD_IMPL_OP(First)
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME<-1,Last,Last,State,BackwardOp,ForwardOp>
{
    typedef State state;
    typedef Last iterator;
};

#else // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< RTIBOOST_MPL_AUX_NTTP_DECL(long, N) >
struct RTIBOOST_AUX778076_FOLD_CHUNK_NAME;

#   define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_UNROLLING, <rtiboost/mpl/aux_/reverse_fold_impl_body.hpp>))
#   include RTIBOOST_PP_ITERATE()

// implementation for N that exceeds RTIBOOST_MPL_LIMIT_UNROLLING
template< RTIBOOST_MPL_AUX_NTTP_DECL(long, N) > 
struct RTIBOOST_AUX778076_FOLD_CHUNK_NAME
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        > 
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;

        RTIBOOST_MPL_PP_REPEAT(
              RTIBOOST_MPL_LIMIT_UNROLLING
            , RTIBOOST_AUX778076_ITER_FOLD_FORWARD_STEP
            , unused
            )

        typedef RTIBOOST_AUX778076_FOLD_IMPL_NAME<
              ( (N - RTIBOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - RTIBOOST_MPL_LIMIT_UNROLLING )
            , RTIBOOST_PP_CAT(iter,RTIBOOST_MPL_LIMIT_UNROLLING)
            , Last
            , RTIBOOST_PP_CAT(fwd_state,RTIBOOST_MPL_LIMIT_UNROLLING)
            , BackwardOp
            , ForwardOp
            > nested_chunk;
            
        RTIBOOST_AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(RTIBOOST_MPL_LIMIT_UNROLLING)

        RTIBOOST_MPL_PP_REPEAT(
              RTIBOOST_MPL_LIMIT_UNROLLING
            , RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP
            , RTIBOOST_MPL_LIMIT_UNROLLING
            )

        typedef bkwd_state0 state;
        typedef typename nested_chunk::iterator iterator;
    };
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_step);

template<
      typename Last
    , typename State
    >
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)
{
    typedef Last iterator;
    typedef State state;
};

template<> 
struct RTIBOOST_AUX778076_FOLD_CHUNK_NAME<-1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        > 
    struct result_
    {
        typedef typename if_<
              typename is_same<First,Last>::type
            , RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)<Last,State>
            , RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_step)<First,Last,State,BackwardOp,ForwardOp>
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

#if defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_step)
{
    typedef RTIBOOST_AUX778076_FOLD_CHUNK_NAME<-1>::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,RTIBOOST_AUX778076_FOLD_IMPL_OP(First)>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , RTIBOOST_AUX778076_FOLD_IMPL_OP(First)
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      RTIBOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME
    : RTIBOOST_AUX778076_FOLD_CHUNK_NAME<N>
        ::template result_<First,Last,State,BackwardOp,ForwardOp>
{
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}}

#   undef RTIBOOST_AUX778076_FIRST_BACKWARD_STATE_TYPEDEF
#   undef RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP
#   undef RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC
#   undef RTIBOOST_AUX778076_ITER_FOLD_FORWARD_STEP

#undef RTIBOOST_AUX778076_FOLD_IMPL_OP
#undef RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX

///// iteration

#else

#   define n_ RTIBOOST_PP_FRAME_ITERATION(1)

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(RTIBOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME<n_,First,Last,State,BackwardOp,ForwardOp>
{
    typedef First iter0;
    typedef State fwd_state0;

    RTIBOOST_MPL_PP_REPEAT(
          n_
        , RTIBOOST_AUX778076_ITER_FOLD_FORWARD_STEP
        , unused
        )

    typedef RTIBOOST_PP_CAT(fwd_state,n_) RTIBOOST_PP_CAT(bkwd_state,n_);

    RTIBOOST_MPL_PP_REPEAT(
          n_
        , RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP
        , n_
        )

    typedef bkwd_state0 state;
    typedef RTIBOOST_PP_CAT(iter,n_) iterator;
};

#else

template<> struct RTIBOOST_AUX778076_FOLD_CHUNK_NAME<n_>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;

        RTIBOOST_MPL_PP_REPEAT(
              n_
            , RTIBOOST_AUX778076_ITER_FOLD_FORWARD_STEP
            , unused
            )

        typedef RTIBOOST_PP_CAT(fwd_state,n_) RTIBOOST_PP_CAT(bkwd_state,n_);

        RTIBOOST_MPL_PP_REPEAT(
              n_
            , RTIBOOST_AUX778076_ITER_FOLD_BACKWARD_STEP
            , n_
            )

        typedef bkwd_state0 state;
        typedef RTIBOOST_PP_CAT(iter,n_) iterator;
    };

#if defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef n_

#endif // RTIBOOST_PP_IS_ITERATING
