#ifndef OMG_DDS_SUB_QUERY_HPP_
#define OMG_DDS_SUB_QUERY_HPP_

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

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/sub/subfwd.hpp>
#include <dds/sub/detail/Query.hpp>

/*
 * NOTE: The Query class is specified as follows to limit the issues associated
 * with includes dependencies and to make it easier to forward declare in places
 * where the information about the delegate layer should not pop out.
 *
 */
namespace dds {
  namespace sub {
    class Query;
  }
}

/**
 * @ingroup DDSQueryConditionModule
 * @RTI_class_definition class dds::sub::Query
 * @headerfile dds/sub/Query.hpp
 *
 * @brief @st_value_type Encapsulates a query for a dds::sub::cond::QueryCondition.
 *
 * A query contains the DataReader to query data from, an expression and
 * optionally a list of parameters.
 *
 * \ref DDSQueryAndFilterSyntaxModule defines the syntax of the expression
 * and the parameters.
 *
 * @see \ref NDDSFilterExampleModule_query_conditions
 */
class dds::sub::Query : public dds::core::Value<detail::Query> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        dds::sub::Query, detail::Query)

  typedef detail::Query DELEGATE;
public:
  // Random access iterators
  typedef DELEGATE::iterator iterator;
  typedef DELEGATE::const_iterator const_iterator;

public:

  /**
   * @brief Creates a query
   *
   * @tparam T The topic-type of the DataReader
   *
   * @param reader DataReader to query data from
   * @param query_expression Expression describing the query
   */
  template<typename T>
  Query(const dds::sub::DataReader<T>& reader, const std::string& query_expression)
      : dds::core::Value<detail::Query> (reader, query_expression)
  {
  }

  /**
   * @brief Creates a query with the expression parameters in an iterator range
   *
   * @tparam T The topic-type of the DataReader
   * @tparam FWIterator A forward iterator whose value type is std::string
   * (or convertible to std::string)
   *
   * @param reader DataReader to query data from
   * @param query_expression Expression describing the query
   * @param params_begin The beginning of a range of parameters for the query expression
   * @param params_end The end of the range
   */
  template<typename T, typename FWIterator>
  Query(const dds::sub::DataReader<T>& reader, const std::string& query_expression,
      const FWIterator& params_begin, const FWIterator& params_end)
      : dds::core::Value<detail::Query> (reader, query_expression, params_begin, params_end)
  {
  }

  /**
   * @brief Creates a query with the expression parameters in a vector
   *
   * @tparam T The topic-type of the DataReader
   *
   * @param reader DataReader to query data from
   * @param query_expression Expression describing the query
   * @param params The parameters for the query expression
   */
  template<typename T>
  Query(
      const dds::sub::DataReader<T>& reader,
      const std::string& query_expression,
      const std::vector<std::string>& params)
      : dds::core::Value<detail::Query> (
          reader, query_expression, params.begin(), params.end())
  {
  }

  /**
   * @brief Gets the expression
   */
  const std::string& expression() const
  {
      return this->delegate().expression();
  }

// TODO:
//  void expression(const std::string& expr)
//  {
//      this->delegate().expression(expr);
//  }

  /**
   * @brief Provides the begin iterator to the parameter list.
   *
   * @return A random-access iterator whose value type is std::string
   */
  const_iterator begin() const
  {
      return this->delegate().begin();
  }

  /**
   * @brief Provides the end iterator to the parameter list.
   *
   * @return A random-access iterator whose value type is std::string
   */
  const_iterator end() const
  {
      return this->delegate().end();
  }

  /**
   * @brief Provides the begin iterator to the parameter list.
   *
   * @return A random-access iterator whose value type is std::string
   */
  iterator begin()
  {
      return this->delegate().begin();
  }

  /**
   * @brief Provides the end iterator to the parameter list.
   *
   * @return A random-access iterator whose value type is std::string
   */
  iterator end()
  {
      return this->delegate().end();
  }

  /**
   * @brief Sets the parameters for the expression
   *
   * @tparam FWIterator A forward iterator whose value type is std::string
   * (or convertible to std::string)
   *
   * @param the_begin The beginning of a range of parameters for the query expression
   * @param the_end The end of the range
   */
  template<typename FWIterator>
  void parameters(const FWIterator& the_begin, const FWIterator the_end)
  {
      this->delegate().parameters(the_begin, the_end);
  }

  /**
   * @brief Appends a parameter
   */
  void add_parameter(const std::string& param)
  {
      this->delegate().add_parameter(param);
  }

  /**
   * @brief Gets the number of parameters
   */
  size_t parameters_length() const
  {
      return this->delegate().parameters_length();
  }

#ifdef DOXYGEN_DOCUMENTATION_ONLY
  /**
   * @brief @extension Gets the parameters
   */
  // This extension method is defined in a base class of the delegate QueryImpl
  const std::vector<std::string>& parameters() const;
#endif

  /**
   * @brief Gets the related DataReader
   */
  const AnyDataReader& data_reader() const
  {
      return this->delegate().data_reader();
  }

};

#endif /* OMG_DDS_SUB_QUERY_HPP_ */
