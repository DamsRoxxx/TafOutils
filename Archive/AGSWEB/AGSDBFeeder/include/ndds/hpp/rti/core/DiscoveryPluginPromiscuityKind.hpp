/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_RTI_CORE_DISCOVERY_PLUGIN_PROMISCUITY_KIND_HPP_
#define RTI_RTI_CORE_DISCOVERY_PLUGIN_PROMISCUITY_KIND_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

//#include "dds_c/dds_c_infrastructure.h"

//#include <dds/core/types.hpp>
//#include <dds/core/Value.hpp>

namespace rti { namespace core {

/** 
 * @ingroup DDSDiscoveryConfigQosModule 
 * @brief The definition of the dds::core::safe_enum DiscoveryPluginPromiscuityKind
 */
struct DiscoveryPluginPromiscuityKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * @brief Give the discovery plugin at least the matches and silently 
         * allow the discovery plug-in to give as much data as it wants.
         */
        DISCOVER_MATCHING_REMOTE_ENTITIES = 0x0001,
        /**
         * @brief Give the discovery plugin information about all 
         * remote entities.
         */
        DISCOVER_ALL_REMOTE_ENTITIES = 0xFFFF
    };
};

/**
 * @ingroup DDSDiscoveryConfigQosModule
 * @brief @ref SafeEnumModule of @ref DiscoveryPluginPromiscuityKind_def. 
 * Type used to indicate promiscuity mode of the discovery plugin. 
 *  
 * @see @ref DiscoveryPluginPromiscuityKind_def
 */
typedef dds::core::safe_enum<DiscoveryPluginPromiscuityKind_def> DiscoveryPluginPromiscuityKind;

} } // namespace rti::core

#endif // RTI_RTI_CORE_DISCOVERY_PLUGIN_PROMISCUITY_KIND_HPP_
