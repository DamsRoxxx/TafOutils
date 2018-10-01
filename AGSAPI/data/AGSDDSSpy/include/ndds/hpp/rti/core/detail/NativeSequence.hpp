/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,22jan13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_DETAIL_SEQUENCE_HPP_
#define RTI_DDS_CORE_DETAIL_SEQUENCE_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>
#include <dds/core/detail/inttypes.hpp>

#include "ndds/ndds_c.h"

/*
 * This macro defines a specialization of native_sequence_traits for a given
 * native sequence type SEQ_TYPE, containing elements of TYPE
 */
#define RTI_DEFINE_SEQUENCE_TRAITS(TYPE, SEQ_TYPE)                             \
template <>                                                                    \
class native_sequence_traits<TYPE> {                                           \
public:                                                                        \
    typedef SEQ_TYPE NativeSequence;                                           \
                                                                               \
    static void finalize(NativeSequence& sequence)                             \
    {                                                                          \
        SEQ_TYPE ## _finalize(&sequence);                                      \
    }                                                                          \
                                                                               \
    static TYPE * get_reference(NativeSequence& sequence, uint32_t i)          \
    {                                                                          \
        return SEQ_TYPE ## _get_reference(&sequence, i);                       \
    }                                                                          \
                                                                               \
    static uint32_t length(const NativeSequence& sequence)                     \
    {                                                                          \
        return SEQ_TYPE ## _get_length(&sequence);                             \
    }                                                                          \
}

namespace rti { namespace core { namespace detail {

/*
 * Specializations of this template class for NativeType allow uniform
 * manipulation of native sequences by NativeSequenceAdapters<NativeType>
 */
template <class NativeType>
class native_sequence_traits {
    // see macro RTI_DEFINE_SEQUENCE_TRAITS for expected static methods
    // required in specializations

};

// --- NativeSequenceAdapter: -------------------------------------------------

/*
 * Provides uniform manipulation and automatic finalization of native sequences.
 *
 * NativeSequenceAdapter<T> requires that native_sequence_traits<T> is defined
 */
template <typename NativeType>
class NativeSequenceAdapter {
public:
    typedef typename native_sequence_traits<NativeType>::NativeSequence
        NativeSequence;

    NativeSequenceAdapter(NativeSequence& sequence) : sequence_(sequence)
    {
    }

    ~NativeSequenceAdapter()
    {
        native_sequence_traits<NativeType>::finalize(sequence_);
    }

    NativeType& operator[](uint32_t index)
    {
        NativeType* entity =
            native_sequence_traits<NativeType>::get_reference(
                sequence_, index);
        return *entity;
    }

    uint32_t size() const
    {
        return native_sequence_traits<NativeType>::length(sequence_);
    }

private:
    // disable copies
    NativeSequenceAdapter(const NativeSequenceAdapter&);
    NativeSequenceAdapter& operator=(const NativeSequenceAdapter&);

    // The managed sequence
    NativeSequence& sequence_;
};

template <>
class native_sequence_traits<char *> {
public:
    typedef struct DDS_StringSeq NativeSequence;

    static void finalize(NativeSequence& sequence)
    {
        DDS_StringSeq_finalize(&sequence);
    }

    static char** get_reference(NativeSequence& sequence, uint32_t index)
    {
        return DDS_StringSeq_get_reference(&sequence, index);
    }

    static uint32_t length(const NativeSequence& sequence)
    {
        return DDS_StringSeq_get_length(&sequence);
    }
};

} } } // namespace rti::core::detail

#endif // RTI_DDS_CORE_DETAIL_SEQUENCE_HPP_

