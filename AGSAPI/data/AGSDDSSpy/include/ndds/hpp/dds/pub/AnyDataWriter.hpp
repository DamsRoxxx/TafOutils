#ifndef OMG_DDS_PUB_ANY_DATA_WRITER_HPP_
#define OMG_DDS_PUB_ANY_DATA_WRITER_HPP_

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

#include <dds/core/ref_traits.hpp>
#include <dds/core/Exception.hpp>
#include <dds/pub/DataWriter.hpp>
#include <dds/pub/detail/AnyDataWriter.hpp>

// Disable informational warning about multiple assignment operators
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    #pragma warning(disable:4522)
#endif

namespace dds { namespace pub {

/** 
 * @ingroup DDSWriterModule
 * @headerfile "dds/pub/AnyDataWriter.hpp"
 *  
 * @brief @st_ref_type This class provides an non-template holder for
 * representing a DataWriter of any type
 *  
 * This class is useful for code that uses DataWriters of different types. It
 * provides access to type-independent DataWriter functions.
 *
 * An AnyDataWriter is always created from a typed DataWriter, increasing its
 * reference count. The member function get() allows getting the typed DataWriter
 * back.
 */
class AnyDataWriter {
public:

    // CPPPSM-197
    typedef detail::DWHolderBase DELEGATE_T;
    typedef dds::core::smart_ptr_traits<DELEGATE_T>::ref_type DELEGATE_REF_T;

    /**
     * @brief Create an AnyDataWriter that represents a generic, untyped 
     * DataWriter 
     * 
     * @tparam T The type of the DataWriter that this AnyDataWriter is 
     * being created from
     * @param dw The typed DataWriter that this AnyDataWriter will represent
     */
    template<typename T>
    AnyDataWriter(const dds::pub::DataWriter<T>& dw)
        : holder_(dw.delegate())
    {
    }

    // Spec error: support ctor from null
    AnyDataWriter(const dds::core::null_type&)
    {
    }

    // Spec error: need this constructor for internal use
    AnyDataWriter(
        dds::core::smart_ptr_traits<detail::DWHolderBase>::ref_type holder)
        : holder_(holder)
    {
    }

public:
    /**
     * @brief Get the QoS for this AnyDataWriter
     * 
     * @return dds::pub::qos::DataWriterQos The DataWriterQos
     */
    dds::pub::qos::DataWriterQos qos() const
    {
        return holder_->qos();
    }

    /**
     * @brief Set the QoS for this AnyDataWriter
     * 
     * @param the_qos The QoS to set
     */
    void qos(const dds::pub::qos::DataWriterQos& the_qos)
    {
        holder_->qos(the_qos);
    }

    /**
     * @brief Get the topic name for this AnyDataWriter
     * 
     * @return The topic name
     */
    const std::string& topic_name() const
    {
        return holder_->topic_name();
    }

    /**
     * @brief Get the type name for this AnyDataWriter
     * 
     * @return The type name
     */
    const std::string& type_name() const
    {
        return holder_->type_name();
    }

    /**
     * @brief Get the publisher for this AnyDataWriter
     * 
     * @return The publisher
     */
    const dds::pub::Publisher& publisher() const
    {
        return holder_->publisher();
    }


    /**
     * @see DataWriter::wait_for_acknowledgments
     */
    void wait_for_acknowledgments(const dds::core::Duration& timeout)
    {
        holder_->wait_for_acknowledgments(timeout);
    }

    /**
     * @brief Close the DataWriter
     *
     * @see DataWriter::close()
     */
    void close()
    {
        holder_->close();
    }

    /**
     * @brief Retain this AnyDataWriter
     *
     * @see DataWriter::retain()
     */
    void retain()
    {
        holder_->retain();
    }

    AnyDataWriter& swap(AnyDataWriter& other)
    {
        std::swap(holder_, other.holder_);
        return *this;
    }

    /**
     * @brief Assign a different DataWriter
     *
     * Replaces the reference to the current writer with a new one, whose type
     * \p T can be different.
     */
    template<typename T>
    AnyDataWriter& operator =(const dds::pub::DataWriter<T>& other)
    {
        *this = AnyDataWriter(other);
        return *this;
    }

    AnyDataWriter& operator =(AnyDataWriter other)
    {
        holder_ = other.holder_;
        return *this;
    }

    /**
     * @brief Gets the typed DataWriter from this AnyDataWriter
     * 
     * @tparam T The type of the DataWriter to extract
     * 
     * @return The typed DataWriter that this AnyDataWriter
     * represents
     *
     * @throw dds::core::InvalidDowncastError If this AnyDataWriter
     * doesn't represent a DataWriter<T>.
     */
    template<typename T>
    DataWriter<T> get()
    {
        typename DataWriter<T>::DELEGATE_REF_T typed_holder =
            rtiboost::dynamic_pointer_cast<typename DataWriter<T>::DELEGATE_T>(
                holder_);
        if (typed_holder == NULL) {
            throw dds::core::InvalidDowncastError(
                "Invalid cast to typed DataWriter");
        }

        return DataWriter<T>(typed_holder);
    }

    bool operator==(const AnyDataWriter& other) const
    {
        return holder_ == other.holder_;
    }

    bool operator!=(const AnyDataWriter& other) const
    {
        return holder_ != other.holder_;
    }

    // CPPPSM-197
    bool operator==(dds::core::null_type) const
    {
        return (holder_.get() == 0);
    }

    // CPPPSM-197
    bool operator!=(dds::core::null_type) const
    {
        return !(holder_.get() == 0);
    }

    const detail::DWHolderBase* operator->() const
    {
        return holder_.get();
    }

    detail::DWHolderBase* operator->()
    {
        return holder_.get();
    }

private:
    dds::core::smart_ptr_traits<detail::DWHolderBase>::ref_type holder_;
};

/**
 * @relatesalso AnyDataWriter
 * @brief Same as AnyDataWriter::get()
 */
template <typename T>
DataWriter<T> get(const AnyDataWriter& any_writer)
{
    return any_writer.get<T>();
}

} } // namespace dds::pub

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    #pragma warning(default:4522)
#endif

#endif /* OMG_DDS_PUB_ANY_DATA_WRITER_HPP_ */
