/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,14mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_PUB_WRITEPARAMS_HPP_
#define RTI_DDS_PUB_WRITEPARAMS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/Time.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <rti/core/SampleIdentity.hpp>
#include <rti/core/Cookie.hpp>
#include <rti/core/Guid.hpp>
#include <rti/core/SampleFlag.hpp>
#include <rti/core/Exception.hpp>

namespace rti { namespace pub {

class WriteParams;

class WriteParamsAdapter {
public:
    typedef DDS_WriteParams_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_WriteParams_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_WriteParams_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        if (DDS_WriteParams_t_copy(&destination, &source) == NULL) {
            rti::core::check_create_entity(NULL, "WriteParams copy");
        }
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_WriteParams_equals(&first, &second) == DDS_BOOLEAN_TRUE;
    }
};

} // namespace pub

namespace core {

template<>
struct native_type_traits<rti::pub::WriteParams> {
    typedef rti::pub::WriteParamsAdapter adapter_type;
    typedef rti::pub::WriteParamsAdapter::native_type native_type;
};

} // namespace core

namespace pub {

/**
 * @ingroup DDSWriterModule
 * @RTI_class_definition class WriteParams
 * @headerfile "rti/pub/WriteParams.hpp"
 *
 * @brief @extension @st_value_type Advanced parameters for writing with a DataWriter
 *
 * @details \dref_details_WriteParams
 *
 * @see dds::pub::DataWriter::write(const T&,rti::pub::WriteParams&)
 */
class OMG_DDS_API WriteParams : public rti::core::NativeValueType<WriteParams> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(WriteParams)

    typedef rti::core::NativeValueType<WriteParams> Base;

    /**
     * @brief Creates a WriteParams object with default values.
     *
     * The default instance is such that it makes
     * dds::pub::DataWriter(const T&, WriteParams&) behave identically to
     * dds::pub::DataWriter(const T&).
     */
    WriteParams() {}

    /**
     * @brief Resets all the fields to their default values
     *
     * @see replace_auto()
     */
    void reset();

    /**
     * @brief Indicates if the replacement of automatic values has been
     * activated or not
     */
    bool replace_automatic_values() const;

    /**
     * @brief Allows retrieving the actual value of those fields that were automatic
     *
     * @details \dref_details_WriteParams_replace_auto
     *
     * @param value Whether to replace automatic values or not
     *
     * @default false
     */
    WriteParams& replace_automatic_values(bool value);

    /**
     * @brief Gets the sample identity
     */
    rti::core::SampleIdentity identity() const;

    /**
     * @brief Sets a explicit sample identity for writing
     *
     * @details \dref_details_WriteParams_identity
     */
    WriteParams& identity(const rti::core::SampleIdentity& value);

    /**
     * @brief Gets the related sample identity
     */
    rti::core::SampleIdentity related_sample_identity() const;

    /**
     * @brief Sets a related sample identity for a sample
     *
     * @details \dref_details_WriteParams_related_sample_identity
     */
    WriteParams& related_sample_identity(const rti::core::SampleIdentity& value);

    /**
     * @brief Gets the timestamp
     */
    dds::core::Time source_timestamp() const;

    /**
     * @brief Sets the source timestamp for writing
     *
     * @details \dref_details_WriteParams_source_timestamp
     */
    WriteParams& source_timestamp(const dds::core::Time& value);

    /**
     * @brief Gets the cookie
     */
    rti::core::Cookie cookie() const;

    /**
     * @brief Sets a cookie for writing
     *
     * @details \dref_details_WriteParams_cookie
     */
    WriteParams& cookie(const rti::core::Cookie& value);

    /**
     * @brief Gets the instance handle
     *
     * @details \dref_details_WriteParams_handle
     */
    dds::core::InstanceHandle handle() const;

    /**
     * @brief Sets the instance handle for writing
     *
     * @details \dref_WriteParams_handle
     */
    WriteParams& handle(const dds::core::InstanceHandle& value);

    /**
     * @brief Gets the priority
     */
    int32_t priority() const;

    /**
     * @brief Sets the priority for writing
     *
     * @details \dref_details_WriteParams_priority
     */
    WriteParams& priority(int32_t value);

    /*i \dref_WriteParams_flush_on_write
     */
    bool flush_on_write() const;

    /*i \dref_WriteParams_flush_on_write
     */
    WriteParams& flush_on_write(bool value);

    /**
     * @brief Gets the sample flag
     */
    rti::core::SampleFlag flag() const;

    /**
     * @brief Sets the sample flags for writing
     *
     * @details \dref_details_WriteParams_flag
     */
    WriteParams& flag(const rti::core::SampleFlag& value);
    
    /**
     * @brief Gets the source GUID
     */
    rti::core::Guid source_guid() const;

    /**
     * @brief Sets the source GUID for writing
     *
     * @details \dref_details_WriteParams_source_guid
     */
    WriteParams& source_guid(const rti::core::Guid& value);

    /**
     * @brief Gets the related source guid
     */
    rti::core::Guid related_source_guid() const;

    /**
     * @brief Sets the related source guid for writing
     *
     * @details \dref_details_WriteParams_related_source_guid
     */
    WriteParams& related_source_guid(const rti::core::Guid& value);

    /**
     * @brief Gets the related reader GUID
     */
    rti::core::Guid related_reader_guid() const;

    /**
     * @brief Sets the related reader guid for writing
     *
     * @details \dref_details_WriteParams_related_reader_guid
     */
    WriteParams& related_reader_guid(const rti::core::Guid& value);
};

} } // namespace rti::pub

#endif // RTI_DDS_PUB_WRITEPARAMS_HPP_
