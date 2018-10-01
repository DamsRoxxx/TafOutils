#ifndef OMG_DDS_CORE_TBUILTIN_TOPIC_TYPES_HPP_
#define OMG_DDS_CORE_TBUILTIN_TOPIC_TYPES_HPP_

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

#include <dds/core/conformance.hpp>
#include <dds/core/String.hpp>
#include <dds/core/vector.hpp>
#include <dds/core/Value.hpp>

#if defined (OMG_DDS_X_TYPES_BUILTIN_TOPIC_TYPES_SUPPORT)
namespace dds {
  namespace core {

    template <typename DELEGATE>
    class TBytesTopicType;

    template <typename DELEGATE>
    class TStringTopicType;

    template <typename DELEGATE>
    class TKeyedBytesTopicType;

    template <typename DELEGATE>
    class TKeyedStringTopicType;
  }
}

/** 
 * @ingroup DDSBuiltInTypesModule
 * @headerfile dds/core/BuiltinTopicTypes.hpp
 * @RTI_class_definition class dds::core::BytesTopicType 
 *  
 * @brief Built-in type consisting of a variable-length array of opaque bytes.
 *  
 * @see \ref DDSBuiltInTypesModule
 */
template <typename DELEGATE>
class dds::core::TBytesTopicType : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TBytesTopicType, DELEGATE)

    /** 
     * @brief Creates a sample with an empty array of bytes
     */
    TBytesTopicType() : dds::core::Value<DELEGATE>()
    {
    }

    /** 
     * @brief Creates a sample with a vector of bytes
     *  
     * @param the_data The octets
     *  
     * Note that this constructor is implicit so you can use a
     * std::vector<uint8_t> wherever a BytesTopicType instance is expected
     */
    TBytesTopicType(const std::vector<uint8_t>& the_data)
        : dds::core::Value<DELEGATE>(the_data)
    {
    }

    /**
     * @brief Automatic conversion to std::vector
     *
     * @return A copy of the bytes
     */
    operator std::vector<uint8_t> () const
    {
        return this->delegate().data();
    }

    /**
     * @brief Gets the bytes in a std::vector
     *
     * @return A copy of the bytes
     */
    std::vector<uint8_t> data() const
    {
        return this->delegate().data();
    }

    /**
     * @brief Sets the bytes
     * 
     * @param value The bytes
     */
    void data(const std::vector<uint8_t>& value)
    {
        this->delegate().data(value);
    }

    /**
     * @brief Access the bytes by index
     */
    uint8_t& operator [](uint32_t index)
    {
        return this->delegate()[index];
    }

    /**
     * @brief Access the bytes by index
     */
    uint8_t operator [](uint32_t index) const
    {
        return this->delegate()[index];
    }

    // Spec Issue: CPPPSM-330
    /**
     * @brief Get the number of bytes
     */
    int32_t length() const
    {
        return this->delegate().length();
    }
};

/** 
 * @ingroup DDSBuiltInTypesModule 
 * @headerfile dds/core/BuiltinTopicTypes.hpp
 * @RTI_class_definition class dds::core::StringTopicType 
 *  
 * @brief Built-in type consisting of a single character string.
 *  
 * @see \ref DDSBuiltInTypesModule
 */
template <typename DELEGATE>
class dds::core::TStringTopicType : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TStringTopicType, DELEGATE)

    /** 
     * @brief Creates a sample containing an empty string
     */ 
    TStringTopicType() : dds::core::Value<DELEGATE>()
    {
    }

    /** 
     * @brief Creates a sample from a dds::core::string
     *  
     * Note that this constructor is implicit so you can use a
     * dds::core::string wherever a StringTopicType instance is expected
     *  
     */ 
    TStringTopicType(const dds::core::string& the_data)
        : dds::core::Value<DELEGATE>(the_data)
    {
    }

    /**
     * @brief Creates a sample from a std::string
     *
     * Note that this constructor is implicit so you can use an std::string
     * wherever a StringTopicType instance is expected, for example:
     * \code
     * dds::pub::DataWriter<StringTopicType> writer(...);
     * std::string str = "Hello World!";
     * writer.write(str);
     * \endcode
     *
     * @param the_data The string to be copied to create this instance
     */
    TStringTopicType(const std::string& the_data)
        : dds::core::Value<DELEGATE>(the_data)
    {
    }

    // Spec error: nice addition to support stuff like this:
    //   writer.write("Hi");
    /** 
     * @brief Creates an instance from a char*
     *  
     * Note that this constructor is implicit so you can use an char*
     * wherever a StringTopicType instance is expected, for example:
     * \code
     * dds::pub::DataWriter<StringTopicType> writer(...);
     * writer.write("Hello, World!");
     * \endcode
     *  
     * @param the_data The string to be copied to create this instance
     *  
     */
    TStringTopicType(const char * the_data)
        : dds::core::Value<DELEGATE>(dds::core::string(the_data))
    {
    }

    /**
     * @brief Automatic conversion to std::string
     * 
     * @return A copy of the string
     */
    operator std::string () const
    {
        return this->delegate().data();
    }

    /**
     * @brief Automatic conversion to dds::core::string
     * 
     * @return A reference to the string
     */
    operator dds::core::string& ()
    {
        return this->delegate().data();
    }

    /**
     * @brief Automatic conversion to dds::core::string
     * 
     * @return A const-reference to the string
     */
    operator const dds::core::string& () const
    {
        return this->delegate().data();
    }

    /**
     * @brief Gets the string
     * 
     * @return A const-reference to the string
     */
    const dds::core::string& data() const
    {
        return this->delegate().data();
    }

    /**
     * @brief Gets the string
     * 
     * @return A reference to the string
     */
    dds::core::string& data()
    {
        return this->delegate().data();
    }

    /**
     * @brief Sets the string
     */
    void data(const dds::core::string& value)
    {
        this->delegate().data(value);
    }
};

/** 
 * @ingroup DDSBuiltInTypesModule 
 * @headerfile dds/core/BuiltinTopicTypes.hpp
 * @RTI_class_definition class dds::core::KeyedStringTopicType 
 *  
 * @brief Built-in type consisting of a string payload and a second string that
 * is the key.
 *
 * @see \ref DDSBuiltInTypesModule
 */
template <typename DELEGATE>
class dds::core::TKeyedStringTopicType : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TKeyedStringTopicType, DELEGATE)

    /** 
     * @brief Creates a sample with two empty strings
     */ 
    TKeyedStringTopicType() : dds::core::Value<DELEGATE> ()
    {
    }

    /** 
     * @brief Creates a sample with the two given strings
     */ 
    TKeyedStringTopicType(
        const dds::core::string& the_key, const dds::core::string& the_value)
        : dds::core::Value<DELEGATE> (the_key, the_value)
    {
    }

    /**
     * @brief Gets the key
     */
    const dds::core::string& key() const
    {
        return this->delegate().key();
    }

    /**
     * @brief Gets the key
     */
    dds::core::string& key()
    {
        return this->delegate().key();
    }

    /**
     * @brief Sets the key
     */
    void key(const dds::core::string& the_value)
    {
        this->delegate().key(the_value);
    }

    /**
     * @brief Gets the value
     */
    const dds::core::string& value() const
    {
        return this->delegate().value();
    }

    /**
     * @brief Gets the key
     */
    dds::core::string& value()
    {
        return this->delegate().value();
    }

    /**
     * @brief Gets the key
     */
    void value(const dds::core::string& the_value)
    {
        this->delegate().value(the_value);
    }
};

/** 
 * @ingroup DDSBuiltInTypesModule 
 * @headerfile dds/core/BuiltinTopicTypes.hpp
 * @RTI_class_definition class dds::core::KeyedBytesTopicType 
 *  
 * @brief Built-in type consisting of a variable-length array of opaque bytes
 * and a string that is the key.
 */
template <typename DELEGATE>
class dds::core::TKeyedBytesTopicType : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TKeyedBytesTopicType, DELEGATE)

    /** 
     * @brief Creates a sample with an empty array of bytes and an empty string
     */ 
    TKeyedBytesTopicType() : dds::core::Value<DELEGATE> ()
    {
    }

    /**
     * @brief Creates a sample with the given key and bytes
     */
    TKeyedBytesTopicType(
        const std::string& the_key, const std::vector<uint8_t>& the_value)
        : dds::core::Value<DELEGATE> (the_key, the_value)
    {
    }

    /**
     * @brief Gets the key
     */
    const dds::core::string& key() const
    {
        return this->delegate().key();
    }

    /**
     * @brief Gets the key
     */
    dds::core::string& key()
    {
        return this->delegate().key();
    }

    /**
     * @brief Sets the key
     */
    void key(const dds::core::string& the_value)
    {
        this->delegate().key(the_value);
    }

    /**
     * @brief Conversion to std::vector by obtaining the bytes
     */
    operator std::vector<uint8_t> () const
    {
        return this->delegate().data();
    }

    /**
     * @brief Gets the bytes
     */
    std::vector<uint8_t> value() const
    {
        return this->delegate().data();
    }

    /**
     * @brief Sets the bytes
     */
    void value(const std::vector<uint8_t>& the_value)
    {
        this->delegate().data(the_value);
    }

    /**
     * @brief Accesses the bytes by index
     */
    uint8_t& operator [](uint32_t index)
    {
        return this->delegate()[index];
    }

    /**
     * @brief Accesses the bytes by index
     */
    uint8_t operator [](uint32_t index) const
    {
        return this->delegate()[index];
    }

    // Spec Issue: CPPPSM-330
    /**
     * @brief Get the number of bytes
     */
    int32_t length() const
    {
        return this->delegate().length();
    }
};

#endif /* OMG_DDS_X_TYPES_BUILTIN_TOPIC_TYPES_SUPPORT */

#endif /* OMG_DDS_CORE_TBUILTIN_TOPIC_TYPES_HPP_ */
