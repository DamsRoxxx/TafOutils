/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,07mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_DETAIL_SELF_REFERENCE_HPP_
#define RTI_DDS_CORE_DETAIL_SELF_REFERENCE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>
#include <dds/core/array.hpp>

namespace rti { namespace core { namespace detail {

/*
 * Inhibit the automatic destruction of a client object (of class T)
 * when all other shared pointers to that object disappear.
 */
template <class T>
class OMG_DDS_API SelfReference {
public:

    typedef typename dds::core::smart_ptr_traits<T>::ref_type ref_type;
    typedef typename dds::core::smart_ptr_traits<T>::weak_ref_type weak_ref_type;

    // set must be called after
    SelfReference() : retain_count_(0)
    {
    }

    SelfReference(ref_type shared_reference)
        : retain_count_(0), self_weak_ref_(shared_reference)
    {
    }

    // set the shared reference after default construction
    void set(ref_type shared_reference)
    {
        self_weak_ref_ = shared_reference;
        if (retain_count_ > 0) {
            // retain() can be called before set()
            //
            // Setting the shared_ptr can be done in a two-step construction
            // process. For example, when you create a DataWriter with a listener
            // the DW needs to be retained, but the self_reference hasn't been
            // set yet (by TDataWriter()).
            self_ref_ = self_weak_ref_.lock();
        }
    }

    ref_type lock()
    {
        return self_weak_ref_.lock();
    }

    // retain the object the reference points to. N calls to retain()
    // require N calls to unretain(), or one call to force_unretain()
    void retain()
    {
        if (!self_ref_) {
            self_ref_ = self_weak_ref_.lock();
        }

        retain_count_++;
    }

    // stop retaining the object the reference points to. N previous call to
    // retain() require N calls to unretain() to actually unretain the object.
    void unretain()
    {
        if (retain_count_ == 0) {
            return;
        }

        if (--retain_count_ == 0) {
            self_ref_.reset();
        }
    }

    // stop retaining the object the reference points to regardless of the
    // number of times retain() has been called
    void force_unretain()
    {
        self_ref_.reset();
        retain_count_ = 0;
    }

    int get_retain_count() {
        return retain_count_;
    }

    // access the weak reference directly
    weak_ref_type& weak_ref()
    {
        return self_weak_ref_;
    }

private:
    int retain_count_;
    weak_ref_type self_weak_ref_;
    ref_type self_ref_;
};

/*
 * A type ImplType can inherit from RetainableType<ImplType> to add support for
 * retaining its instances. ImplType should be the implementation type of
 * a reference type RefType that inherits from Reference<ImplType>. All the constructors
 * of RefType should call
 * RetainableType<ImplType>::remember_reference(RefType::delegate()).
 *
 * With that relationship, calls to ImplType::retain() will inhibit the
 * destruction of the instance of ImplType referenced by RefTypes even if
 * the reference count reaches zero (i.e. all RefTypes pointing to that ImplType
 * disappear). Calling unretain() will allow destroying again when needed.
 *
 * This is useful to keep weak references of ImplType inside the native C layer
 * and being able to recreate the appropriate RefType (the C++ type) when
 * looking up a native C instance.
 */
template <typename T, size_t MaxRetainReasonCount = 1>
class RetainableType {
public:
    typedef typename dds::core::smart_ptr_traits<T>::ref_type ref_type;
    typedef typename dds::core::smart_ptr_traits<T>::weak_ref_type weak_ref_type;

    RetainableType()
    {
        reset_reasons();
    }

    void retain(size_t reason_id = 0)
    {
        if (!retained_for_reason_[reason_id]) {
            self_reference_.retain();
            retained_for_reason_[reason_id] = true;
        }
    }

    void unretain(size_t reason_id = 0)
    {
        if (retained_for_reason_[reason_id]) {
            self_reference_.unretain();
            retained_for_reason_[reason_id] = false;
        }
    }

    void unretain_all()
    {
        self_reference_.force_unretain();
        reset_reasons();
    }

    void remember_reference(ref_type reference)
    {
        // Set the weak_ref in the self reference
        self_reference_.set(reference);
    }

    ref_type get_reference()
    {
        ref_type ref = self_reference_.lock();
        if (!ref) {
            throw dds::core::AlreadyClosedError("already closed");
        }

        return ref;
    }

    weak_ref_type& get_weak_reference()
    {
        return self_reference_.weak_ref();
    }

private:
    void reset_reasons()
    {
        std::fill(retained_for_reason_.begin(), retained_for_reason_.end(), false);
    }

    detail::SelfReference<T> self_reference_;
    dds::core::array<bool, MaxRetainReasonCount> retained_for_reason_;
};

} } } // namespace rti::core::detail

#endif // RTI_DDS_CORE_DETAIL_SELF_REFERENCE_HPP_

