
#ifndef RTIBOOST_MPL_HAS_XXX_HPP_INCLUDED
#define RTIBOOST_MPL_HAS_XXX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2006
// Copyright David Abrahams 2002-2003
// Copyright Daniel Walker 2007
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/bool.hpp>
#include <rtiboost/mpl/aux_/na_spec.hpp>
#include <rtiboost/mpl/aux_/type_wrapper.hpp>
#include <rtiboost/mpl/aux_/yes_no.hpp>
#include <rtiboost/mpl/aux_/config/gcc.hpp>
#include <rtiboost/mpl/aux_/config/has_xxx.hpp>
#include <rtiboost/mpl/aux_/config/msvc_typename.hpp>
#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#include <rtiboost/preprocessor/array/elem.hpp>
#include <rtiboost/preprocessor/cat.hpp>
#include <rtiboost/preprocessor/control/if.hpp>
#include <rtiboost/preprocessor/repetition/enum_params.hpp>
#include <rtiboost/preprocessor/repetition/enum_trailing_params.hpp>

#if RTIBOOST_WORKAROUND( __BORLANDC__, RTIBOOST_TESTED_AT(0x590) )
# include <rtiboost/type_traits/is_class.hpp>
#endif

#if !defined(RTIBOOST_MPL_CFG_NO_HAS_XXX)

#   if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1300)

// agurt, 11/sep/02: MSVC-specific version (< 7.1), based on a USENET 
// newsgroup's posting by John Madsen (comp.lang.c++.moderated, 
// 1999-11-12 19:17:06 GMT); the code is _not_ standard-conforming, but 
// it works way more reliably than the SFINAE-based implementation

// Modified dwa 8/Oct/02 to handle reference types.

#   include <rtiboost/mpl/if.hpp>
#   include <rtiboost/mpl/bool.hpp>

namespace rtiboost { namespace mpl { namespace aux {

struct has_xxx_tag;

#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1300)
template< typename U > struct msvc_incomplete_array
{
    typedef char (&type)[sizeof(U) + 1];
};
#endif

template< typename T >
struct msvc_is_incomplete
{
    // MSVC is capable of some kinds of SFINAE.  If U is an incomplete
    // type, it won't pick the second overload
    static char tester(...);

#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1300)
    template< typename U >
    static typename msvc_incomplete_array<U>::type tester(type_wrapper<U>);
#else
    template< typename U >
    static char (& tester(type_wrapper<U>) )[sizeof(U)+1];
#endif 
    
    RTIBOOST_STATIC_CONSTANT(bool, value = 
          sizeof(tester(type_wrapper<T>())) == 1
        );
};

template<>
struct msvc_is_incomplete<int>
{
    RTIBOOST_STATIC_CONSTANT(bool, value = false);
};

}}}

#   define RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF_(trait, name, default_) \
template< typename T, typename name = ::rtiboost::mpl::aux::has_xxx_tag > \
struct RTIBOOST_PP_CAT(trait,_impl) : T \
{ \
    static rtiboost::mpl::aux::no_tag \
    test(void(*)(::rtiboost::mpl::aux::has_xxx_tag)); \
    \
    static rtiboost::mpl::aux::yes_tag test(...); \
    \
    RTIBOOST_STATIC_CONSTANT(bool, value = \
          sizeof(test(static_cast<void(*)(name)>(0))) \
            != sizeof(rtiboost::mpl::aux::no_tag) \
        ); \
    typedef rtiboost::mpl::bool_<value> type; \
}; \
\
template< typename T, typename fallback_ = rtiboost::mpl::bool_<default_> > \
struct trait \
    : rtiboost::mpl::if_c< \
          rtiboost::mpl::aux::msvc_is_incomplete<T>::value \
        , rtiboost::mpl::bool_<false> \
        , RTIBOOST_PP_CAT(trait,_impl)<T> \
        >::type \
{ \
}; \
\
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, void) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, bool) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, char) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, signed char) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, unsigned char) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, signed short) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, unsigned short) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, signed int) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, unsigned int) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, signed long) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, unsigned long) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, float) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, double) \
RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, long double) \
/**/

#   define RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, T) \
template<> struct trait<T> \
{ \
    RTIBOOST_STATIC_CONSTANT(bool, value = false); \
    typedef rtiboost::mpl::bool_<false> type; \
}; \
/**/

#if !defined(RTIBOOST_NO_INTRINSIC_WCHAR_T)
#   define RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, unused) \
    RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF_(trait, name, unused) \
    RTIBOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(trait, wchar_t) \
/**/
#else
#   define RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, unused) \
    RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF_(trait, name, unused) \
/**/
#endif


// SFINAE-based implementations below are derived from a USENET newsgroup's 
// posting by Rani Sharoni (comp.lang.c++.moderated, 2002-03-17 07:45:09 PST)

#   elif RTIBOOST_WORKAROUND(RTIBOOST_MSVC, RTIBOOST_TESTED_AT(1400)) \
      || RTIBOOST_WORKAROUND(__IBMCPP__, <= 700)

// MSVC 7.1+ & VACPP

// agurt, 15/jun/05: replace overload-based SFINAE implementation with SFINAE
// applied to partial specialization to fix some apparently random failures 
// (thanks to Daniel Wallin for researching this!)

#   define RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, default_) \
template< typename T > \
struct RTIBOOST_PP_CAT(trait, _msvc_sfinae_helper) \
{ \
    typedef void type; \
};\
\
template< typename T, typename U = void > \
struct RTIBOOST_PP_CAT(trait,_impl_) \
{ \
    RTIBOOST_STATIC_CONSTANT(bool, value = false); \
    typedef rtiboost::mpl::bool_<value> type; \
}; \
\
template< typename T > \
struct RTIBOOST_PP_CAT(trait,_impl_)< \
      T \
    , typename RTIBOOST_PP_CAT(trait, _msvc_sfinae_helper)< typename T::name >::type \
    > \
{ \
    RTIBOOST_STATIC_CONSTANT(bool, value = true); \
    typedef rtiboost::mpl::bool_<value> type; \
}; \
\
template< typename T, typename fallback_ = rtiboost::mpl::bool_<default_> > \
struct trait \
    : RTIBOOST_PP_CAT(trait,_impl_)<T> \
{ \
}; \
/**/

#   elif RTIBOOST_WORKAROUND( __BORLANDC__, RTIBOOST_TESTED_AT(0x590) )

#   define RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_BCB_DEF(trait, trait_tester, name, default_) \
template< typename T, bool IS_CLASS > \
struct trait_tester \
{ \
    RTIBOOST_STATIC_CONSTANT( bool,  value = false ); \
}; \
template< typename T > \
struct trait_tester< T, true > \
{ \
    struct trait_tester_impl \
    { \
        template < class U > \
        static int  resolve( rtiboost::mpl::aux::type_wrapper<U> const volatile * \
                           , rtiboost::mpl::aux::type_wrapper<typename U::name >* = 0 ); \
        static char resolve( ... ); \
    }; \
    typedef rtiboost::mpl::aux::type_wrapper<T> t_; \
    RTIBOOST_STATIC_CONSTANT( bool, value = ( sizeof( trait_tester_impl::resolve( static_cast< t_ * >(0) ) ) == sizeof(int) ) ); \
}; \
template< typename T, typename fallback_ = rtiboost::mpl::bool_<default_> > \
struct trait           \
{                      \
    RTIBOOST_STATIC_CONSTANT( bool, value = (trait_tester< T, rtiboost::is_class< T >::value >::value) );     \
    typedef rtiboost::mpl::bool_< trait< T, fallback_ >::value > type; \
};

#   define RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, default_) \
    RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_BCB_DEF( trait \
                                         , RTIBOOST_PP_CAT(trait,_tester)      \
                                         , name       \
                                         , default_ ) \
/**/

#   else // other SFINAE-capable compilers

#   define RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, default_) \
template< typename T, typename fallback_ = rtiboost::mpl::bool_<default_> > \
struct trait \
{ \
    struct gcc_3_2_wknd \
    { \
        template< typename U > \
        static rtiboost::mpl::aux::yes_tag test( \
              rtiboost::mpl::aux::type_wrapper<U> const volatile* \
            , rtiboost::mpl::aux::type_wrapper<RTIBOOST_MSVC_TYPENAME U::name>* = 0 \
            ); \
    \
        static rtiboost::mpl::aux::no_tag test(...); \
    }; \
    \
    typedef rtiboost::mpl::aux::type_wrapper<T> t_; \
    RTIBOOST_STATIC_CONSTANT(bool, value = \
          sizeof(gcc_3_2_wknd::test(static_cast<t_*>(0))) \
            == sizeof(rtiboost::mpl::aux::yes_tag) \
        ); \
    typedef rtiboost::mpl::bool_<value> type; \
}; \
/**/

#   endif // RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1300)


#else // RTIBOOST_MPL_CFG_NO_HAS_XXX

// placeholder implementation

#   define RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, default_) \
template< typename T, typename fallback_ = rtiboost::mpl::bool_<default_> > \
struct trait \
{ \
    RTIBOOST_STATIC_CONSTANT(bool, value = fallback_::value); \
    typedef fallback_ type; \
}; \
/**/

#endif

#define RTIBOOST_MPL_HAS_XXX_TRAIT_DEF(name) \
    RTIBOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(RTIBOOST_PP_CAT(has_,name), name, false) \
/**/


#if !defined(RTIBOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE)

// Create a boolean Metafunction to detect a nested template
// member. This implementation is based on a USENET newsgroup's
// posting by Aleksey Gurtovoy (comp.lang.c++.moderated, 2002-03-19),
// Rani Sharoni's USENET posting cited above, the non-template has_xxx
// implementations above, and discussion on the Boost mailing list.

#   if !defined(RTIBOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES)
#     if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1400)
#       define RTIBOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES 1
#     endif
#   endif

#   if !defined(RTIBOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION)
#     if (defined(RTIBOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS))
#       define RTIBOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION 1
#     endif
#   endif

#   if !defined(RTIBOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE)
#     if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1400)
#       define RTIBOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE 1
#     endif
#   endif

// NOTE: Many internal implementation macros take a Boost.Preprocessor
// array argument called args which is of the following form.
//           ( 4, ( trait, name, max_arity, default_ ) )

#   define RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args) \
      RTIBOOST_PP_CAT(RTIBOOST_PP_ARRAY_ELEM(0, args) , _introspect) \
    /**/

#   define RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) \
      RTIBOOST_PP_CAT(RTIBOOST_PP_CAT(RTIBOOST_PP_ARRAY_ELEM(0, args) , _substitute), n) \
    /**/

#   define RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args) \
      RTIBOOST_PP_CAT(RTIBOOST_PP_ARRAY_ELEM(0, args) , _test) \
    /**/

// Thanks to Guillaume Melquiond for pointing out the need for the
// "substitute" template as an argument to the overloaded test
// functions to get SFINAE to work for member templates with the
// correct name but different number of arguments.
#   define RTIBOOST_MPL_HAS_MEMBER_MULTI_SUBSTITUTE(z, n, args) \
      template< \
          template< RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_INC(n), typename V) > class V \
       > \
      struct RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) { \
      }; \
    /**/

#   define RTIBOOST_MPL_HAS_MEMBER_SUBSTITUTE(args, substitute_macro) \
      RTIBOOST_PP_REPEAT( \
          RTIBOOST_PP_ARRAY_ELEM(2, args) \
        , RTIBOOST_MPL_HAS_MEMBER_MULTI_SUBSTITUTE \
        , args \
      ) \
    /**/

#   if !RTIBOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION
#     define RTIBOOST_MPL_HAS_MEMBER_REJECT(args, member_macro) \
        template< typename V > \
        static rtiboost::mpl::aux::no_tag \
        RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)(...); \
      /**/
#   else
#     define RTIBOOST_MPL_HAS_MEMBER_REJECT(args, member_macro) \
        static rtiboost::mpl::aux::no_tag \
        RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)(...); \
      /**/
#   endif

#   if !RTIBOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES
#     define RTIBOOST_MPL_HAS_MEMBER_MULTI_ACCEPT(z, n, args) \
        template< typename V > \
        static rtiboost::mpl::aux::yes_tag \
        RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)( \
            rtiboost::mpl::aux::type_wrapper< V > const volatile* \
          , RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) < \
                V::template RTIBOOST_PP_ARRAY_ELEM(1, args) \
            >* = 0 \
        ); \
      /**/
#     define RTIBOOST_MPL_HAS_MEMBER_ACCEPT(args, member_macro) \
        RTIBOOST_PP_REPEAT( \
            RTIBOOST_PP_ARRAY_ELEM(2, args) \
          , RTIBOOST_MPL_HAS_MEMBER_MULTI_ACCEPT \
          , args \
        ) \
      /**/
#   else
#     define RTIBOOST_MPL_HAS_MEMBER_ACCEPT(args, member_macro) \
        template< typename V > \
        static rtiboost::mpl::aux::yes_tag \
        RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)( \
            V const volatile* \
          , member_macro(args, V, T)* = 0 \
        ); \
      /**/
#   endif

#   if !RTIBOOST_MPL_HAS_XXX_NO_EXPLICIT_TEST_FUNCTION
#     define RTIBOOST_MPL_HAS_MEMBER_TEST(args) \
          sizeof(RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)< U >(0)) \
              == sizeof(rtiboost::mpl::aux::yes_tag) \
      /**/
#   else
#     if !RTIBOOST_MPL_HAS_XXX_NO_WRAPPED_TYPES
#       define RTIBOOST_MPL_HAS_MEMBER_TEST(args) \
          sizeof( \
              RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)( \
                  static_cast< rtiboost::mpl::aux::type_wrapper< U >* >(0) \
              ) \
          ) == sizeof(rtiboost::mpl::aux::yes_tag) \
        /**/
#     else
#       define RTIBOOST_MPL_HAS_MEMBER_TEST(args) \
          sizeof( \
              RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)( \
                  static_cast< U* >(0) \
              ) \
          ) == sizeof(rtiboost::mpl::aux::yes_tag) \
        /**/
#     endif
#   endif

#   define RTIBOOST_MPL_HAS_MEMBER_INTROSPECT( \
               args, substitute_macro, member_macro \
           ) \
      template< typename U > \
      struct RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args) { \
          RTIBOOST_MPL_HAS_MEMBER_SUBSTITUTE(args, substitute_macro) \
          RTIBOOST_MPL_HAS_MEMBER_REJECT(args, member_macro) \
          RTIBOOST_MPL_HAS_MEMBER_ACCEPT(args, member_macro) \
          RTIBOOST_STATIC_CONSTANT( \
              bool, value = RTIBOOST_MPL_HAS_MEMBER_TEST(args) \
          ); \
          typedef rtiboost::mpl::bool_< value > type; \
      }; \
    /**/

#   define RTIBOOST_MPL_HAS_MEMBER_IMPLEMENTATION( \
               args, introspect_macro, substitute_macro, member_macro \
           ) \
      template< \
          typename T \
        , typename fallback_ \
              = rtiboost::mpl::bool_< RTIBOOST_PP_ARRAY_ELEM(3, args) > \
      > \
      class RTIBOOST_PP_ARRAY_ELEM(0, args) { \
          introspect_macro(args, substitute_macro, member_macro) \
      public: \
          static const bool value \
              = RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args)< T >::value; \
          typedef typename RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args)< \
              T \
          >::type type; \
      }; \
    /**/

// RTIBOOST_MPL_HAS_MEMBER_WITH_FUNCTION_SFINAE expands to the full
// implementation of the function-based metafunction. Compile with -E
// to see the preprocessor output for this macro.
#   define RTIBOOST_MPL_HAS_MEMBER_WITH_FUNCTION_SFINAE( \
               args, substitute_macro, member_macro \
           ) \
      RTIBOOST_MPL_HAS_MEMBER_IMPLEMENTATION( \
          args \
        , RTIBOOST_MPL_HAS_MEMBER_INTROSPECT \
        , substitute_macro \
        , member_macro \
      ) \
    /**/

#   if RTIBOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE

#     if !defined(RTIBOOST_MPL_HAS_XXX_NEEDS_NAMESPACE_LEVEL_SUBSTITUTE)
#       if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1400)
#         define RTIBOOST_MPL_HAS_XXX_NEEDS_NAMESPACE_LEVEL_SUBSTITUTE 1
#       endif
#     endif

#     if !RTIBOOST_MPL_HAS_XXX_NEEDS_NAMESPACE_LEVEL_SUBSTITUTE
#       define RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                   args, n \
               ) \
          RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) \
        /**/
#     else
#       define RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                   args, n \
               ) \
          RTIBOOST_PP_CAT( \
              boost_mpl_has_xxx_ \
            , RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME(args, n) \
          ) \
        /**/
#     endif

#     define RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_TAG_NAME( \
                 args \
             ) \
        RTIBOOST_PP_CAT( \
            RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                args, 0 \
            ) \
          , _tag \
        ) \
      /**/

#     define RTIBOOST_MPL_HAS_MEMBER_MULTI_SUBSTITUTE_WITH_TEMPLATE_SFINAE( \
                 z, n, args \
             ) \
        template< \
             template< RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_PP_INC(n), typename U) > class U \
        > \
        struct RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                args, n \
               ) { \
            typedef \
                RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_TAG_NAME(args) \
                type; \
        }; \
      /**/

#     define RTIBOOST_MPL_HAS_MEMBER_SUBSTITUTE_WITH_TEMPLATE_SFINAE( \
                 args, substitute_macro \
             ) \
        typedef void \
            RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_TAG_NAME(args); \
        RTIBOOST_PP_REPEAT( \
            RTIBOOST_PP_ARRAY_ELEM(2, args) \
          , RTIBOOST_MPL_HAS_MEMBER_MULTI_SUBSTITUTE_WITH_TEMPLATE_SFINAE \
          , args \
        ) \
      /**/

#     define RTIBOOST_MPL_HAS_MEMBER_REJECT_WITH_TEMPLATE_SFINAE( \
                 args, member_macro \
             ) \
        template< \
            typename U \
          , typename V \
                = RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_TAG_NAME(args) \
        > \
        struct RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args) { \
            RTIBOOST_STATIC_CONSTANT(bool, value = false); \
            typedef rtiboost::mpl::bool_< value > type; \
        }; \
      /**/

#     define RTIBOOST_MPL_HAS_MEMBER_MULTI_ACCEPT_WITH_TEMPLATE_SFINAE( \
                 z, n, args \
             ) \
        template< typename U > \
        struct RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)< \
            U \
          , typename \
                RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_SUBSTITUTE_NAME_WITH_TEMPLATE_SFINAE( \
                    args, n \
                )< \
                    RTIBOOST_MSVC_TYPENAME U::RTIBOOST_PP_ARRAY_ELEM(1, args)< > \
                >::type \
        > { \
            RTIBOOST_STATIC_CONSTANT(bool, value = true); \
            typedef rtiboost::mpl::bool_< value > type; \
        }; \
      /**/

#     define RTIBOOST_MPL_HAS_MEMBER_ACCEPT_WITH_TEMPLATE_SFINAE( \
                 args, member_macro \
             ) \
        RTIBOOST_PP_REPEAT( \
            RTIBOOST_PP_ARRAY_ELEM(2, args) \
          , RTIBOOST_MPL_HAS_MEMBER_MULTI_ACCEPT_WITH_TEMPLATE_SFINAE \
          , args \
        ) \
      /**/

#     define RTIBOOST_MPL_HAS_MEMBER_INTROSPECT_WITH_TEMPLATE_SFINAE( \
                 args, substitute_macro, member_macro \
             ) \
        RTIBOOST_MPL_HAS_MEMBER_REJECT_WITH_TEMPLATE_SFINAE(args, member_macro) \
        RTIBOOST_MPL_HAS_MEMBER_ACCEPT_WITH_TEMPLATE_SFINAE(args, member_macro) \
        template< typename U > \
        struct RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_NAME(args) \
            : RTIBOOST_MPL_HAS_MEMBER_INTROSPECTION_TEST_NAME(args)< U > { \
        }; \
      /**/
 
// RTIBOOST_MPL_HAS_MEMBER_WITH_TEMPLATE_SFINAE expands to the full
// implementation of the template-based metafunction. Compile with -E
// to see the preprocessor output for this macro.
//
// Note that if RTIBOOST_MPL_HAS_XXX_NEEDS_NAMESPACE_LEVEL_SUBSTITUTE is
// defined RTIBOOST_MPL_HAS_MEMBER_SUBSTITUTE_WITH_TEMPLATE_SFINAE needs
// to be expanded at namespace level before
// RTIBOOST_MPL_HAS_MEMBER_WITH_TEMPLATE_SFINAE can be used.
#     define RTIBOOST_MPL_HAS_MEMBER_WITH_TEMPLATE_SFINAE( \
                 args, substitute_macro, member_macro \
             ) \
        RTIBOOST_MPL_HAS_MEMBER_SUBSTITUTE_WITH_TEMPLATE_SFINAE( \
            args, substitute_macro \
        ) \
        RTIBOOST_MPL_HAS_MEMBER_IMPLEMENTATION( \
            args \
          , RTIBOOST_MPL_HAS_MEMBER_INTROSPECT_WITH_TEMPLATE_SFINAE \
          , substitute_macro \
          , member_macro \
        ) \
      /**/

#   endif // RTIBOOST_MPL_HAS_XXX_NEEDS_TEMPLATE_SFINAE

// Note: In the current implementation the parameter and access macros
// are no longer expanded.
#   if !RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1400)
#     define RTIBOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(trait, name, default_) \
        RTIBOOST_MPL_HAS_MEMBER_WITH_FUNCTION_SFINAE( \
            ( 4, ( trait, name, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, default_ ) ) \
          , RTIBOOST_MPL_HAS_MEMBER_TEMPLATE_SUBSTITUTE_PARAMETER \
          , RTIBOOST_MPL_HAS_MEMBER_TEMPLATE_ACCESS \
        ) \
      /**/
#   else
#     define RTIBOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(trait, name, default_) \
        RTIBOOST_MPL_HAS_MEMBER_WITH_TEMPLATE_SFINAE( \
            ( 4, ( trait, name, RTIBOOST_MPL_LIMIT_METAFUNCTION_ARITY, default_ ) ) \
          , RTIBOOST_MPL_HAS_MEMBER_TEMPLATE_SUBSTITUTE_PARAMETER \
          , RTIBOOST_MPL_HAS_MEMBER_TEMPLATE_ACCESS \
        ) \
      /**/
#   endif

#else // RTIBOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

// placeholder implementation

#   define RTIBOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(trait, name, default_) \
      template< typename T \
              , typename fallback_ = rtiboost::mpl::bool_< default_ > > \
      struct trait { \
          RTIBOOST_STATIC_CONSTANT(bool, value = fallback_::value); \
          typedef fallback_ type; \
      }; \
    /**/

#endif // RTIBOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#   define RTIBOOST_MPL_HAS_XXX_TEMPLATE_DEF(name) \
      RTIBOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF( \
          RTIBOOST_PP_CAT(has_, name), name, false \
      ) \
    /**/

#endif // RTIBOOST_MPL_HAS_XXX_HPP_INCLUDED
