#ifndef OMG_TDDS_CORE_COND_GUARD_CONDITION_HPP_
#define OMG_TDDS_CORE_COND_GUARD_CONDITION_HPP_

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

#include <dds/core/cond/TCondition.hpp>

namespace dds {
  namespace core {
    namespace cond {
      template <typename DELEGATE>
      class TGuardCondition;
    }
  }
}

/**
 * @ingroup DDSConditionsModule
 * @RTI_class_definition class dds::core::cond::GuardCondition : public Condition
 * @headerfile dds/core/cond/GuardCondition.hpp
 *
 * @brief @st_ref_type A condition whose trigger value is under the control of
 * the application.
 *
 * @details \dref_details_GuardCondition.
 */
template <typename DELEGATE>
class dds::core::cond::TGuardCondition : public dds::core::cond::TCondition<DELEGATE> {
public:
    OMG_DDS_BASIC_REF_TYPE_NODC(TGuardCondition, TCondition, DELEGATE)

public:
  TGuardCondition() : TCondition<DELEGATE>(new DELEGATE())
  {
      this->delegate()->remember_reference(this->delegate());
  }

  ~TGuardCondition()
  {
  }

public:

  /**
   * @brief Registers a custom handler with this condition.
   *
   * For information about condition handlers, see
   * \link dds::sub::cond::ReadCondition::ReadCondition(const dds::sub::DataReader&,const dds::sub::status::DataState&,const Functor&)
   * this ReadCondition constructor\endlink
   *
   * @mtsafety It is not safe to call handler(), reset_handler() or
   * trigger_value() concurrently.
   */
  template <typename Functor>
  void handler(const Functor& func)
  {
      this->delegate()->handler(func);
  }

  /**
   * @brief Resets the handler for this condition.
   *
   * After the invocation of this method no handler will be registered with
   * this condition.
   *
   * @mtsafety It is not safe to call handler(), reset_handler() or
   * trigger_value() concurrently.
   *
   */
  void reset_handler()
  {
      this->delegate()->reset_handler();
  }

public:

  using TCondition<DELEGATE>::trigger_value; // getter overload in base class

  /**
   * @brief Manually sets the trigger value
   *
   * Setting the trigger value to true causes the activation of the condition
   * in a WaitSet.
   *
   * @see WaitSet::wait()
   * @see WaitSet::dispatch()
   */
  void trigger_value(bool value)
  {
      this->delegate()->trigger_value(value);
  }

};

#endif /* OMG_TDDS_CORE_GUARD_CONDITION_HPP_ */
