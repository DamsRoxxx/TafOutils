// Copyright (C) 2004 Arkadiy Vertleyb
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <rtiboost/typeof/encode_decode_params.hpp>

#define n RTIBOOST_PP_ITERATION()

// function pointers

template<class V, class R RTIBOOST_PP_ENUM_TRAILING_PARAMS(n, class P)>
struct encode_type_impl<V, R(*)(RTIBOOST_PP_ENUM_PARAMS(n, P))>
{
    typedef R RTIBOOST_PP_CAT(P, n);
    typedef RTIBOOST_TYPEOF_ENCODE_PARAMS(RTIBOOST_PP_INC(n), FUN_PTR_ID + n) type;
};

template<class V, class R RTIBOOST_PP_ENUM_TRAILING_PARAMS(n, class P)>
struct encode_type_impl<V, R(*)(RTIBOOST_PP_ENUM_PARAMS(n, P) ...)>
{
    typedef R RTIBOOST_PP_CAT(P, n);
    typedef RTIBOOST_TYPEOF_ENCODE_PARAMS(RTIBOOST_PP_INC(n), FUN_VAR_PTR_ID + n) type;
};

template<class Iter>
struct decode_type_impl<rtiboost::mpl::size_t<FUN_PTR_ID + n>, Iter>
{
    typedef Iter iter0;
    RTIBOOST_TYPEOF_DECODE_PARAMS(RTIBOOST_PP_INC(n))
    typedef RTIBOOST_PP_CAT(p, n)(*type)(RTIBOOST_PP_ENUM_PARAMS(n, p));
    typedef RTIBOOST_PP_CAT(iter, RTIBOOST_PP_INC(n)) iter;
};

template<class Iter>
struct decode_type_impl<rtiboost::mpl::size_t<FUN_VAR_PTR_ID + n>, Iter>
{
    typedef Iter iter0;
    RTIBOOST_TYPEOF_DECODE_PARAMS(RTIBOOST_PP_INC(n))
    typedef RTIBOOST_PP_CAT(p, n)(*type)(RTIBOOST_PP_ENUM_PARAMS(n, p) ...);
    typedef RTIBOOST_PP_CAT(iter, RTIBOOST_PP_INC(n)) iter;
};

#ifndef RTIBOOST_TYPEOF_NO_FUNCTION_TYPES

    // function references

    template<class V, class R RTIBOOST_PP_ENUM_TRAILING_PARAMS(n, class P)>
    struct encode_type_impl<V, R(&)(RTIBOOST_PP_ENUM_PARAMS(n, P))>
    {
        typedef R RTIBOOST_PP_CAT(P, n);
        typedef RTIBOOST_TYPEOF_ENCODE_PARAMS(RTIBOOST_PP_INC(n), FUN_REF_ID + n) type;
    };

    template<class V, class R RTIBOOST_PP_ENUM_TRAILING_PARAMS(n, class P)>
    struct encode_type_impl<V, R(&)(RTIBOOST_PP_ENUM_PARAMS(n, P) ...)>
    {
        typedef R RTIBOOST_PP_CAT(P, n);
        typedef RTIBOOST_TYPEOF_ENCODE_PARAMS(RTIBOOST_PP_INC(n), FUN_VAR_REF_ID + n) type;
    };

    template<class Iter>
    struct decode_type_impl<rtiboost::mpl::size_t<FUN_REF_ID + n>, Iter>
    {
        typedef Iter iter0;
        RTIBOOST_TYPEOF_DECODE_PARAMS(RTIBOOST_PP_INC(n))
        typedef RTIBOOST_PP_CAT(p, n)(&type)(RTIBOOST_PP_ENUM_PARAMS(n, p));
        typedef RTIBOOST_PP_CAT(iter, RTIBOOST_PP_INC(n)) iter;
    };

    template<class Iter>
    struct decode_type_impl<rtiboost::mpl::size_t<FUN_VAR_REF_ID + n>, Iter>
    {
        typedef Iter iter0;
        RTIBOOST_TYPEOF_DECODE_PARAMS(RTIBOOST_PP_INC(n))
        typedef RTIBOOST_PP_CAT(p, n)(&type)(RTIBOOST_PP_ENUM_PARAMS(n, p) ...);
        typedef RTIBOOST_PP_CAT(iter, RTIBOOST_PP_INC(n)) iter;
    };

    // functions

    template<class V, class R RTIBOOST_PP_ENUM_TRAILING_PARAMS(n, class P)>
    struct encode_type_impl<V, R(RTIBOOST_PP_ENUM_PARAMS(n, P))>
    {
        typedef R RTIBOOST_PP_CAT(P, n);
        typedef RTIBOOST_TYPEOF_ENCODE_PARAMS(RTIBOOST_PP_INC(n), FUN_ID + n) type;
    };

    template<class V, class R RTIBOOST_PP_ENUM_TRAILING_PARAMS(n, class P)>
    struct encode_type_impl<V, R(RTIBOOST_PP_ENUM_PARAMS(n, P) ...)>
    {
        typedef R RTIBOOST_PP_CAT(P, n);
        typedef RTIBOOST_TYPEOF_ENCODE_PARAMS(RTIBOOST_PP_INC(n), FUN_VAR_ID + n) type;
    };

    template<class Iter>
    struct decode_type_impl<rtiboost::mpl::size_t<FUN_ID + n>, Iter>
    {
        typedef Iter iter0;
        RTIBOOST_TYPEOF_DECODE_PARAMS(RTIBOOST_PP_INC(n))
        typedef RTIBOOST_PP_CAT(p, n)(type)(RTIBOOST_PP_ENUM_PARAMS(n, p));
        typedef RTIBOOST_PP_CAT(iter, RTIBOOST_PP_INC(n)) iter;
    };

    template<class Iter>
    struct decode_type_impl<rtiboost::mpl::size_t<FUN_VAR_ID + n>, Iter>
    {
        typedef Iter iter0;
        RTIBOOST_TYPEOF_DECODE_PARAMS(RTIBOOST_PP_INC(n))
        typedef RTIBOOST_PP_CAT(p, n)(type)(RTIBOOST_PP_ENUM_PARAMS(n, p) ...);
        typedef RTIBOOST_PP_CAT(iter, RTIBOOST_PP_INC(n)) iter;
    };

#endif//RTIBOOST_TYPEOF_NO_FUNCTION_TYPES

#ifndef RTIBOOST_TYPEOF_NO_MEMBER_FUNCTION_TYPES
// member functions

#define RTIBOOST_TYPEOF_qualifier
#define RTIBOOST_TYPEOF_id MEM_FUN_ID
#include <rtiboost/typeof/register_mem_functions.hpp>

#define RTIBOOST_TYPEOF_qualifier const
#define RTIBOOST_TYPEOF_id CONST_MEM_FUN_ID
#include <rtiboost/typeof/register_mem_functions.hpp>

#define RTIBOOST_TYPEOF_qualifier volatile
#define RTIBOOST_TYPEOF_id VOLATILE_MEM_FUN_ID
#include <rtiboost/typeof/register_mem_functions.hpp>

#define RTIBOOST_TYPEOF_qualifier volatile const
#define RTIBOOST_TYPEOF_id VOLATILE_CONST_MEM_FUN_ID
#include <rtiboost/typeof/register_mem_functions.hpp>

#undef n
#endif
