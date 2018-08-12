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
#ifndef OMG_DDS_SUB_TSAMPLE_INFO_HPP_
#define OMG_DDS_SUB_TSAMPLE_INFO_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Time.hpp>
#include <dds/core/Value.hpp>
#include <dds/sub/GenerationCount.hpp>
#include <dds/sub/Rank.hpp>
#include <dds/sub/status/DataState.hpp>
#include <dds/core/InstanceHandle.hpp>

namespace dds { 
  namespace sub {
    template <typename DELEGATE>
    class TSampleInfo;
  }
}

/** 
 * @ingroup DDSSampleInfoModule
 * @RTI_class_definition class dds::sub::SampleInfo
 * @headerfile "dds/sub/SampleInfo.hpp"
 * @brief @st_value_type Information that accompanies each sample received by a DataReader
 * @details @dref_SampleInfo
 */
template<typename DELEGATE>
class dds::sub::TSampleInfo : public dds::core::Value<DELEGATE> {
public:
    // Required for containers
    TSampleInfo() : dds::core::Value<DELEGATE>()
    {
    }

    // Spec issue: method name was wrong
    /**
     * @brief Get the timestamp when the sample was written by a DataWriter.
     */
    dds::core::Time source_timestamp() const
    {
        return this->delegate().source_timestamp();
    }

    /**
     * @brief Get the dds::sub::status::DataState of the sample. 
     *  
     * The DataState encapsulates the sample's dds::sub::status::InstanceState, 
     * dds::sub::status::ViewState, and dds::sub::status::SampleState
     *  
     */
    dds::sub::status::DataState state() const
    {
        return this->delegate().state();
    }

    /**
     * @brief Get the dds::sub::GenerationCount of the sample.
     */
    dds::sub::GenerationCount generation_count() const
    {
        return this->delegate().generation_count();
    }

    /**
     * @brief Get the dds::sub::Rank of the sample.
     */
    dds::sub::Rank rank() const
    {
        return this->delegate().rank();
    }

    /**
     * @brief Indicates whether the DataSample contains data or else it is 
     * only used to communicate a change in the dds::sub::status::InstanceState 
     * of the instance. 
     *  
     * @details @dref_details_SampleInfo_valid_data
     */
    bool valid() const
    {
        return this->delegate().valid();
    }

    /**
     * @brief Identifies locally the corresponding instance.
     */
    dds::core::InstanceHandle instance_handle() const
    {
        return this->delegate().instance_handle();
    }

    /**
     * @brief Identifies locally the DataWriter that modified the instance. 
     *  
     * @details @dref_details_SampleInfo_publication_handle
     */
    dds::core::InstanceHandle publication_handle() const
    {
        return this->delegate().publication_handle();
    }
};

//
// Pretty Print Utility
//
// #if (OMG_DDS_HAS_PRETTY_PRINT_COUT == 1)
template<typename DELEGATE>
std::ostream& operator << (std::ostream& os, const dds::sub::TSampleInfo<DELEGATE>& si);

// #endif 

#endif /* OMG_DDS_SUB_TSAMPLE_INFO_HPP_ */
