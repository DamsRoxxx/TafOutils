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

#ifndef OMG_RTI_DDS_BOUNDED_SEQUENCE_HPP_
#define OMG_RTI_DDS_BOUNDED_SEQUENCE_HPP_

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

namespace rti { namespace core {

namespace detail {

// This is the function used in bounded_sequence<T>::resize() to initialize
// new members when the sequence grows. Since this members may have already
// been created because the bounded_sequence's underlying vector can preallocate
// them, we need to assign the default value T().
//
// However, in some STL implementations, the assignment of a std::string default
// doesn't behave like the assignment of the literal "":
//
// std::string s;
// s.reserve(100);
//
// s = ""; // s.capacity() == 100
// s = std::string(); // s.capacity() == 0 (!)
//
// For that reason we need to specialize this assignment for std::string to use
// the literal.
template <typename T>
struct initialize_impl {
    template <typename Iter>
    static void init(Iter begin, Iter end)
    {
        std::fill(begin, end, T());
    }
};

template <>
struct initialize_impl<std::string> {
    template <typename Iter>
    static void init(Iter begin, Iter end)
    {
        std::fill(begin, end, "");
    }
};

} // namespace detail

/**
 * @ingroup DDSCPP2SupportingTypes
 * @headerfile rti/core/BoundedSequence.hpp
 *
 * @brief @st_value_type A bounded sequence of elements
 *
 * @tparam T The element type
 * @tparam MaxLength The maximum number of elements
 *
 * IDL bounded sequences map to this type, as described in \ref DDSTypesModule.
 *
 * This type has a interface similar to std::vector, but it differs in two aspects:
 *
 * \li It enforces its bound, \p MaxLength, in its operations. Operations that would make the
 * sequence grow beyond the limit throw \p dds::core::PreconditionNotMetError.
 *
 * \li it implements a different element life-cycle strategy that
 * optimizes the performance of the internal dds::sub::DataReader and
 * dds::pub::DataWriter serialization operations. Just like a std::vector, a bounded_sequence
 * has a size and a capacity. But when capacity > size, the extra elements are
 * default-constructed, unlike a std::vector where the extra elements are
 * uninitialized memory. Functions that reduce the size of the sequence do not
 * destroy the elements that they remove. Only shrink_to_fit() does.
 *
 * @see DDSTypesModule.
 */
template <typename T, size_t MaxLength>
class UserDllExport bounded_sequence {
public:
    /**
     * @brief The type of the underlying vector
     */
    typedef std::vector<T> vector_type;
    /**
     * @brief The type of the elements, \p T
     */
    typedef typename vector_type::value_type value_type;
    /**
     * @brief The allocator type of the underlying vector
     */
    typedef typename vector_type::allocator_type allocator_type;

    /**
     * @brief The size type
     */
    typedef typename vector_type::size_type size_type;
    /**
     * @brief The difference type
     */
    typedef typename vector_type::difference_type difference_type;
    /**
     * @brief The reference type
     */
    typedef typename vector_type::reference reference;
    /**
     * @brief The const reference type
     */
    typedef typename vector_type::const_reference const_reference;
    /**
     * @brief The pointer type
     */
    typedef typename vector_type::pointer pointer;
    /**
     * @brief The const pointer type
     */
    typedef typename vector_type::const_pointer const_pointer;
    /**
     * @brief The iterator type
     */
    typedef typename vector_type::iterator iterator;
    /**
     * @brief The const iterator type
     */
    typedef typename vector_type::const_iterator const_iterator;
    /**
     * @brief The reverse iterator type
     */
    typedef typename vector_type::reverse_iterator reverse_iterator;
    /**
     * @brief The const reverse iterator type
     */
    typedef typename vector_type::const_reverse_iterator const_reverse_iterator;

    /**
     * @brief Creates an empty bounded_sequence
     */
    bounded_sequence() : size_(0)
    {
    }

    /**
     * @brief Copy constructor
     */
    bounded_sequence(const bounded_sequence& other)
        : v_(other.begin(), other.end()), size_(other.size_)
    {
        // Note: other.size() must be <= MaxLength
    }

    /**
     * @brief Copies a bounded sequence with a different bound \p M
     *
     * @throw dds::core::PreconditionNotMetError if other.size() > MaxLength
     */
    template <size_t M>
    explicit bounded_sequence(const bounded_sequence<T, M>& other)
            : v_((check_size(other.size()), other.begin()), other.end()),
              size_(other.size())
    {
    }

    /**
     * @brief Create a bounded_sequence with a number of default-construced elements
     */
    bounded_sequence(size_type count) : v_(count), size_(count)
    {
        check_size(count);
    }

    /**
     * @brief Create a bounded_sequence with a number of elements
     */
    bounded_sequence(size_type count, const value_type& value)
        : v_(count <= MaxLength ? count : 0, value), size_(count)
    {
        check_size(count); // throw exception if count > MaxLength
    }

    /**
     * @brief Create a bounded_sequence from a range of elements
     */
    template <typename InputIt>
    bounded_sequence(InputIt first, InputIt last)
        : v_(first, last)
    {
        check_size(v_.size());
        size_ = v_.size();
    }

    /**
     * @brief Create a bounded_sequence copying the elements of a std::vector
     *
     * @throw dds::core::PreconditionNotMetError if v.size() > MaxLength
     */
    bounded_sequence(const std::vector<T>& v)
        : v_((check_size(v.size()), v)), size_(v.size())
    {
    }

#ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Move constructor
     */
    bounded_sequence(bounded_sequence&& other) OMG_NOEXCEPT
            : v_(std::move(other.v_)), size_(other.size_)
    {
    }

    /**
     * @brief @st_cpp11 Creates a bounded_sequence by moving a std::vector
     */
    bounded_sequence(std::vector<T>&& v)
        : v_((check_size(v.size()), std::move(v))), size_(v_.size())
    {
    }
#endif

    /**
     * @brief Assignment operator
     */
    bounded_sequence& operator=(const bounded_sequence& other)
    {
        resize_uninitialized(other.size());
        std::copy(other.begin(), other.end(), begin());
        return *this;
    }

    /**
     * @brief Copies the elements of a sequence with a different bound
     *
     * @throw dds::core::PreconditionNotMetError if other.size() > MaxLength
     */
    template <typename U, size_t M>
    bounded_sequence& operator=(const bounded_sequence<U, M>& other)
    {
        resize_uninitialized(other.size()); // will throw if other.size() > MaxLength
        // U must be convertible to T, else this won't compile
        std::copy(other.begin(), other.end(), begin());
        return *this;
    }

    /**
     * @brief Copies the elements of a std::vector
     */
    bounded_sequence& operator=(const std::vector<T>& v)
    {
        resize_uninitialized(v.size());
        std::copy(v.begin(), v.end(), begin());
        return *this;
    }

#ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Move-assignment operator
     */
    bounded_sequence& operator=(bounded_sequence&& other) OMG_NOEXCEPT
    {
        using std::swap;

        bounded_sequence tmp(std::move(other)); // steal other's contents
        swap(*this, tmp);// steal contents and let old ones be destroyed
        return *this;
    }

    /**
     * @brief @st_cpp11 Moves a std::vector into this bounded_sequence
     */
    bounded_sequence& operator=(std::vector<T>&& v)
    {
        using std::swap;

        check_size(v.size());
        size_ = v.size();
        v_ = std::move(v);
        return *this;
    }
#endif

    /**
     * @brief Index access
     */
    reference operator[](size_type pos)
    {
        return v_[pos];
    }

    /**
     * @brief Index access
     */
    const_reference operator[](size_type pos) const
    {
        return v_[pos];
    }

    /**
     * @brief Index access with bounds check
     *
     * @throws std::out_of_range if pos is >= size()
     */
    reference at(size_type pos)
    {
        if (pos >= size_) {
            throw std::out_of_range("bounded_sequence::at(): out of range");
        }
        return v_[pos];
    }

    /**
     * @brief Index access with bounds check
     *
     * @throws std::out_of_range if pos is >= size()
     */
    const_reference at(size_type pos) const
    {
        if (pos >= size_) {
            throw std::out_of_range("bounded_sequence::at(): out of range");
        }
        return v_[pos];
    }

    /**
     * @brief Returns a reference to the first element
     */
    reference front()
    {
        return *begin();
    }

    /**
     * @brief Returns a const reference to the first element
     */
    const_reference front() const
    {
        return *begin();
    }

    /**
     * @brief Returns a reference to the last element
     */
    reference back()
    {
        iterator tmp = end();
        --tmp;
        return *tmp;
    }

    /**
     * @brief Returns a const reference to the last element
     */
    const_reference back() const
    {
        const_iterator tmp = end();
        --tmp;
        return *tmp;
    }

    /**
     * @brief Returns a pointer to the underlying data buffer
     */
    pointer data()
    {
        return &v_[0];
    }

    /**
     * @brief Returns a pointer to the underlying data buffer
     */
    const_pointer data() const
    {
        return &v_[0];
    }

    /**
     * @brief Returns an iterator to the first element
     */
    iterator begin() OMG_NOEXCEPT
    {
        return v_.begin();
    }

    /**
     * @brief Returns an const iterator to the first element
     */
    const_iterator begin() const OMG_NOEXCEPT
    {
        return v_.begin();
    }

    /**
     * @brief Returns an const iterator to the first element
     */
    const_iterator cbegin() const OMG_NOEXCEPT
    {
        return begin();
    }

    /**
     * @brief Returns an iterator to one past the last element
     */
    iterator end() OMG_NOEXCEPT
    {
        return v_.begin() + size_;
    }

    /**
     * @brief Returns an const iterator to one past the last element
     */
    const_iterator end() const OMG_NOEXCEPT
    {
        return v_.begin() + size_;
    }

    /**
     * @brief Returns a const iterator to one past the last element
     */
    const_iterator cend() const OMG_NOEXCEPT
    {
        return end();
    }

    /**
     * @brief Returns an iterator to the reverse-beginning of the sequence
     */
    reverse_iterator rbegin() OMG_NOEXCEPT
    {
        return reverse_iterator(end());
    }

    /**
     * @brief Returns a const iterator to the reverse-beginning of the sequence
     */
    const_reverse_iterator rbegin() const OMG_NOEXCEPT
    {
        return const_reverse_iterator(end());
    }

    /**
     * @brief Returns a const iterator to the reverse-beginning of the sequence
     */
    const_reverse_iterator crbegin() const OMG_NOEXCEPT
    {
        return rbegin();
    }

    /**
     * @brief Returns an iterator to the reverse-end of the sequence
     */
    reverse_iterator rend() OMG_NOEXCEPT
    {
        return v_.rend();
    }

    const_reverse_iterator rend() const OMG_NOEXCEPT
    {
        return v_.rend();
    }

    /**
     * @brief Returns a const iterator to the reverse-end of the sequence
     */
    const_reverse_iterator crend() const OMG_NOEXCEPT
    {
        return rend();
    }

    /**
     * @brief Returns whether there are no elements
     */
    bool empty() const OMG_NOEXCEPT
    {
        return size_ == 0;
    }

    /**
     * @brief Returns the number of elements
     */
    size_type size() const OMG_NOEXCEPT
    {
        return size_;
    }

    /**
     * @brief Returns \p MaxLength
     */
    size_type max_size() const OMG_NOEXCEPT
    {
        return MaxLength;
    }

    /**
     * @brief Pre-allocates elements up to new_capacity
     *
     * This operation reserves space for \p new_capacity elements and, unlike
     * std::vector, it also default-constructs the extra elements.
     * The size() remains the same.
     *
     */
    void reserve(size_type new_capacity)
    {
        // bounded_sequence::reserve() does more than vector::reserve(). It does
        // also construct the additional objects
        if (new_capacity > v_.size()) {
            v_.resize(new_capacity);
        }
    }

    /**
     * @brief Returns the current capacity
     *
     * @see reserve()
     */
    size_type capacity() const OMG_NOEXCEPT
    {
        return v_.size();
    }

    /**
     * @brief Removes the elements
     *
     * This operation resizes the sequence to 0, but it doesn't destroy the
     * elements, like std::vector would.
     *
     * To destroy the elements, follow with a call to shrink_to_fit.
     *
     */
    void clear() OMG_NOEXCEPT
    {
        size_ = 0;
    }


    /**
     * @brief Destroys any extra elements reserved above the current size
     *
     * Note that resize() or clear() alone won't destroy the extra elements when
     * they reduce the size of a sequence.
     *
     * For example
     * \code
     * bounded_sequence<Foo, 20> s;
     * s.resize(10); // 10 elements
     * s.resize(4);  // size is now 4, but the other 6 elements are not destroyed
     * s.shrink_to_fit(); // size is 4, and the other 6 elements are destroyed
     * \endcode
     */
    void shrink_to_fit()
    {
        v_.resize(size_);
        // TODO: also call v_.shrink_to_fit()
    }

    /**
     * @brief Inserts a new element in a position specified by an iterator
     *
     * @throw dds::core::PreconditionNotMetError if size() == MaxLength
     */
    iterator insert(iterator pos, const T& value)
    {
        if (size_ == v_.size()) {
            // v_ doesn't have extra space: insert if we can
            check_size(size_ + 1);
            pos = v_.insert(pos, value);
        } else {
            // v_ has extra space: move elements to the right make space for one
            // more where pos was. Now pos points to the inserted object.
            std::copy_backward(pos, end(), end() + 1);
            *pos = value;
        }
        size_++;
        return pos;
    }

    /**
     * @brief Erases an element specified by an iterator
     */
    iterator erase(iterator pos)
    {
        iterator next = pos;
        ++next;
        std::copy(next, end(), pos); // move elements one to the left
        --size_;
        return pos;
    }

    /**
     * @brief Adds a new element at the end
     *
     * @throw dds::core::PreconditionNotMetError if size() == MaxLength
     */
    void push_back(const T& value)
    {
        if (size_ == v_.size()) {
            check_size(size_ + 1);
            v_.push_back(value);
        } else { // v_ has more elements; end() is a valid element in v_
            *end() = value;
        }
        size_++;
    }

#ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief Adds a new element at the end by moving it
     *
     * @throw dds::core::PreconditionNotMetError if size() == MaxLength
     */
    void push_back(T&& value)
    {
        if (size_ == v_.size()) {
            check_size(size_ + 1);
            v_.push_back(std::move(value));
        } else { // v_ has more elements; end() is a valid element in v_
            *end() = std::move(value);
        }
        size_++;
    }
#endif

    /**
     * @brief Removes the last element
     *
     * The element removed is not destroyed. To destroy it, follow pop_back
     * with a call to shrink_to_fit.
     */
    void pop_back()
    {
        if (size_ == 0) {
            return;
        }
        size_--;
    }

    /**
     * @brief Resizes the container to contain count elements.
     *
     * If count < size(), the sequence is reduced to the first count elements,
     * but elements are not destroyed.
     *
     * If count > size(), the sequence is expanded as follows: if capacity() >= count,
     * new elements are not constructed, since they already had been.
     * If capacity() < count, the extra elements are default-constructed.
     *
     * @throw dds::core::PreconditionNotMetError if count > MaxLength
     */
    void resize(size_type count)
    {
        // Note: this is more efficient than just calling
        // resize(count, T()), because we save the construction of one T if
        // we don't need to expand the collection.
        size_type size_before = resize_uninitialized(count);
        if (count > size_before) {
            iterator end_before = begin() + size_before;
            // Calls fill(end_before, end(), <default value>)
            detail::initialize_impl<T>::init(end_before, end());
        }
    }

    /**
     * @brief Resizes the container to contain count elements.
     *
     * This overload specifies the value.
     */
    void resize(size_type count, const T& value)
    {
        size_type size_before = resize_uninitialized(count);
        if (count > size_before) {
            iterator end_before = begin() + size_before;
            // Calls fill(end_before, end(), <default value>)
            std::fill(end_before, end(), value);
        }
    }

    /**
     * @brief Swap the contents of two sequences
     */
    void swap(bounded_sequence& other) OMG_NOEXCEPT
    {
        using std::swap;

        v_.swap(other.v_);
        swap(size_, other.size_);
    }


    // for internal use: it leaves the new elements uninitialized, so any new
    // elements between size_before...size_ may contain values from objects
    // before this sequence shrunk. For example:
    //
    // bounded_sequence<int, 10> s;
    // s.push_back(1);
    // s.push_back(2);
    // s.push_back(3); // s = {1, 2, 3}
    // s.resize(1); // s = {1}
    // s.resize_uninitialized(2); // s = {1, 2} (watch out!)
    // s.resize(1); // s = {1}
    // s.resize(3); // s = {1, 0, 0} (good)
    size_type resize_uninitialized(size_type count)
    {
        check_size(count);
        size_type size_before = size_;
        reserve(count);
        size_ = count;
        return size_before;
    }

private:

    static void check_size(size_t new_size)
    {
        if (new_size > MaxLength) {
            throw dds::core::PreconditionNotMetError(
                    "bounded_sequence would go over its MaxLength");
        }
    }



    // member variables

    // The underlying std::vector.
    //
    // It stores the existing elements (v_[0]...v[size_ - 1]), plus extra
    // storage for additional elements (v_[size_]...v_[capacity() - 1], where
    // capacity() == v_.size() >= size_.
    //
    // Memory from v_[size_]...v[capacity() - 1] is not only reserved, but,
    // unlike a regular vector, the elements are also initialized. The memory
    // of a vector from its size to its capacity is reserved, but not
    // initialized. If the element type T is a complex type, with strings,
    // other sequences etc, pre-allocating and pre-initializing them is critical
    // for high performance.
    //
    vector_type v_;
    size_t size_; // is always <= v_.size()
};

template <typename T, size_t M>
void swap(bounded_sequence<T, M>& lhs, bounded_sequence<T, M>& rhs) OMG_NOEXCEPT
{
    lhs.swap(rhs);
}

template<typename T, size_t N, size_t M>
bool operator==(
        const bounded_sequence<T, N>& lhs,
        const bounded_sequence<T, M>& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, size_t N, size_t M>
bool operator!=(
        const bounded_sequence<T, N>& lhs,
        const bounded_sequence<T, M>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, size_t N, size_t M>
bool operator<(
        const bounded_sequence<T, N>& lhs,
        const bounded_sequence<T, M>& rhs)
{
    return std::lexicographical_compare(
            lhs.begin(),
            lhs.end(),
            rhs.begin(),
            rhs.end());
}

template<typename T, size_t N, size_t M>
bool operator<=(
        const bounded_sequence<T, N>& lhs,
        const bounded_sequence<T, M>& rhs)
{
    return lhs < rhs || lhs == rhs;
}

template<typename T, size_t N, size_t M>
bool operator>(
        const bounded_sequence<T, N>& lhs,
        const bounded_sequence<T, M>& rhs)
{
    return !(lhs <= rhs);
}

template<typename T, size_t N, size_t M>
bool operator>=(
        const bounded_sequence<T, N>& lhs,
        const bounded_sequence<T, M>& rhs)
{
    return !(lhs < rhs);
}

/**
 * @relatesalso dds::core::vector
 * @brief Print a vector applying \p << to all of its elements
 */
template<typename T, size_t N>
std::ostream& operator <<(std::ostream& out, const bounded_sequence<T, N>& v)
{
    typedef typename bounded_sequence<T, N>::const_iterator iterator;

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


#endif // OMG_RTI_DDS_BOUNDED_SEQUENCE_HPP_
