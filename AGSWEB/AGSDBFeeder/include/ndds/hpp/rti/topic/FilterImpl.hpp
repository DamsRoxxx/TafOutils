/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,20feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_FILTER_IMPL_HPP_
#define RTI_DDS_TOPIC_FILTER_IMPL_HPP_

#include <string>
#include <iterator>     // std::back_inserter

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/topic/topicfwd.hpp>

namespace dds { namespace topic { 

typedef detail::Filter Filter;

} } // namespace dds::topic

namespace rti { namespace topic {

/**
 * @RTI_class_definition NA
 */
class FilterImpl {
public:

    typedef dds::core::StringSeq ParameterContainer;
    typedef ParameterContainer::iterator iterator;
    typedef ParameterContainer::const_iterator const_iterator;

    typedef dds::topic::Filter WrapperType;
public:
    FilterImpl(const std::string& query_expression)
        : expression_(query_expression)
    {
    }

    template<typename FwdIterator>
    FilterImpl(
        const std::string& query_expression,
        const FwdIterator& params_begin,
        const FwdIterator& params_end)
        : expression_(query_expression),
          parameters_(params_begin, params_end)
    {
    }

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    FilterImpl(FilterImpl&& other) OMG_NOEXCEPT
        : expression_(std::move(other.expression_)),
          parameters_(std::move(other.parameters_)),
          name_(std::move(other.name_))
    {
    }
  #endif

    const std::string& expression() const
    {
        return expression_;
    }

    const_iterator begin() const
    {
        return parameters_.begin();
    }

    const_iterator end() const
    {
        return parameters_.end();
    }

    iterator begin()
    {
        return parameters_.begin();
    }

    iterator end()
    {
        return parameters_.end();
    }

    template<typename FwdITerator>
    void parameters(const FwdITerator& the_begin, const FwdITerator the_end)
    {
        parameters_.clear();
        std::copy(the_begin, the_end, std::back_inserter(parameters_));
    }

    void add_parameter(const std::string& param)
    {
        parameters_.push_back(param);
    }

    size_t parameters_length() const
    {
        return parameters_.size();
    }

    bool operator==(const FilterImpl& other) const
    {
        return expression_ == other.expression_
            && parameters_ == other.parameters_;
    }

    // Extension
    const ParameterContainer& parameters() const
    {
        return parameters_;
    }

    /**
     * @memberof dds::topic::Filter
     * @brief @extension Gets the filter name
     *
     * @return The name of the filter, or an empty string when using the
     * default SQL filter.
     */
    std::string name() const
    {
        return name_;
    }

    /**
     * @memberof dds::topic::Filter
     * @brief @extension Sets a filter name
     *
     * You can use one of the built-in filters: rti::topic::SQLFILTER_NAME and
     * rti::topic::STRINGMATCHFILTER_NAME. Or a custom filter,
     * which you need to register using
     * dds::domain::DomainParticipant::register_contentfilter().
     *
     * @default Empty string (equivalent to rti::topic::SQLFILTER_NAME)
     */
    dds::topic::Filter& name(const std::string& the_name)
    {
        name_ = the_name;
        return rti::core::native_conversions::cast_from_delegate(*this);
    }

    friend inline void swap(FilterImpl& left, FilterImpl& right) OMG_NOEXCEPT
    {
        swap(left.expression_, right.expression_);
        swap(left.parameters_, right.parameters_);
        swap(left.name_, right.name_);
    }

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    FilterImpl& operator=(FilterImpl&& other) OMG_NOEXCEPT
    {
        FilterImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

private:
    std::string expression_;
    ParameterContainer parameters_;
    // If name_ != "", then a custom filter is being used
    std::string name_;
/** @RTI_remove_lines 1 */
};

} }

#endif // RTI_DDS_TOPIC_FILTER_IMPL_HPP_
