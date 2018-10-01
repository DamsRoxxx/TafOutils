/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
-------------------- 
1.7a,04apr14,eam Added equals 
1.0a,20mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_SAMPLE_INFO_IMPL_HPP_
#define RTI_DDS_SUB_SAMPLE_INFO_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/NativeValueType.hpp>
#include <dds/sub/GenerationCount.hpp>
#include <dds/sub/Rank.hpp>
#include <rti/core/SampleIdentity.hpp>
#include <rti/core/SampleFlag.hpp>

#include "ndds/ndds_c.h"

namespace rti { namespace sub {

class SampleInfoImpl;

class SampleInfoAdapter {
public:
    typedef DDS_SampleInfo native_type;

    static void initialize(native_type& native_value)
    {
        native_value = DDS_SAMPLEINFO_DEFAULT;
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        destination = source;
    }

    /* Implemented in SampleInfoImpl
    static bool equals(const native_type& first, const native_type& second)
    {
    } 
    */ 
};

} // namespace sub

namespace core {

template<>
struct native_type_traits<rti::sub::SampleInfoImpl> {
    typedef rti::sub::SampleInfoAdapter adapter_type;
    typedef rti::sub::SampleInfoAdapter::native_type native_type;
};

} // namespace core

namespace sub {

/** @RTI_class_definition NA */
class SampleInfoImpl : public rti::core::NativeValueType<SampleInfoImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(SampleInfoImpl)

private:
    typedef rti::core::NativeValueType<SampleInfoImpl> Base;

public:

    SampleInfoImpl() : Base()
    {
    }

    const dds::core::Time source_timestamp() const
    {
        return dds::core::Time(
            native().source_timestamp.sec, native().source_timestamp.nanosec);
    }

    const dds::sub::status::DataState state() const
    {
        using namespace dds::sub::status;

        return DataState(
            SampleState(native().sample_state),
            ViewState(native().view_state),
            InstanceState(native().instance_state));
    }

    dds::sub::GenerationCount generation_count() const
    {
        return dds::sub::GenerationCount(
            native().disposed_generation_count,
            native().no_writers_generation_count);
    }

    dds::sub::Rank rank() const
    {
        return dds::sub::Rank(
            native().sample_rank,
            native().generation_rank,
            native().absolute_generation_rank);
    }

    bool valid() const
    {
        return (native().valid_data != DDS_BOOLEAN_FALSE);
    }

    dds::core::InstanceHandle instance_handle() const
    {
        return dds::core::InstanceHandle(native().instance_handle);
    }

    dds::core::InstanceHandle publication_handle() const
    {
        return dds::core::InstanceHandle(native().publication_handle);
    }

    // --- Extensions: --------------------------------------------------------

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The timestamp when the sample was committed by a 
     * dds::sub::DataReader.
     */
    dds::core::Time reception_timestamp() const
    {
        return dds::core::Time(
            native().reception_timestamp.sec, native().reception_timestamp.nanosec);
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The publication sequence number.
     */
    rti::core::SequenceNumber publication_sequence_number() const
    {
        return rti::core::SequenceNumber(native().publication_sequence_number);
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The reception sequence number when sample was 
     * committed by a dds::sub::DataReader
     */
    rti::core::SequenceNumber reception_sequence_number() const
    {
        return rti::core::SequenceNumber(native().reception_sequence_number);
    }

    /*i 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension
     */
    rti::core::Guid publication_virtual_guid() const
    {
        return rti::core::Guid(native().publication_virtual_guid);
    }

    /*i 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension
     */
    rti::core::SequenceNumber publication_virtual_sequence_number() const
    {
        return rti::core::SequenceNumber(
           native().publication_virtual_sequence_number);
    }

    /*i
     * @memberof dds::sub::SampleInfo 
     * @brief @extension Retrieves the information provided by publication_virtual_guid()
     * and publication_virtual_sequence_number() combined in a SampleIdentity instance
     */
    rti::core::SampleIdentity publication_virtual_sample_identity() const
    {
        return rti::core::SampleIdentity(
            publication_virtual_guid(), publication_virtual_sequence_number());
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The original publication virtual GUID. 
     *  
     * @details @dref_details_SampleInfo_original_publication_virtual_guid
     */
    rti::core::Guid original_publication_virtual_guid() const
    {
        return rti::core::Guid(native().original_publication_virtual_guid);
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The original publication virtual sequence number. 
     *  
     * @details @dref_details_SampleInfo_original_publication_virtual_sequence_number
     */
    rti::core::SequenceNumber original_publication_virtual_sequence_number() const
    {
        return rti::core::SequenceNumber(
           native().original_publication_virtual_sequence_number);
    }

    /**
     * @memberof dds::sub::SampleInfo 
     * @brief @extension Retrieves the information provided by 
     * original_publication_virtual_guid()
     * and original_publication_virtual_sequence_number()
     * combined in a SampleIdentity instance
     */
    rti::core::SampleIdentity original_publication_virtual_sample_identity() const
    {
        return rti::core::SampleIdentity(
            original_publication_virtual_guid(),
            original_publication_virtual_sequence_number());
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The original publication virtual GUID of a 
     * related sample
     */
    rti::core::Guid related_original_publication_virtual_guid() const
    {
        return rti::core::Guid(
           native().related_original_publication_virtual_guid);
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The original publication virtual sequence number of a 
     * related sample
     */
    rti::core::SequenceNumber related_original_publication_virtual_sequence_number() const
    {
        return rti::core::SequenceNumber(
           native().related_original_publication_virtual_sequence_number);
    }

    /**
     * @memberof dds::sub::SampleInfo 
     * @brief @extension Retrieves the information provided by
     * related_original_publication_virtual_guid()
     * and related_original_publication_virtual_sequence_number()
     * combined in a SampleIdentity instance
     */
    rti::core::SampleIdentity related_original_publication_virtual_sample_identity() const
    {
        return rti::core::SampleIdentity(
            related_original_publication_virtual_guid(),
            related_original_publication_virtual_sequence_number());
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension Flags associated with the sample. 
     *  
     * @details @dref_details_SampleInfo_flag
     */
    rti::core::SampleFlag flag() const
    {
        return rti::core::SampleFlag(native().flag);
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The application logical data source associated 
     * with the sample. 
     *  
     * @details @dref_details_SampleInfo_source_guid
     */
    rti::core::Guid source_guid() const
    {
        return rti::core::Guid(native().source_guid);
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The application logical data source that is 
     * related to the sample.
     *  
     * @details @dref_details_SampleInfo_source_guid
     */
    rti::core::Guid related_source_guid() const
    {
        return rti::core::Guid(native().related_source_guid);
    }

    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The related_reader_guid associated with 
     * the sample. 
     *  
     * @details @dref_details_SampleInfo_related_subscription_guid
     */
    rti::core::Guid related_subscription_guid() const
    {
        return rti::core::Guid(native().related_subscription_guid);
    }
    
    /** 
     * @memberof dds::sub::SampleInfo 
     * @brief @extension The GUID of the \idref_TopicQuery that is
     * related to the sample.
     *  
     * @details @dref_details_SampleInfo_topic_query_guid
     */
    rti::core::Guid topic_query_guid() const
    {
        return rti::core::Guid(native().topic_query_guid);
    }

    /**
     * @brief Compare two dds::sub::SampleInfo objects for equality
     */
    bool operator==(const SampleInfoImpl& other) const
    {
        return 
            (this->state() == other.state() &&
            this->source_timestamp() == other.source_timestamp() &&
            this->instance_handle() == other.instance_handle() &&
            this->publication_handle() == other.publication_handle() &&
            this->generation_count().disposed() == other.generation_count().disposed() &&
            this->generation_count().no_writers() == other.generation_count().no_writers() &&
            this->rank().sample() == other.rank().sample() &&
            this->rank().generation() == other.rank().generation() &&
            this->rank().absolute_generation() == other.rank().absolute_generation() &&
            this->valid() == other.valid() &&
            this->reception_timestamp() == other.reception_timestamp() &&
            this->publication_sequence_number() == other.publication_sequence_number() &&
            this->reception_sequence_number() == other.reception_sequence_number() &&
            this->publication_virtual_guid() == other.publication_virtual_guid() &&
            this->publication_virtual_sequence_number() == other.publication_virtual_sequence_number() &&
            this->original_publication_virtual_guid() == other.original_publication_virtual_guid() &&
            this->original_publication_virtual_sequence_number() == other.original_publication_virtual_sequence_number() &&
            this->related_original_publication_virtual_guid() == other.related_original_publication_virtual_guid() &&
            this->related_original_publication_virtual_sequence_number() == other.related_original_publication_virtual_sequence_number() &&
            this->flag() == other.flag() &&
            this->source_guid() == other.source_guid() &&
            this->related_source_guid() == other.related_source_guid() &&
            this->related_subscription_guid() == other.related_subscription_guid() &&
            this->topic_query_guid() == other.topic_query_guid());
    }
};

} } // namespace rti::sub

#endif // RTI_DDS_SUB_SAMPLE_INFO_IMPL_HPP_
