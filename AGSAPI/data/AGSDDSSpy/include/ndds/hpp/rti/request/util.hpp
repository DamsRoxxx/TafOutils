/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_REQUEST_UTIL_HPP_
#define RTI_REQUEST_UTIL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/sub/LoanedSample.hpp>

namespace rti { namespace request {

/**
 * @ingroup PatternsInfrastructureModule
 * @brief Functor to match replies by their related request
 *
 * Useful for C++ standard algorithms like <tt>std::find_if()</tt>
 *
 * @see \ref RequestReplyExampleModule_correlation
 */
template <typename T>
class IsReplyRelatedPredicate {
public:

    /**
     * @brief Creates the predicate with the request id to match
     */
    IsReplyRelatedPredicate(const rti::core::SampleIdentity& related_request_id)
        : related_request_id_(related_request_id)
    {
    }

    /**
     * @brief Determines if a reply is related to the request id this object
     * contains
     */
    bool operator()(dds::sub::Sample<T> sample)
    {
        return sample.info()->related_original_publication_virtual_sample_identity()
                == related_request_id_;
    }

    /**
     * @brief Determines if a reply is related to the request id this object
     * contains
     */
    bool operator()(rti::sub::LoanedSample<T> sample)
    {
        return sample.info()->related_original_publication_virtual_sample_identity()
                == related_request_id_;
    }

    /**
     * @brief Determines if a reply info is related to the request id this object
     * contains
     */
    bool operator()(dds::sub::SampleInfo sample_info)
    {
        return sample_info->related_original_publication_virtual_sample_identity()
                == related_request_id_;
    }

private:
    rti::core::SampleIdentity related_request_id_;
};

} } // namespace rti::request

#endif // RTI_REQUEST_UTIL_HPP_
