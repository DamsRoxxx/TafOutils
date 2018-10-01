/*
 Copyright (c) 2013, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_POINTER_HPP_
#define RTI_DDS_CORE_POINTER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rtiboost/make_shared.hpp>

// DllExport.hpp should be the second include
#include <rti/core/DllExport.hpp>
#include <dds/core/Exception.hpp>

#if (defined(RTIUSERDllExport) || defined(NDDS_USER_DLL_EXPORT)) \
        && defined(RTI_NO_CXX11_SMART_PTR)
// To export an instantiation of shared_ptr<X>, shared count has to be exported
// as well
class UserDllExport rtiboost::detail::shared_count;
#endif

namespace rti { namespace core {

/**
 * Helper class for generated types that contain IDL pointers (an RTI extension)
 *
 * It wraps a loaned pointer and provides overloads of certain operators
 * to access the contents rather than the pointer. It never deep-copies or
 * deletes the underlying pointer.
 */
template <typename T>
class UserDllExport pointer {
public:

    /**
     * Initialize to NULL
     */
    pointer() OMG_NOEXCEPT
        : ptr_ (NULL)
    {
    }

    // implicit copy ctor and assignment operator shallow-copy the pointer
    //
    // pointer(const pointer&) = default;
    // pointer& operator=(const pointer&) = default;

    /**
     * Shallow-copy the pointer and allow automatic conversion from T *
     */
    pointer(T * ptr) OMG_NOEXCEPT
        : ptr_ (ptr)
    {
    }

    /**
     * Set the underlying pointer. This function
     * does not copy or delete, it just replaces this pointer.
     */
    void set(T * ptr) OMG_NOEXCEPT
    {
        ptr_ = ptr;
    }

    /**
     * Returns the underlying pointer
     */
    T * get() const OMG_NOEXCEPT
    {
        return ptr_;
    }


    /**
     * Assign another pointer replacing the current one
     */
    pointer<T>& operator= (T * other) OMG_NOEXCEPT
    {
        ptr_ = other;
        return *this;
    }


    /**
     * Deep equality comparison
     */
    bool operator ==(const pointer<T>& other) const
    {
        if (get() == other.get()) {
            return true; // Both are NULL or same address
        }

        if (get() == NULL || other.get() == NULL) {
            return false; // One is NULL and one isn't
        }

        return *get() == *other.get(); // both are set
    }

    /**
     * Deep inequality comparison
     */
    bool operator !=(const pointer<T>& other) const
    {
        return !(*this == other);
    }

    T& operator*() OMG_NOEXCEPT
    {
        return *ptr_;
    }

    const T& operator*() const OMG_NOEXCEPT
    {
        return *ptr_;
    }

    T* operator->() OMG_NOEXCEPT
    {
        return ptr_;
    }

    const T* operator->() const OMG_NOEXCEPT
    {
        return ptr_;
    }

    friend void swap(pointer& left, pointer& right) OMG_NOEXCEPT
    {
        std::swap(left.ptr_, right.ptr_);
    }

private:
    T * ptr_;
};

// Comparison to dds::core::null/nullptr
template <typename T>
bool operator ==(const pointer<T>& ptr, dds::core::null_type)
{
    return ptr.get() == NULL;
}

template <typename T>
bool operator ==(dds::core::null_type, const pointer<T>& ptr)
{
    return ptr.get() == NULL;
}

template <typename T>
bool operator !=(const pointer<T>& ptr, dds::core::null_type)
{
    return ptr.get() != NULL;
}

template <typename T>
bool operator !=(dds::core::null_type, const pointer<T>& ptr)
{
    return ptr.get() != NULL;
}

/**
 * Write pointer contents or the string "NULL"
 */
template<typename T>
std::ostream& operator <<(std::ostream& out, const pointer<T>& ptr)
{
    if (ptr != dds::core::null) {
        out << *ptr;
    } else {
        out << "NULL";
    }
    return out;
}

} }

#endif // RTI_DDS_CORE_POINTER_HPP_
