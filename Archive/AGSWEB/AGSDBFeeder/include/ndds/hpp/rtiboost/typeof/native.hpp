// Copyright (C) 2006 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_NATIVE_HPP_INCLUDED
#define RTIBOOST_TYPEOF_NATIVE_HPP_INCLUDED

#ifndef MSVC_TYPEOF_HACK

#ifdef RTIBOOST_NO_SFINAE

namespace rtiboost { namespace type_of {

    template<class T> 
        T& ensure_obj(const T&);

}}

#else

#include <rtiboost/type_traits/is_function.hpp> 
#include <rtiboost/utility/enable_if.hpp>

namespace rtiboost { namespace type_of {
# ifdef RTIBOOST_NO_SFINAE
    template<class T> 
    T& ensure_obj(const T&);
# else
    template<typename T>
        typename enable_if<is_function<T>, T&>::type
        ensure_obj(T&);

    template<typename T>
        typename disable_if<is_function<T>, T&>::type
        ensure_obj(const T&);
# endif
}}

#endif//RTIBOOST_NO_SFINAE

#define RTIBOOST_TYPEOF(expr) RTIBOOST_TYPEOF_KEYWORD(rtiboost::type_of::ensure_obj(expr))
#define RTIBOOST_TYPEOF_TPL RTIBOOST_TYPEOF

#define RTIBOOST_TYPEOF_NESTED_TYPEDEF_TPL(name,expr) \
    struct name {\
        typedef RTIBOOST_TYPEOF_TPL(expr) type;\
    };

#define RTIBOOST_TYPEOF_NESTED_TYPEDEF(name,expr) \
    struct name {\
        typedef RTIBOOST_TYPEOF(expr) type;\
    };

#endif//MSVC_TYPEOF_HACK

#define RTIBOOST_TYPEOF_REGISTER_TYPE(x)
#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE(x, params)

#endif//RTIBOOST_TYPEOF_NATIVE_HPP_INCLUDED

