/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_SAMPLE_FLAG_HPP_
#define RTI_DDS_CORE_SAMPLE_FLAG_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <bitset>

namespace rti { namespace core {

/** 
 * @ingroup DDSInfrastructureModule 
 * @headerfile SampleFlag.hpp "rti/core/SampleFlag.hpp"
 *  
 * @brief @extension A set of flags that can be associated with a sample. 
 *  
 * @dref_SampleFlag 
 */
class OMG_DDS_API SampleFlag : public std::bitset<32> {
public:
    /**
     * @brief A typedef of std::bitset<32> for convenience
     */
    typedef std::bitset<32> MaskType;

public:
    /**
     * @brief Construct an empty SampleFlag with no bits set
     */
    SampleFlag()
    {
    }

    /**
     * @brief Construct a SampleFlag from an integer
     * 
     * @param mask Value whose bits are copied to the bitset positions
     */
    explicit SampleFlag(uint64_t mask) 
        : MaskType(mask)
    {
    }

    /**
     * @brief Construct a SampleFlag from a MaskType object
     * 
     * @param mask A std::bitset<32> to construct this SampleFlag from 
     */
    SampleFlag(const MaskType& mask) 
        : MaskType(mask)
    {
    }

    /**
     * @brief Indicates that a sample has been redelivered by 
     * RTI Queuing Service.
     */
    static const SampleFlag redelivered()
    {
        return SampleFlag(DDS_REDELIVERED_SAMPLE);
    }

    /**
       @brief Indicates that a response sample is not the last response 
       sample for a given request. This bit is usually set by Connext 
       Repliers sending multiple responses for a request.
     */
    static const SampleFlag intermediate_reply_sequence()
    {
        return SampleFlag(DDS_INTERMEDIATE_REPLY_SEQUENCE_SAMPLE);
    }

    /**
     * @brief Indicates if a sample must be broadcast by one RTI Queuing 
     * Service replica to other replicas.
     */
    static const SampleFlag replicate()
    {
        return SampleFlag(DDS_REPLICATE_SAMPLE);
    }

    /**
     * @brief Indicates that a sample is the last sample in a SharedReaderQueue 
     * for a QueueConsumer DataReader.                
     */
    static const SampleFlag last_shared_reader_queue()
    {
        return SampleFlag(DDS_LAST_SHARED_READER_QUEUE_SAMPLE);
    }

    /**
     * @brief Indicates that a sample for a TopicQuery will be followed by
     * more samples.
     *
     * @details @dref_details_SampleFlagBits_INTERMEDIATE_TOPIC_QUERY_SAMPLE
     */
    static const SampleFlag intermediate_topic_query_sample()
    {
        return SampleFlag(DDS_INTERMEDIATE_TOPIC_QUERY_SAMPLE);
    }
};

} } // namespace rti::core

#endif // RTI_DDS_CORE_SAMPLE_FLAG_HPP_
