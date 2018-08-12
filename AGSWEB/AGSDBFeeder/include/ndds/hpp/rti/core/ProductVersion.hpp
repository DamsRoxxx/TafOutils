/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_PRODUCT_VERSION_HPP_
#define RTI_DDS_CORE_PRODUCT_VERSION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure_impl.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

class ProductVersionAdapter {
public:
    typedef struct DDS_ProductVersion_t native_type;

    static void initialize(native_type& native_value)
    {
        static const native_type DEFAULT = DDS_PRODUCTVERSION_UNKNOWN;
        native_value = DEFAULT;
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_ProductVersion_copyI(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_ProductVersion_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

class ProductVersion;

template <>
struct native_type_traits<ProductVersion> {
    typedef rti::core::ProductVersionAdapter adapter_type;
    typedef DDS_ProductVersion_t native_type;
};

/** 
 * @ingroup DDSBuiltInTopicCommonModule
 * @RTI_class_definition class ProductVersion 
 * @headerfile rti/core/ProductVersion.hpp
 *  
 * @brief @extension @st_value_type Represents the current version of \ndds
 */
class OMG_DDS_API ProductVersion : public NativeValueType<ProductVersion> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ProductVersion)

    typedef NativeValueType<ProductVersion> Base;
    /**
     * @brief Creates the unknown() product version
     */
    ProductVersion()
    {
    }

    ProductVersion(const struct DDS_ProductVersion_t& native_product_version) 
      : Base(native_product_version)
    {
    }

    /**
     * @brief Get the product version as a string
     */
    std::string to_string() const
    {
        char dst[DDS_PRODUCTVERSION_MAX_STRING_SIZE];

        if (!DDS_ProductVersion_to_string(
                const_cast<DDS_ProductVersion_t *>(&native()), dst)) {
            throw dds::core::Error("Failed to convert ProductVersion to string");
        }

        return dst;
    }

    /**
     * @brief Get the major product version
     */
    uint8_t major_version() const
    {
        return native().major;
    }

    /**
     * @brief Get the minor product version
     */
    uint8_t minor_version() const
    {
        return native().minor;
    }

    /**
     * @brief Get the release letter for product version
     */
    uint8_t release_version() const
    {
        return native().release;
    }

    /**
     * @brief Get the revision number of product
     */
    uint8_t revision_version() const
    {
        return native().revision;
    }

    /**
     * @brief Returns the current version of \ndds
     */
    static ProductVersion current()
    {
        struct DDS_ProductVersion_t current_version;
        DDS_ProductVersion_get_rtidds_version(&current_version);
        return current_version;
    }

    /**
     * @brief Returns the value to indicate that the version is unknown
     */
    static ProductVersion unknown()
    {
        return ProductVersion();
    }

};

} }

#endif // RTI_DDS_CORE_PRODUCT_VERSION_HPP_
