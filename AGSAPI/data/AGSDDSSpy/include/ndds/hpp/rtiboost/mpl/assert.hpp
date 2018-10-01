
#ifndef RTIBOOST_MPL_ASSERT_HPP_INCLUDED
#define RTIBOOST_MPL_ASSERT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <rtiboost/mpl/not.hpp>
#include <rtiboost/mpl/aux_/value_wknd.hpp>
#include <rtiboost/mpl/aux_/nested_type_wknd.hpp>
#include <rtiboost/mpl/aux_/yes_no.hpp>
#include <rtiboost/mpl/aux_/na.hpp>
#include <rtiboost/mpl/aux_/adl_barrier.hpp>

#include <rtiboost/mpl/aux_/config/nttp.hpp>
#include <rtiboost/mpl/aux_/config/dtp.hpp>
#include <rtiboost/mpl/aux_/config/gcc.hpp>
#include <rtiboost/mpl/aux_/config/msvc.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/pp_counter.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#include <rtiboost/preprocessor/cat.hpp>

#include <rtiboost/config.hpp> // make sure 'size_t' is placed into 'std'
#include <cstddef>

#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1700)
#include <rtiboost/mpl/if.hpp>
#endif

#if RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x610)) \
    || (RTIBOOST_MPL_CFG_GCC != 0) \
    || RTIBOOST_WORKAROUND(__IBMCPP__, <= 600)
#   define RTIBOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES
#endif

#if RTIBOOST_WORKAROUND(__MWERKS__, < 0x3202) \
    || RTIBOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
    || RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x610)) \
    || RTIBOOST_WORKAROUND(__DMC__, RTIBOOST_TESTED_AT(0x840))
#   define RTIBOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER
#endif

// agurt, 10/nov/06: use enums for Borland (which cannot cope with static constants) 
// and GCC (which issues "unused variable" warnings when static constants are used 
// at a function scope)
#if RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x610)) \
    || (RTIBOOST_MPL_CFG_GCC != 0)
#   define RTIBOOST_MPL_AUX_ASSERT_CONSTANT(T, expr) enum { expr }
#else
#   define RTIBOOST_MPL_AUX_ASSERT_CONSTANT(T, expr) RTIBOOST_STATIC_CONSTANT(T, expr)
#endif


RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

struct failed {};

// agurt, 24/aug/04: MSVC 7.1 workaround here and below: return/accept 
// 'assert<false>' by reference; can't apply it unconditionally -- apparently it
// degrades the quality of GCC diagnostics
#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1310)
#   define RTIBOOST_AUX778076_ASSERT_ARG(x) x&
#else
#   define RTIBOOST_AUX778076_ASSERT_ARG(x) x
#endif

template< bool C >  struct assert        { typedef void* type; };
template<>          struct assert<false> { typedef RTIBOOST_AUX778076_ASSERT_ARG(assert) type; };

template< bool C >
int assertion_failed( typename assert<C>::type );

template< bool C >
struct assertion
{
    static int failed( assert<false> );
};

template<>
struct assertion<true>
{
    static int failed( void* );
};

struct assert_
{
#if !defined(RTIBOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
    template< typename T1, typename T2 = na, typename T3 = na, typename T4 = na > struct types {};
#endif
    static assert_ const arg;
    enum relations { equal = 1, not_equal, greater, greater_equal, less, less_equal };
};


#if !defined(RTIBOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES)

bool operator==( failed, failed );
bool operator!=( failed, failed );
bool operator>( failed, failed );
bool operator>=( failed, failed );
bool operator<( failed, failed );
bool operator<=( failed, failed );

#if defined(__EDG_VERSION__)
template< bool (*)(failed, failed), long x, long y > struct assert_relation {};
#   define RTIBOOST_MPL_AUX_ASSERT_RELATION(x, y, r) assert_relation<r,x,y>
#else
template< RTIBOOST_MPL_AUX_NTTP_DECL(long, x), RTIBOOST_MPL_AUX_NTTP_DECL(long, y), bool (*)(failed, failed) > 
struct assert_relation {};
#   define RTIBOOST_MPL_AUX_ASSERT_RELATION(x, y, r) assert_relation<x,y,r>
#endif

#else // RTIBOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES

rtiboost::mpl::aux::weighted_tag<1>::type operator==( assert_, assert_ );
rtiboost::mpl::aux::weighted_tag<2>::type operator!=( assert_, assert_ );
rtiboost::mpl::aux::weighted_tag<3>::type operator>(  assert_, assert_ );
rtiboost::mpl::aux::weighted_tag<4>::type operator>=( assert_, assert_ );
rtiboost::mpl::aux::weighted_tag<5>::type operator<( assert_, assert_ );
rtiboost::mpl::aux::weighted_tag<6>::type operator<=( assert_, assert_ );

template< assert_::relations r, long x, long y > struct assert_relation {};

#endif 

#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1700)

template<class Pred>
struct extract_assert_pred;

template<class Pred>
struct extract_assert_pred<void(Pred)> { typedef Pred type; };

template<class Pred>
struct eval_assert {
    typedef typename extract_assert_pred<Pred>::type P;
    typedef typename P::type p_type;
    typedef typename ::rtiboost::mpl::if_c<p_type::value,
        RTIBOOST_AUX778076_ASSERT_ARG(assert<false>),
        failed ************ P::************
    >::type type;
};

template<class Pred>
struct eval_assert_not {
    typedef typename extract_assert_pred<Pred>::type P;
    typedef typename P::type p_type;
    typedef typename ::rtiboost::mpl::if_c<!p_type::value,
        RTIBOOST_AUX778076_ASSERT_ARG(assert<false>),
        failed ************ ::rtiboost::mpl::not_<P>::************
    >::type type;
};

template< typename T >
T make_assert_arg();

#elif !defined(RTIBOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER)

template< bool > struct assert_arg_pred_impl { typedef int type; };
template<> struct assert_arg_pred_impl<true> { typedef void* type; };

template< typename P > struct assert_arg_pred
{
    typedef typename P::type p_type;
    typedef typename assert_arg_pred_impl< p_type::value >::type type;
};

template< typename P > struct assert_arg_pred_not
{
    typedef typename P::type p_type;
    RTIBOOST_MPL_AUX_ASSERT_CONSTANT( bool, p = !p_type::value );
    typedef typename assert_arg_pred_impl<p>::type type;
};

template< typename Pred >
failed ************ (Pred::************ 
      assert_arg( void (*)(Pred), typename assert_arg_pred<Pred>::type )
    );

template< typename Pred >
failed ************ (rtiboost::mpl::not_<Pred>::************ 
      assert_not_arg( void (*)(Pred), typename assert_arg_pred_not<Pred>::type )
    );

template< typename Pred >
RTIBOOST_AUX778076_ASSERT_ARG(assert<false>)
assert_arg( void (*)(Pred), typename assert_arg_pred_not<Pred>::type );

template< typename Pred >
RTIBOOST_AUX778076_ASSERT_ARG(assert<false>)
assert_not_arg( void (*)(Pred), typename assert_arg_pred<Pred>::type );


#else // RTIBOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER
        
template< bool c, typename Pred > struct assert_arg_type_impl
{
    typedef failed      ************ Pred::* mwcw83_wknd;
    typedef mwcw83_wknd ************* type;
};

template< typename Pred > struct assert_arg_type_impl<true,Pred>
{
    typedef RTIBOOST_AUX778076_ASSERT_ARG(assert<false>) type;
};

template< typename Pred > struct assert_arg_type
    : assert_arg_type_impl< RTIBOOST_MPL_AUX_VALUE_WKND(RTIBOOST_MPL_AUX_NESTED_TYPE_WKND(Pred))::value, Pred >
{
};

template< typename Pred >
typename assert_arg_type<Pred>::type 
assert_arg(void (*)(Pred), int);

template< typename Pred >
typename assert_arg_type< rtiboost::mpl::not_<Pred> >::type 
assert_not_arg(void (*)(Pred), int);

#   if !defined(RTIBOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES)
template< long x, long y, bool (*r)(failed, failed) >
typename assert_arg_type_impl< false,RTIBOOST_MPL_AUX_ASSERT_RELATION(x,y,r) >::type
assert_rel_arg( RTIBOOST_MPL_AUX_ASSERT_RELATION(x,y,r) );
#   else
template< assert_::relations r, long x, long y >
typename assert_arg_type_impl< false,assert_relation<r,x,y> >::type
assert_rel_arg( assert_relation<r,x,y> );
#   endif

#endif // RTIBOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER

#undef RTIBOOST_AUX778076_ASSERT_ARG

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, == 1700)

// RTIBOOST_MPL_ASSERT((pred<x,...>))

#define RTIBOOST_MPL_ASSERT(pred) \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,RTIBOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          rtiboost::mpl::assertion_failed<false>( \
              rtiboost::mpl::make_assert_arg< \
                  typename rtiboost::mpl::eval_assert<void pred>::type \
                >() \
            ) \
        ) \
    ) \
/**/

// RTIBOOST_MPL_ASSERT_NOT((pred<x,...>))

#define RTIBOOST_MPL_ASSERT_NOT(pred) \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,RTIBOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          rtiboost::mpl::assertion_failed<false>( \
              rtiboost::mpl::make_assert_arg< \
                  typename rtiboost::mpl::eval_assert_not<void pred>::type \
                >() \
            ) \
        ) \
    ) \
/**/

#else

// RTIBOOST_MPL_ASSERT((pred<x,...>))

#define RTIBOOST_MPL_ASSERT(pred) \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,RTIBOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          rtiboost::mpl::assertion_failed<false>( \
              rtiboost::mpl::assert_arg( (void (*) pred)0, 1 ) \
            ) \
        ) \
    ) \
/**/

// RTIBOOST_MPL_ASSERT_NOT((pred<x,...>))

#if RTIBOOST_WORKAROUND(RTIBOOST_MSVC, <= 1300)
#   define RTIBOOST_MPL_ASSERT_NOT(pred) \
enum { \
      RTIBOOST_PP_CAT(mpl_assertion_in_line_,RTIBOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          rtiboost::mpl::assertion<false>::failed( \
              rtiboost::mpl::assert_not_arg( (void (*) pred)0, 1 ) \
            ) \
        ) \
}\
/**/
#else
#   define RTIBOOST_MPL_ASSERT_NOT(pred) \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,RTIBOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
          rtiboost::mpl::assertion_failed<false>( \
              rtiboost::mpl::assert_not_arg( (void (*) pred)0, 1 ) \
            ) \
        ) \
   ) \
/**/
#endif

#endif

// RTIBOOST_MPL_ASSERT_RELATION(x, ==|!=|<=|<|>=|>, y)

#if defined(RTIBOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES)

#   if !defined(RTIBOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER)
// agurt, 9/nov/06: 'enum' below is a workaround for gcc 4.0.4/4.1.1 bugs #29522 and #29518
#   define RTIBOOST_MPL_ASSERT_RELATION_IMPL(counter, x, rel, y)      \
enum { RTIBOOST_PP_CAT(mpl_assert_rel_value,counter) = (x rel y) }; \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,counter) = sizeof( \
        rtiboost::mpl::assertion_failed<RTIBOOST_PP_CAT(mpl_assert_rel_value,counter)>( \
            (rtiboost::mpl::failed ************ ( rtiboost::mpl::assert_relation< \
                  rtiboost::mpl::assert_::relations( sizeof( \
                      rtiboost::mpl::assert_::arg rel rtiboost::mpl::assert_::arg \
                    ) ) \
                , x \
                , y \
                >::************)) 0 ) \
        ) \
    ) \
/**/
#   else
#   define RTIBOOST_MPL_ASSERT_RELATION_IMPL(counter, x, rel, y)    \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assert_rel,counter) = sizeof( \
          rtiboost::mpl::assert_::arg rel rtiboost::mpl::assert_::arg \
        ) \
    ); \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( bool, RTIBOOST_PP_CAT(mpl_assert_rel_value,counter) = (x rel y) ); \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,counter) = sizeof( \
        rtiboost::mpl::assertion_failed<RTIBOOST_PP_CAT(mpl_assert_rel_value,counter)>( \
              rtiboost::mpl::assert_rel_arg( rtiboost::mpl::assert_relation< \
                  rtiboost::mpl::assert_::relations(RTIBOOST_PP_CAT(mpl_assert_rel,counter)) \
                , x \
                , y \
                >() ) \
            ) \
        ) \
    ) \
/**/
#   endif

#   define RTIBOOST_MPL_ASSERT_RELATION(x, rel, y) \
RTIBOOST_MPL_ASSERT_RELATION_IMPL(RTIBOOST_MPL_AUX_PP_COUNTER(), x, rel, y) \
/**/

#else // !RTIBOOST_MPL_CFG_ASSERT_USE_RELATION_NAMES

#   if defined(RTIBOOST_MPL_CFG_ASSERT_BROKEN_POINTER_TO_POINTER_TO_MEMBER)
#   define RTIBOOST_MPL_ASSERT_RELATION(x, rel, y) \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,RTIBOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
        rtiboost::mpl::assertion_failed<(x rel y)>( rtiboost::mpl::assert_rel_arg( \
              rtiboost::mpl::RTIBOOST_MPL_AUX_ASSERT_RELATION(x,y,(&rtiboost::mpl::operator rel))() \
            ) ) \
        ) \
    ) \
/**/
#   else
#   define RTIBOOST_MPL_ASSERT_RELATION(x, rel, y) \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,RTIBOOST_MPL_AUX_PP_COUNTER()) = sizeof( \
        rtiboost::mpl::assertion_failed<(x rel y)>( (rtiboost::mpl::failed ************ ( \
            rtiboost::mpl::RTIBOOST_MPL_AUX_ASSERT_RELATION(x,y,(&rtiboost::mpl::operator rel))::************))0 ) \
        ) \
    ) \
/**/
#   endif

#endif


// RTIBOOST_MPL_ASSERT_MSG( (pred<x,...>::value), USER_PROVIDED_MESSAGE, (types<x,...>) ) 

#if RTIBOOST_WORKAROUND(__MWERKS__, RTIBOOST_TESTED_AT(0x3202))
#   define RTIBOOST_MPL_ASSERT_MSG_IMPL( counter, c, msg, types_ ) \
struct msg; \
typedef struct RTIBOOST_PP_CAT(msg,counter) : rtiboost::mpl::assert_ \
{ \
    using rtiboost::mpl::assert_::types; \
    static rtiboost::mpl::failed ************ (msg::************ assert_arg()) types_ \
    { return 0; } \
} RTIBOOST_PP_CAT(mpl_assert_arg,counter); \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,counter) = sizeof( \
        rtiboost::mpl::assertion<(c)>::failed( RTIBOOST_PP_CAT(mpl_assert_arg,counter)::assert_arg() ) \
        ) \
    ) \
/**/
#else
#   define RTIBOOST_MPL_ASSERT_MSG_IMPL( counter, c, msg, types_ )  \
struct msg; \
typedef struct RTIBOOST_PP_CAT(msg,counter) : rtiboost::mpl::assert_ \
{ \
    static rtiboost::mpl::failed ************ (msg::************ assert_arg()) types_ \
    { return 0; } \
} RTIBOOST_PP_CAT(mpl_assert_arg,counter); \
RTIBOOST_MPL_AUX_ASSERT_CONSTANT( \
      std::size_t \
    , RTIBOOST_PP_CAT(mpl_assertion_in_line_,counter) = sizeof( \
        rtiboost::mpl::assertion_failed<(c)>( RTIBOOST_PP_CAT(mpl_assert_arg,counter)::assert_arg() ) \
        ) \
    ) \
/**/
#endif

#define RTIBOOST_MPL_ASSERT_MSG( c, msg, types_ ) \
RTIBOOST_MPL_ASSERT_MSG_IMPL( RTIBOOST_MPL_AUX_PP_COUNTER(), c, msg, types_ ) \
/**/

#endif // RTIBOOST_MPL_ASSERT_HPP_INCLUDED
