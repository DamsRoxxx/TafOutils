
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

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
#   include <rtiboost/mpl/numeric_cast.hpp>
#   include <rtiboost/mpl/apply_wrap.hpp>
#   include <rtiboost/mpl/if.hpp>
#   include <rtiboost/mpl/tag.hpp>
#   include <rtiboost/mpl/aux_/numeric_cast_utils.hpp>
#   include <rtiboost/mpl/aux_/na.hpp>
#   include <rtiboost/mpl/aux_/na_spec.hpp>
#   include <rtiboost/mpl/aux_/lambda_support.hpp>
#   include <rtiboost/mpl/aux_/msvc_eti_base.hpp>
#   include <rtiboost/mpl/aux_/value_wknd.hpp>
#   include <rtiboost/mpl/aux_/config/eti.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>
#endif

#include <rtiboost/mpl/aux_/config/static_constant.hpp>

#if defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    || defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/def_params_tail.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/repeat.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/ext_params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/enum.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/add.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/sub.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/config/eti.hpp>
#   include <rtiboost/mpl/aux_/config/msvc.hpp>
#   include <rtiboost/mpl/aux_/config/workaround.hpp>

#   include <rtiboost/preprocessor/dec.hpp>
#   include <rtiboost/preprocessor/inc.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/cat.hpp>


#if !defined(RTIBOOST_AUX778076_OP_ARITY)
#   define RTIBOOST_AUX778076_OP_ARITY RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY
#endif

#if !defined(RTIBOOST_AUX778076_OP_IMPL_NAME)
#   define RTIBOOST_AUX778076_OP_IMPL_NAME RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_PREFIX,_impl)
#endif

#if !defined(RTIBOOST_AUX778076_OP_TAG_NAME)
#   define RTIBOOST_AUX778076_OP_TAG_NAME RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_PREFIX,_tag)
#endif

namespace rtiboost { namespace mpl {

template< 
      typename Tag1
    , typename Tag2
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1300)
    , RTIBOOST_MPL_AUX_NTTP_DECL(int, tag1_) = RTIBOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value 
    , RTIBOOST_MPL_AUX_NTTP_DECL(int, tag2_) = RTIBOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value 
    >
struct RTIBOOST_AUX778076_OP_IMPL_NAME
    : if_c<
          ( tag1_ > tag2_ )
#else
    >
struct RTIBOOST_AUX778076_OP_IMPL_NAME
    : if_c<
          ( RTIBOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > RTIBOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )
#endif
        , aux::cast2nd_impl< RTIBOOST_AUX778076_OP_IMPL_NAME<Tag1,Tag1>,Tag1,Tag2 >
        , aux::cast1st_impl< RTIBOOST_AUX778076_OP_IMPL_NAME<Tag2,Tag2>,Tag1,Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct RTIBOOST_AUX778076_OP_IMPL_NAME<na,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value = 0);
    };
};

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename Tag > struct RTIBOOST_AUX778076_OP_IMPL_NAME<na,Tag>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value = 0);
    };
};

template< typename Tag > struct RTIBOOST_AUX778076_OP_IMPL_NAME<Tag,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value = 0);
    };
};
#else
template<> struct RTIBOOST_AUX778076_OP_IMPL_NAME<na,rtiboost_integral_c_tag>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value = 0);
    };
};

template<> struct RTIBOOST_AUX778076_OP_IMPL_NAME<rtiboost_integral_c_tag,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value = 0);
    };
};
#endif


#if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && RTIBOOST_WORKAROUND(RTIBOOST_MSVC, >= 1300)
template< typename T > struct RTIBOOST_AUX778076_OP_TAG_NAME
    : tag<T,na>
{
};
#else
template< typename T > struct RTIBOOST_AUX778076_OP_TAG_NAME
{
    typedef typename T::tag type;
};
#endif


#if RTIBOOST_AUX778076_OP_ARITY != 2

#   if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define RTIBOOST_AUX778076_OP_RIGHT_OPERAND(unused, i, N) , RTIBOOST_PP_CAT(N, RTIBOOST_MPL_PP_ADD(i, 2))>
#   define RTIBOOST_AUX778076_OP_N_CALLS(i, N) \
    RTIBOOST_MPL_PP_REPEAT( RTIBOOST_PP_DEC(i), RTIBOOST_MPL_PP_REPEAT_IDENTITY_FUNC, RTIBOOST_AUX778076_OP_NAME< ) \
    N1 RTIBOOST_MPL_PP_REPEAT( RTIBOOST_MPL_PP_SUB(i, 1), RTIBOOST_AUX778076_OP_RIGHT_OPERAND, N ) \
/**/

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(N1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N2)
    RTIBOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename N, na)
    >
struct RTIBOOST_AUX778076_OP_NAME
    : RTIBOOST_AUX778076_OP_N_CALLS(RTIBOOST_AUX778076_OP_ARITY, N)
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(
          RTIBOOST_AUX778076_OP_ARITY
        , RTIBOOST_AUX778076_OP_NAME
        , ( RTIBOOST_MPL_PP_PARAMS(RTIBOOST_AUX778076_OP_ARITY, N) )
        )
};

#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,( RTIBOOST_PP_DEC(RTIBOOST_AUX778076_OP_ARITY), 2, <rtiboost/mpl/aux_/numeric_op.hpp> ))
#include RTIBOOST_PP_ITERATE()

#   undef RTIBOOST_AUX778076_OP_N_CALLS
#   undef RTIBOOST_AUX778076_OP_RIGHT_OPERAND

#   else // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

/// forward declaration
template< 
      typename RTIBOOST_MPL_AUX_NA_PARAM(N1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N2)
    >
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,2);

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(N1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N2)
    RTIBOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename N, na)
    >
struct RTIBOOST_AUX778076_OP_NAME
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1300)
    : aux::msvc_eti_base< typename if_<
#else
    : if_<
#endif
          is_na<N3>
        , RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,2)<N1,N2>
        , RTIBOOST_AUX778076_OP_NAME<
              RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,2)<N1,N2>
            , RTIBOOST_MPL_PP_EXT_PARAMS(3, RTIBOOST_PP_INC(RTIBOOST_AUX778076_OP_ARITY), N)
            >
        >::type
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1300)
    >
#endif
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(
          RTIBOOST_AUX778076_OP_ARITY
        , RTIBOOST_AUX778076_OP_NAME
        , ( RTIBOOST_MPL_PP_PARAMS(RTIBOOST_AUX778076_OP_ARITY, N) )
        )
};

template< 
      typename N1
    , typename N2
    >
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,2)

#endif

#else // RTIBOOST_AUX778076_OP_ARITY == 2

template< 
      typename RTIBOOST_MPL_AUX_NA_PARAM(N1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N2)
    >
struct RTIBOOST_AUX778076_OP_NAME

#endif

#if !defined(RTIBOOST_MPL_CFG_MSVC_ETI_BUG)
    : RTIBOOST_AUX778076_OP_IMPL_NAME<
          typename RTIBOOST_AUX778076_OP_TAG_NAME<N1>::type
        , typename RTIBOOST_AUX778076_OP_TAG_NAME<N2>::type
        >::template apply<N1,N2>::type
#else
    : aux::msvc_eti_base< typename apply_wrap2<
          RTIBOOST_AUX778076_OP_IMPL_NAME<
              typename RTIBOOST_AUX778076_OP_TAG_NAME<N1>::type
            , typename RTIBOOST_AUX778076_OP_TAG_NAME<N2>::type
            >
        , N1
        , N2
        >::type >::type
#endif
{
#if RTIBOOST_AUX778076_OP_ARITY != 2

#   if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          RTIBOOST_AUX778076_OP_ARITY
        , RTIBOOST_AUX778076_OP_NAME
        , ( RTIBOOST_MPL_PP_PARTIAL_SPEC_PARAMS(2, N, na) )
        )
#   else
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2, RTIBOOST_PP_CAT(RTIBOOST_AUX778076_OP_NAME,2), (N1, N2))
#   endif

#else
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2, RTIBOOST_AUX778076_OP_NAME, (N1, N2))
#endif
};

RTIBOOST_MPL_AUX_NA_SPEC2(2, RTIBOOST_AUX778076_OP_ARITY, RTIBOOST_AUX778076_OP_NAME)

}}

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// RTIBOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // RTIBOOST_PP_IS_ITERATING
#if RTIBOOST_PP_ITERATION_DEPTH() == 1

#   define i_ RTIBOOST_PP_FRAME_ITERATION(1)

template<
      RTIBOOST_MPL_PP_PARAMS(i_, typename N)
    >
struct RTIBOOST_AUX778076_OP_NAME<RTIBOOST_MPL_PP_PARTIAL_SPEC_PARAMS(i_, N, na)>
#if i_ != 2
    : RTIBOOST_AUX778076_OP_N_CALLS(i_, N)
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          RTIBOOST_AUX778076_OP_ARITY
        , RTIBOOST_AUX778076_OP_NAME
        , ( RTIBOOST_MPL_PP_PARTIAL_SPEC_PARAMS(i_, N, na) )
        )
};
#endif

#   undef i_

#endif // RTIBOOST_PP_ITERATION_DEPTH()
#endif // RTIBOOST_PP_IS_ITERATING
