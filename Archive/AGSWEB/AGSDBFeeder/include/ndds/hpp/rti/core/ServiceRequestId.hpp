/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_SERVICEREQUESTID_HPP_
#define RTI_DDS_CORE_SERVICEREQUESTID_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/SafeEnumeration.hpp>

namespace rti { namespace core {

/** 
 * @ingroup DDSServiceRequestBuiltInTopicModule 
 * @headerfile rti/core/ServiceRequestId.hpp
 * @brief The definition of the rti::core::safe_enum ServiceRequestId
 *
 * Use ServiceRequestId.
 */
struct ServiceRequestId_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * @brief An unknown service.
         */
        UNKNOWN = PRES_SERVICE_REQUEST_ID_UNKNOWN,
        /**
         * @brief The topic query service.
         */
        TOPIC_QUERY = PRES_SERVICE_REQUEST_ID_TOPIC_QUERY,
        /**  
         * @brief The locator reachability service.
         */
        LOCATOR_REACHABILITY = PRES_SERVICE_REQUEST_ID_LOCATOR_REACHABILITY
    }; 
};

/**
 * @ingroup DDSServiceRequestBuiltInTopicModule
 * @headerfile rti/core/ServiceRequestId.hpp
 * @brief @ref SafeEnumModule of @ref ServiceRequestId_def 
 * @see @ref ServiceRequestId_def 
 */
typedef dds::core::safe_enum<ServiceRequestId_def> ServiceRequestId;

} }

#endif // RTI_DDS_CORE_SERVICEREQUESTID_HPP_
