// Copyright (C) 2005 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
//
// Copyright (C) 2006 Tobias Schwinger
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_VECTOR_HPP_INCLUDED

#include <rtiboost/mpl/int.hpp>
#include <rtiboost/preprocessor/iteration/self.hpp>

#ifndef RTIBOOST_TYPEOF_LIMIT_SIZE
#   define RTIBOOST_TYPEOF_LIMIT_SIZE 50
#endif

//
// To recreate the preprocessed versions of this file preprocess and run
//
//   $(RTIBOOST_ROOT)/libs/typeof/tools/preprocess.pl
//

#if defined(RTIBOOST_TYPEOF_PP_INCLUDE_EXTERNAL)

#   undef RTIBOOST_TYPEOF_PP_INCLUDE_EXTERNAL

#elif !defined(RTIBOOST_TYPEOF_PREPROCESSING_MODE) && !RTIBOOST_PP_IS_SELFISH

#   define RTIBOOST_PP_INDIRECT_SELF <rtiboost/typeof/vector.hpp>
#   if   RTIBOOST_TYPEOF_LIMIT_SIZE < 50
#     include RTIBOOST_PP_INCLUDE_SELF()
#   elif RTIBOOST_TYPEOF_LIMIT_SIZE < 100
#     include <rtiboost/typeof/vector50.hpp>
#     define  RTIBOOST_TYPEOF_PP_START_SIZE 51
#     include RTIBOOST_PP_INCLUDE_SELF()
#   elif RTIBOOST_TYPEOF_LIMIT_SIZE < 150
#     include <rtiboost/typeof/vector100.hpp>
#     define  RTIBOOST_TYPEOF_PP_START_SIZE 101
#     include RTIBOOST_PP_INCLUDE_SELF()
#   elif RTIBOOST_TYPEOF_LIMIT_SIZE < 200
#     include <rtiboost/typeof/vector150.hpp>
#     define  RTIBOOST_TYPEOF_PP_START_SIZE 151
#     include RTIBOOST_PP_INCLUDE_SELF()
#   elif RTIBOOST_TYPEOF_LIMIT_SIZE <= 250
#     include <rtiboost/typeof/vector200.hpp>
#     define  RTIBOOST_TYPEOF_PP_START_SIZE 201
#     include RTIBOOST_PP_INCLUDE_SELF()
#   else
#     error "RTIBOOST_TYPEOF_LIMIT_SIZE too high"
#   endif

#else// defined(RTIBOOST_TYPEOF_PREPROCESSING_MODE) || RTIBOOST_PP_IS_SELFISH

#   ifndef RTIBOOST_TYPEOF_PP_NEXT_SIZE
#     define RTIBOOST_TYPEOF_PP_NEXT_SIZE RTIBOOST_TYPEOF_LIMIT_SIZE
#   endif
#   ifndef RTIBOOST_TYPEOF_PP_START_SIZE
#     define RTIBOOST_TYPEOF_PP_START_SIZE 0
#   endif

#   if RTIBOOST_TYPEOF_PP_START_SIZE <= RTIBOOST_TYPEOF_LIMIT_SIZE

#     include <rtiboost/preprocessor/enum_params.hpp>
#     include <rtiboost/preprocessor/repeat.hpp>
#     include <rtiboost/preprocessor/repeat_from_to.hpp>
#     include <rtiboost/preprocessor/cat.hpp>
#     include <rtiboost/preprocessor/inc.hpp>
#     include <rtiboost/preprocessor/dec.hpp>
#     include <rtiboost/preprocessor/comma_if.hpp>
#     include <rtiboost/preprocessor/iteration/local.hpp>
#     include <rtiboost/preprocessor/control/expr_iif.hpp>
#     include <rtiboost/preprocessor/logical/not.hpp>

// iterator

#     define RTIBOOST_TYPEOF_spec_iter(n)\
        template<class V>\
        struct v_iter<V, mpl::int_<n> >\
        {\
            typedef typename V::item ## n type;\
            typedef v_iter<V, mpl::int_<n + 1> > next;\
        };

namespace rtiboost { namespace type_of {

    template<class V, class Increase_RTIBOOST_TYPEOF_LIMIT_SIZE> struct v_iter; // not defined
#     define  RTIBOOST_PP_LOCAL_MACRO  RTIBOOST_TYPEOF_spec_iter
#     define  RTIBOOST_PP_LOCAL_LIMITS \
        (RTIBOOST_PP_DEC(RTIBOOST_TYPEOF_PP_START_SIZE), \
         RTIBOOST_PP_DEC(RTIBOOST_TYPEOF_LIMIT_SIZE))
#     include RTIBOOST_PP_LOCAL_ITERATE()

}}

#     undef RTIBOOST_TYPEOF_spec_iter

// vector

#     define RTIBOOST_TYPEOF_typedef_item(z, n, _)\
        typedef P ## n item ## n;

#     define RTIBOOST_TYPEOF_typedef_fake_item(z, n, _)\
        typedef mpl::int_<1> item ## n;

#     define RTIBOOST_TYPEOF_define_vector(n)\
        template<RTIBOOST_PP_ENUM_PARAMS(n, class P) RTIBOOST_PP_EXPR_IIF(RTIBOOST_PP_NOT(n), class T = void)>\
        struct vector ## n\
        {\
            typedef v_iter<vector ## n<RTIBOOST_PP_ENUM_PARAMS(n,P)>, rtiboost::mpl::int_<0> > begin;\
            RTIBOOST_PP_REPEAT(n, RTIBOOST_TYPEOF_typedef_item, ~)\
            RTIBOOST_PP_REPEAT_FROM_TO(n, RTIBOOST_TYPEOF_PP_NEXT_SIZE, RTIBOOST_TYPEOF_typedef_fake_item, ~)\
        };

namespace rtiboost { namespace type_of {

#     define  RTIBOOST_PP_LOCAL_MACRO  RTIBOOST_TYPEOF_define_vector
#     define  RTIBOOST_PP_LOCAL_LIMITS \
        (RTIBOOST_TYPEOF_PP_START_SIZE,RTIBOOST_TYPEOF_LIMIT_SIZE)
#     include RTIBOOST_PP_LOCAL_ITERATE()

}}

#     undef RTIBOOST_TYPEOF_typedef_item
#     undef RTIBOOST_TYPEOF_typedef_fake_item
#     undef RTIBOOST_TYPEOF_define_vector

// push_back

#     define RTIBOOST_TYPEOF_spec_push_back(n)\
        template<RTIBOOST_PP_ENUM_PARAMS(n, class P) RTIBOOST_PP_COMMA_IF(n) class T>\
        struct push_back<RTIBOOST_PP_CAT(rtiboost::type_of::vector, n)<RTIBOOST_PP_ENUM_PARAMS(n, P)>, T>\
        {\
            typedef RTIBOOST_PP_CAT(rtiboost::type_of::vector, RTIBOOST_PP_INC(n))<\
                RTIBOOST_PP_ENUM_PARAMS(n, P) RTIBOOST_PP_COMMA_IF(n) T\
            > type;\
        };

namespace rtiboost { namespace type_of {

#   if   RTIBOOST_TYPEOF_LIMIT_SIZE < 50
    template<class V, class T> struct push_back {
        typedef V type;
    };
#   endif
    //default behaviour is to let push_back ignore T, and return the input vector.
    //This is to let RTIBOOST_TYPEOF_NESTED_TYPEDEF work properly with the default vector.
#     define  RTIBOOST_PP_LOCAL_MACRO  RTIBOOST_TYPEOF_spec_push_back
#     define  RTIBOOST_PP_LOCAL_LIMITS \
        (RTIBOOST_PP_DEC(RTIBOOST_TYPEOF_PP_START_SIZE), \
         RTIBOOST_PP_DEC(RTIBOOST_TYPEOF_LIMIT_SIZE))
#     include RTIBOOST_PP_LOCAL_ITERATE()

}}

#     undef RTIBOOST_TYPEOF_spec_push_back

#   endif//RTIBOOST_TYPEOF_PP_START_SIZE<=RTIBOOST_TYPEOF_LIMIT_SIZE
#   undef  RTIBOOST_TYPEOF_PP_START_SIZE
#   undef  RTIBOOST_TYPEOF_PP_NEXT_SIZE

#endif//RTIBOOST_TYPEOF_PREPROCESSING_MODE || RTIBOOST_PP_IS_SELFISH

#define RTIBOOST_TYPEOF_VECTOR_HPP_INCLUDED
#endif//RTIBOOST_TYPEOF_VECTOR_HPP_INCLUDED

