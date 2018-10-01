/*
 (c) 2014 Glen Joseph Fernandes
 glenjofe at gmail dot com

 Distributed under the Boost Software
 License, Version 1.0.
 http://boost.org/LICENSE_1_0.txt
*/
#ifndef RTIBOOST_ALIGN_DETAIL_ADDRESS_HPP
#define RTIBOOST_ALIGN_DETAIL_ADDRESS_HPP

#include <rtiboost/cstdint.hpp>
#include <cstddef>

namespace rtiboost {
    namespace alignment {
        namespace detail {
#if defined(RTIBOOST_HAS_INTPTR_T)
            typedef rtiboost::uintptr_t address_t;
#else
            typedef std::size_t address_t;
#endif
        }
    }
}

#endif
