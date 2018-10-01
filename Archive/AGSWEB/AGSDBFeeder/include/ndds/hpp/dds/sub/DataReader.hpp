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
#ifndef OMG_DDS_SUB_DATA_READER_HPP_
#define OMG_DDS_SUB_DATA_READER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/sub/TDataReader.hpp>
#include <dds/sub/detail/DataReader.hpp>
#include <dds/pub/pubfwd.hpp>
#include <dds/sub/cond/QueryCondition.hpp>

// Spec issue: had to refactor DataReader.hpp and move the forward
// declaration of dds::pub::DataReader (with default template argument) to
// subfwd.hpp in order to fix circular dependencies.

// Manipulators
namespace dds {
  namespace sub {
    namespace functors {
      typedef dds::sub::functors::detail::MaxSamplesManipulatorFunctor MaxSamplesManipulatorFunctor;
      typedef dds::sub::functors::detail::ContentFilterManipulatorFunctor ContentFilterManipulatorFunctor;
      typedef dds::sub::functors::detail::ConditionManipulatorFunctor ConditionManipulatorFunctor;
      typedef dds::sub::functors::detail::StateFilterManipulatorFunctor StateFilterManipulatorFunctor;
      typedef dds::sub::functors::detail::InstanceManipulatorFunctor InstanceManipulatorFunctor;
      typedef dds::sub::functors::detail::NextInstanceManipulatorFunctor NextInstanceManipulatorFunctor;
    }
  }
} // namespace dds::sub::functors

namespace dds { namespace sub {

 /** 
  * @relatesalso dds::sub::DataReader  
  * @headerfile dds/sub/DataReader.hpp 
  * @brief The stream manipulator to indicate that the reader should read samples 
  * as opposed to taking the samples 
  *  
   * Usage: 
   * @code 
   * reader >> read >> loaned_samples;
   * @endcode 
  *  
  * @see dds::sub::DataReader::operator >>(bool(*manipulator)(ReadModeDummyType))	
  */
  OMG_DDS_API
  bool read(dds::sub::ReadModeDummyType);

 /** 
  * @relatesalso dds::sub::DataReader  
  * @headerfile dds/sub/DataReader.hpp 
  * @brief The stream manipulator to indicate that the reader should take samples 
  * as opposed to reading the samples 
  *  
  * Usage: 
  * @code 
  * reader >> take >> loaned_samples;
  * @endcode 
  *  
  *  
  * The default mode to access samples is to take, so the above is equivalent 
  * to:
  * @code 
  * reader >> loaned_samples;
  * @endcode 
  *  
  * @see dds::sub::DataReader::operator >>(bool(*manipulator)(ReadModeDummyType))	
  */
  OMG_DDS_API
  bool take(dds::sub::ReadModeDummyType);

 /** 
  * @relatesalso dds::sub::DataReader 
  * @headerfile dds/sub/DataReader.hpp 
  * @brief Stream manipulator to set the maximum number of samples to read or 
  * take. 
  *  
  * Use this function to set the maximum number of samples to read/take by 
  * passing it to the DataReader::operator >>(Functor f) operator. 
  *  
  * @param n The maximum number of samples to take 
  *  
  * @see dds::sub::DataReader::operator >>(Functor f)  
  */
  inline dds::sub::functors::MaxSamplesManipulatorFunctor
  max_samples(uint32_t n)
  {
      return dds::sub::functors::MaxSamplesManipulatorFunctor(n);
  }

 /** 
  * @relatesalso dds::sub::DataReader  
  * @headerfile dds/sub/DataReader.hpp 
  * @brief Stream manipulator to set a Query to use during the subsequent 
  * read/take operation. 
  *  
  * The effect of using this manipulator is that the subsequent read/take 
  * will filter the samples based on the Query's expression. If the DataReader 
  * has no samples that meet the constraints, the read/take will not return 
  * any data. 
  *  
  * If this stream manipulator comes before a call to the 
  * condition(const dds::sub::cond::QueryCondition& query_condition) manipulator 
  * then it will be overridden and will not have any effect on the read or take 
  * operation. Similarly, if this operation follows a call to condition(), 
  * then the previously set QueryCondition will be cleared.   
  *  
  * @param query The Query to use during the read/take 
  *  
  * @see dds::sub::DataReader::operator >>(Functor f) 
  * @see dds::sub::condition(const dds::sub::cond::QueryCondition& query_condition) 
  */
  inline dds::sub::functors::ContentFilterManipulatorFunctor
  content(const dds::sub::Query& query)
  {
      return dds::sub::functors::ContentFilterManipulatorFunctor(query);
  }

 /** 
  * @relatesalso dds::sub::DataReader  
  * @headerfile dds/sub/DataReader.hpp 
  * @brief Stream manipulator to set a QueryCondition to use during the 
  * subsequent read/take operation 
  *  
  * The effect of using this manipulator is that the subsequent read/take 
  * will filter the samples based on the QueryConditions's expression and state. 
  * If the DataReader has no samples that meet the constraints, 
  * the read/take will not return any data. 
  *  
  * If this stream manipulator comes before a call to the 
  * content(const dds::sub::Query& query) manipulator 
  * then it will be overridden and will not have any effect on the read or take 
  * operation. Similarly, if this operation follows a call to content() and/or 
  * state(const dds::sub::status::DataState& s), 
  * then the previously set Query and DataState will be cleared. 
  *  
  * This manipulator is effectively a combination of the content and state 
  * manipulators. 
  *  
  * For example: 
  * @code
  * reader >> read
  *        >> content(dds::sub::Query(system.reader, "foo = 7"))
  *        >> state(dds::sub::status::DataState::new_data())
  *        >> samples;
  * @endcode
  *  
  * is equivalent to: 
  * @code
  * reader >> read
  *        >> condition(Query(system.reader, "foo = 7"), DataState()::new_data())
  *        >> samples;
  * @endcode
  *  
  * @param condition The QueryCondition to use during the read/take
  *  
  * @see dds::sub::DataReader::operator >>(Functor f) 
  * @see content(const dds::sub::Query& query)
  */
  inline dds::sub::functors::ConditionManipulatorFunctor
  condition(const dds::sub::cond::ReadCondition& condition)
  {
      return dds::sub::functors::ConditionManipulatorFunctor(condition);
  }

 /** 
  * @relatesalso dds::sub::DataReader  
  * @headerfile dds/sub/DataReader.hpp 
  * @brief Stream manipulator to specify the DataState of the samples that 
  * should be read/taken 
  *  
  * By setting the dds::sub::status::DataState you can specify the state of the 
  * samples that  should be read or taken. The DataState of a sample encapsulates 
  * the  dds::sub::status::SampleState, dds::sub::status::ViewState, and 
  * dds::sub::status::InstanceState of a sample. 
  *  
  * If this stream manipulator comes before a call to the 
  * condition(const dds::sub::cond::QueryCondition& query_condition) manipulator 
  * then it will be overridden and will not have any effect on the read or take 
  * operation. 
  *  
  * @param s The DataState of the samples to be read or taken 
  *  
  * @see dds::sub::DataReader::operator >>(Functor f)  
  */
  inline dds::sub::functors::StateFilterManipulatorFunctor
  state(const dds::sub::status::DataState& s)
  {
      return dds::sub::functors::StateFilterManipulatorFunctor(s);
  }

 /** 
  * @relatesalso dds::sub::DataReader  
  * @headerfile dds/sub/DataReader.hpp 
  * @brief Stream manipulator to specify the instance whose samples should be 
  * read or taken 
  *  
  * This operation causes the subsequent read or take operation to access only 
  * samples belonging the single specified instance whose handle is \p h. 
  *  
  * Upon successful completion, the data collection will contain
  * samples all belonging to the same instance. The corresponding SampleInfo 
  * verifies SampleInfo.instance_handle() == \p h. 
  *  
  * The subsequent read/take operation will be semantically equivalent to 
  * a read or take without specifying the instance, except in 
  * building the collection, the DataReader will check that the sample belongs 
  * to the specified instance and otherwise it will not place the sample in 
  * the returned collection. 
  *  
  * The subsequent read/take may operation may fail with
  * dds::core::InvalidArgumentError if the InstanceHandle does not correspond
  * to an existing data-object known to the DataReader. 
  *  
  * @param h The handle of the instance to access
  *  
  * @see dds::sub::DataReader::operator >>(Functor f)  
  */
  inline dds::sub::functors::InstanceManipulatorFunctor
  instance(const dds::core::InstanceHandle& h)
  {
      return dds::sub::functors::InstanceManipulatorFunctor(h);
  }

  /** 
   * @relatesalso dds::sub::DataReader  
   * @brief Stream manipulator to specify the samples belonging to the 'next' 
   * instance after the provided instance handle should be accessed.
   *  
   * \dref_details_FooDataReader_read_next_instance
   *  
   * @param h The reference instance. The instance after this one will 
   * be selected
   *  
   * @see dds::sub::DataReader::operator >>(Functor f)  
   */
  inline dds::sub::functors::NextInstanceManipulatorFunctor
  next_instance(const dds::core::InstanceHandle& h)
  {
      return dds::sub::functors::NextInstanceManipulatorFunctor(h);
  }

} } // namespace dds::sub


#endif /* OMG_DDS_SUB_DATA_READER_HPP_ */
