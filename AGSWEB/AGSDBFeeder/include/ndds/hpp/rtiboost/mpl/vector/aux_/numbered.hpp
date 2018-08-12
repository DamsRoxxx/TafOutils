
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(RTIBOOST_PP_IS_ITERATING)

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

#include <rtiboost/preprocessor/enum_params.hpp>
#include <rtiboost/preprocessor/enum_shifted_params.hpp>
#include <rtiboost/preprocessor/comma_if.hpp>
#include <rtiboost/preprocessor/repeat.hpp>
#include <rtiboost/preprocessor/dec.hpp>
#include <rtiboost/preprocessor/cat.hpp>

#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

#if defined(RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   define RTIBOOST_AUX778076_VECTOR_TAIL(vector, i_, T) \
    RTIBOOST_PP_CAT(vector,i_)< \
          RTIBOOST_PP_ENUM_PARAMS(i_, T) \
        > \
    /**/

#if i_ > 0
template<
      RTIBOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(vector,i_)
    : v_item<
          RTIBOOST_PP_CAT(T,RTIBOOST_PP_DEC(i_))
        , RTIBOOST_AUX778076_VECTOR_TAIL(vector,RTIBOOST_PP_DEC(i_),T)
        >
{
    typedef RTIBOOST_PP_CAT(vector,i_) type;
};
#endif

#   undef RTIBOOST_AUX778076_VECTOR_TAIL

#else // "brute force" implementation

#   if i_ > 0

template<
      RTIBOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct RTIBOOST_PP_CAT(vector,i_)
{
    typedef aux::vector_tag<i_> tag;
    typedef RTIBOOST_PP_CAT(vector,i_) type;

#   define RTIBOOST_AUX778076_VECTOR_ITEM(unused, i_, unused2) \
    typedef RTIBOOST_PP_CAT(T,i_) RTIBOOST_PP_CAT(item,i_); \
    /**/

    RTIBOOST_PP_REPEAT(i_, RTIBOOST_AUX778076_VECTOR_ITEM, unused)
#   undef RTIBOOST_AUX778076_VECTOR_ITEM
    typedef void_ RTIBOOST_PP_CAT(item,i_);
    typedef RTIBOOST_PP_CAT(T,RTIBOOST_PP_DEC(i_)) back;

    // Borland forces us to use 'type' here (instead of the class name)
    typedef v_iter<type,0> begin;
    typedef v_iter<type,i_> end;
};

template<>
struct push_front_impl< aux::vector_tag<RTIBOOST_PP_DEC(i_)> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef RTIBOOST_PP_CAT(vector,i_)<
              T
              RTIBOOST_PP_COMMA_IF(RTIBOOST_PP_DEC(i_))
              RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_DEC(i_), typename Vector::item)
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef RTIBOOST_PP_CAT(vector,RTIBOOST_PP_DEC(i_))<
              RTIBOOST_PP_ENUM_SHIFTED_PARAMS(i_, typename Vector::item)
            > type;
    };
};


template<>
struct push_back_impl< aux::vector_tag<RTIBOOST_PP_DEC(i_)> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef RTIBOOST_PP_CAT(vector,i_)<
              RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_DEC(i_), typename Vector::item)
              RTIBOOST_PP_COMMA_IF(RTIBOOST_PP_DEC(i_))
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef RTIBOOST_PP_CAT(vector,RTIBOOST_PP_DEC(i_))<
              RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_DEC(i_), typename Vector::item)
            > type;
    };
};

#   endif // i_ > 0

#   if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(RTIBOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

template< typename V >
struct v_at<V,i_>
{
    typedef typename V::RTIBOOST_PP_CAT(item,i_) type;
};

#   else

namespace aux {
template<> struct v_at_impl<i_>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::RTIBOOST_PP_CAT(item,i_) type;
    };
};
}

template<>
struct at_impl< aux::vector_tag<i_> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<RTIBOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

#if i_ > 0
template<>
struct front_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};
#endif

template<>
struct size_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
        : long_<i_>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<i_> >
    : size_impl< aux::vector_tag<i_> >
{
};

template<>
struct clear_impl< aux::vector_tag<i_> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#   endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // RTIBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#undef i_

#endif // RTIBOOST_PP_IS_ITERATING
