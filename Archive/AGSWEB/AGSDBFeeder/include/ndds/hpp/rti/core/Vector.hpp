/* $Id$
 (c) Copyright, Real-Time Innovations, 2014-2016.
 All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
--------------------
1.0a,21apr14,acr Created
============================================================================= */

#ifndef OMG_RTI_DDS_CORE_VECTOR_HPP_
#define OMG_RTI_DDS_CORE_VECTOR_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

// DllExport.hpp should be the second include
#include <rti/core/DllExport.hpp>

#include <memory>
#include <vector>
#include <stdexcept>

#include "osapi/osapi_type.h"
#include "osapi/osapi_heap.h"
#include "dds_c/dds_c_infrastructure.h" // for DDS_OctetSeq

#include <rti/core/array.hpp> // for operator<<

#include <rti/util/util.hpp>
#include <rti/core/VectorIterator.hpp>

/** @RTI_namespace_start dds::core */
namespace rti { namespace core {

// Encapsulates the a native DDS_OctectSeq and provides default initialization
// (no memory allocation) and access to it as a typed buffer
template <typename T>
class NativeSequenceWrapper {
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

protected:
    // We need the same memory layout as native sequences. All native sequences
    // have the same layout so we just pick one: DDS_OctetSeq.
    typedef DDS_OctetSeq NativeSeq;

    NativeSequenceWrapper()
    {
        set_default();
    }

    void set_default()
    {
        // Initializes a default, empty DDS_OctetSeq
        static const NativeSeq DEFAULT = DDS_SEQUENCE_INITIALIZER;
        seq_ = DEFAULT;
    }

    void swap(NativeSequenceWrapper& other) OMG_NOEXCEPT
    {
        using std::swap;

        swap(seq_, other.seq_); // shallow assignment
    }

    inline value_type*& get_buffer()
    {
        return reinterpret_cast<value_type*&>(seq_._contiguous_buffer);
    }

    inline value_type * get_buffer() const
    {
        return reinterpret_cast<value_type*>(seq_._contiguous_buffer);
    }


    inline size_type get_maximum() const
    {
        return seq_._maximum;
    }

    inline size_type get_length() const
    {
        return seq_._length;
    }

    void set_length(size_type the_length)
    {
        seq_._length = rti::util::cast_length(the_length);
    }

    void set_maximum(size_type the_maximum)
    {
        seq_._maximum = rti::util::cast_length(the_maximum);
    }

    inline value_type* get_end_of_contents() const
    {
        return get_buffer() + get_length();
    }

    inline value_type* get_end_of_storage() const
    {
        return get_buffer() + get_maximum();
    }

    reference get_reference(size_type i)
    {
        return get_buffer()[i];
    }

    const_reference get_reference(size_type i) const
    {
        return get_buffer()[i];
    }

    // This class's only data member must be a native DDS sequence
    NativeSeq seq_;
};

// Wraps a native sequence and prov
// Manages memory, but doesn't initialize elements
template <typename T>
class SequenceBase : public NativeSequenceWrapper<T> {
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
protected:
    typedef DDS_OctetSeq NativeSeq;

    SequenceBase()
    {
        // The base class constructor initializes the sequence
    }

    SequenceBase(size_type initial_capacity)
    {
        // The base class constructor initializes the sequence
        realloc_buffer(initial_capacity);
    }

    ~SequenceBase()
    {
        free_buffer();
    }

    void realloc_buffer(size_type capacity)
    {
        if (capacity > 0) {
            if (!RTIOsapiHeap_allocateArray(&this->get_buffer(), capacity, T)) {
                throw std::bad_alloc();
            }
            this->set_maximum(capacity);
        } else {
            free_buffer();
        }
    }

    void free_buffer()
    {
        if (this->get_buffer() != NULL) {
            RTIOsapiHeap_freeArray(this->get_buffer());
            this->set_default();
        }
    }
};

template <typename T>
void destroy(T * first, T * last)
{
    for (; first != last; ++first) {
       first->~T();
    }
}

/**
 * @ingroup DDSCPP2SupportingTypes
 * @headerfile dds/core/vector.hpp
 * @RTI_class_definition template <typename T> class vector
 *
 * @brief @st_value_type A vector convertible to std::vector and with similar
 * functionality
 *
 * In many cases, for performance reasons and other implementation requirements,
 * the \ndds API uses dds::core::vector instead of std::vector. The most
 * significant case is the C++ types that \ref DDSNddsgenModule generates from
 * \ref DDSTypesModule "IDL".
 *
 * A dds::core::vector provides a subset of the functionality of a \p std::vector,
 * including iterators, resizing and indexed access. It also provides automatic
 * conversion to and from std::vector, making code like the following possible:
 *
 * @code
 *   // IDL-generated type
 *   class Foo {
 *   public:
 *       // ...
 *       const dds::core::vector<int32_t>& my_ints() const;
 *   };
 *
 *   // Application
 *   Foo sample = ...;
 *   dds::vector<int32_t> my_std_vector = sample.my_ints(); // conversion to std::vector
 *   // ...
 *   sample.my_ints() = my_std_vector; // conversion from std::vector
 * @endcode
 */
template <typename T>
class UserDllExport vector : public SequenceBase<T> {
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

    typedef VectorIterator<T*> iterator;
    typedef VectorIterator<const T*> const_iterator;

    typedef typename iterator::iterator_category iterator_category;
    typedef typename iterator::difference_type difference_type;
    typedef typename iterator::pointer pointer;

protected:
    typedef SequenceBase<T> Base;

    using Base::get_buffer;
    using Base::get_end_of_storage;
    using Base::get_end_of_contents;

public:
    /**
     * @brief Creates an empty vector
     */
    vector()
    {
    }

    /**
     * @brief Creates a vector with a number of default-constructed elements
     */
    explicit vector(size_type initial_size) : Base (initial_size)
    {
        std::uninitialized_fill(
            this->get_buffer(), this->get_end_of_storage(), T());
        this->set_length(initial_size);
    }

    /**
     * @brief Creates a vector with a number of copies of a value
     */
    vector(size_type initial_size, const T& value) : Base(initial_size)
    {
        std::uninitialized_fill(get_buffer(), get_end_of_storage(), value);
        this->set_length(initial_size);
    }

    /**
     * @brief Creates a copy
     */
    vector(const vector& other) : Base(other.capacity())
    {
        this->set_length(other.size());
        if (other.size() != 0) {
            std::uninitialized_copy(
                other.get_buffer(), other.get_end_of_contents(), get_buffer());
            std::uninitialized_fill(
                get_end_of_contents(), get_end_of_storage(), T());
        }
    }

    /**
     * @brief Implicit construction from std::vector
     *
     * Note: this operation makes a copy of all the elements in \p other
     */
    vector(const std::vector<T>& other) : Base (other.size())
    {
        if (other.size() != 0) {
            std::uninitialized_copy(other.begin(), other.end(), get_buffer());
        }
        this->set_length(other.size());
    }


  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief Creates a vector by moving an existing one
     */
    vector(vector&& other) OMG_NOEXCEPT
        : SequenceBase<T>() // base ctor doesn't allocate, it initializes to 0
    {
        this->swap(other); // swap empty *this with contents of other
    }
  #endif

    ~vector()
    {
        if (get_buffer() != 0) {
            destroy(get_buffer(), get_end_of_storage());
        }
    }

    /**
     * @brief Provides a conversion to std::vector
     *
     * Note: this operation makes a copy of all the elements in this vector
     */
    operator std::vector<T>() const
    {
        std::vector<T> std_vector;
        std_vector.reserve(size());
        std::copy(begin(), end(), std::back_inserter(std_vector));
        return std_vector;
    }

    /** 
     * @brief Get the current size
     */
    size_type size() const
    {
        return this->get_length();
    }

    /**
     * @brief Get the current capacity
     */
    size_type capacity() const
    {
        return this->get_maximum();
    }

    /**
     * @brief Set the size to new_size
     */
    void resize(size_type new_size)
    {
        this->resize(new_size, value_type());
    }

    /**
     * @brief Set the size to new_size, copying value if new elements are added
     */
    void resize(size_type new_size, const T& value)
    {
        if (new_size == size()) {
            return; // Nothing to do
        }

        if (new_size > size()) {
            if (new_size > capacity()) { // Need to reallocate
                vector tmp (*this, new_size);
                std::fill(
                    tmp.get_end_of_contents(), tmp.get_end_of_storage(), value);
                tmp.set_length(new_size);
                this->swap(tmp);
            } else { // Can use existing storage
                std::fill_n(
                    get_end_of_contents(), new_size - size(), value);
                this->set_length(new_size);
            }
        } else { // Need to destroy extra elements
            this->set_length(new_size);
        }
    }

    /**
     * @brief Resize to zero
     */
    void clear()
    {
        if (get_buffer() != NULL) {
            this->set_length(0);
        }
    }

    /**
     * @brief Reserve a new capacity without creating any elements or changing the size
     */
    void reserve(size_type new_capacity)
    {
        if (new_capacity > capacity()) {
            vector<T> tmp (*this, new_capacity);
            this->swap(tmp);
        }
    }

    /**
     * @brief Get an element by reference and check bounds
     * @throws std::out_of_range if \p i is out of bounds
     */
    reference at(size_type i)
    {
        if (i >= size()) {
            throw std::out_of_range("dds::core::vector::at()");
        }
        return this->get_reference(i);
    }

    /**
     * @brief Get an element by const-reference and check bounds
     * @throws std::out_of_range if \p i is out of bounds
     */
    const_reference at(size_type i) const
    {
        if (i >= size()) {
            throw std::out_of_range("dds::core::vector::at()");
        }
        return this->get_reference(i);
    }

    /**
     * @brief Get an element by reference
     */
    reference operator[] (size_type i)
    {
        return this->get_reference(i);
    }

    /**
     * @brief Get an element by const-reference
     */
    const_reference operator[] (size_type i) const
    {
        return this->get_reference(i);
    }

    /**
     * @brief Assign another vector to this one
     */
    vector& operator=(const vector& other)
    {
        // This implementation is simple and strongly exception safe,
        // but could be more efficient when this has enough space to
        // copy other
        vector tmp (other);
        this->swap(tmp);
        return *this;
    }

    #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief Move-assign another vector to this one
     */
    vector& operator=(vector&& other) OMG_NOEXCEPT
    {
        vector tmp(std::move(other));
        this->swap(tmp);
        return *this;
    }
    #endif

    /**
     * @brief Returns if the elements of two vectors are equal
     *
     */
    bool operator==(const vector& other) const
    {
        if (size() == other.size()) {
            if (size() != 0) {
                return std::equal(
                    get_buffer(), get_end_of_contents(), other.get_buffer());
            }
            return true;
        }

        return false;
    }

    /**
     * @brief Returns if two vectors are different
     */
    bool operator!=(const vector& other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Iterator to the first element
     */
    iterator begin()
    {
        return iterator(get_buffer());
    }

    /**
     * @brief Const iterator to first element
     */
    const_iterator begin() const
    {
        return const_iterator(get_buffer());
    }

    /**
     * @brief Iterator to last element plus one
     */
    iterator end()
    {
        return iterator(get_end_of_contents());
    }

    /**
     * @brief Const iterator to last element plus one
     */
    const_iterator end() const
    {
        return const_iterator(get_end_of_contents());
    }

    /**
     * @brief Efficiently swaps the contents of two vectors
     */
    friend void swap(vector& left, vector& right) OMG_NOEXCEPT
    {
        left.swap(right); // call vector's base-class swap
    }

private:
    // Creates a vector copying the contents from another vector but allocates
    // a larger buffer for additional capacity.
    vector(const vector& other, size_type the_capacity)
        : Base(other.size() > the_capacity ? other.size() : the_capacity)
    {
        // Copy contents from other vector
        if (other.size() != 0) {
            std::uninitialized_copy(
                other.get_buffer(), other.get_end_of_contents(), get_buffer());
        }
        this->set_length(other.size());

        std::uninitialized_fill(
            get_end_of_contents(), get_end_of_storage(), T());
    }
};

/**
 * @relatesalso dds::core::vector
 * @brief Print a vector applying \p << to all of its elements
 */
template<typename T>
std::ostream& operator <<(std::ostream& out, const vector<T>& v)
{
    typedef typename vector<T>::const_iterator iterator;

    out << "{";
    iterator it;
    for (it = v.begin(); it != v.end();) {
        out << *it;
        ++it;

        if (it != v.end()) {
            out << ", ";
        }
    }

    out << "}";

    return out;
}


} } // namespace rti::core

#endif // OMG_RTI_DDS_CORE_VECTOR_HPP_
