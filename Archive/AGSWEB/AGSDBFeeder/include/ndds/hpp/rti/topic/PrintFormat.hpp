/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
5.20,08aug14,ajm CODEGENII-303 Adding impl_type trait
5.20,16jun14,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_PRINTFORMAT_HPP_
#define RTI_DDS_TOPIC_PRINTFORMAT_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <ostream>

#include "dds_c/dds_c_printformat.h"

#include <rti/core/NativeValueType.hpp>

namespace rti { namespace topic {

class PrintFormatProperty;

typedef rti::core::PODNativeAdapter<DDS_PrintFormatProperty>
    PrintFormatPropertyAdapter;

} } // namespace rti::topic

namespace rti { namespace core {

template<>
struct native_type_traits<rti::topic::PrintFormatProperty> {
    typedef rti::topic::PrintFormatPropertyAdapter adapter_type;
    typedef rti::topic::PrintFormatPropertyAdapter::native_type native_type;
};

} } // namespace rti::core

namespace rti { namespace topic {

/**
 * @ingroup DDSTopicTraitsModule
 * @brief The definition of the dds::core::safe_enum PrintFormatKind
 */
struct PrintFormatKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * @brief Use a default format specific to \ndds to represent the data
         * when converting a data sample to a string.
         */
        DEFAULT = DDS_DEFAULT_PRINT_FORMAT,
        /**
         * @brief Use an XML format to represent the data when converting a
         * data sample to a string.
         */
        XML = DDS_XML_PRINT_FORMAT,
        /**
         * @brief Use an JSON format to represent the data when converting a
         * data sample to a string.
         */
        JSON = DDS_JSON_PRINT_FORMAT
    };
};

/**
 * @ingroup DDSTopicTraitsModule
 * @brief @ref SafeEnumModule of @ref PrintFormatKind_def 
 * Format kinds available when converting data samples to string 
 * representations. 
 * @see @ref PrintFormatKind_def
 */
typedef dds::core::safe_enum<PrintFormatKind_def> PrintFormatKind;


/**
 * @ingroup DDSTopicTraitsModule 
 * @headerfile rti/topic/PrintFormat.hpp
 * @RTI_class_definition class PrintFormatProperty 
 *  
 * @brief @extension @st_value_type A collection of attributes used to 
 * configure how data samples will be formatted when converted 
 * to a string. 
 *  
 * \dref_details_PrintFormatProperty 
 *  
 * @see rti::topic::to_string 
 */
class OMG_DDS_API PrintFormatProperty
    : public rti::core::NativeValueType<PrintFormatProperty> {

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(PrintFormatProperty)

public:

    /**
     * @brief Initializes the properties
     */
    PrintFormatProperty(
        PrintFormatKind the_kind = PrintFormatKind::DEFAULT,
        bool is_pretty_print = true,
        bool is_enum_as_int = false,
        bool is_include_root_elements = true)
    {
        kind(the_kind);
        pretty_print(is_pretty_print);
        enum_as_int(is_enum_as_int);
        include_root_elements(is_include_root_elements);
    }

    /**
     * @brief Get the value of kind. 
     * @see kind(PrintFormatKind value)
     */
    PrintFormatKind kind() const
    {
        return (PrintFormatKind::type) native().kind;
    }

    /**
     * @brief Set the value for kind, indicating the kind of format
     * to be used when converting a data sample to a string.
     *  
     * \dref_details_PrintFormatProperty_kind
     * 
     * @param value The value to set for kind
     */
    PrintFormatProperty& kind(PrintFormatKind value)
    {
        native().kind =
               (DDS_PrintFormatKind) value.underlying();
        return *this;
    }

    /**
     * @brief Get the value of pretty_print. 
     * @see pretty_print(bool value)
     */
    bool pretty_print() const
    {
        return native().pretty_print == DDS_BOOLEAN_TRUE;
    }

    /**
     * @brief Set the value for pretty_print, indicating if the 
     * string representation of the data sample should be a more
     * readable format or should be void of all white space. 
     *  
     * \dref_details_PrintFormatProperty_pretty_print 
     * 
     * @param value The value to set for pretty_print
     */
    PrintFormatProperty& pretty_print(bool value)
    {
        native().pretty_print = value ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;
        return *this;
    }

    /**
     * @brief Get the value of enum_as_int. 
     * @see enum_as_int(bool value)
     */
    bool enum_as_int() const
    {
        return native().enum_as_int == DDS_BOOLEAN_TRUE;
    }

    /**
     * @brief Set the value for enum_as_int, indicating whether to format enum  
     * values as integers or as strings when converting data samples to strings.
     *  
     * \dref_details_PrintFormatProperty_enum_as_int
     * 
     * @param value The value to set for enum_as_int
     */
    PrintFormatProperty& enum_as_int(bool value)
    {
        native().enum_as_int = value ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;
        return *this;
    }

    /**
     * @brief Get the value of include_root_elements. 
     * @see include_root_elements(bool value)
     */
    bool include_root_elements() const
    {
        return native().include_root_elements == DDS_BOOLEAN_TRUE;
    }

    /**
     * @brief Set the value for include_root_elements, indicating 
     * whether to include the root elements of the print format in the output
     * string when converting data samples to strings. 
     *  
     * \dref_details_PrintFormatProperty_include_root_elements
     * 
     * @param value The value to set for include_root_elements
     */
    PrintFormatProperty& include_root_elements(bool value)
    {
        native().include_root_elements =
                value ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;
        return *this;
    }

    /**
     * @brief Creates a property with PrintFormatKind::DEFAULT
     */
    static PrintFormatProperty Default()
    {
        return PrintFormatProperty();
    }

    /**
     * @brief Creates a property with PrintFormatKind::XML
     */
    static PrintFormatProperty Xml()
    {
        return PrintFormatProperty(PrintFormatKind::XML);
    }

    /**
     * @brief Creates a property with PrintFormatKind::JSON
     */
    static PrintFormatProperty Json()
    {
        return PrintFormatProperty(PrintFormatKind::JSON);
    }
};

} } // namespace rti::topic

#endif // RTI_DDS_TOPIC_PRINTFORMAT_HPP_
