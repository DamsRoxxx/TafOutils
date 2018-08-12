/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_LOCATOR_FILTER_HPP_
#define RTI_DDS_CORE_LOCATOR_FILTER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure_impl.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/vector.hpp>
#include <dds/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/detail/NativeConversion.hpp>
#include <rti/core/Locator.hpp>

namespace rti { namespace core {


class LocatorFilterImplAdapter {
public:
    typedef struct DDS_LocatorFilter_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_LocatorFilter_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_LocatorFilter_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_LocatorFilter_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return 
            (DDS_LocatorFilter_t_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

class LocatorFilterElement;

template <>
struct native_type_traits<LocatorFilterElement> {
    typedef rti::core::LocatorFilterImplAdapter adapter_type;
    typedef DDS_LocatorFilter_t native_type;
};


/** 
 * @ingroup DDSLocatorFilterQosModule
 * @RTI_class_definition class LocatorFilterElement
 * @brief @extension @st_value_type Specifies the configuration of an
 * individual channel within a MultiChannel DataWriter. 
 *  
 * @see dds::core::policy::LocatorFilter
 */
class LocatorFilterElement : public NativeValueType<LocatorFilterElement> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(LocatorFilterElement)

    typedef NativeValueType<LocatorFilterElement> Base;
public:

    LocatorFilterElement() {}

    /**
     * @brief Creates an instance with the provided filter_expression
     * and locators
     * 
     * @param the_filter_expression A logical expression used to determine the 
     * data that will be published in the channel.
     * @param the_locators Sequence containing from one to four 
     * rti::core::Locator
     */
    LocatorFilterElement(
        const std::string& the_filter_expression, 
        const rti::core::LocatorSeq& the_locators)
    {
        filter_expression(the_filter_expression);
        locators(the_locators);
    }

    LocatorFilterElement(const struct DDS_LocatorFilter_t& native_filter_locator) 
      : Base(native_filter_locator)
    {
    }

public:
    /**
      * @brief Get the locators associated with this filter.
      *
      * The locators are a sequence containing from one to four rti::core::Locator,
      * used to specify the multicast address locators of an individual channel 
      * within a MultiChannel DataWriter.
      */
    rti::core::LocatorSeq locators() const 
    {
        using namespace rti::core::native_conversions;
        return from_native<Locator, DDS_LocatorSeq>(native().locators);
    }

    /**
     * @brief Set the locators associated with this LocatorFilterImpl
     */
    LocatorFilterElement& locators(const LocatorSeq& the_locators)
    {
        using namespace rti::core::native_conversions;

        to_native<Locator, LocatorSeq, DDS_LocatorSeq>(
            the_locators, 
            native().locators, 
            rti::core::Locator(
                rti::core::LocatorKind::INVALID, 
                0, 
                dds::core::ByteSeq()));

        return *this;
    }

    /**
     * @brief Get the filter expression
     */
    std::string filter_expression() const 
    {
        return native().filter_expression;
    }

    /**
     * @brief Set the filter expression.
     *
     * The filter expression is a logical expression used to determine the
     * data that will be published in the channel.
     *
     * @dref_details_LocatorFilter_t_filter_expression
     */
    LocatorFilterElement& filter_expression(const std::string& the_expression)
    {
        if (!DDS_String_replace(
                &native().filter_expression, the_expression.c_str())) {
            throw std::bad_alloc();
        }
        return *this;
    }
};

} }

#endif // RTI_DDS_CORE_LOCATOR_FILTER_HPP_
