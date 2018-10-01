#ifndef OMG_DDS_SUB_ANY_DATA_READER_HPP_
#define OMG_DDS_SUB_ANY_DATA_READER_HPP_

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

#include <dds/core/Exception.hpp>
#include <dds/core/ref_traits.hpp>
#include <dds/sub/detail/AnyDataReader.hpp>

namespace dds {  namespace sub {

/** 
 * @ingroup DDSReaderModule
 * @headerfile "dds/sub/AnyDataReader.hpp"
 *  
 * @brief @st_ref_type This class provides an non-template holder for
 * representing a DataReader of any type
 *  
 * This class is useful for code that uses DataReaders of different types. It
 * provides access to type-independent DataReader functions.
 *
 * An AnyDataReader is always created from a typed DataReader, increasing its
 * reference count. The member function get() allows getting the typed DataReader
 * back.
 */
class AnyDataReader {
public:

    // Issue CPPPSM-197: need this typedef
    typedef detail::DRHolderBase DELEGATE_T;
    typedef dds::core::smart_ptr_traits<DELEGATE_T>::ref_type DELEGATE_REF_T;

    /**
     * @brief Create an AnyDataReader that represents a generic, untyped 
     * DataReader 
     * 
     * @tparam T The type of the DataReader that this AnyDataReader is 
     * being created from
     * @param reader The typed DataReader that this AnyDataReader will represent
     */
    template<typename T>
    AnyDataReader(const dds::sub::DataReader<T>& reader)
        : holder_(reader.delegate())
    {
    }

    // Spec issue CPPPSM-31: multiple missing methods
    AnyDataReader(const dds::core::null_type&)
    {
    }

    AnyDataReader(
        dds::core::smart_ptr_traits<detail::DRHolderBase>::ref_type holder)
        : holder_(holder)
    {
    }

    /**
     * @brief Get the QoS for this AnyDataReader
     * 
     * @return dds::sub::qos::DataReaderQos The DataReaderQos
     */
    dds::sub::qos::DataReaderQos qos() const
    {
        return holder_->qos();
    }

    /**
     * @brief Set the QoS for this AnyDataReader
     * 
     * @param the_qos The QoS to set
     */
    void qos(const dds::sub::qos::DataReaderQos& the_qos)
    {
        holder_->qos(the_qos);
    }

    /**
     * @brief Get the topic name for this AnyDataReader
     * 
     * @return The topic name
     */
    const std::string& topic_name() const
    {
        return holder_->topic_name();
    }

    /**
     * @brief Get the type name for this AnyDataReader
     * 
     * @return The type name
     */
    const std::string& type_name() const
    {
        return holder_->type_name();
    }

    /**
     * @brief Get the publisher for this AnyDataReader
     * 
     * @return The subscriber
     */
    const dds::sub::Subscriber& subscriber() const
    {
        return holder_->subscriber();
    }

public:
    AnyDataReader& swap(AnyDataReader& other)
    {
        std::swap(holder_, other.holder_);
        return *this;
    }

    /**
     * @brief Assign a different DataReader
     *
     * Replaces the reference to the current reader with a new one, whose type
     * \p T can be different.
     */
    template<typename T>
    AnyDataReader& operator =(const DataReader<T>& other)
    {
        *this = AnyDataReader(other);
        return *this;
    }

    AnyDataReader& operator =(AnyDataReader other)
    {
        holder_ = other.holder_;
        return *this;
    }

public:
    /**
     * @brief Gets the typed DataReader from this AnyDataReader
     * 
     * @tparam T The type of the DataReader to extract
     * 
     * @return The typed DataReader that this AnyDataReader
     * represents
     *
     * @throw dds::core::InvalidDowncastError If this AnyDataReader
     * doesn't represent a DataReader<T>.
     */
    template<typename T>
    dds::sub::DataReader<T> get() const
    {
        if (!holder_) {
            return DataReader<T>(dds::core::null_type());
        } 

        typename DataReader<T>::DELEGATE_REF_T typed_holder =
            rtiboost::dynamic_pointer_cast<typename DataReader<T>::DELEGATE_T>(
                holder_);
        if (typed_holder == NULL) {
            throw dds::core::InvalidDowncastError(
                "Invalid cast to typed DataReader");
        }

        return DataReader<T>(typed_holder);
    }

    bool operator==(const AnyDataReader& other) const
    {
        return holder_ == other.holder_;
    }

    bool operator!=(const AnyDataReader& other) const
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

    const detail::DRHolderBase* operator->() const
    {
        return holder_.get();
    }

    detail::DRHolderBase* operator->()
    {
        return holder_.get();
    }

    /**
     * @brief Close this AnyDataReader 
     *  
     * @see DataReader::close() 
     */
    void close()
    {
        holder_->close();
    }

    /**
     * @brief Retain this AnyDataReader
     *
     * @see DataReader::retain()
     */
    void retain() 
    {
        holder_->retain();
    }

private:
    dds::core::smart_ptr_traits<detail::DRHolderBase>::ref_type holder_;
};

/**
 * @relatesalso AnyDataReader
 * @brief Same as AnyDataReader::get()
 */
template <typename T>
DataReader<T> get(const AnyDataReader& any_reader)
{
    return any_reader.get<T>();
}

} } // namespace dds::sub

#endif /* OMG_DDS_SUB_ANY_DATA_READER_HPP_ */
