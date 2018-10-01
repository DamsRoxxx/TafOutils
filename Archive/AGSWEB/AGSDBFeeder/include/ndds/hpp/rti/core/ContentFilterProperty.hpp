/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_CONTENT_FILTER_PROPERTY_HPP_
#define RTI_DDS_CORE_CONTENT_FILTER_PROPERTY_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/detail/NativeConversion.hpp>
#include <dds/core/String.hpp>
#include <rti/core/OptionalValue.hpp>

namespace rti { namespace core {

class ContentFilterPropertyAdapter {
public:
    typedef struct DDS_ContentFilterProperty_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_ContentFilterProperty_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_ContentFilterProperty_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_ContentFilterProperty_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_ContentFilterProperty_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

class ContentFilterProperty;

template <>
struct native_type_traits<ContentFilterProperty> {
    typedef rti::core::ContentFilterPropertyAdapter adapter_type;
    typedef DDS_ContentFilterProperty_t native_type;
};

/**
 * @ingroup DDSBuiltInTopicCommonModule
 * @RTI_class_definition class ContentFilterProperty
 * @brief @extension @st_value_type Provides all the required information to
 * enable content filtering.
 *
 */
class ContentFilterProperty : public NativeValueType<ContentFilterProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ContentFilterProperty)

    typedef NativeValueType<ContentFilterProperty> Base;
    typedef rti::core::optional_value<std::string> optional_string;
public:
    
    ContentFilterProperty()
    {
    }

    ContentFilterProperty(const struct DDS_ContentFilterProperty_t& native_filter) 
      : Base(native_filter)
    {
    }

    /**
     * @brief Name of the ContentFilteredTopic associated with the DataReader
     */
    optional_string content_filter_topic_name() const
    {
        if (native().content_filter_topic_name == NULL) {
            return optional_string();
        }

        return optional_string(native().content_filter_topic_name);
    }

    /**
     * @brief The ContentFilteredTopic filter parameters
     */
    dds::core::StringSeq expression_parameters() const
    {
        return rti::core::native_conversions::from_native<
            std::string, DDS_StringSeq>(native().expression_parameters);
    }

    /**
     * @brief Identifies the filter class this filter belongs to.
     */
    optional_string filter_class_name() const 
    {
        if (native().filter_class_name == NULL) {
            return optional_string();
        }

        return optional_string(native().filter_class_name);
    }

    /**
     * @brief The filter expression
     */
    optional_string filter_expression() const
    {
        if (native().filter_expression == NULL) {
            return optional_string();
        }

        return optional_string(native().filter_expression);
    }

    /**
     * @brief The name of the ContentFilteredTopic's related Topic
     */
    optional_string related_topic_name() const
    {
        if (native().related_topic_name == NULL) {
            return optional_string();
        }

        return optional_string(native().related_topic_name);
    }
};

} }

#endif // RTI_DDS_CORE_CONTENT_FILTER_PROPERTY_HPP_
