/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_UTIL_UTIL_HPP_
#define RTI_UTIL_UTIL_HPP_

#include <iosfwd>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Duration.hpp>

namespace rti {

/**
 * @brief @extension Contains general-purpose utilities
 */
namespace util {

/** 
 * @ingroup NDDSUtilityModule 
 * @brief Block the calling thread for the specified duration. 
 *  
 * \dref_details_Utility_sleep
 */
OMG_DDS_API
void sleep(const dds::core::Duration& durationIn);

template <typename T>
bool equal_ptr(const T * a, const T * b);

template <typename T>
std::ostream& print_ptr(std::ostream& out, const T * ptr);

OMG_DDS_API
std::string ptr_to_str(const void * p);

OMG_DDS_API
void * str_to_ptr(const std::string& s);

/**
 * @brief Returns the number of spin operations needed to wait 1 microsecond.
 *
 * @details \dref_details_Utility_get_spin_per_microsecond
 *
 * @see spin
 */
OMG_DDS_API
uint64_t spin_per_microsecond();

/**
 * @brief Performs a spin operation (active wait) as many times as indicated.
 *
 * @details \dref_details_Utility_spin
 *
 * @see spin_per_microsecond
 */
OMG_DDS_API
void spin(uint64_t spin_count);

namespace heap_monitoring {

/**
 * @ingroup NDDSUtilityModule
 * @brief Starts monitoring the heap memory used by \ndds.
 *
 * @details \dref_details_Utility_enable_heap_monitoring
 *
 */
OMG_DDS_API
bool enable();

/**
 * @ingroup NDDSUtilityModule
 * @brief Stops monitoring the heap memory used by \ndds.
 *
 * @details \dref_details_Utility_disable_heap_monitoring
 *
 */
OMG_DDS_API
void disable();

/**
 * @ingroup NDDSUtilityModule
 * @brief Pauses heap monitoring.
 *
 * @details \dref_details_Utility_pause_heap_monitoring
 *
 */
OMG_DDS_API
bool pause();

/**
 * @ingroup NDDSUtilityModule
 * @brief Resumes heap monitoring.
 *
 * @details \dref_details_Utility_resume_heap_monitoring
 *
 */
OMG_DDS_API
bool resume();

/**
 * @ingroup NDDSUtilityModule
 * @brief Saves the current heap memory usage in a file.
 *
 * @details \dref_details_Utility_take_heap_snapshot
 *
 */
OMG_DDS_API
bool take_snapshot(const std::string& filename, bool print_details = false);

}


// ---------------------------------------------------------------------------

template <typename T>
bool equal_ptr(const T * a, const T * b)
{
    if (a == b) {
        return true; // Both are NULL or same address
    }

    if (a == NULL || b == NULL) {
        return false; // One is NULL and one isn't
    }

    return *a == *b; // None is NULL
}

template <typename T>
std::ostream& print_ptr(std::ostream& out, const T * ptr)
{
    if (ptr == NULL) {
        out << "NULL";
    } else {
        out << *ptr;
    }

    return out;
}

// This helper method takes in a size_t and checks if it is greater than
// INT_MAX, throwing an error if true. This is needed for x64 architectures
// when trying to use the result of pointer arithmetic (which retuns int64
// values) to set the length of something that is assumed to be of type int32
OMG_DDS_API
int cast_length(size_t length);

} }

#endif // RTI_UTIL_UTIL_HPP_
