
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

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <rtiboost/mpl/integral_c_tag.hpp>
#include <rtiboost/mpl/aux_/static_cast.hpp>
#include <rtiboost/mpl/aux_/nttp_decl.hpp>
#include <rtiboost/mpl/aux_/config/static_constant.hpp>
#include <rtiboost/mpl/aux_/config/workaround.hpp>

#include <rtiboost/preprocessor/cat.hpp>

#if !defined(RTIBOOST_AUX_WRAPPER_NAME)
#   define RTIBOOST_AUX_WRAPPER_NAME RTIBOOST_PP_CAT(RTIBOOST_AUX_WRAPPER_VALUE_TYPE,_)
#endif

#if !defined(RTIBOOST_AUX_WRAPPER_PARAMS)
#   define RTIBOOST_AUX_WRAPPER_PARAMS(N) RTIBOOST_MPL_AUX_NTTP_DECL(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, N)
#endif

#if !defined(RTIBOOST_AUX_WRAPPER_INST)
#   if RTIBOOST_WORKAROUND(__MWERKS__, <= 0x2407)
#       define RTIBOOST_AUX_WRAPPER_INST(value) RTIBOOST_AUX_WRAPPER_NAME< value >
#   else 
#       define RTIBOOST_AUX_WRAPPER_INST(value) RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::RTIBOOST_AUX_WRAPPER_NAME< value >
#   endif
#endif

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< RTIBOOST_AUX_WRAPPER_PARAMS(N) >
struct RTIBOOST_AUX_WRAPPER_NAME
{
    RTIBOOST_STATIC_CONSTANT(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, value = N);
// agurt, 08/mar/03: SGI MIPSpro C++ workaround, have to #ifdef because some 
// other compilers (e.g. MSVC) are not particulary happy about it
#if RTIBOOST_WORKAROUND(__EDG_VERSION__, <= 238)
    typedef struct RTIBOOST_AUX_WRAPPER_NAME type;
#else
    typedef RTIBOOST_AUX_WRAPPER_NAME type;
#endif
    typedef RTIBOOST_AUX_WRAPPER_VALUE_TYPE value_type;
    typedef rtiboost_integral_c_tag tag;

// have to #ifdef here: some compilers don't like the 'N + 1' form (MSVC),
// while some other don't like 'value + 1' (Borland), and some don't like
// either
#if RTIBOOST_WORKAROUND(__EDG_VERSION__, <= 243)
 private:
    RTIBOOST_STATIC_CONSTANT(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, next_value = RTIBOOST_MPL_AUX_STATIC_CAST(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, (N + 1)));
    RTIBOOST_STATIC_CONSTANT(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, prior_value = RTIBOOST_MPL_AUX_STATIC_CAST(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, (N - 1)));
 public:
    typedef RTIBOOST_AUX_WRAPPER_INST(next_value) next;
    typedef RTIBOOST_AUX_WRAPPER_INST(prior_value) prior;
#elif RTIBOOST_WORKAROUND(__BORLANDC__, RTIBOOST_TESTED_AT(0x561)) \
    || RTIBOOST_WORKAROUND(__IBMCPP__, RTIBOOST_TESTED_AT(502)) \
    || (RTIBOOST_WORKAROUND(__HP_aCC, <= 53800) && (RTIBOOST_WORKAROUND(__hpxstd98, != 1)))
    typedef RTIBOOST_AUX_WRAPPER_INST( RTIBOOST_MPL_AUX_STATIC_CAST(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, (N + 1)) ) next;
    typedef RTIBOOST_AUX_WRAPPER_INST( RTIBOOST_MPL_AUX_STATIC_CAST(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, (N - 1)) ) prior;
#else
    typedef RTIBOOST_AUX_WRAPPER_INST( RTIBOOST_MPL_AUX_STATIC_CAST(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, (value + 1)) ) next;
    typedef RTIBOOST_AUX_WRAPPER_INST( RTIBOOST_MPL_AUX_STATIC_CAST(RTIBOOST_AUX_WRAPPER_VALUE_TYPE, (value - 1)) ) prior;
#endif

    // enables uniform function call syntax for families of overloaded 
    // functions that return objects of both arithmetic ('int', 'long',
    // 'double', etc.) and wrapped integral types (for an example, see 
    // "mpl/example/power.cpp")
    operator RTIBOOST_AUX_WRAPPER_VALUE_TYPE() const { return static_cast<RTIBOOST_AUX_WRAPPER_VALUE_TYPE>(this->value); } 
};

#if !defined(RTIBOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< RTIBOOST_AUX_WRAPPER_PARAMS(N) >
RTIBOOST_AUX_WRAPPER_VALUE_TYPE const RTIBOOST_AUX_WRAPPER_INST(N)::value;
#endif

RTIBOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#undef RTIBOOST_AUX_WRAPPER_NAME
#undef RTIBOOST_AUX_WRAPPER_PARAMS
#undef RTIBOOST_AUX_WRAPPER_INST
#undef RTIBOOST_AUX_WRAPPER_VALUE_TYPE
