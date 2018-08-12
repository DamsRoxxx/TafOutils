/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_BUILTIN_TOPIC_TYPES_IMPL_HPP_
#define RTI_DDS_CORE_BUILTIN_TOPIC_TYPES_IMPL_HPP_

#include <iosfwd>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_builtintypes.h"

#include <dds/core/corefwd.hpp>
#include <dds/core/String.hpp>
#include <dds/core/vector.hpp>
#include <rti/topic/TopicTraits.hpp>
#include <dds/domain/domainfwd.hpp>

namespace rti { namespace core {

void swap(StringTopicTypeImpl& left, StringTopicTypeImpl& right) OMG_NOEXCEPT;
void swap(KeyedStringTopicTypeImpl& left, KeyedStringTopicTypeImpl& right) OMG_NOEXCEPT;
void swap(BytesTopicTypeImpl& left, BytesTopicTypeImpl& right) OMG_NOEXCEPT;
void swap(KeyedBytesTopicTypeImpl& left, KeyedBytesTopicTypeImpl& right) OMG_NOEXCEPT;

namespace detail {

OMG_DDS_API
std::vector<char>& to_cdr_buffer(
    std::vector<char>& buffer,
    const rti::core::StringTopicTypeImpl& sample);

OMG_DDS_API
void from_cdr_buffer(
    rti::core::StringTopicTypeImpl& sample,
    const std::vector<char>& buffer);

OMG_DDS_API
std::vector<char>& to_cdr_buffer(
    std::vector<char>& buffer,
    const rti::core::KeyedStringTopicTypeImpl& sample);

OMG_DDS_API
void from_cdr_buffer(
    rti::core::KeyedStringTopicTypeImpl& sample,
    const std::vector<char>& buffer);

OMG_DDS_API
std::vector<char>& to_cdr_buffer(
    std::vector<char>& buffer,
    const rti::core::BytesTopicTypeImpl& sample);

OMG_DDS_API
void from_cdr_buffer(
    rti::core::BytesTopicTypeImpl& sample,
    const std::vector<char>& buffer);

OMG_DDS_API
std::vector<char>& to_cdr_buffer(
    std::vector<char>& buffer,
    const rti::core::KeyedBytesTopicTypeImpl& sample);

OMG_DDS_API
void from_cdr_buffer(
    rti::core::KeyedBytesTopicTypeImpl& sample,
    const std::vector<char>& buffer);

} // namespace detail

// --- StringTopicTypeImpl ----------------------------

class OMG_DDS_API StringTopicTypeImpl {
public:
    StringTopicTypeImpl() {}
    StringTopicTypeImpl(const dds::core::string& data);

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    StringTopicTypeImpl(StringTopicTypeImpl&& other)
        : m_data_(std::move(other.m_data_))
    {
    }

    StringTopicTypeImpl& operator=(StringTopicTypeImpl&& other)
    {
        StringTopicTypeImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    dds::core::string& data();
    const dds::core::string& data() const;
    void data(const dds::core::string& value);

    bool operator == (const StringTopicTypeImpl& other) const;
    bool operator != (const StringTopicTypeImpl& other) const;

 private:
    dds::core::string m_data_;

};

inline void swap(StringTopicTypeImpl& left, StringTopicTypeImpl& right) OMG_NOEXCEPT
{
    swap(left.data(), right.data());
}

// --- KeyedStringTopicTypeImpl ----------------------------

class OMG_DDS_API KeyedStringTopicTypeImpl {
public:
    KeyedStringTopicTypeImpl() {}
    KeyedStringTopicTypeImpl(
        const dds::core::string& key,
        const dds::core::string& value);

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    KeyedStringTopicTypeImpl(KeyedStringTopicTypeImpl&& other)
        : m_key_(std::move(other.m_key_)), m_value_(std::move(other.m_value_))
    {
    }

    KeyedStringTopicTypeImpl& operator=(KeyedStringTopicTypeImpl&& other)
    {
        KeyedStringTopicTypeImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    dds::core::string& key();
    const dds::core::string& key() const;
    void key(const dds::core::string& value);

    dds::core::string& value();
    const dds::core::string& value() const;
    void value(const dds::core::string& value);

    bool operator == (const KeyedStringTopicTypeImpl& other) const;
    bool operator != (const KeyedStringTopicTypeImpl& other) const;

private:
    dds::core::string m_key_;
    dds::core::string m_value_;
};

inline void swap(KeyedStringTopicTypeImpl& left, KeyedStringTopicTypeImpl& right) OMG_NOEXCEPT
{
    swap(left.key(), right.key());
    swap(left.value(), right.value());
}

// --- BytesTopicTypeImpl ----------------------------

class OMG_DDS_API BytesTopicTypeImpl {
public: 
    typedef rti::core::memory::OsapiAllocator<char> Allocator;
    friend inline void swap(BytesTopicTypeImpl& left, BytesTopicTypeImpl& right) OMG_NOEXCEPT;

public:
    BytesTopicTypeImpl();
    BytesTopicTypeImpl(const std::vector<uint8_t>& data);
    BytesTopicTypeImpl(const BytesTopicTypeImpl& other);
    ~BytesTopicTypeImpl();

    BytesTopicTypeImpl& operator=(const BytesTopicTypeImpl& other);

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    BytesTopicTypeImpl(BytesTopicTypeImpl&& other) OMG_NOEXCEPT
        : m_length_(std::move(other.m_length_)), 
          m_value_(NULL)
    {
        std::swap(m_value_, other.m_value_);
    }

    BytesTopicTypeImpl& operator=(BytesTopicTypeImpl&& other) OMG_NOEXCEPT
    {
        BytesTopicTypeImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    std::vector<uint8_t> data();
    std::vector<uint8_t> data() const;
    void data(const std::vector<uint8_t>& value);

    const char * begin() const
    {
        return m_value_;
    }

    const char * end() const 
    {
        return m_value_ == NULL ? NULL : m_value_ + m_length_;
    }

    uint8_t& operator [](uint32_t index);
    uint8_t operator [](uint32_t index) const;

    bool operator == (const BytesTopicTypeImpl& other) const;
    bool operator != (const BytesTopicTypeImpl& other) const;

    int32_t length() const;
    void length(int32_t length);

    char* value() const; 
    void value(char* the_value, int32_t size);

private:
    int32_t m_length_;
    char* m_value_;
};

inline void swap(BytesTopicTypeImpl& left, BytesTopicTypeImpl& right) OMG_NOEXCEPT
{
    using std::swap; 

    swap(left.m_length_, right.m_length_);
    swap(left.m_value_, right.m_value_);
}

// --- KeyedBytesTopicTypeImpl ----------------------------

class OMG_DDS_API KeyedBytesTopicTypeImpl {
public: 
    typedef rti::core::memory::OsapiAllocator<char> Allocator;
    friend inline void swap(
        KeyedBytesTopicTypeImpl& left, KeyedBytesTopicTypeImpl& right) OMG_NOEXCEPT;

public:
    KeyedBytesTopicTypeImpl();
    KeyedBytesTopicTypeImpl(
        const dds::core::string& key,
        const std::vector<uint8_t>& data);
    KeyedBytesTopicTypeImpl(const KeyedBytesTopicTypeImpl& other);
    ~KeyedBytesTopicTypeImpl();

    KeyedBytesTopicTypeImpl& operator=(const KeyedBytesTopicTypeImpl& other);

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    KeyedBytesTopicTypeImpl(KeyedBytesTopicTypeImpl&& other) OMG_NOEXCEPT
        : m_key_(std::move(other.m_key_)),
          m_length_(std::move(other.m_length_)), 
          m_value_(NULL)
    {
        std::swap(m_value_, other.m_value_);
    }

    KeyedBytesTopicTypeImpl& operator=(
        KeyedBytesTopicTypeImpl&& other) OMG_NOEXCEPT
    {
        KeyedBytesTopicTypeImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    dds::core::string& key();
    const dds::core::string& key() const;
    void key(const dds::core::string& value);

    std::vector<uint8_t> data();
    std::vector<uint8_t> data() const;
    void data(const std::vector<uint8_t>& value);

    const char * begin() const
    {
        return m_value_;
    }

    const char * end() const 
    {
        return m_value_ == NULL ? NULL : m_value_ + m_length_;
    }

    uint8_t& operator [](uint32_t index);
    uint8_t operator [](uint32_t index) const;

    bool operator == (const KeyedBytesTopicTypeImpl& other) const;
    bool operator != (const KeyedBytesTopicTypeImpl& other) const;

    int32_t length() const;
    void length(int32_t length);

    char* value() const;
    void value(const char* the_value, int32_t size);

private:
    dds::core::string m_key_;
    int32_t m_length_;
    char* m_value_;
};

inline void swap(
    KeyedBytesTopicTypeImpl& left, KeyedBytesTopicTypeImpl& right) OMG_NOEXCEPT
{
    using std::swap; 

    swap(left.m_key_, right.m_key_);
    swap(left.m_length_, right.m_length_);
    swap(left.m_value_, right.m_value_);
}

} } // namespace rti::namespace core

namespace dds { namespace topic {

// --- StringTopicType
template<>
struct topic_type_name<dds::core::StringTopicType> {
    static std::string value() {
        return DDS_StringTYPENAME;
    }
};

template<>
struct is_topic_type<dds::core::StringTopicType> {
    enum {
        value = 1
    };
};

// --- KeyedStringTopicType
template<>
struct topic_type_name<dds::core::KeyedStringTopicType> {
    static std::string value() {
        return DDS_KeyedStringTYPENAME;
    }
};

template<>
struct is_topic_type<dds::core::KeyedStringTopicType> {
    enum {
        value = 1
    };
};

// --- BytesTopicType
template<>
struct topic_type_name<dds::core::BytesTopicType> {
    static std::string value() {
        return DDS_OctetsTYPENAME;
    }
};

template<>
struct is_topic_type<dds::core::BytesTopicType> {
    enum {
        value = 1
    };
};

// --- KeyedBytesTopicType
template<>
struct topic_type_name<dds::core::KeyedBytesTopicType> {
    static std::string value() {
        return DDS_KeyedOctetsTYPENAME;
    }
};

template<>
struct is_topic_type<dds::core::KeyedBytesTopicType> {
    enum {
        value = 1
    };
};

} } // namespace dds::topic

namespace dds { namespace core {

OMG_DDS_API
std::ostream& operator << (std::ostream& out, 
                           const rti::core::StringTopicTypeImpl& sample);

OMG_DDS_API
std::ostream& operator << (
    std::ostream& out, const rti::core::KeyedStringTopicTypeImpl& sample);

OMG_DDS_API
std::ostream& operator << (std::ostream& out, 
                           const rti::core::BytesTopicTypeImpl& sample);

OMG_DDS_API
std::ostream& operator << (std::ostream& out, 
                           const rti::core::KeyedBytesTopicTypeImpl& sample);

} }

#endif
