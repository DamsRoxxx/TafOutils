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

#ifndef RTI_DDS_CORE_DETAIL_ENTITY_HPP_
#define RTI_DDS_CORE_DETAIL_ENTITY_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>
#include <dds/core/status/Status.hpp>
#include <dds/pub/Publisher.hpp>

namespace rti { namespace core { namespace detail {

template <typename NativeEntity>
class native_entity_cast {
    // specializations should define:
    // static DDS_Entity * as_entity(NativeEntity * entity);
};

// --- DomainParticipant specializations: -------------------------------------

template <>
class native_entity_cast<DDS_DomainParticipant> {
public:
    static DDS_Entity * as_entity(DDS_DomainParticipant * entity)
    {
        return DDS_DomainParticipant_as_entity(entity);
    }
};

template <>
class native_sequence_traits<DDS_DomainParticipant> {
public:
    typedef DDS_DomainParticipantSeq NativeSequence;

    static void finalize(NativeSequence& sequence)
    {
        DDS_DomainParticipantSeq_finalize(&sequence);
    }

    static DDS_DomainParticipant* get_reference(NativeSequence& sequence, uint32_t index)
    {
        return *DDS_DomainParticipantSeq_get_reference(&sequence, index);
    }

    static uint32_t length(const NativeSequence& sequence)
    {
        return DDS_DomainParticipantSeq_get_length(&sequence);
    }
};

// --- Topic specializations: -------------------------------------------------

template <>
class native_entity_cast<DDS_Topic> {
public:
    static DDS_Entity * as_entity(DDS_Topic * entity)
    {
        return DDS_Topic_as_entity(entity);
    }
};

template <>
class native_sequence_traits<DDS_Topic> {
public:
    typedef DDS_TopicSeq NativeSequence;

    static void finalize(NativeSequence& sequence)
    {
        DDS_TopicSeq_finalize(&sequence);
    }

    static DDS_Topic* get_reference(NativeSequence& sequence, uint32_t index)
    {
        return *DDS_TopicSeq_get_reference(&sequence, index);
    }

    static uint32_t length(const NativeSequence& sequence)
    {
        return DDS_TopicSeq_get_length(&sequence);
    }
};

template <>
class native_sequence_traits<DDS_ContentFilteredTopic> {
public:
    typedef DDS_ContentFilteredTopicSeq NativeSequence;

    static void finalize(NativeSequence& sequence)
    {
        DDS_ContentFilteredTopicSeq_finalize(&sequence);
    }

    static DDS_ContentFilteredTopic* get_reference(NativeSequence& sequence, uint32_t index)
    {
        return *DDS_ContentFilteredTopicSeq_get_reference(&sequence, index);
    }

    static uint32_t length(const NativeSequence& sequence)
    {
        return DDS_ContentFilteredTopicSeq_get_length(&sequence);
    }
};

// --- Publisher specializations: ---------------------------------------------

template <>
class native_entity_cast<DDS_Publisher> {
public:
    static DDS_Entity * as_entity(DDS_Publisher * entity)
    {
        return DDS_Publisher_as_entity(entity);
    }
};


template <>
class native_sequence_traits<DDS_Publisher> {
public:
    typedef DDS_PublisherSeq NativeSequence;

    static void finalize(NativeSequence& sequence)
    {
        DDS_PublisherSeq_finalize(&sequence);
    }

    static DDS_Publisher* get_reference(NativeSequence& sequence, uint32_t index)
    {
        return *DDS_PublisherSeq_get_reference(&sequence, index);
    }

    static uint32_t length(const NativeSequence& sequence)
    {
        return DDS_PublisherSeq_get_length(&sequence);
    }
};

// --- DataWriter specializations: --------------------------------------------

template <>
class native_entity_cast<DDS_DataWriter> {
public:
    static DDS_Entity * as_entity(DDS_DataWriter * entity)
    {
        return DDS_DataWriter_as_entity(entity);
    }
};

template <>
class native_sequence_traits<DDS_DataWriter> {
public:
    typedef DDS_DataWriterSeq NativeSequence;

    static void finalize(NativeSequence& sequence)
    {
        DDS_DataWriterSeq_finalize(&sequence);
    }

    static DDS_DataWriter* get_reference(NativeSequence& sequence, uint32_t index)
    {
        return *DDS_DataWriterSeq_get_reference(&sequence, index);
    }

    static uint32_t length(const NativeSequence& sequence)
    {
        return DDS_DataWriterSeq_get_length(&sequence);
    }
};


// --- Subscriber specializations: ---------------------------------------------

template <>
class native_entity_cast<DDS_Subscriber> {
public:
    static DDS_Entity * as_entity(DDS_Subscriber * entity)
    {
        return DDS_Subscriber_as_entity(entity);
    }
};


template <>
class native_sequence_traits<DDS_Subscriber> {
public:
    typedef DDS_SubscriberSeq NativeSequence;

    static void finalize(NativeSequence& sequence)
    {
        DDS_SubscriberSeq_finalize(&sequence);
    }

    static DDS_Subscriber* get_reference(NativeSequence& sequence, uint32_t index)
    {
        return *DDS_SubscriberSeq_get_reference(&sequence, index);
    }

    static uint32_t length(const NativeSequence& sequence)
    {
        return DDS_SubscriberSeq_get_length(&sequence);
    }
};

// --- DataReader specializations: --------------------------------------------

template <>
class native_entity_cast<DDS_DataReader> {
public:
    static DDS_Entity * as_entity(DDS_DataReader * entity)
    {
        return DDS_DataReader_as_entity(entity);
    }
};

template <>
class native_sequence_traits<DDS_DataReader> {
public:
    typedef DDS_DataReaderSeq NativeSequence;

    static void finalize(NativeSequence& sequence)
    {
        DDS_DataReaderSeq_finalize(&sequence);
    }

    static DDS_DataReader* get_reference(NativeSequence& sequence, uint32_t index)
    {
        return *DDS_DataReaderSeq_get_reference(&sequence, index);
    }

    static uint32_t length(const NativeSequence& sequence)
    {
        return DDS_DataReaderSeq_get_length(&sequence);
    }
};

// --- Creation from native: --------------------------------------------------




// Note: this is a struct with a single static method to allow partial
// template specialization
template <typename EntityImpl, typename NativeEntity>
struct get_ptr_from_native_entity {
    typedef typename dds::core::smart_ptr_traits<EntityImpl>::ref_type
        ActualEntityRef;
    typedef rti::core::Entity::weak_ref_type EntityWeakRef;
    typedef rti::core::Entity::ref_type EntityRef;

    /*
     * Creates a C++ entity from the corresponding native object. EntityImpl is a
     * class derived from rti::core::Entity. NativeEntity is a C structure
     * whose pointer can be cast to DDS_Entity*.
     *
     * For example: EntityImpl = rti::domain::DomainParticipant,
     *              NativeEntity = DDS_DomainParticipant
     *
     */
    static ActualEntityRef do_it(NativeEntity * native_object)
    {
        // EntityImpl is the actual subclass of rti::core::Entity

        // First get the weak reference we store as reserved data in the native
        // entity
        const DDS_Entity * native_entity =
            native_entity_cast<NativeEntity>::as_entity(native_object);

        EntityWeakRef * weak_ref = static_cast<EntityWeakRef *>(
            DDS_Entity_get_reserved_dataI((DDS_Entity *) native_entity));

        if (weak_ref == NULL) {
            // If the weak reference doesn't exist it's because someone else
            // created this entity natively, bypassing the C++ API. An example is
            // the XML application-creation. We return an empty reference.
            return ActualEntityRef();
        }

        // Locking a weak reference creates a strong reference
        EntityRef entity_ref = weak_ref->lock();
        if (!entity_ref) {
            // The weak reference has expired
            return ActualEntityRef();
        }

        // Downcast from rti::core::Entity to the actual class, EntityImpl
        ActualEntityRef actual_entity_ref =
            rtiboost::dynamic_pointer_cast<EntityImpl>(entity_ref);
        if (!actual_entity_ref) {
            throw dds::core::InvalidDowncastError(
                "Internal downcast error: reference in native entity has wrong type");
        }

        return actual_entity_ref;
    }
};

// Obtains a C++ entity from a C entity. If the entity only existed in the C
// layer, this function returns an empty reference.
// (i.e. returned_entity.delegate() == nullptr)
template <typename Entity, typename NativeEntity>
Entity get_from_native_entity(NativeEntity * native_object)
{
    typedef typename Entity::DELEGATE_T delegate_type;

    return Entity(
        get_ptr_from_native_entity<delegate_type, NativeEntity>::do_it(native_object));
}

// Creates a C++ entity from a C entity. If the entity already existed in C++
// this is equivalent to get_from_native_entity(). But if the entity didn't exist
// in the C++ layer, this function creates a new C++ entity--and a new shared_ptr.
// This template has specializations for the AnyXXX classes (e.g. AnyTopic)
template <typename Entity, typename NativeEntity>
Entity create_from_native_entity(
    NativeEntity * native_object, bool create_new = true)
{
    typedef typename Entity::DELEGATE_T delegate_type;
    typedef typename Entity::DELEGATE_REF_T ref_type;

    // Locking a weak reference creates a strong reference
    ref_type ref = get_ptr_from_native_entity<delegate_type, NativeEntity>::do_it(
        native_object);

    if (!ref && create_new) {
        // If the C entity didn't have a valid weak_ptr we create a
        // new entity with a new shared_ptr
        Entity entity(
            dds::core::construct_from_native_tag_t(),
            new delegate_type(native_object));
        entity->created_from_c(true);
        return entity;
    }

    // If the weak reference was valid, we can create the Entity with
    // the existing delegate that ref points to so it shares ownership with
    // existing references.
    return Entity(ref);
}

// Create entities from in a sequence into a forward iterator
template <typename Entity, typename NativeEntity, typename ForwardIterator>
void create_from_native_entity(
    ForwardIterator begin,
    uint32_t max_size,
    NativeSequenceAdapter<NativeEntity>& sequence,
    bool create_new = true)
{
    for (uint32_t i = 0; i < sequence.size() && i < max_size; i++) {
        Entity element = create_from_native_entity<Entity, NativeEntity>(
            &sequence[i], create_new);
        if (element != dds::core::null) {
            *begin++ = element;
        }
    }
}

// Create entities from in a sequence into a back-insertion iterator
template <typename Entity, typename NativeEntity, typename BackInsertIterator>
void create_from_native_entity(
    BackInsertIterator begin,
    NativeSequenceAdapter<NativeEntity>& sequence,
    bool create_new = true)
{
    create_from_native_entity<Entity, NativeEntity, BackInsertIterator>(
        begin, sequence.size(), sequence, create_new);
}

} } } // namespace rti::core::detail

#endif // RTI_DDS_CORE_DETAIL_ENTITY_HPP_

