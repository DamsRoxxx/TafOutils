/* $Id: SharedSamplesImpl.hpp,v 1.4 2015/02/23 22:43:59 erin Exp $

(c) Copyright, Real-Time Innovations, 2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,27mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_STATUS_DATA_STATE_EX_HPP_
#define RTI_DDS_SUB_STATUS_DATA_STATE_EX_HPP_


// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>
#include <rti/core/Guid.hpp>
#include "dds_c/dds_c_subscription_impl.h"

namespace rti { namespace sub { namespace status {

/**
 * @ingroup DDSDataStateModule
 * @headerfile rti/sub/status/DataStateEx.hpp
 * @brief @extension Indicates which stream to read from: live stream,
 * topic-query stream or both
 *
 * @see \ref DDSTopicQueryModule
 */
class StreamKind : public std::bitset<OMG_DDS_STATE_BIT_COUNT > {
public:
    /**
     * @brief An std::bitset of StreamKinds
     */
    typedef std::bitset<OMG_DDS_STATE_BIT_COUNT > MaskType;

    StreamKind()
    {
    }

    /* Must do this cast to (uint64_t here because of a bug with the VS
       Implementation of bitset */
    explicit StreamKind(uint32_t mask) : MaskType((uint64_t)mask)
    {
    }

    /**
     * @brief Create an StreamKind from MaskType
     *
     * @param other The MaskType to create the StreamKind with
     */
    StreamKind(const MaskType& other) : MaskType(other)
    {
    }

    /**
     * @brief Returns the StreamKind that selects the live stream
     *
     */
    static StreamKind live()
    {
        return StreamKind(DDS_LIVE_STREAM);
    }

    /**
     * @brief Returns the StreamKind that selects the topic-query stream
     *
     */
    static StreamKind topic_query()
    {
        return StreamKind(DDS_TOPIC_QUERY_STREAM);
    }

    /**
     * @brief Returns the StreamKind that selects either stream
     */
    static StreamKind any()
    {
        return StreamKind(DDS_ANY_STREAM);
    }
};


/**
 * @ingroup DDSDataStateModule
 * @brief @extension @st_value_type An extended version of dds::sub::status::DataState
 * that also contains StreamKind
 *
 * DataStateEx is an extension of DataState that allows setting an additional
 * state mask: the StreamKind. It is used by
 * rti::sub::cond::create_read_condition_ex and
 * rti::sub::cond::create_query_condition_ex to create conditions that can
 * filter based on the StreamKind.
 *
 * A DataStateEx contains the state masks InstanceState, ViewState and SampleState
 * (with the same getters and setters: instance_state(), view_state() and sample_state()).
 *
 * In addition it contains the mask StreamKind with its getter and setter: stream_kind().
 *
 */
class OMG_DDS_API DataStateEx
    : private dds::sub::status::DataState {
    // Inheritance is private because a DataStateEx is not interchangeable with
    // a DataState (functions expecting a DataState won't handle a DataStateEx),
    // but a DataStateEx does provide the functionality of DataState (included
    // in DataStateEx via using statements).
public:
    
    typedef dds::sub::status::DataState Base;

    /**
     * @brief Create a DataStateEx with InstanceState::any(), ViewState::any(),
     * SampleState::any(), and StreamKind::any().
     */
    DataStateEx() : stream_kind_(StreamKind::any())
    {
    }

    /**
     * @brief Create a DataStateEx with InstanceState::any(), ViewState::any(),
     * SampleState::any() and the provided StreamKind.
     *
     * Note that the constructor is implicit, so you can use a StreamKind
     * wherever a DataStateEx is expected.
     */
    /* implicit */ DataStateEx(const StreamKind& the_stream_kind)
        : stream_kind_(the_stream_kind)
    {
    }

    /**
     * @brief Create a DataStateEx with the provided SampleState, ViewState,
     * InstanceState, and StreamKind::any()
     *
     * The constructor is implicit, so DataState can automatically be converted
     * to a DataStateEx with StreamKind::any().
     *
     * @param the_data_state Contains the SampleState, ViewState and InstanceState
     */
    /* implicit */ DataStateEx(const dds::sub::status::DataState& the_data_state)
        : Base(the_data_state), stream_kind_(StreamKind::any())
    {
    }

    /**
     * @brief Create a DataStateEx with the provided SampleState, ViewState,
     * InstanceState, and StreamKind
     *
     * @param the_data_state Contains the SampleState, ViewState and InstanceState
     * @param the_stream_kind Contains the StreamKind
     */
    DataStateEx(
        const dds::sub::status::DataState& the_data_state,
        const StreamKind& the_stream_kind)
        : Base(the_data_state), stream_kind_(the_stream_kind)
    {
    }


    // Make sure client code using DataState's operators << and >> works as
    // expected (setting the sample, view or instance state). Without this,
    // the compiler may attempt to incorrectly convert to StreamKind from e.g.
    // SampleState
    using Base::operator <<;
    using Base::operator >>;

    /**
     * @brief Access the SampleState
     */
    using Base::sample_state;

    /**
     * @brief Access the ViewState
     */
    using Base::view_state;

    /**
     * @brief Access the InstanceState
     */
    using Base::instance_state;

    using Base::any;
    using Base::new_data;
    using Base::any_data;
    using Base::new_instance;

    /**
     * @brief Set the StreamKind
     */
    DataStateEx& operator <<(const StreamKind& the_stream_kind)
    {
        stream_kind_ = the_stream_kind;
        return *this;
    }

    /**
     * @brief Get the StreamKind
     */
    const DataStateEx& operator >>(StreamKind& the_stream_kind) const
    {
        the_stream_kind = stream_kind_;
        return *this;
    }

    /**
     * @brief Get the StreamKind
     */
    const StreamKind& stream_kind() const
    {
        return stream_kind_;
    }

    /**
     * @brief Set the StreamKind
     */
    void stream_kind(const StreamKind& the_stream_kind)
    {
        *this << the_stream_kind;
    }

    /**
     * @brief Access the view, sample and instance states
     */
    const DataState& data_state() const
    {
        return static_cast<const DataState&>(*this);
    }

    /**
     * @brief Swap the contents of two DataState objects
     */
    friend inline void swap(DataStateEx& left, DataStateEx& right) OMG_NOEXCEPT
    {
        // Call the swap overload for DataState
        swap(static_cast<DataState&>(left), static_cast<DataState&>(right));
        // Swap the extended fields
        swap(left.stream_kind_, right.stream_kind_);
    }

    /**
     * @brief Compare two DataStateEx objects for equality
     */
    bool operator ==(const DataStateEx& other) const
    {
        return data_state() == other.data_state()
            && stream_kind() == other.stream_kind();
    }


    /**
     * @brief Compare two DataStateEx objects for inequality
     */
    bool operator !=(const DataStateEx& other) const
    {
        return !(*this == other);
    }

private:
    StreamKind stream_kind_;
};

} } } // namespace rti::sub::status

#endif // RTI_DDS_SUB_STATUS_DATA_STATE_EX_HPP_
