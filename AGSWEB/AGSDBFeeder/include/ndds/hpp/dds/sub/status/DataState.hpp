#ifndef OMG_DDS_SUB_DATA_STATE_HPP_
#define OMG_DDS_SUB_DATA_STATE_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <bitset>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
// Spec issue CPPPSM-184: without the inclusion of this header
// the spec is assuming that DataState is completely self-contained
#include <dds/sub/detail/DataState.hpp>

namespace dds { namespace sub { namespace status {

/** 
 * @ingroup DDSDataStateModule
 * @headerfile dds/sub/status/DataState.hpp 
 * @brief Indicates whether or not a sample has ever been read.
 */
class SampleState : public std::bitset<OMG_DDS_STATE_BIT_COUNT > {
public:
    /**
     * @brief An std::bitset of SampleStates
     */
    typedef std::bitset<OMG_DDS_STATE_BIT_COUNT > MaskType;

    SampleState()
    {
    }

    /* Must do this cast to (uint64_t here because of a bug with the VS
       implemenetation of bitset */
    explicit SampleState(uint32_t mask) : MaskType((uint64_t)mask)
    {
    }

    /**
     * @brief Create an SampleState from MaskType
     * 
     * @param other The MaskType to create the SampleState with
     */
    SampleState(const MaskType& other) : MaskType(other)
    {
    }

    /**
     * @brief Creates a read SampleState
     * 
     * A read SampleState indicates that the dds::sub::DataReader has already 
     * accessed that sample by means of a read or take operation.
     */
    static const SampleState read()
    {
        return SampleState(DDS_READ_SAMPLE_STATE);
    }

    /**
     * @brief Creates a not_read SampleState object 
     *  
     * A not_read SampleState indicates that the dds::sub::DataReader has not 
     * accessed that sample before. 
     * 
     */
    static const SampleState not_read()
    {
        return SampleState(DDS_NOT_READ_SAMPLE_STATE);
    }

    /**
     * @brief Creates a SampleState object representing any sample state
     */
    static const SampleState any()
    {
        return SampleState(DDS_ANY_SAMPLE_STATE);
    }
};

/** 
 * @ingroup DDSDataStateModule
 * @headerfile dds/sub/status/DataState.hpp 
 * @brief Indicates whether or not an instance is new. 
 *  
 * \dref_details_ViewStateKind 
 */
class ViewState: public std::bitset<OMG_DDS_STATE_BIT_COUNT > {
public:
    /**
     * @brief An std::bitset of ViewStates
     */
    typedef std::bitset<OMG_DDS_STATE_BIT_COUNT > MaskType;

    ViewState()
    {
    }

    explicit ViewState(uint32_t mask) : MaskType((uint64_t)mask)
    {
    }

    /**
     * @brief Create an ViewState from MaskType
     * 
     * @param other The MaskType to create the ViewState with
     */
    ViewState(const MaskType& other) : MaskType(other)
    {
    }

    /**
     * @brief Creates a new_view ViewState object. 
     *  
     * The latest generation of the instance has not previously been accessed.
     */
    static const ViewState new_view()
    {
        return ViewState(DDS_NEW_VIEW_STATE);
    }

    /**
     * @brief Creates a not_new_view ViewState object. 
     *  
     * The latest generation of the instance has previously been accessed.
     */
    static const ViewState not_new_view()
    {
        return ViewState(DDS_NOT_NEW_VIEW_STATE);
    }

    /**
     * @brief Creates an any ViewState object. 
     *  
     * new_view() | not_new_view() 
     */
    static const ViewState any()
    {
        return ViewState(DDS_ANY_VIEW_STATE);
    }
};

/** 
 * @ingroup DDSDataStateModule
 * @headerfile dds/sub/status/DataState.hpp 
 * @brief Indicates if the samples are from a live dds::pub::DataWriter or not. 
 *  
 * \dref_details_InstanceStateKind
 */
class InstanceState: public std::bitset<OMG_DDS_STATE_BIT_COUNT > {
public:
    /**
     * @brief An std::bitset of InstanceStates
     */
    typedef std::bitset<OMG_DDS_STATE_BIT_COUNT > MaskType;

    InstanceState()
    {
    }

    explicit InstanceState(uint32_t mask) : MaskType((uint64_t)mask)
    {
    }

    /**
     * @brief Create an InstanceState from MaskType
     * 
     * @param other The MaskType to create the InstanceState with
     */
    InstanceState(const MaskType& other) : MaskType(other)
    {
    }

    /**
     * @brief Creates an alive InstanceState object. 
     *  
     * The instance is currently in existence. 
     *  
     */
    static const InstanceState alive()
    {
        return InstanceState(DDS_ALIVE_INSTANCE_STATE);
    }

    /**
     * @brief Creates a not_alive_disposed InstanceState object 
     *  
     * The instance has been disposed by a DataWriter.
     * 
     */
    static const InstanceState not_alive_disposed()
    {
        return InstanceState(DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE);
    }

    /**
     * @brief Creates a not_alive_no_writers InstanceState object 
     *   
     * None of the DataWriters that are currently alive (according to the 
     * dds::core::policy::Liveliness policy) are writing the instance.
     */
    static const InstanceState not_alive_no_writers()
    {
        return InstanceState(DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE);
    }

    /**
     * @brief Creates an InstanceState object representing any not alive 
     * states (not_alive_disposed() | not_alive_no_writers())
     * 
     */
    static const InstanceState not_alive_mask()
    {
        return InstanceState(DDS_NOT_ALIVE_INSTANCE_STATE);
    }

    /**
     * @brief Creates an InstanceState object representing any instance states
     * (not_alive_disposed() | not_alive_no_writers() | alive())
     */
    static const InstanceState any()
    {
        return InstanceState(DDS_ANY_INSTANCE_STATE);
    }
};

/** 
 * @ingroup DDSDataStateModule 
 * @headerfile dds/sub/status/DataState.hpp 
 * @brief The DataState class describes the state of a sample and includes the 
 * information about the sample's InstanceState, ViewState, and SampleState
 */
class DataState {
public:
    /**
     * @brief Create a DataState with InstanceState::any(), ViewState::any(), 
     * and SampleState::any()
     */
    DataState()
        : sample_state_(SampleState::any()),
          view_state_(ViewState::any()),
          instance_state_(InstanceState::any())
    {
    }

    /**
     * @brief Create a DataState with InstanceState::any(), ViewState::any(), 
     * and the provided SampleState
     *
     * Note that the constructor is implicit, so you can use a SampleState
     * wherever a DataState is expected.
     */
    /* implicit */ DataState(const SampleState& the_sample_state)
        : sample_state_(the_sample_state),
          view_state_(ViewState::any()),
          instance_state_(InstanceState::any())
    {
    }

    /**
     * @brief Create a DataState with InstanceState::any(), SampleState::any(), 
     * and the provided ViewState
     *
     * Note that the constructor is implicit, so you can use a ViewState
     * wherever a DataState is expected.
     */
    /* implicit */ DataState(const ViewState& the_view_state)
        : sample_state_(SampleState::any()),
          view_state_(the_view_state),
          instance_state_(InstanceState::any())
    {
    }

    /**
     * @brief Create a DataState with SampleState::any(), ViewState::any(), 
     * and the provided InstanceState
     *
     * Note that the constructor is implicit, so you can use a InstanceState
     * wherever a DataState is expected.
     */
    /* implicit */ DataState(const InstanceState& the_instance_state)
        : sample_state_(SampleState::any()),
          view_state_(ViewState::any()),
          instance_state_(the_instance_state)
    {
    }

    /**
     * @brief Create a DataState with the provided SampleState, ViewState, 
     * and InstanceState
     */
    DataState(
        const SampleState& the_sample_state,
        const ViewState& the_view_state,
        const InstanceState& the_instance_state) :
        sample_state_(the_sample_state), view_state_(the_view_state),
            instance_state_(the_instance_state)
    {
    }

    /**
     * @brief Compare two DataState objects for equality
     */
    bool operator ==(const DataState& other) const
    {
        return sample_state() == other.sample_state()
            && view_state() == other.view_state()
            && instance_state() == other.instance_state();
    }

    /**
     * @brief Compare two DataState objects for inequality
     */
    bool operator !=(const DataState& other) const
    {
        return !this->operator==(other);
    }

    /**
     * @brief Set the provided SampleState in a DataState object
     */
    DataState& operator <<(const SampleState& the_sample_state)
    {
        sample_state_ = the_sample_state;
        return *this;
    }

    /**
     * @brief Set the provided InstanceState in a DataState object
     */
    DataState& operator <<(
        const InstanceState& the_instance_state)
    {
        instance_state_ = the_instance_state;
        return *this;
    }

    /**
     * @brief Set the provided ViewState in a DataState object
     */
    DataState& operator <<(const ViewState& the_view_state)
    {
        view_state_ = the_view_state;
        return *this;
    }

    /**
     * @brief Get the SampleState from a DataState object
     */
    const DataState& operator >>(
        SampleState& the_sample_state) const
    {
        the_sample_state = sample_state_;
        return *this;
    }

    /**
     * @brief Get the InstanceState from a DataState object
     */
    const DataState& operator >>(
        InstanceState& the_instance_state) const
    {
        the_instance_state = instance_state_;
        return *this;
    }

    /**
     * @brief Get the ViewState from a DataState object
     */
    const DataState& operator >>(ViewState& the_view_state) const
    {
        the_view_state = view_state_;
        return *this;
    }

    /**
     * @brief Get the SampleState from a DataState object
     */
    const SampleState& sample_state() const
    {
        return sample_state_;
    }

    /**
     * @brief Set the provided SampleState in a DataState object
     */
    void sample_state(const SampleState& the_sample_state)
    {
        *this << the_sample_state;
    }

    /**
     * @brief Get the InstanceState from a DataState object
     */
    const InstanceState& instance_state() const
    {
        return instance_state_;
    }

    /**
     * @brief Set the provided InstanceState in a DataState object
     */
    void instance_state(const InstanceState& the_instance_state)
    {
        *this << the_instance_state;
    }

    /**
     * @brief Get the ViewState from a DataState object
     */
    const ViewState& view_state() const
    {
        return view_state_;
    }

    /**
     * @brief Set the provided ViewState in a DataState object
     */
    void view_state(const ViewState& the_view_state)
    {
        *this << the_view_state;
    }

    /**
     * @brief Create a DataState with InstanceState::any(), ViewState::any(), 
     * and SampleState::any()
     */
    static DataState any()
    {
        return DataState(
            SampleState::any(),
            ViewState::any(),
            InstanceState::any());
    }

    /**
     * @brief Create a DataState with InstanceState::alive(), ViewState::any(), 
     * and SampleState::not_read()
     */
    static DataState new_data()
    {
        return DataState(
            SampleState::not_read(),
            ViewState::any(),
            InstanceState::alive());
    }

    /**
     * @brief Create a DataState with InstanceState::alive(), ViewState::any(), 
     * and SampleState::any()
     */
    static DataState any_data()
    {
        return DataState(
            SampleState::any(),
            ViewState::any(),
            InstanceState::alive());
    }

    /**
     * @brief Create a DataState with InstanceState::alive(), 
     * ViewState::new_view(), and SampleState::any()
     */
    static DataState new_instance()
    {
        return DataState(
            SampleState::any(),
            ViewState::new_view(),
            InstanceState::alive());
    }

    /**
     * @brief Swap the contents of two DataState objects
     */
    friend inline void swap(DataState& left, DataState& right) OMG_NOEXCEPT
    {
        swap(left.sample_state_, right.sample_state_);
        swap(left.view_state_, right.view_state_);
        swap(left.instance_state_, right.instance_state_);
    }

private:
    SampleState sample_state_;
    ViewState view_state_;
    InstanceState instance_state_;

};

} } } // namespace dds::sub::status

//
// Pretty Print Utility
//
// #if (OMG_DDS_HAS_PRETTY_PRINT_COUT == 1)
// std::ostream& operator << (std::ostream& os, const dds::sub::status::DataState& s);

// #endif 

#endif /* OMG_DDS_SUB_DATA_STATE_HPP_ */
