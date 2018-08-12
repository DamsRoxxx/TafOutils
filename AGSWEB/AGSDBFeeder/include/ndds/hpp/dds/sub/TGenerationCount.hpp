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
#ifndef OMG_DDS_SUB_T_GENERATION_COUNT_HPP_
#define OMG_DDS_SUB_T_GENERATION_COUNT_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Value.hpp>

namespace dds { namespace sub {
  template <typename DELEGATE>
  class TGenerationCount;
} }

/**   
 * @ingroup DDSSampleInfoModule
 * @RTI_class_definition class dds::sub::GenerationCount
 * @brief @st_value_type
 */
template<typename DELEGATE>
class dds::sub::TGenerationCount : public dds::core::Value<DELEGATE> {
public:
    /**
     * @brief Create a default GenerationCount object
     */
    TGenerationCount() : dds::core::Value<DELEGATE>()
    {
    }

    /**
     * @brief Create a GenerationCount object with the provided disposed_count 
     * and no_writers count 
     */
    TGenerationCount(int32_t disposed_count, int32_t no_writers_count)
        : dds::core::Value<DELEGATE>(disposed_count, no_writers_count)
    {
    }

    /**
     * @brief Get the disposed generation count 
     *  
     * @dref_SampleInfo_disposed_generation_count 
     */
    int32_t disposed() const
    {
        return this->delegate().disposed();
    }

    /**
     * @brief Get the no_writers generation count 
     *  
     * @dref_SampleInfo_no_writers_generation_count 
     */
    int32_t no_writers() const
    {
        return this->delegate().no_writers();
    }
};

#endif /*  OMG_DDS_SUB_T_GENERATION_COUNT_HPP_ */
