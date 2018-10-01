/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_CONFIG_VERSION_HPP_
#define RTI_CONFIG_VERSION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "ndds/ndds_config_c.h"
#include "core_version/core_version_version.h"
#include <rti/config/buildid.hpp>
#include <dds/core/types.hpp>    
#include <rti/core/NativeValueType.hpp>
#include <rti/core/ProductVersion.hpp>

namespace rti { namespace config {

typedef rti::core::PODNativeAdapter<NDDS_Config_LibraryVersion_t> LibraryVersionAdapter;

class LibraryVersion;

} // namespace config

namespace core { 

template <>
struct native_type_traits<rti::config::LibraryVersion> {
    typedef rti::config::LibraryVersionAdapter adapter_type;
    typedef NDDS_Config_LibraryVersion_t native_type;
};

} // namespace core

namespace config { 

/** 
 * @ingroup NDDSConfigModule
 * @RTI_class_definition class LibraryVersion 
 * @headerfile rti/config/Version.hpp
 *  
 * @brief @extension @st_value_type The version of a single library shipped 
 * as part of an \ndds distribution. 
 *  
 * \dref_details_LibraryVersion_t 
 */
class OMG_DDS_API LibraryVersion : public rti::core::NativeValueType<LibraryVersion> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(LibraryVersion)

    typedef rti::core::NativeValueType<LibraryVersion> Base;

    LibraryVersion()
    {
    }

    LibraryVersion(int32_t major, int32_t minor, int32_t build, char release);

    LibraryVersion(const struct NDDS_Config_LibraryVersion_t& native_library_version) 
      : Base(native_library_version)
    {
    }

    /**
     * @brief Get the major version of a single \ndds library.
     */
    int32_t major_version() const;

    /**
     * @brief Get the minor version of a single \ndds library.
     */
    int32_t minor_version() const;

    /**
     * @brief Get the release letter of a single \ndds library.
     */
    char release_version() const;

    /**
     * @brief Get the build number of a single \ndds library.
     */
    int32_t build_version() const;
};

/**
 * @ingroup NDDSConfigModule
 * @brief Get the version of the core library.
 */
OMG_DDS_API
LibraryVersion core_version();

/**
 * @ingroup NDDSConfigModule
 * @brief Get the build number of the core library.
 */
OMG_DDS_API
std::string core_build_number();

/**
 * @ingroup NDDSConfigModule
 * @brief Get the version of the C API library.
 */
OMG_DDS_API
LibraryVersion c_api_version();

/**
 * @ingroup NDDSConfigModule
 * @brief Get the build number of the C API library.
 */
OMG_DDS_API
std::string c_build_number();

/**
 * @ingroup NDDSConfigModule
 * @brief Get the version of the C++ API library.
 */
OMG_DDS_API
LibraryVersion cpp_api_version();

/**
 * @ingroup NDDSConfigModule
 * @brief Get the build number of the C++ API library.
 */
OMG_DDS_API
std::string cpp_build_number();

/**
 * @ingroup NDDSConfigModule
 * @brief Get the \ndds product version.
 */
OMG_DDS_API
rti::core::ProductVersion product_version();

} } // namespace rti::config

#endif // RTI_CONFIG_VERSION_HPP_
