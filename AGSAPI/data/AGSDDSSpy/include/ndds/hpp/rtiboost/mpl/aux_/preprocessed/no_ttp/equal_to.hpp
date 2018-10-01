
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "rtiboost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace rtiboost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( RTIBOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > RTIBOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(N1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

RTIBOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace rtiboost { namespace mpl {

template<>
struct equal_to_impl< rtiboost_integral_c_tag,rtiboost_integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        RTIBOOST_STATIC_CONSTANT(bool, value =
             ( RTIBOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             RTIBOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}
