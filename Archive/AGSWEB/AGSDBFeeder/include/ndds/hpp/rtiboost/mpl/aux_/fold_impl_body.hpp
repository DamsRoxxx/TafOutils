
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

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
#   include <rtiboost/mpl/aux_/config/workaround.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>
#   include <rtiboost/mpl/aux_/config/eti.hpp>

#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/dec.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

// local macros, #undef-ined at the end of the header

#   define RTIBOOST_AUX778076_ITER_FOLD_STEP(unused, i, unused2) \
    typedef typename apply2< \
          ForwardOp \
        , RTIBOOST_PP_CAT(state,i) \
        , RTIBOOST_AUX778076_FOLD_IMPL_OP(RTIBOOST_PP_CAT(iter,i)) \
        >::type RTIBOOST_PP_CAT(state,RTIBOOST_PP_INC(i)); \
    typedef typename mpl::next<RTIBOOST_PP_CAT(iter,i)>::type \
        RTIBOOST_PP_CAT(iter,RTIBOOST_PP_INC(i)); \
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
      RTIBOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME;

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   if !RTIBOOST_WORKAROUND(__BORLANDC__, < 0x600)

#   define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_UNROLLING, <rtiboost/mpl/aux_/fold_impl_body.hpp>))
#   include RTIBOOST_PP_ITERATE()

// implementation for N that exceeds RTIBOOST_MPL_LIMIT_UNROLLING
template<
      RTIBOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME
{
    typedef RTIBOOST_AUX778076_FOLD_IMPL_NAME<
          RTIBOOST_MPL_LIMIT_UNROLLING
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef RTIBOOST_AUX778076_FOLD_IMPL_NAME<
          ( (N - RTIBOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - RTIBOOST_MPL_LIMIT_UNROLLING )
        , typename chunk_::iterator
        , Last
        , typename chunk_::state
        , ForwardOp
        > res_;
        
    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME<-1,First,Last,State,ForwardOp>
    : RTIBOOST_AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,RTIBOOST_AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME<-1,Last,Last,State,ForwardOp>
{
    typedef State state;
    typedef Last iterator;
};

#   else // RTIBOOST_WORKAROUND(__BORLANDC__, < 0x600)

// Borland have some serious problems with the unrolled version, so
// we always use a basic implementation
template<
      RTIBOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME
{
    typedef RTIBOOST_AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,RTIBOOST_AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        > res_;

    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
    typedef state type;
};

template<
      RTIBOOST_MPL_AUX_NTTP_DECL(int, N)
     , typename Last
    , typename State
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME<N,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
    typedef state type;
};

#   endif // RTIBOOST_WORKAROUND(__BORLANDC__, < 0x600)
 
#else // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N) >
struct RTIBOOST_AUX778076_FOLD_CHUNK_NAME;

#   define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_MPL_LIMIT_UNROLLING, <rtiboost/mpl/aux_/fold_impl_body.hpp>))
#   include RTIBOOST_PP_ITERATE()

// implementation for N that exceeds RTIBOOST_MPL_LIMIT_UNROLLING
template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N) > 
struct RTIBOOST_AUX778076_FOLD_CHUNK_NAME
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        > 
    struct result_
    {
        typedef RTIBOOST_AUX778076_FOLD_IMPL_NAME<
              RTIBOOST_MPL_LIMIT_UNROLLING
            , First
            , Last
            , State
            , ForwardOp
            > chunk_;

        typedef RTIBOOST_AUX778076_FOLD_IMPL_NAME<
              ( (N - RTIBOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - RTIBOOST_MPL_LIMIT_UNROLLING )
            , typename chunk_::iterator
            , Last
            , typename chunk_::state
            , ForwardOp
            > res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
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
        , typename ForwardOp
        > 
    struct result_
    {
        typedef typename if_<
              typename is_same<First,Last>::type
            , RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)<Last,State>
            , RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_step)<First,Last,State,ForwardOp>
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

#if defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int>
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
    , typename ForwardOp
    > 
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX,_step)
{
    // can't inherit here - it breaks MSVC 7.0
    typedef RTIBOOST_AUX778076_FOLD_CHUNK_NAME<-1>::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,RTIBOOST_AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      RTIBOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME
    : RTIBOOST_AUX778076_FOLD_CHUNK_NAME<N>
        ::template result_<First,Last,State,ForwardOp>
{
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}}

#   undef RTIBOOST_AUX778076_FOLD_IMPL_NAME
#   undef RTIBOOST_AUX778076_FOLD_CHUNK_NAME
#   undef RTIBOOST_AUX778076_ITER_FOLD_STEP

#undef RTIBOOST_AUX778076_FOLD_IMPL_OP
#undef RTIBOOST_AUX778076_FOLD_IMPL_NAME_PREFIX

///// iteration

#else

#   define n_ RTIBOOST_PP_FRAME_ITERATION(1)

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct RTIBOOST_AUX778076_FOLD_IMPL_NAME<n_,First,Last,State,ForwardOp>
{
    typedef First iter0;
    typedef State state0;

    RTIBOOST_MPL_PP_REPEAT(n_, RTIBOOST_AUX778076_ITER_FOLD_STEP, unused)

    typedef RTIBOOST_PP_CAT(state,n_) state;
    typedef RTIBOOST_PP_CAT(iter,n_) iterator;
};

#else

template<> struct RTIBOOST_AUX778076_FOLD_CHUNK_NAME<n_>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;

        RTIBOOST_MPL_PP_REPEAT(n_, RTIBOOST_AUX778076_ITER_FOLD_STEP, unused)

        typedef RTIBOOST_PP_CAT(state,n_) state;
        typedef RTIBOOST_PP_CAT(iter,n_) iterator;
    };

#if defined(RTIBOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef n_

#endif // RTIBOOST_PP_IS_ITERATING
