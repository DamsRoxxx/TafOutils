#ifndef OMG_DDS_CORE_DURATION_HPP_
#define OMG_DDS_CORE_DURATION_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>

#ifndef RTI_NO_CXX11_HDR_CHRONO
#include <chrono>
#endif

/**
 * @defgroup DDSTimeSupportModule Time Support
 * @ingroup DDSInfrastructureModule
 * @brief Time and duration types
 */

namespace dds { namespace core {

  /** 
   * @ingroup DDSTimeSupportModule
   * @brief @st_value_type Represents a time interval
   */
  class OMG_DDS_API Duration {
  public:
    /**
     * @brief Returns a zero duration
     *
     * @return Duration()
     */
    static Duration zero();       // {0, 0}

    /**
     * @brief Special value that represents an infinite Duration
     */
    static Duration infinite();   // {0x7fffffff, 0x7fffffff}

    /**
     * @brief Special value that indicates that \ndds will automatically assign
     * a value.
     */
    static Duration automatic();   // {0xffffffffL, 0UL}
  public:
    /** 
     * @brief Create a Duration elapsing zero seconds. 
     */
    Duration();

    /**
     * @brief Create a duration elapsing a specific amount of time. 
     *  
     * @param sec The number of seconds to represent 
     * @param nanosec The number of nanoseconds to represent
     */
    explicit Duration(int32_t sec, uint32_t nanosec = 0);

  #ifndef RTI_NO_CXX11_HDR_CHRONO
    /**
     * @brief @st_cpp11 @extension Allow implicit creation from std::chrono::duration
     *
     * For example:
     * \code
     * dds::core::cond::WaitSet waitset;
     * // ...
     * waitset.wait(std::chrono::seconds(1) + std::chrono::milliseconds(250));
     * \endcode
     *
     */
    template <typename Rep, typename Period>
    /* implicit */ Duration(const std::chrono::duration<Rep, Period>& duration)
        : sec_(static_cast<int32_t>(
              std::chrono::duration_cast<std::chrono::seconds, Rep, Period>(duration).count())),
          nsec_(static_cast<uint32_t>(
              (std::chrono::nanoseconds(duration) % 1000000000).count()))
    {
    }
  #endif

  public:
    /**
     * @brief Create a Duration elapsing a specific number of 
     *        microseconds
     * 
     * @param microseconds The number of microseconds to construct 
     *                the object from
     * 
     * @return A newly constructed Duration object
     */
    static Duration from_microsecs(uint64_t microseconds);

    /**
     * @brief Create a Duration elapsing a specific number of 
     *        milliseconds
     * 
     * @param milliseconds The number of milliseconds to construct 
     *                the object from
     * 
     * @return A newly constructed Duration object
     */
    static Duration from_millisecs(uint64_t milliseconds);
    /**
     * @brief Create a Duration elapsing a specific number of 
     *        seconds
     * 
     * @param seconds The number of seconds to construct the object 
     *                from 
     * 
     * @return A newly constructed Duration object
     */
    static Duration from_secs(double seconds);

  public:
    /**
     * @brief Get the number of seconds represented by this Duration 
     *        object
     * 
     * @return The number of seconds (excluding the nanoseconds)
     */
    int32_t sec() const;

    /**
     * @brief Set the number of seconds represented by this Duration
     *        object
     * 
     * @param s The number of seconds to set
     */
    void    sec(int32_t s);

    /**
     * @brief Get the number of nanoseconds represented by this 
     *        Duration object
     * 
     * @return The number of nanoseconds (excluding the seconds)
     */
    uint32_t nanosec() const;

    /**
     * @brief Set the number of nanoseconds represented by this 
     *        Duration object
     * 
     * @param ns The number of nanoseconds to set
     */
    void     nanosec(uint32_t ns);

  public:
    /**
     * @brief Compare two Duration objects
     * @param that The Duration object to compare with this 
     *             Duration.
     * 
     * @return int The result of the comparison can be: -1 if this 
     *         Duration is less than other; 0 if they are equal; 1
     *         if this Duration is greater than other
     */
    int compare(const Duration& that) const;

    /**
     * @brief Check if this Duration is greater than 
     *        another. 
     * @param that The Duration to compare with this Duration.
     * 
     * @return bool false if this Duration is less than or equal to 
     *         the other object, true otherwise. 
     */
    bool operator >(const Duration& that) const;

    /**
     * @brief Check if this Duration is greater than or equal
     *        another. 
     * @param that The Duration to compare with this Duration.
     * 
     * @return bool false if this Duration is less than to the other
     *         object, true otherwise.
     */
    bool operator >=(const Duration& that) const;

    /**
     * @brief Check if this Duration is equal to another.
     * @param that The Duration to compare with this Duration.
     * 
     * @return bool false if this Duration is not equal to the other
     *         object, true otherwise.
     */
    bool operator ==(const Duration& that) const;

    /**
     * @brief Check if this Duration is not equal to another.
     * @param other The Duration to compare with this Duration.
     * 
     * @return bool false if this Duration is equal to the other
     *         object, true otherwise.
     */
    bool operator !=(const Duration& other) const;

    /**
     * @brief Check if this Duration is less than or equal another.
     * @param that The Duration to compare with this Duration.
     * 
     * @return bool false if this Duration is greater than to the 
     *         other object, true otherwise.
     */
    bool operator <=(const Duration& that) const;

    /**
     * @brief Check if this Duration is less than 
     *        another. 
     * @param that The Duration to compare with this Duration.
     * 
     * @return bool false if this Duration is greater than or equal 
     *         to the other object, true otherwise.
     */
    bool operator <(const Duration& that) const;

  public:
    /**
     * @brief Add a Duration to this Duration
     * 
     * @param a_ti The Duration to add
     * 
     * @return Duration& This Duration, with the added Duration 
     */
    Duration& operator+=(const Duration &a_ti);

    /**
     * @brief Subtract a Duration from this Duration
     * 
     * @param a_ti The Duration to subtract
     * 
     * @return Duration& This Duration, after the subtraction
     */
    Duration& operator-=(const Duration &a_ti);

    /**
     * @brief Add two Duration objects
     * 
     * @param other The other Duration to add to this one
     * 
     * @return The result of the addition
     */
    Duration operator +(const Duration& other) const;

    /**
     * @brief Subtract a Duration 
     * 
     * @param other The Duration to subract from this one
     * 
     * @return The result of the subtraction
     */
    Duration operator -(const Duration& other) const;
  public:

    /**
     * @brief Returns this Duration in milliseconds.
     *
     * @return the Duration in milliseconds
     */
    uint64_t to_millisecs() const;

    /**
     * @brief Returns this <code>Duration</code> in microseconds.
     *
     * @return the Duration in microseconds
     */    
    uint64_t to_microsecs() const;

    /**
     * @brief Returns this <code>Duration</code> in seconds.
     *
     * @return the Duration in seconds
     */
    double to_secs() const;

  #ifndef RTI_NO_CXX11_HDR_CHRONO
    /**
     * @brief @st_cpp11 @extension Converts to std::chrono::nanoseconds
     *  
     * @return The Duration in nanoseconds.
     */
     std::chrono::nanoseconds to_chrono() const
     {
        return std::chrono::seconds(sec()) + std::chrono::nanoseconds(nanosec());
     }
  #endif

private:
    int32_t sec_; // Spec error: was uint32_t
    uint32_t nsec_;
  };

/**
 * @brief Multiply a Duration object by an unsigned integer
 * @relatesalso dds::core::Duration 
 * 
 * @param lhs The unsigned integer to multiply the Duration
 *            object by
 * @param rhs The Duration object to multiply
 * 
 * @return Duration The result of the multiplication
 */
  OMG_DDS_API Duration operator *(uint32_t lhs, const Duration& rhs);

/**
 * 
 * @brief Multiply a Duration object by an unsigned integer
 * @relatesalso dds::core::Duration 
 * 
 * @param lhs The Duration object to multiply
 * @param rhs The unsigned integer to multiply the Duration 
 *            object by
 * 
 * @return Duration The result of the multiplication
 */
  OMG_DDS_API Duration operator *(const Duration& lhs, uint32_t rhs);

/**
 * @brief Divide a Duration object by an unsigned integer
 * @relatesalso dds::core::Duration 
 *  
 * @param lhs The dividend
 * @param rhs The divisor
 * 
 * @return Duration The result of dividing the two
 *         Duration objects
 */
  OMG_DDS_API Duration operator /(const Duration& lhs, uint32_t rhs);

/**
 * @brief Swap the contents of two Duration objects 
 * @relatesalso dds::core::Duration 
 * 
 * @param lhs One of the Duration objects
 * @param rhs One of the Duration objects
 */
  OMG_DDS_API void swap(Duration& lhs, Duration& rhs) OMG_NOEXCEPT;

} } /* namespace dds / namespace core  */
#endif /* OMG_DDS_CORE_DURATION_HPP_ */

