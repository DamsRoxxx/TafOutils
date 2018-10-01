#ifndef DDS_TOPIC_TFILTER__HPP_
#define DDS_TOPIC_TFILTER__HPP_

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

namespace dds {
  namespace topic {
    template<typename DELEGATE>
    class TFilter;
  }
}

/**
 * @ingroup DDSTopicEntityModule
 * @RTI_class_definition class dds::topic::Filter
 * @headerfile dds/topic/Filter.hpp
 *
 * @brief Defines the filter to create a ContentFilteredTopic
 *
 * Contains the filter expression and optionally the expression parameters. It
 * also contains the filter name, which allows selecting the filter class to
 * use--by default it's the built-in SQL filter.
 */
template<typename DELEGATE>
class dds::topic::TFilter : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TFilter, DELEGATE)

    // Random access iterators
    typedef typename DELEGATE::iterator iterator;
    typedef typename DELEGATE::const_iterator const_iterator;

public:
    /**
     * @brief Creates a filter with a expression with no parameters
     *
     * @see \ref DDSQueryAndFilterSyntaxModule
     */
    TFilter(const std::string& filter_expression)
        : dds::core::Value<DELEGATE>(filter_expression)
    {
    }

    /**
     * @brief Creates a filter with an expression that contains parameters
     *
     * @tparam FwdIterator A forwar iterator whose value type is std::string
     * (or convertible to)
     *
     * @param filter_expression The filter expression
     * @param params_begin The beginning of the range of expression parameters
     * @param params_end The end of the range (the number of parameter
     * to create a ContentFilteredTopic can't exceed 100)
     *
     * @see \ref DDSQueryAndFilterSyntaxModule
     */
    template<typename FwdIterator>
    TFilter(
        const std::string& filter_expression,
        const FwdIterator& params_begin,
        const FwdIterator& params_end)
        : dds::core::Value<DELEGATE>(filter_expression, params_begin, params_end)
    {
    }

    /**
     * @brief Creates a filter with an expression that contains parameters
     *
     *
     * @param query_expression The query expression
     * @param params The expression parameters (the number of parameter
     * to create a ContentFilteredTopic can't exceed 100)
     *
     * @see \ref DDSQueryAndFilterSyntaxModule
     */
    TFilter(
        const std::string& query_expression,
        const std::vector<std::string>& params)
        : dds::core::Value<DELEGATE>(
            query_expression, params.begin(), params.end())
    {
    }

    /**
     * @brief Gets the filter expression
     */
    const std::string& expression() const
    {
        return this->delegate().expression();
    }

    /**
     * @brief Provides the begin iterator to the parameter list.
     */
    const_iterator begin() const
    {
        return this->delegate().begin();
    }

    /**
     * @brief The end iterator to the parameter list.
     */
    const_iterator end() const
    {
        return this->delegate().end();
    }

    /**
     * @brief Provides the begin iterator to the parameter list.
     */
    iterator begin()
    {
        return this->delegate().begin();
    }

    /**
     * @brief The end iterator to the parameter list.
     */
    iterator end()
    {
        return this->delegate().end();
    }

    /**
     * @brief Modifies the parameters
     */
    template<typename FwdITerator>
    TFilter& parameters(const FwdITerator& the_begin, const FwdITerator the_end)
    {
        this->delegate().parameters(the_begin, the_end);
        return *this;
    }

    /**
     * @brief Appends a parameter
     */
    TFilter& add_parameter(const std::string& param)
    {
        this->delegate().add_parameter(param);
        return *this;
    }

    /**
     * @brief Gets the number of parameters
     */
    size_t parameters_length() const
    {
        return this->delegate().parameters_length();
    }
};

#endif /* DDS_TOPIC_TFILTER__HPP_ */
