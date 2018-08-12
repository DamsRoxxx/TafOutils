// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#include <rtiboost/typeof/encode_decode_params.hpp>

// member functions

template<class V, class T, class R RTIBOOST_PP_ENUM_TRAILING_PARAMS(n, class P)> 
struct encode_type_impl<V, R(T::*)(RTIBOOST_PP_ENUM_PARAMS(n, P)) RTIBOOST_TYPEOF_qualifier>
{
    typedef R RTIBOOST_PP_CAT(P, n);
    typedef T RTIBOOST_PP_CAT(P, RTIBOOST_PP_INC(n));
    typedef RTIBOOST_TYPEOF_ENCODE_PARAMS(RTIBOOST_PP_ADD(n, 2), RTIBOOST_TYPEOF_id + n) type;
};

template<class Iter>
struct decode_type_impl<rtiboost::mpl::size_t<RTIBOOST_TYPEOF_id + n>, Iter>
{
    typedef Iter iter0;
    RTIBOOST_TYPEOF_DECODE_PARAMS(RTIBOOST_PP_ADD(n, 2))
    template<class T> struct workaround{
        typedef RTIBOOST_PP_CAT(p, n)(T::*type)(RTIBOOST_PP_ENUM_PARAMS(n, p)) RTIBOOST_TYPEOF_qualifier;
    };
    typedef typename workaround<RTIBOOST_PP_CAT(p, RTIBOOST_PP_INC(n))>::type type;
    typedef RTIBOOST_PP_CAT(iter, RTIBOOST_PP_ADD(n, 2)) iter;
};

// undef parameters

#undef RTIBOOST_TYPEOF_id
#undef RTIBOOST_TYPEOF_qualifier
