#ifndef OMG_DDS_SUB_TCOND_READ_CONDITION_HPP_
#define OMG_DDS_SUB_TCOND_READ_CONDITION_HPP_


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

namespace dds { namespace sub { namespace cond {

/**
 * @ingroup DDSReadConditionModule
 * @RTI_class_definition class ReadCondition : public dds::core::cond::Condition
 * @headerfile dds/sub/cond/ReadCondition.hpp
 *
 * @brief @st_ref_type Condition specifically dedicated to read operations and
 * attached to one dds::sub::DataReader.
 *
 * @details \dref_details_ReadCondition
 */
template <typename DELEGATE>
class TReadCondition : public dds::core::cond::TCondition<DELEGATE> {
public:
    OMG_DDS_REF_TYPE(TReadCondition, dds::core::cond::TCondition, DELEGATE)

  /**
   * @brief Creates a ReadCondition
   *
   * @tparam T The topic-type of the DataReader.
   *
   * @param reader The reader associated to the condition. One reader can have
   * multiple ReadConditions but one ReadCondition belongs to exactly one DataReader.
   * @param status The sample, view and instance states of interest.
   *
   * @see rti::sub::cond::create_read_condition_ex
   */
  template <typename T>
  TReadCondition(
      const dds::sub::DataReader<T>& reader,
      const dds::sub::status::DataState& status)
          : dds::core::cond::TCondition<DELEGATE>(new DELEGATE(reader, status))
  {
      this->delegate()->remember_reference(this->delegate());
  }

  /**
   * @brief Creates a ReadCondition with a handler
   *
   * @tparam T The topic-type of the DataReader.
   * @tparam Functor Any type whose instances can be called with a
   * no-argument function call (i.e. \p f(), if \p f is an instance of \p Functor),
   * or with a Condition argument (\p f(condition))
   * Examples are functions, types that override \p operator(), and lambdas.
   *
   * @param reader The reader associated to the condition. One reader can have
   * multiple ReadConditions but one ReadCondition belongs to exactly one DataReader.
   * @param status The sample, view and instance states of interest.
   * @param handler The handler that dds::core::cond::WaitSet::dispatch() will call when the
   * condition is triggered.
   *
   * The following examples creates two ReadConditions with handlers. The first
   * one receives a lambda function with no arguments. The second one
   * receives a function with the condition as an argument.
   *
   * \code
   * // Example 1: lambda function with no arguments
   * dds::sub::cond::ReadCondition my_read_condition(
   *        reader,
   *        dds::sub::status::DataState::any(),
   *        []()
   *        {
   *            std::cout << "condition has been triggered\n";
   *        }
   * );
   *
   * // Example 2: function with a condition argument
   * void function_handler(dds::core::cond::Condition c)
   * {
   *     // function receiving the condition
   *     std::cout << "condition has been triggered\n";
   * }
   *
   * dds::sub::cond::ReadCondition my_read_condition2(
   *        reader,
   *        dds::sub::status::DataState::any(),
   *        function_handler
   * );
   * \endcode
   *
   * @see dds::core::cond::WaitSet::dispatch()
   * @see \ref DDSWaitsetExampleModule_trigger "WaitSet wait and dispatch examples"
   */
  template <typename T, typename Functor>
  TReadCondition(
      const dds::sub::DataReader<T>& reader,
      const dds::sub::status::DataState& status, 
      const Functor& handler)
          : dds::core::cond::TCondition<DELEGATE>(new DELEGATE(reader, status, handler))
  {
      this->delegate()->remember_reference(this->delegate());
  }

  ~TReadCondition()
  {
  }

public:
  /**
   * @brief Returns the DataState of this condition.
   */
  const dds::sub::status::DataState state_filter() const
  {
      return this->delegate()->state_filter();
  }

  /**
   * @brief Returns the DataReader associated to this condition
   *
   * To obtain the actual typed DataReader, see AnyDataReader::get()
   */
  const AnyDataReader& data_reader() const
  {
      return this->delegate()->data_reader();
  }

  /**
   * @brief Closes the ReadCondition
   *
   * This is a explicit deletion, which otherwise would occur when all
   * references to this ReadCondition go out of scope.
   *
   * @pre The ReadCondition must not be attached to any Waitsets.
   *
   * @throw dds::core::PreconditionNotMetError If the ReadCondition is attached
   * to a Waitset when it is closed.
   */
  void close()
  {
      this->delegate()->close();
  }

  /**
   * @brief Indicates whether this ReadCondition has been closed with close().
   */
  bool closed() const
  {
      return this->delegate()->closed();
  }
};

} } } // namespace dds::sub::status

#endif /* OMG_DDS_SUB_TCOND_READ_CONDITION_HPP_ */


