/*
(c) 2014 Glen Joseph Fernandes
<glenjofe -at- gmail.com>

Distributed under the Boost Software
License, Version 1.0.
http://boost.org/LICENSE_1_0.txt
*/
#ifndef RTIBOOST_ALIGN_DETAIL_ALIGN_HPP
#define RTIBOOST_ALIGN_DETAIL_ALIGN_HPP

#include <rtiboost/align/detail/is_alignment.hpp>
#include <rtiboost/assert.hpp>

namespace rtiboost {
namespace alignment {

inline void* align(std::size_t alignment, std::size_t size,
    void*& ptr, std::size_t& space)
{
    RTIBOOST_ASSERT(detail::is_alignment(alignment));
    if (size <= space) {
        char* p = reinterpret_cast<char*>((reinterpret_cast<std::
            size_t>(ptr) + alignment - 1) & ~(alignment - 1));
        std::ptrdiff_t n = p - static_cast<char*>(ptr);
        if (size <= space - n) {
            ptr = p;
            space -= n;
            return p;
        }
    }
    return 0;
}

} /* .alignment */
} /* .boost */

#endif
