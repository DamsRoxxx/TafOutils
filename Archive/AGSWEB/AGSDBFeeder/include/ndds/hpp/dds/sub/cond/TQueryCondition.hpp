#ifndef OMG_DDS_SUB_TQUERY_CONDITION_HPP_
#define OMG_DDS_SUB_TQUERY_CONDITION_HPP_

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

#include <dds/core/detail/conformance.hpp>
#include <dds/sub/cond/TReadCondition.hpp>

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

namespace dds { namespace sub { namespace cond {

/**
 * @ingroup DDSQueryConditionModule
 * @RTI_class_definition class QueryCondition : public dds::sub::cond::ReadCondition
 * @headerfile dds/sub/cond/QueryCondition.hpp
 *
 * @brief @st_ref_type Specialized ReadCondition that allows applications to also
 * specify a filter on the data available in a dds::sub::DataReader
 *
 * @details \dref_details_QueryCondition
 *
 * @see \ref NDDSFilterExampleModule_query_conditions
 */
template <typename DELEGATE>
class TQueryCondition : public dds::sub::cond::TReadCondition<DELEGATE> {
public:

  OMG_DDS_REF_TYPE(TQueryCondition, TReadCondition, DELEGATE)

  /**
   * @brief Parameter iterator. A random-access iterator of std::string.
   */
  typedef typename DELEGATE::iterator iterator;

  /**
   * @brief Parameter iterator. A random-access iterator of std::string.
   */
  typedef typename DELEGATE::const_iterator const_iterator;

  /**
   * @brief Creates a QueryCondition
   *
   * @param query The query
   * @param status The sample, view and instance states of interest.
   *
   * @see ReadCondition
   * @see rti::sub::cond::create_query_condition_ex
   */
  TQueryCondition(
      const dds::sub::Query& query,
      const dds::sub::status::DataState& status)
      : dds::sub::cond::TReadCondition<DELEGATE>(new DELEGATE(query, status))
  {
      this->delegate()->remember_reference(this->delegate());
  }

  /**
   * @brief Creates a QueryCondition with a handler
   *
   * This constructor is similar to
   * \link dds::sub::cond::ReadCondition::ReadCondition(const dds::sub::DataReader&,const dds::sub::status::DataState&,const Functor&)
   * this ReadCondition constructor\endlink.
   */
  template <typename Functor>
  TQueryCondition(
      const dds::sub::Query& query,
      const dds::sub::status::DataState& status,
      const Functor& functor)
      : dds::sub::cond::TReadCondition<DELEGATE>(
          new DELEGATE(query, status, functor))
  {
      this->delegate()->remember_reference(this->delegate());
  }

  ~TQueryCondition()
  {
  }


//
// TODO:
//  void expression(const std::string& expr)
//  {
//      this->delegate()->expression(expr);
//  }

  /**
   * @brief Gets the expression
   */
  std::string expression() const
  {
      return this->delegate()->expression();
  }

//
// Issue CPPPSM-174: Direct access to iterators not implemented.
//
// Instead, we implement a getter that returns a vector
// (same as ContentFilteredTopic)
//
//
//  /**
//   * Provides the begin iterator to the parameter list.
//   */
//  const_iterator begin() const
//  {
//      return this->delegate()->begin();
//  }
//
//  /**
//   * The end iterator to the parameter list.
//   */
//  const_iterator end() const
//  {
//      return this->delegate()->end();
//  }
//
//  /**
//   * Provides the begin iterator to the parameter list.
//   */
//  iterator begin()
//  {
//      return this->delegate()->begin();
//  }
//
//  /**
//   * The end iterator to the parameter list.
//   */
//  iterator end()
//  {
//      return this->delegate()->end();
//  }

  /**
   * @brief Gets the parameters
   */
  dds::core::StringSeq parameters() const
  {
      return this->delegate()->parameters();
  }

  /**
   * @brief Modifies the query parameters
   *
   * @tparam FWIterator A forward iterator whose value type is std::string
   * (or convertible to std::string).
   *
   * @param begin The beginning of the range of parameters
   * @param end The end of the range
   */
  template<typename FWIterator>
  void parameters(const FWIterator& begin, const FWIterator& end)
  {
      this->delegate()->parameters(begin, end);
  }

//
//  Spec issue CPPPSM-174: Parameters need to be set all at once
//
//  void add_parameter(const std::string& param)
//  {
//      this->delegate()->add_parameter(param);
//  }

  /**
   * @brief Gets the number of parameters
   */
  uint32_t parameters_length() const
  {
      return this->delegate()->parameters_length();
  }
};

#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

} } } // namespace dds::sub::cond

#endif /* OMG_DDS_SUB_TQUERY_CONDITION_HPP_ */
