#ifndef OMG_TDDS_DDS_CORE_COND_CONDITION_HPP_
#define OMG_TDDS_DDS_CORE_COND_CONDITION_HPP_

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

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Reference.hpp>


/**
 * @defgroup DDSConditionsModule Conditions and WaitSets
 * @ingroup DDSInfrastructureModule
 *
 * @brief dds::core::cond::Condition and dds::core::cond::WaitSet.
 */

namespace dds {
  namespace core {
    namespace cond {
      template <typename DELEGATE>
      class TCondition;
    }
  }
}

/**
 * @ingroup DDSConditionsModule
 * @RTI_class_definition class dds::core::cond::Condition
 * @headerfile dds/core/cond/Condition.hpp
 *
 * @brief @st_ref_type Abstract base class of all the conditions
 *
 * @details \dref_details_Condition
 *
 * @see \ref DDSWaitsetExampleModule
 */
template <typename DELEGATE>
class dds::core::cond::TCondition : public dds::core::Reference<DELEGATE> {
public:
  OMG_DDS_REF_TYPE(TCondition, dds::core::Reference, DELEGATE)

public:

    TCondition(
        const typename ::dds::core::smart_ptr_traits<DELEGATE>::ref_type& delegate_ref) :
        dds::core::Reference<DELEGATE>(delegate_ref)
    {
        this->delegate()->remember_reference(this->delegate());
    }

    ~TCondition()
    {
    }

    /**
     * @brief Dispatches the functors that have been registered with the condition.
     *
     * If trigger_value() is true, calling dispatch() will call the registered
     * functor handlers.
     *
     * Note: it is more common to use WaitSet::dispatch() rather than this
     * function.
     */
    void dispatch()
    {
        this->delegate()->dispatch();
    }

    /**
     * @brief This operation retrieves the trigger_value of the Condition.
     */
    bool trigger_value() const
    {
        return this->delegate()->trigger_value();
    }

};

#endif /* OMG_TDDS_DDS_CORE_CONDITION_HPP_ */
