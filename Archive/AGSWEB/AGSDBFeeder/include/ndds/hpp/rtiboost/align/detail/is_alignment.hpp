/*
(c) 2014 Glen Joseph Fernandes
<glenjofe -at- gmail.com>

Distributed under the Boost Software
License, Version 1.0.
http://boost.org/LICENSE_1_0.txt
*/
#ifndef RTIBOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP
#define RTIBOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP

#include <rtiboost/config.hpp>
#include <cstddef>

namespace rtiboost {
namespace alignment {
namespace detail {

RTIBOOST_CONSTEXPR inline bool is_alignment(std::size_t value)
    RTIBOOST_NOEXCEPT
{
    return (value > 0) && ((value & (value - 1)) == 0);
}

} /* .detail */
} /* .alignment */
} /* .boost */

#endif
