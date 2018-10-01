
#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

#ifndef RTIBOOST_MPL_QUOTE_HPP_INCLUDED
#define RTIBOOST_MPL_QUOTE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
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
#   include <rtiboost/mpl/void.hpp>
#   include <rtiboost/mpl/aux_/has_type.hpp>
#endif

#include <rtiboost/mpl/aux_/config/bcc.hpp>
#include <rtiboost/mpl/aux_/config/ttp.hpp>

#if defined(RTIBOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && !defined(RTIBOOST_MPL_CFG_BCC590_WORKAROUNDS)
#   define RTIBOOST_MPL_CFG_NO_QUOTE_TEMPLATE
#endif

#if !defined(RTIBOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS) \
    && defined(RTIBOOST_MPL_CFG_NO_HAS_XXX)
#   define RTIBOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS
#endif

#include <rtiboost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
 && !defined(RTIBOOST_MPL_PREPROCESSING_MODE)

#   define RTIBOOST_MPL_PREPROCESSED_HEADER quote.hpp
#   include <rtiboost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <rtiboost/mpl/limits/arity.hpp>
#   include <rtiboost/mpl/aux_/preprocessor/params.hpp>
#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/config/workaround.hpp>

#   include <rtiboost/preprocessor/iterate.hpp>
#   include <rtiboost/preprocessor/cat.hpp>

#if !defined(RTIBOOST_MPL_CFG_NO_QUOTE_TEMPLATE)

namespace rtiboost { namespace mpl {

#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T, bool has_type_ >
struct quote_impl
// GCC has a problem with metafunction forwarding when T is a
// specialization of a template called 'type'.
# if RTIBOOST_WORKAROUND(__GNUC__, RTIBOOST_TESTED_AT(4)) \
    && RTIBOOST_WORKAROUND(__GNUC_MINOR__, RTIBOOST_TESTED_AT(0)) \
    && RTIBOOST_WORKAROUND(__GNUC_PATCHLEVEL__, RTIBOOST_TESTED_AT(2))
{
    typedef typename T::type type;
};
# else 
    : T
{
};
# endif 

template< typename T >
struct quote_impl<T,false>
{
    typedef T type;
};

#else // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< bool > struct quote_impl
{
    template< typename T > struct result_
        : T
    {
    };
};

template<> struct quote_impl<false>
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

#endif 

#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, <rtiboost/mpl/quote.hpp>))
#include RTIBOOST_PP_ITERATE()

}}

#endif // RTIBOOST_MPL_CFG_NO_QUOTE_TEMPLATE

#endif // RTIBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // RTIBOOST_MPL_QUOTE_HPP_INCLUDED

///// iteration

#else
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

template<
      template< RTIBOOST_MPL_PP_PARAMS(i_, typename P) > class F
    , typename Tag = void_
    >
struct RTIBOOST_PP_CAT(quote,i_)
{
    template< RTIBOOST_MPL_PP_PARAMS(i_, typename U) > struct apply
#if defined(RTIBOOST_MPL_CFG_BCC590_WORKAROUNDS)
    {
        typedef typename quote_impl<
              F< RTIBOOST_MPL_PP_PARAMS(i_, U) >
            , aux::has_type< F< RTIBOOST_MPL_PP_PARAMS(i_, U) > >::value
            >::type type;
    };
#elif !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        : quote_impl<
              F< RTIBOOST_MPL_PP_PARAMS(i_, U) >
            , aux::has_type< F< RTIBOOST_MPL_PP_PARAMS(i_, U) > >::value
            >
    {
    };
#else
        : quote_impl< aux::has_type< F< RTIBOOST_MPL_PP_PARAMS(i_, U) > >::value >
            ::template result_< F< RTIBOOST_MPL_PP_PARAMS(i_, U) > >
    {
    };
#endif
};

#undef i_
#endif // RTIBOOST_PP_IS_ITERATING
