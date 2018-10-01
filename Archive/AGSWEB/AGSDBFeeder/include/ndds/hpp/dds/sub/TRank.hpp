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
#ifndef OMG_DDS_SUB_TRANK_HPP_
#define OMG_DDS_SUB_TRANK_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Value.hpp>

namespace dds  { namespace sub {
  template <typename DELEGATE>
  class TRank;
} }

/** 
 * @ingroup DDSSampleInfoModule 
 * @RTI_class_definition class dds::sub::Rank
 * @brief @st_value_type
 */
template<typename DELEGATE>
class dds::sub::TRank : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TRank, DELEGATE)

    /**
     * @brief Create a default Rank object
     */
    TRank() : dds::core::Value<DELEGATE>()
    {
    }

    /**
     * @brief Create a Rank object with the provided 
     * sample_rank, generation_rank, and absolute_generation_rank
     */
    TRank(
        int32_t sample_rank,
        int32_t generation_rank,
        int32_t absolute_generation_rank)
        : dds::core::Value<DELEGATE>(
            sample_rank,
            generation_rank,
            absolute_generation_rank)
    {
    }

    /**
     * @brief Get the sample rank of the sample 
     *  
     * @dref_SampleInfo_sample_rank
     */
    int32_t sample() const
    {
        return this->delegate().sample();
    }

    /**
     * @brief Get the generation rank of the sample. 
     *  
     * @dref_SampleInfo_generation_rank
     */
    int32_t generation() const
    {
        return this->delegate().generation();
    }

    /**
     * @brief Get the absolute generation rank of the sample. 
     *  
     * @dref_SampleInfo_absolute_generation_rank
     */
    int32_t absolute_generation() const
    {
            return this->delegate().absolute_generation();
    }
};


//
// Pretty Print Utility
//
// #if (OMG_DDS_HAS_PRETTY_PRINT_COUT == 1)
template<typename DELEGATE>
std::ostream& operator << (std::ostream& os, const dds::sub::TRank<DELEGATE>& r);

// #endif 

#endif /* OMG_DDS_SUB_TRANK_HPP_ */
