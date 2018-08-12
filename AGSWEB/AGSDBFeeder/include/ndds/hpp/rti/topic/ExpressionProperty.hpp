/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_EXPRESSION_PROPERTY_HPP_
#define RTI_DDS_CORE_EXPRESSION_PROPERTY_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_topic.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace topic {
    class ExpressionProperty;
} }

namespace rti { namespace core {

class ExpressionPropertyAdapter {
public:
    typedef struct DDS_ExpressionProperty native_type;

    static void initialize(native_type& native_value)
    {
        static const DDS_ExpressionProperty expression = 
            DDS_ExpressionProperty_DEFAULT;
        native_value = expression;    
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        destination = source;
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return ((first.key_only_filter == second.key_only_filter) &&
                (first.writer_side_filter_optimization == 
                second.writer_side_filter_optimization));
    }
};

template <>
struct native_type_traits<rti::topic::ExpressionProperty> {
    typedef rti::core::ExpressionPropertyAdapter adapter_type;
    typedef DDS_ExpressionProperty native_type;
};

} } // namespace rti::core

namespace rti { namespace topic {
/**
 * @ingroup DDSCustomContentFilterModule 
 * @headerfile rti/topic/ContentFilter.hpp
 * @RTI_class_definition class ExpressionProperty 
 *  
 * @brief @extension @st_value_type Provides additional information about the 
 * filter expression passed to the writer_compile method of 
 * rti::topic::WriterContentFilter 
 *  
 * \dref_details_ExpressionProperty 
 *  
 * @see rti::topic::WriterContentFilter 
 */
class ExpressionProperty : public rti::core::NativeValueType<ExpressionProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ExpressionProperty)

    typedef rti::core::NativeValueType<ExpressionProperty> Base;
public:
    // Default Ctor
    /**
     * @brief Create a default ExpressionProperty with key_only_filter = false 
     * and writer_side_filter_optimization = false 
     */
    ExpressionProperty() : Base() 
    {
    }

    ExpressionProperty(
       const struct DDS_ExpressionProperty &native_expression_property)
       : Base(native_expression_property)
    {
    }

    /**
     * @brief Create an ExpressionProperty with the provided key_only_filter,
     * and writer_side_filter_optimization
     * 
     * @param the_key_only_filter The value for key_only_filter
     * @param the_writer_side_filter_optimization The value for writer_side_filter_optimization
     */
    ExpressionProperty(
       bool the_key_only_filter, bool the_writer_side_filter_optimization)
    {
        key_only_filter(the_key_only_filter);
        writer_side_filter_optimization(the_writer_side_filter_optimization);
    }

    /**
     * @brief Get the value of key_only_filter. 
     * @see key_only_filter(bool the_key_only_filter)
     */
    bool key_only_filter() const
    {
        return (native().key_only_filter == DDS_BOOLEAN_TRUE);
    }

    /**
     * @brief Set the value for key_only_filter, indicating if the filter 
     * expression is based only on key fields. In this case, 
     * \ndds itself can cache the filtering results. 
     *  
     * \dref_details_ExpressionProperty_key_only_filter 
     * 
     * @param the_key_only_filter The value to set for key_only_filter
     */
    ExpressionProperty& key_only_filter(bool the_key_only_filter)
    {
        native().key_only_filter = the_key_only_filter;

        return *this;
    }

    /**
     * @brief Get the value of writer_side_filter_optimization. 
     * @see writer_side_filter_optimization(bool the_writer_side_filter_optimization)
     */
    bool writer_side_filter_optimization() const
    {
        return (native().writer_side_filter_optimization == DDS_BOOLEAN_TRUE);
    }

    /**
     * @brief Set the value for writer_side_filter_optimization, indicating if 
     * the filter implementation can cache the filtering result for the 
     * provided expression. 
     *  
     * \dref_details_ExpressionProperty_writer_side_filter_optimization
     * 
     * @param the_writer_side_filter_optimization The value to set for 
     * writer_side_filter_optimization 
     */
    ExpressionProperty& writer_side_filter_optimization(
       bool the_writer_side_filter_optimization)
    {
        native().writer_side_filter_optimization = 
            the_writer_side_filter_optimization;

        return *this;
    }
};

} } // namespace rti::topic

#endif // RTI_DDS_CORE_EXPRESSION_PROPERTY_HPP_
