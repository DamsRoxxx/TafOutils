#ifndef OMG_DDS_CORE_EXTERNAL_HPP_
#define OMG_DDS_CORE_EXTERNAL_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Inc.
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

#include <dds/core/Value.hpp>
#include <rti/core/Pointer.hpp>
#ifndef RTI_NO_CXX11_SMART_PTR
#include <memory> // std::shared_ptr
#endif

namespace dds { namespace core {

template <typename T>
class external;

namespace detail {

template <typename T>
void make_locked(dds::core::external<T>& s);

template <typename T>
void make_shared(dds::core::external<T>& s);

// IDL-generated code uses this definition
#ifdef RTI_NO_CXX11_SMART_PTR
  using rtiboost::shared_ptr;
#else
  using std::shared_ptr;
#endif

}

/**
 * @ingroup DDSCPP2SupportingTypes
 * @headerfile dds/core/External.hpp
 *
 * @brief A managed reference to an object
 *
 * @tparam T The type of the object this \p external<T> manages
 *
 * Members of an \ref DDSTypesModule "IDL" type marked with the \p \@Shared or
 * \@external tag map to this C++ type. External members can share the same
 * object when publishing different data samples. This can make more
 * efficient the publication of large objects by saving extra copies.
 *
 * This class behaves like a \p std::shared_ptr, except when the object is in
 * "locked" state.
 *
 * Objects of this class created with any of the constructors documented here
 * behave like a \p std::shared_ptr<T>. Objects that the middleware returns in a
 * LoanedSample (for example, from \idref_FooDataReader_take) are in a "locked" state
 * and its contents can't be shared or modified. When assigning a sample with
 * locked external members into another one where those members are not locked,
 * the contents are copied, not shared. Modifying a locked object is not
 * allowed. This special behavior prevents applications from corrupting loaned
 * memory.
 *
 * @see DDSTypesModule
 */
template <typename T>
class UserDllExport external {
public:

  #ifdef RTI_NO_CXX11_SMART_PTR
    typedef rtiboost::shared_ptr<T> shared_ptr;
  #else
    /**
     * @ingroup DDSCPP2SupportingTypes
     *
     * @brief The smart pointer that external<T> uses.
     *
     * Selects \p std::shared_ptr if available when compiling or a boost
     * implementation otherwise.
     */
    typedef std::shared_ptr<T> shared_ptr;
  #endif

    /**
     * @brief Creates an empty shared object
     */
    external() OMG_NOEXCEPT
            : locked_(false)
    {
    }

    /**
     * @brief Creates a new shared object with the managed object \p p
     *
     * @param p The pointer to manage
     *
     * @param locked Should always be false except in objects created internally
     * by the middleware.
     */
    external(T* p, bool locked = false)
            : ptr_(p), locked_(locked)
    {
    }

    /**
     * @brief Creates an \p external instance that shares the managed object and
     * reference counting with an existing \p shared_ptr.
     *
     * This constructor is implicit to allow the direct usage of \p shared_ptr.
     *
     * For example:
     *
     * \code
     * shared_ptr<MyResource> resource(new MyResource);
     * // pass resource directly to a data-type with a my_resource external
     * // member whose setter expects an external<MyResource>.
     * sample1.my_resource(resource);
     * sample2.my_resource(resource);
     * // ...
     * writer.write(sample1);
     * writer.write(sample2);
     * \endcode
     */
    external(shared_ptr p)
            : ptr_(p), locked_(false)
    {
    }

    /**
     * @brief Creates a shared object from an existing shared object.
     *
     * In general, the new shared object shares ownership with \p other. Only
     * if \p other.is_locked(), then the new shared object is allocated and its
     * contents copied from \p other.
     *
     * @post if \p !other.is_locked(), then \p *this \p == \p other.
     * If \p other.is_locked, then *(*this) == *other but *this != other.
     *
     */
    external(const external& other)
            : ptr_(other.locked_ ? clone_ptr(other) : other.ptr_), locked_(false)
    {
    }

    /**
     * @brief Destroys the managed object if this is the last shared object
     * pointing to it.
     */
    ~external()
    {
        // ptr_'s destructor will do the right thing. If we locked it, it will
        // be destroyed because we have the only reference. Otherwise the
        // reference count will decrease.
    }

    /**
     * @brief Assigns another external, depending on the locked state
     *
     * Depending on whether \p this or \p other are locked the behavior varies:
     *
     * \li If \p this->is_locked() this operation throws \p dds::core::PreconditionNotMetError
     * \li If \p other.is_locked() it performs a deep copy of \p *other
     * \li In any other case, after the assignment, \p *this and \p other share the
     * same reference to the underlying object, that is, a \p shared_ptr
     * assignment.
     *
     * @throw dds::core::PreconditionNotMetError if this->is_locked()
     */
    external& operator=(const external& other)
    {
        if (is_locked()) {
            throw dds::core::PreconditionNotMetError(
                    "cannot copy to locked external<T> instance");
        }

        if (other.ptr_) {
            if (other.is_locked()) {
                // If other is locked, we can't share references,
                // we need to copy
                if (ptr_) {
                    // If this pointer is not null we copy its contents
                    *ptr_ = *other.ptr_;
                } else {
                    // If this pointer is null we need a new pointer with a
                    // copy of the contents
                    ptr_ = clone_ptr(other);
                }
            } else {
                // If none is locked, we just share the same reference
                ptr_ = other.ptr_;
            }
        } else {
            // If other is null, we just reset this. If we locked this pointer
            // it will be destroyed, since we must own the only reference.
            ptr_.reset();
        }

        return *this;
    }

    /**
     * @brief Obtains a reference to the managed object
     */
    T& operator*() OMG_NOEXCEPT
    {
        return *ptr_;
    }

    /**
     * @brief Obtains a const reference to the managed object
     */
    const T& operator*() const OMG_NOEXCEPT
    {
        return *ptr_;
    }

    /**
     * @brief Obtains a pointer to the managed  object
     *
     * @warning The returned pointer may become invalid if this is destroyed
     */
    T* get() OMG_NOEXCEPT
    {

        return ptr_.get();
    }

    /**
     * @brief Obtains a const pointer to the managed object
     *
     * @warning The returned pointer may become invalid if this is destroyed
     */
    const T* get() const OMG_NOEXCEPT
    {
        return ptr_.get();
    }

    /**
     * @brief Obtains a \p shared_ptr to the managed object
     *
     * The returned shared_ptr shares the same reference count.
     *
     * @throw dds::core::IllegalOperationError if \p is_locked().
     */
    shared_ptr get_shared_ptr()
    {
        if (locked_) {
            throw dds::core::IllegalOperationError(
                    "this shared object points to locked memory; "
                    "retrieving a shared_ptr is not allowed");
        }

        return ptr_;
    }

    /**
     * @brief Allows accessing members of the managed object
     */
    T* operator->() OMG_NOEXCEPT
    {
        return ptr_.get();
    }

    /**
     * @brief Allows accessing members of the managed object
     */
    const T* operator->() const OMG_NOEXCEPT
    {
        return ptr_.get();
    }

    /**
     * @brief Returns whether two shared objects manage the same object or
     * are both empty
     */
    bool operator==(const external<T>& other) const OMG_NOEXCEPT
    {
        return ptr_ == other.ptr_;
    }

    /**
     * @brief Returns whether two shared objects do not manage the same object
     */
    bool operator!=(const external<T>& other) const
    {
        return ptr_ != other.ptr_;
    }

    /**
     * @brief Checks if there is a managed object (is not null) or not (is null)
     */
    operator bool() const OMG_NOEXCEPT
    {
        return ptr_ ? true : false;
    }

    /**
     * @brief Indicates whether the managed object is locked or not.
     */
    bool is_locked() const
    {
        return locked_;
    }

    /**
     * @brief Swaps the managed objects and the locked state.
     */
    friend void swap(external<T>& a, external<T>& b) OMG_NOEXCEPT
    {
        std::swap(a.ptr_, b.ptr_);
        std::swap(a.locked_, b.locked_);
    }

private:
    static shared_ptr clone_ptr(const external<T>& other)
    {
        if (other.ptr_) {
            return shared_ptr(new T(*other.ptr_));
        } else {
            return shared_ptr();
        }
    }

    friend void detail::make_locked<T>(external<T>&);
    friend void detail::make_shared<T>(external<T>&);

    shared_ptr ptr_;
    bool locked_;
};

namespace detail {

// For internal use only
template <typename T>
void make_locked(dds::core::external<T>& s)
{
#ifdef RTI_NO_CXX11_SMART_PTR
    s.ptr_ = rtiboost::make_shared<T>();
#else
    s.ptr_ = std::make_shared<T>();
#endif

    s.locked_ = true;
}

// For internal use only
template <typename T>
void make_shared(dds::core::external<T>& s)
{
#ifdef RTI_NO_CXX11_SMART_PTR
    s.ptr_ = rtiboost::make_shared<T>();
#else
    s.ptr_ = std::make_shared<T>();
#endif

    s.locked_ = false;
}

}

template<typename T>
std::ostream& operator <<(std::ostream& out, const dds::core::external<T>& ptr)
{
    if (ptr) {
        out << *ptr;
    } else {
        out << "NULL";
    }
    return out;
}

} } // namespace dds::core

#endif // OMG_DDS_CORE_EXTERNAL_HPP_
