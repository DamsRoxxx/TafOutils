/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_VENDOR_ID_HPP_
#define RTI_DDS_CORE_VENDOR_ID_HPP_

#include <algorithm>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

class VendorIdAdapter {
public:
    typedef struct DDS_VendorId_t native_type;

    static void initialize(native_type& native_value)
    {
        static const native_type UNKNOWN = DDS_VENDORID_UNKNOWN;
        copy(native_value, UNKNOWN);
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        std::copy(
            source.vendorId,
            source.vendorId + DDS_VENDOR_ID_LENGTH_MAX,
            destination.vendorId);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return std::equal(
            first.vendorId,
            first.vendorId + DDS_VENDOR_ID_LENGTH_MAX,
            second.vendorId);
    }
};

class VendorId;

template <>
struct native_type_traits<VendorId> {
    typedef rti::core::VendorIdAdapter adapter_type;
    typedef DDS_VendorId_t native_type;
};

/**
 * @ingroup DDSBuiltInTopicCommonModule
 * @RTI_class_definition class VendorId
 * @headerfile rti/core/VendorId.hpp
 *
 * @brief @extension Represents the vendor of the service implementing the RTPS
 * protocol.
 */
class VendorId : public NativeValueType<VendorId> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(VendorId)

    typedef NativeValueType<VendorId> Base;
public:
    /**
     * @brief Creates the unknown() vendor id
     */
    VendorId()
    {
    }

    VendorId(const struct DDS_VendorId_t &native_vendor_id) 
      : Base(native_vendor_id)
    {
    }

    /**
     * @brief Provides access to the bytes that represent the vendor id
     */
    std::vector<uint8_t> value() const
    {
        return std::vector<uint8_t>(
            native().vendorId, native().vendorId + DDS_VENDOR_ID_LENGTH_MAX);
    }

    /**
     * @brief The ID that indicates that the vendor is unknown
     */
    static VendorId unknown()
    {
        return VendorId();
    }
};

} }

#endif // RTI_DDS_CORE_VENDOR_ID_HPP_
