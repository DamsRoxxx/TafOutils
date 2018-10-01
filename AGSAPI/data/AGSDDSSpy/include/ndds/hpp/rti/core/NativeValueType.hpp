/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,21jan13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_NATIVE_TYPE_HPP_
#define RTI_DDS_CORE_NATIVE_TYPE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_string.h"
#include <string>
#include <vector>

#include <dds/core/String.hpp>

namespace rti { namespace core {

/*i
   Specializations of this template associate a DDS C++ type with its
   corresponding native type (from dds_c.1.0) and the adapter that allows
   initializing, finalizing, copying and comparing the native type.

   Specializations should define the native type and the adapter type. For
   example:

   template <>
   struct native_type_traits<TypeX> {
       typedef TypeXAdapter adapter;
       typedef DDS_TypeX native_type;
   };

   The adapter type is a class with the following structure:

   class TypeXAdapter {
   public:
    typedef DDS_TypeX native_type;

    static void initialize(native_type& native_value);
    static void finalize(native_type& native_value);
    static void copy(native_type& destination, const native_type& source);
    static bool equals(const native_type& first, const native_type& second);
   };

   With this infrastructure, expressions like the following are possible:

   native_type_traits<T>::native_type native_value;
   native_type_traits<T>::adapter::initialize(native_value);
*/
template <typename T>
struct native_type_traits {
    // typedef ... adapter_type;
    // typedef ... native_type;
};

// A type adapter for types where the default copy operator and an empty
// destructor suffice. A derived type adapter still needs to implement the
// initialization and equality functions.
template <typename NativeType>
class SimpleTypeAdapter {
public:
    typedef NativeType native_type;

    static void finalize(native_type&)
    {
        // empty
    }

    static void copy(native_type& destination, const native_type& source)
    {
        memcpy(&destination, &source, sizeof(native_type));
    }
};

// A fully implemented adapter for types where memset, memcpy and memcmp
// can be used to initialize, copy and compare.
template <typename NativeType>
class PODNativeAdapter : public SimpleTypeAdapter<NativeType> {
public:
    typedef NativeType native_type;

    static void initialize(native_type& native_value)
    {
         memset(&native_value, 0, sizeof(native_type));
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return memcmp(&first, &second, sizeof(native_type)) == 0;
    }
};


/* Base class for types in the C++ API that map directly to a native type.
   This class contains directly a native value-type and defines constructors
   and operators that manipulate the native type.

   T is the derived type. For example:

   class InstanceHandle : public NativeValueType<InstanceHandle> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(InstanceHandle)
 ... }

   Native<T> should not be used polymorphically.
*/
template <
    typename T,
    typename NATIVE_T = typename native_type_traits<T>::native_type,
    typename ADAPTER = typename native_type_traits<T>::adapter_type>
class NativeValueType {
public:
    typedef NATIVE_T native_type;
    typedef ADAPTER adapter_type;


protected: // Ctors are protected: this class should not be instantiated
    NativeValueType()
    {
        adapter_type::initialize(native());
    }

    NativeValueType(const NativeValueType& other)
    {
        adapter_type::initialize(native());
        adapter_type::copy(this->native(), other.native());
    }

    explicit NativeValueType(const native_type& other)
    {
        adapter_type::initialize(native());
        adapter_type::copy(this->native(), other);
    }

    // This constructor is for internal use only
    NativeValueType(native_type&, bool)
    {
        // assume caller already initialized referenced_instance
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    NativeValueType(NativeValueType&& other) OMG_NOEXCEPT
    {
        memcpy(&native(), &other.native(), sizeof(native())); // shallow copy
        memset(&other.native(), 0, sizeof(other.native())); // prevent destruction
    }
  #endif

    ~NativeValueType() // non-virtual
    {
        adapter_type::finalize(native());
    }

public:
    NativeValueType& operator=(const NativeValueType& other)
    {
        adapter_type::copy(this->native(), other.native());
        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    NativeValueType& operator=(NativeValueType&& other) OMG_NOEXCEPT
    {
        NativeValueType tmp(std::move(other)); // steal other's contents
        swap(*this, tmp); // steal contents and let old ones be destroyed
        return *this;
    }
  #endif

    bool operator==(const NativeValueType& other) const
    {
        return adapter_type::equals(native(), other.native());
    }

    bool operator!=(const NativeValueType& other) const
    {
        return !adapter_type::equals(native(), other.native());
    }

public:
    native_type& native()
    {
        return native_value_;
    }

    const native_type& native() const
    {
        return native_value_;
    }

    void native(const native_type& value)
    {
        adapter_type::copy(native(), value);
    }

private:
    native_type native_value_;
};

template <typename T, typename NATIVE_T, typename ADAPTER>
void swap(
    NativeValueType<T, NATIVE_T, ADAPTER>& left,
    NativeValueType<T, NATIVE_T, ADAPTER>& right) OMG_NOEXCEPT
{
    // Swap by shallow-copying the C type
    typedef typename NativeValueType<T, NATIVE_T, ADAPTER>::native_type native_type;

    native_type tmp;
    memcpy(&tmp, &left, sizeof(native_type));
    memcpy(&left, &right, sizeof(native_type));
    memcpy(&right, &tmp, sizeof(native_type));
}

template <>
struct native_type_traits<dds::core::string> {
    typedef char* native_type;
};

namespace native_conversions {

// The following functions encapsulate a reinterpret_cast from the C type to its
// equivalent C++ type inheriting from NativeValueType. This is safer, because it
// will only compile if the C++ type and the C type are related via the
// native_type_traits.
template <typename T>
T& cast_from_native(typename native_type_traits<T>::native_type& value)
{
    return reinterpret_cast<T&>(value);
}

template <typename T>
const T& cast_from_native(const typename native_type_traits<T>::native_type& value)
{
    return reinterpret_cast<const T&>(value);
}

template <typename T>
T*& cast_from_native_ptr(typename native_type_traits<T>::native_type*& value)
{
    return reinterpret_cast<T*&>(value);
}

template <typename T>
const T*& cast_from_native_ptr(const typename native_type_traits<T>::native_type*& value)
{
    return reinterpret_cast<const T*&>(value);
}

// The following cast allows us ot convert from the rti DELEGATE to the  
// enclosing dds:: wrapper type 
template <typename DELEGATE>
typename DELEGATE::WrapperType& cast_from_delegate(DELEGATE& value)
{
    return reinterpret_cast<typename DELEGATE::WrapperType&>(value);
}

template <typename T, typename NativeSequence>
std::vector<T> sequence_to_vector(const NativeSequence& sequence)
{
    // This method requires that T has an implicit constructor from the type
    // of the sequence
    return std::vector<T>(
        sequence._contiguous_buffer,
        sequence._contiguous_buffer + sequence._length);
}

} // namespace native_conversions

} } // namespace rti::core

#define RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(T) \
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(T, rti::core::NativeValueType<T>)

#endif // RTI_DDS_CORE_NATIVE_TYPE_HPP_
