/*
 Copyright (c) 2013, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_OPTIONAL_VALUE_HPP_
#define RTI_DDS_CORE_OPTIONAL_VALUE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Exception.hpp>

namespace rti { namespace core {


// This is a very basic implementation--boost::optional more efficient and flexible.
// Constructors of dds::core::optional<T> always call the default constructor
// of T. rtiboost::optional by-passes the default ctor by using a memory buffer
//  where it constructs T in-place only as needed.
//
// This class differs from dds::core::optional<T> in that optional_value<T> keeps
// a value of the type (T value_) whereas optional<T> keeps a pointer (T*). We
// use optional_value in some RTI-extension APIs; optional<T> is for XTypes
// optional members in topic types.
//
//

/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief @extension Represents a value that can be initialized or not
 *
 * Note: this class is similar to dds::core::optional. They are different due
 * to implementation details. dds::core::optional is only used in IDL-generated
 * types. rti::core::optional_value is used in parts of the API.
 */
template <typename T>
class optional_value {

public:
    /**
     * @brief Creates an uninitialized value
     */
    optional_value() : is_set_(false) { }

    /**
     * @brief Creates an instance with a value
     */
    optional_value(const T& value) : value_(value), is_set_(true) { }

    /**
     * @brief Conditionally creates an instance that can be uninitialized or
     * initialized with a value.
     *
     * @param condition If it is true it assigns \p value, otherwise this
     * optional_value is uninitialized
     * @param value The value to use if \p condition is true.
     */
    optional_value(bool condition, const T& value) : is_set_(condition)
    {
        if (condition) {
            value_ = value;
        }
    }

    /**
     * @brief Copy constructor
     *
     * This optional_value will be initialized only if \p other is initialized.
     */
    optional_value(const optional_value<T>& other) : is_set_(other.is_set_)
    {
        if (other.is_set()) {
            value_ = other.get();
        }
    }

public:
    /**
     * Returns true only if the value is initialized.
     */
    bool is_set() const
    {
        return is_set_;
    }

    /**
     * @brief After calling this function, this optional_value is not set.
     */
    void reset()
    {
        is_set_ = false;
    }

    /**
     *  Get the value.
     *
     *  @throws dds::core::PreconditionNotMetError if !is_set
     */
    const T& get() const
    {
        if (!is_set()) {
            throw dds::core::PreconditionNotMetError(
                "uninitialized optional value");
        }

        return value_;
    }

    /**
     *  Get the value.
     *
     *  @throws dds::core::PreconditionNotMetError if !is_set
     */
    T& get()
    {
        if (!is_set()) {
            throw dds::core::PreconditionNotMetError(
                "uninitialized optional value");
        }

        return value_;
    }

private:
    T value_;
    bool is_set_;
};

} }
#endif /* RTI_DDS_CORE_OPTIONAL_VALUE_HPP_ */
