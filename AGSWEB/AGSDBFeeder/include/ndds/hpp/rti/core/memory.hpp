/* $Id$
 (c) Copyright, Real-Time Innovations, 2014-2016.
 All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
--------------------
1.0,30may14,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_MEMORY_HPP_
#define RTI_DDS_CORE_MEMORY_HPP_

#ifdef RTI_CXX11_RVALUE_REFERENCES
#include <utility> // for std::forward
#endif

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "osapi/osapi_heap.h"
#include <dds/core/ref_traits.hpp> // for shared pointers

namespace rti { namespace core { namespace memory {

template <typename T>
struct OsapiAllocator {
    /**
     *  Allocates an object of type T on the heap using RTI internal OSAPI
     *  it throws std::bad_alloc if allocation fails
     */
    static T * allocate()
    {
        T * object = NULL;

        RTIOsapiHeap_allocateStructure(&object, T);
        if (object == NULL) {
            throw std::bad_alloc();
        }

        return object;
    }

    static T * allocate_array(size_t size)
    {
        T * array = NULL;

        RTIOsapiHeap_allocateArray(&array, size, T);
        if (array == NULL) {
            throw std::bad_alloc();
        }

        return array;
    }

    static void release(void * object)
    {
        RTIOsapiHeap_freeStructure(object);
    }
};

template <typename T, typename Allocator = OsapiAllocator<T> >
struct ObjectAllocator {
    typedef rtiboost::shared_ptr<T> shared_ptr;

    static T * create()
    {
        T * object = Allocator::allocate();
        try {
            new (object) T(); // In-place construction
        } catch (...) {
            Allocator::release(object);
            throw;
        }

        return object;
    }

    static shared_ptr make_shared()
    {
        return shared_ptr(create(), destroy);
    }

    static T * create(const T& arg)
    {
        T * object = Allocator::allocate();
        try {
            new (object) T(arg); // In-place construction
        } catch (...) {
            Allocator::release(object);
            throw;
        }

        return object;
    }

    static shared_ptr make_shared(const T& arg)
    {
        return shared_ptr(create(arg), destroy);
    }

    #ifdef RTI_CXX11_RVALUE_REFERENCES
    static T * create(T&& arg)
    {
        T * object = Allocator::allocate();
        try {
            new (object) T(std::forward<T>(arg)); // In-place construction
        } catch (...) {
            Allocator::release(object);
            throw;
        }

        return object;
    }

    static shared_ptr make_shared(T&& arg)
    {
        return shared_ptr(create(std::forward<T>(arg)), destroy);
    }
    #endif

    static void destroy(T * object)
    {
        if (object != NULL) {
            object->~T();
            Allocator::release(object);
        }
    }
};


} } } // namespace rti::core::memory

#endif // RTI_DDS_CORE_MEMORY_HPP_
