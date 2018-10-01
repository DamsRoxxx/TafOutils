#ifndef OMG_DDS_CORE_TIME_HPP_
#define OMG_DDS_CORE_TIME_HPP_

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

namespace dds {
  namespace core {
    class Duration;
    class Time;
  }
}

/**
 * @ingroup DDSTimeSupportModule
 *  
 * @brief @extension Represents a point in time
 */
class OMG_DDS_API dds::core::Time {
public:
    /**
     * @brief Get a Time object representing an invalid amount of 
     *        time. 
     * 
     * @return const Time A Time object representing an invalid 
     *         amount of time.
     */
    static Time invalid(); // {-1, 0}

    /**
     * @brief Get a Time object representing zero
     *        time.
     *
     * @return const Time A Time object representing zero
     *        time.
     */
    static Time zero();
    /**
        * @brief Get a Time object representing the maximum amount of
        *        time.
        *
        * @return const Time A Time object representing the maximum
        *         amount of time.
        */
    static Time maximum();

    /**
     * @brief Create a Time object from microseconds
     * 
     * @param microseconds How many microseconds this Time 
     *                     represent
     * 
     * @return Time A new instance of Time representing the
     *         given microseconds
     */
    static Time from_microsecs(uint64_t microseconds);

    /**
     * @brief Create a Time object from milliseconds
     * 
     * @param milliseconds How many milliseconds this Time 
     *                should represent
     * 
     * @return Time A new instance of Time representing the
     *         given milliseconds
     */
    static Time from_millisecs(uint64_t milliseconds);

    /**
     * @brief Create a Time object from seconds
     * 
     * @param seconds How many seconds this Time should 
     *                represent
     * 
     * @return Time A new instance of Time representing the
     *         given seconds
     */
    static Time from_secs(double seconds);

    /**
     * @brief Create a default Time object. 
     *  The constructed Time object will represent 0 seconds 
     *          and 0 nanoseconds. 
     */
    Time();

    /**
     * @brief Create a Time object. 
     *  The constructed Time object will represent the given
     *          amount of time.
     */
    explicit Time(int32_t sec, uint32_t nanosec = 0);

    // Spec error: missing copy ctor
    /**
     * @brief Copy-construct a Time object from another Time object.
     */
    Time(const Time& other);

    /**
     * @brief Get the number of seconds that are represented by this 
     *        Time object.
     * 
     * @return int32_t The number of seconds
     */
    int32_t sec() const;

    /**
     * @brief Set the number of seconds that are represented by this
     *        Time object.
     * 
     * @param s The number of seconds to set. 
     */
    void sec(int32_t s);

    /**
     * @brief Get the number of nanoseconds that are represented by 
     *        this Time object.
     * 
     * @return uint32_t The number of nanoseconds
     */
    uint32_t nanosec() const;

    /**
     * @brief Set the number of nanoseconds that are represented by 
     *        this Time object.
     * 
     * @param ns The number of nanoseconds to set. 
     */
    void nanosec(uint32_t ns);

    // Spec error: operators were not const
    /**
     * @brief Compare two Time objects
     * @param other The Time object to compare with this Time.
     * 
     * @return int The result of the comparison can be: -1 if this 
     *         Time is less than other; 0 if they are equal; 1
     *         if this Time is greater than other
     */
    int compare(const Time& other) const;

    /**
     * @brief Check if this Time is greater than another.
     * @param other The Time object to compare with this Time.
     * 
     * @return bool false if this Time is less than or equal to 
     *         the other object, true otherwise. 
     */
    bool operator >(const Time& other) const;

    /**
     * @brief Check if this Time is greater than or equal another.
     * @param other The Time object to compare with this Time.
     * 
     * @return bool false if this Time is less than to the other
     *         object, true otherwise.
     */
    bool operator >=(const Time& other) const;

    /**
     * @brief Check if this Time of Time is equal to another.
     * @param other The Time object to compare with this Time.
     * 
     * @return bool false if this Time is not equal to 
     *         the other object, true otherwise. 
     */
    bool operator ==(const Time& other) const;

    // Spec error: missing operator !=
    /**
     * @brief Check if this Time is not equal to another.
     * @param other The Time object to compare with this Time.
     * 
     * @return bool false if this Time is equal to
     *         the other object, true otherwise. 
     */
    bool operator !=(const Time& other) const;

    /**
     * @brief Check if this Time is less than or equal another. 
     * @param other The Time object to compare with this Time.
     * 
     * @return bool false if this Time is greater than to the 
     *         other object, true otherwise.
     */
    bool operator <=(const Time& other) const;

    /**
     * @brief Check if this Time is less than another. 
     * @param other The Time object to compare with this Time.
     * 
     * @return bool false if this Time is greater than or equal 
     *         to the other object, true otherwise.
     */
    bool operator <(const Time& other) const;

    /**
     * @brief Add a Duration to this Time object
     * 
     * @param duration The Duration to add
     * 
     * @return Time& This Time, with the added Duration
     */
    Time& operator+=(const Duration& duration);

    /**
     * @brief Subtract a Duration from this Time object
     * 
     * @param duration The Duration to subtract
     * 
     * @return Time& This Time, with the subtracted Duration 
     */
    Time& operator-=(const Duration& duration);

    /**
     * @brief Convert this Time to milliseconds
     * 
     * @return uint64_t The number of milliseconds represented by
     *         this Time object. 
     */

    uint64_t to_millisecs() const;

    // Spec error: method signature was incorrect
    /**
     * @brief Convert this Time to microseconds
     * 
     * @return uint64_t The number of microseconds represented by
     *         this Time object. 
     */
    uint64_t to_microsecs() const;

    /**
     * @brief Convert this Time to seconds
     * 
     * @return double The number of seconds represented by
     *         this Time object. 
     */
    double to_secs() const;

private:
    int32_t sec_;
    uint32_t nsec_;
};

namespace dds { namespace core {

// Time arithmetic operators.

/**
 * @brief Add a Time and a Duration together
 * @relatesalso dds::core::Time 
 * 
 * @param time The Time object to add
 * @param duration The Duration object to add
 * 
 * @return Time The result of the addition represented as a Time object
 */
OMG_DDS_API Time operator +(const Time& time, const Duration &duration);

/**
 * @brief Add a Time and a Duration together
 * @relatesalso dds::core::Time 
 * 
 * @param duration The Duration object to add
 * @param time The Time object to add
 * 
 * @return Time The result of the addition represented as a Time object
 */
OMG_DDS_API Time operator +(const Duration& duration, const Time& time);

/**
 * @brief Subtract a Duration from a Time 
 * @relatesalso dds::core::Time
 * 
 * @param time The Time object to subtract from
 * @param duration The Duration object to subtract
 * 
 * @return Time The result of the subtraction represented
 *         as a Time object
 */
OMG_DDS_API Time operator -(const Time& time, const Duration &duration);

/**
 * @brief Calculate the duration between two times
 * @relatesalso dds::core::Time
 *
 * @param time1 The first ("before") time
 * @param time2 The second ("after") time
 *
 * @return The duration elapsed between time1 and time2.
 *         If time1 > time2 the duration is zero.
 *         If time1 is Time::maximum(), the duration is Duration::infinite();
 */
OMG_DDS_API Duration operator -(const Time& time1, const Time& time2);

} }


#endif /* OMG_DDS_CORE_TIME_HPP_ */

