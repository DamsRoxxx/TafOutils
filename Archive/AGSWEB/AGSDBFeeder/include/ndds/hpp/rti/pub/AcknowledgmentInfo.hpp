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

#ifndef RTI_DDS_PUB_ACKNOWLEDGMENTINFO_HPP_
#define RTI_DDS_PUB_ACKNOWLEDGMENTINFO_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"
#include "dds_c/dds_c_publication_impl.h"

#include <dds/core/InstanceHandle.hpp>
#include <rti/core/SampleIdentity.hpp>
#include <rti/core/Cookie.hpp>
#include <rti/core/Exception.hpp>
#include <rti/sub/AckResponseData.hpp>

namespace rti { namespace pub {

class AcknowledgmentInfo;

class AcknowledgmentInfoAdapter {
public:
    typedef DDS_AcknowledgmentInfo native_type;

    static void initialize(native_type& native_value)
    {
        DDS_AcknowledgmentInfo_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_AcknowledgmentInfo_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        if (DDS_AcknowledgmentInfo_copy(&destination, &source) == NULL) {
            throw std::bad_alloc();
        }
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_AcknowledgmentInfo_equals(&first, &second) == DDS_BOOLEAN_TRUE;
    } 
};

} // namespace pub

namespace core {

template<>
struct native_type_traits<rti::pub::AcknowledgmentInfo> {
    typedef rti::pub::AcknowledgmentInfoAdapter adapter_type;
    typedef rti::pub::AcknowledgmentInfoAdapter::native_type native_type;
};

} // namespace core

namespace pub {

/**
 * @RTI_class_definition class AcknowledgmentInfo
 * @ingroup DDSWriterModule
 * @brief @extension @st_value_type Information about an application-acknowledged sample
 *
 * @details \dref_details_AcknowledgmentInfo
 */
class OMG_DDS_API AcknowledgmentInfo
    : public rti::core::NativeValueType<AcknowledgmentInfo> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(AcknowledgmentInfo)

    AcknowledgmentInfo() {}

    // For internal use only
    AcknowledgmentInfo(const DDS_AcknowledgmentInfo& native_value);

    /**
     * @brief Gets the subscription handle of the acknowledging \idref_DataReader
     * @details \dref_details_AcknowledgmentInfo_subscription_handle
     */
    dds::core::InstanceHandle subscription_handle() const;

    /**
     * @brief Gets the identity of the sample being acknowledged
     * @details \dref_details_AcknowledgmentInfo_sample_identity
     */
    rti::core::SampleIdentity sample_identity() const;

    /*i
     * @brief Cookie of the acknowledged sample.
     * 
     * \dref_details_AcknowledgmentInfo_cookie
     */
    rti::core::Cookie cookie() const;

    /**
     * @brief Flag indicating validity of the user response data 
     * in the acknowledgment 
     *  
     * \dref_details_AcknowledgmentInfo_valid_response_data 
     */
    bool valid_response_data() const;

    /**
     * @brief User data payload of application-level acknowledgment message
     *  
     * \dref_details_AcknowledgmentInfo_response_data 
     */ 
    rti::sub::AckResponseData response_data() const;
};

} } // namespace rti::pub

#endif // RTI_DDS_PUB_ACKNOWLEDGMENTINFO_HPP_
