// Copyright (C) 2010 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef RTIBOOST_TYPEOF_UNSUPPORTED_HPP_INCLUDED
#define RTIBOOST_TYPEOF_UNSUPPORTED_HPP_INCLUDED

namespace rtiboost { namespace type_of {
    struct typeof_emulation_is_unsupported_on_this_compiler {};
}}

#define RTIBOOST_TYPEOF(expr) rtiboost::type_of::typeof_emulation_is_unsupported_on_this_compiler
#define RTIBOOST_TYPEOF_TPL RTIBOOST_TYPEOF

#define RTIBOOST_TYPEOF_NESTED_TYPEDEF_TPL(name,expr) \
struct name {\
    typedef RTIBOOST_TYPEOF_TPL(expr) type;\
};

#define RTIBOOST_TYPEOF_NESTED_TYPEDEF(name,expr) \
struct name {\
    typedef RTIBOOST_TYPEOF(expr) type;\
};


#define RTIBOOST_TYPEOF_REGISTER_TYPE(x)
#define RTIBOOST_TYPEOF_REGISTER_TEMPLATE(x, params)

#endif