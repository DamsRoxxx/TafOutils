#ifndef OMG_TDDS_CORE_POLICY_CORE_POLICY_HPP_
#define OMG_TDDS_CORE_POLICY_CORE_POLICY_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
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

#include <dds/core/detail/conformance.hpp>
#include <dds/core/LengthUnlimited.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/policy/PolicyKind.hpp>
#include <dds/core/Duration.hpp>


// ============================================================================
// DDS Policy Classes

namespace dds { namespace core { namespace policy {

/** 
 * @RTI_class_definition class UserData
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Attaches a buffer of opaque data that is distributed by
 * \ref DDSBuiltInTopicModule during discovery.
 *
 * @details \dref_details_UserDataQosPolicy
 */
template <typename D>
class TUserData : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TUserData, D)

    /**
     * @brief Creates an instance with an empty sequence of bytes
     */
    TUserData() : dds::core::Value<D>() 
    { 
    }

    /**
     * @brief Creates an instance with a sequence of bytes
     *
     * @param seq A vector containing the bytes to create this UserData
     */
    explicit TUserData(const dds::core::ByteSeq& seq)
        : Value<D>(seq)
    {
    }

    /**
     * @brief Creates an instance with a sequence of bytes
     *
     * @param value_begin Beginning of a range of bytes
     * @param value_end End of the reange
     */
    TUserData(const uint8_t* value_begin, const uint8_t* value_end)
        : Value<D>(value_begin, value_end)
    {
    }

  public:

    // Spec Error: CPPPSM-216: This setter conflicts with the getter which 
    // takes in a ByteSeq
    /* *
     * Set the value for the user data.
     *
     * @param seq a sequence of bytes representing the user data.
     
    TUserData& value(const dds::core::ByteSeq& seq)
    {
        this->delegate().value(seq);
        return *this;
    }
    */

    /**
     * @brief Sets the byte sequence
     *
     * @tparam OctetIter An input iterator of bytes (convertible to uint8_t). If
     * the iterator is a random-acess iterator this method is more efficient.
     *
     * @param the_begin Beginning of the range
     * @param the_end End of the range
     */
    template <typename OctetIter>
    TUserData& value(OctetIter the_begin, OctetIter the_end)
    {
        this->delegate().value(the_begin, the_end);
        return *this;
    }

    /**
     * @brief Gets the user data.
     * 
     * @return the sequence of bytes representing the user data
     */
    const dds::core::ByteSeq value() const
    {
        return this->delegate().value();
    }

    // Spec Error, CPPPSM-216, this getter was missing

    /**
     * @brief Gets the user data.
     *
     * @param dest The vector where the bytes will be copied
     * @return A reference to \p dest
     */
    dds::core::ByteSeq& value(dds::core::ByteSeq& dest) const
    {
        return this->delegate().value(dest);
    }

    /**
     * @brief Gets the beginning of the range of bytes in this UserData
     */
    const uint8_t* begin() const
    {
        return this->delegate().begin();
    }

    /**
     * @brief Gets the end of the range of bytes in this UserData
     */
    const uint8_t* end() const
    {
        return this->delegate().end();
    }
};

// ==========================================================================

/** 
 * @RTI_class_definition class Durability
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Specifies whether a dds::pub::DataWriter will store and deliver
 * previously published data samples to late-joining dds::sub::DataReader entities.
 *
 * @details \dref_details_DurabilityQosPolicy
 */
template <typename D>
class TDurability : public Value<D> {
  public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TDurability, D)

    /**
     * @brief Creates the default Durability
     */
    TDurability() : Value<D>() { }

    /**
     * @brief Creates an instance with a specific durability kind
     *
     * @details \dref_DurabilityQosPolicy_kind
     */
    explicit TDurability(dds::core::policy::DurabilityKind the_kind)
        : Value<D>(the_kind)
    {
    }

    /**
     * @brief Sets the Durability kind
     *
     * @details \dref_DurabilityQosPolicy_kind
     */
    TDurability& kind(dds::core::policy::DurabilityKind the_kind)
    {
        this->delegate().kind(the_kind);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::policy::DurabilityKind kind() const
    {
        return this->delegate().kind();
    }

    /**
     * @brief Creates a Durability instance with volatile kind
     */
    static TDurability Volatile()
    {
        return TDurability(DurabilityKind::VOLATILE);
    }

    /**
     * @brief Creates a Durability instance with trasient-local kind
     */
    static TDurability TransientLocal()
    {
        return TDurability(DurabilityKind::TRANSIENT_LOCAL);
    }

    /**
     * @brief Creates a Durability instance with trasient kind
     */
    static TDurability Transient()
    {
        return TDurability(DurabilityKind::TRANSIENT);
    }

    /**
     * @brief Creates a Durability instance with persistent kind
     */
    static TDurability Persistent()
    {
        return TDurability(DurabilityKind::PERSISTENT);
    }
};

// ==========================================================================

/** 
 * @RTI_class_definition class Presentation
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Specifies how the samples representing changes to data instances are
 * presented to a subscribing application.
 *
 * @details \dref_details_PresentationQosPolicy
 */
template <typename D>
class TPresentation : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TPresentation, D)

    /**
     * @brief Create an instance with the default value
     */
    TPresentation() : dds::core::Value<D>() { }

    /**
     * @brief Creates an instance with the specified access scope and coherent
     * and ordered access.
     *
     * See the corresponding setters.
     */
    TPresentation(
      dds::core::policy::PresentationAccessScopeKind the_access_scope,
      bool the_coherent_access,
      bool the_ordered_access)
      : dds::core::Value<D>(
          the_access_scope, the_coherent_access, the_ordered_access)
    {
    }

  public:
    /**
     * @brief Determines the largest scope spanning the entities for which the
     * order and coherency of changes can be preserved.
     * 
     * @details \dref_details_PresentationQosPolicy_access_scope
     */
    TPresentation& access_scope(
      dds::core::policy::PresentationAccessScopeKind the_access_scope)
    {
      this->delegate().access_scope(the_access_scope);
      return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::policy::PresentationAccessScopeKind  access_scope() const
    {
        return this->delegate().access_scope();
    }

    /**
     * @brief Controls whether coherent access is supported within the access_scope.
     * 
     * @details \dref_details_PresentationQosPolicy_coherent_access
     */
    TPresentation& coherent_access(bool enable)
    {
        this->delegate().coherent_access(enable);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool coherent_access() const
    {
        return this->delegate().coherent_access();
    }

    /**
     * @brief Controls whether ordered access is supported within the access_scope.
     * 
     * @details \dref_details_PresentationQosPolicy_ordered_access
     */
    TPresentation& ordered_access(bool enable)
    {
        this->delegate().ordered_access(enable);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool ordered_access() const
    {
      return this->delegate().ordered_access();
    }

    /**
     * @brief Creates a Presentation instnace with group access scope
     */
    static TPresentation GroupAccessScope(
        bool coherent, bool ordered)
    {
        return TPresentation(
            dds::core::policy::PresentationAccessScopeKind::GROUP,
            coherent,
            ordered);
    }

    /**
     * @brief Creates a Presentation instance with instance access scope
     */
    static TPresentation InstanceAccessScope(
        bool coherent, bool ordered)
    {
        return TPresentation(
            dds::core::policy::PresentationAccessScopeKind::INSTANCE,
            coherent,
            ordered);
    }

    /**
     * @brief Creates a Presentation instance with topic access scope
     */
    static TPresentation TopicAccessScope(
        bool coherent, bool ordered)
    {
        return TPresentation(
            dds::core::policy::PresentationAccessScopeKind::TOPIC,
            coherent,
            ordered);
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class Deadline
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Expresses the maximum duration (deadline) within which an instance
 * is expected to be updated.
 *
 * @details \dref_details_DeadlineQosPolicy
 */
template <typename D>
class TDeadline : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TDeadline, D)


    /**
     * @brief Creates the default deadline, with an infinite period.
     */
    TDeadline() : Value<D>() { }

    /**
     * @brief Creates a deadline policy with the specified period
     */
    explicit TDeadline(const dds::core::Duration& d) : Value<D>(d) { }

  public:

    /**
     * @brief Sets the duration of the deadline period.
     *
     * @details \dref_details_DeadlineQosPolicy_period
     */
    TDeadline& period(const dds::core::Duration& the_period)
    {
        this->delegate().period(the_period);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::Duration period() const
    {
        return this->delegate().period();
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class LatencyBudget
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Provides a hint as to the maximum acceptable delay from the time the
 * data is written to the time it is received by the subscribing applications.
 *
 * @details \dref_details_LatencyBudgetQosPolicy
 */
template <typename D>
class TLatencyBudget : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TLatencyBudget, D)

    /**
     * @brief Creates a latency budget with zero duration.
     */
    TLatencyBudget() : Value<D>() { }

    /**
     * @brief Creates an instance with the specified duration
     */
    explicit TLatencyBudget(const dds::core::Duration& the_duration)
        : Value<D>(the_duration)
    {
    }

  public:
    /**
     * @brief Sets the duration of the maximum acceptable delay.
     * 
     * @details \dref_details_LatencyBudgetQosPolicy_duration
     */
    TLatencyBudget& duration(const dds::core::Duration& the_duration)
    {
        this->delegate().duration(the_duration);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::Duration duration() const
    {
        return this->delegate().duration();
    }
};

// ============================================================================

/** @RTI_remove_lines 1 */
#ifdef OMG_DDS_OWNERSHIP_SUPPORT

/** 
 * @RTI_class_definition class Ownership
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Specifies whether it is allowed for multiple dds::pub::DataWriter's
 * to write the same instance of the data and if so, how these modifications
 * should be arbitrated.
 *
 * @details \dref_details_OwnershipQosPolicy
 */
template <typename D>
class TOwnership : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TOwnership, D)

    /**
    * @brief Creates an ownership policy set to shared.
    */
    TOwnership() : Value<D>() { }

    /**
     * @brief Creates an instance with the specified ownership kind
     */
    explicit TOwnership(dds::core::policy::OwnershipKind the_kind)
        : Value<D>(the_kind)
    {
    }

    /**
     * @brief Sets the ownership kind
     * @details \dref_details_OwnershipQosPolicy_kind
     */
    TOwnership& kind(dds::core::policy::OwnershipKind the_kind)
    {
        this->delegate().kind(the_kind);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::policy::OwnershipKind kind() const
    {
        return this->delegate().kind();
    }

    /**
     * @brief Creates a Ownership instance with exclusive kind
     */
    static TOwnership Exclusive()
    {
        return TOwnership(OwnershipKind::EXCLUSIVE);
    }

    /**
     * @brief Creates a Ownership instance with shared kind
     */
    static TOwnership Shared()
    {
        return TOwnership(OwnershipKind::SHARED);
    }
};

// ============================================================================

/** 
 * @RTI_class_definition class OwnershipStrength
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Specifies the value of the strength used to arbitrate among multiple
 * dds::pub::DataWriter objects that attempt to modify the same instance of a
 * data type (identified by its dds::topic::Topic and key).
 *
 * @details \dref_details_OwnershipStrengthQosPolicy
 */
template <typename D>
class TOwnershipStrength : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TOwnershipStrength, D)


    // Spec error: default constructor was missing
    /**
     * @brief Creates an instance with the default strength (0)
     */
    TOwnershipStrength() : Value<D>(0) { }

    /**
     * @brief Creates an instance with the specified strength value
     */
    explicit TOwnershipStrength(int32_t strength) : Value<D>(strength) { }

  public:

    /**
     * @brief Sets the ownership strength to arbitrate among multiple writers
     * 
     * @details \dref_details_OwnershipStrengthQosPolicy_value
     */
    TOwnershipStrength& value(int32_t strength)
    {
        this->delegate().value(strength);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t value() const
    {
        return this->delegate().value();
    }
};

/** @RTI_remove_lines 1 */
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

// ============================================================================


/** 
 * @RTI_class_definition class Liveliness
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Specifies and configures the mechanism that allows
 * dds::sub::DataReader's to detect when dds::pub::DataWriter's become
 * disconnected
 *
 * @details \dref_details_LivelinessQosPolicy
 */
template <typename D>
class TLiveliness : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TLiveliness, D)

    /**
     * @brief Creates an automatic liveliness policy with infinite lease duration.
     */
    TLiveliness()
    {
    }

    /**
     * @brief Creates an instance with the specified liveliness kind and
     * lease duration
     */
    TLiveliness(
        dds::core::policy::LivelinessKind the_kind,
        const dds::core::Duration& the_lease_duration)
        : Value<D>(the_kind, the_lease_duration)
    {
    }


    /**
     * @brief Sets the liveliness kind
     *
     * @details \dref_details_LivelinessQosPolicy_kind
     */
    TLiveliness& kind(dds::core::policy::LivelinessKind the_kind)
    {
        this->delegate().kind(the_kind);
        return *this;
    }

    /**
     * @brief Getter (see the setter with the same name)
     */
    dds::core::policy::LivelinessKind kind() const
    {
        return this->delegate().kind();
    }

    /**
     * @brief Sets the duration within which a dds::core::Entity must be
     * asserted or else it is considered not alive
     *
     * @details \dref_LivelinessQosPolicy_lease_duration
     */
    TLiveliness& lease_duration(const dds::core::Duration& the_lease_duration)
    {
        this->delegate().lease_duration(the_lease_duration);
        return *this;
    }

    /**
     * @brief Getter (see the setter with the same name)
     */
    dds::core::Duration lease_duration() const
    {
        return this->delegate().lease_duration();
    }

    /**
     * @brief Creates a Liveliness instance with LivelinessKind::AUTOMATIC
     */
    static TLiveliness Automatic()
    {
        return TLiveliness(
            dds::core::policy::LivelinessKind::AUTOMATIC,
            dds::core::Duration::infinite());
    }

    /**
     * @brief Creates a Liveliness instance with LivelinessKind::MANUAL_BY_PARTICIPANT
     * and the specified lease duration (infinite by default)
     */
    static TLiveliness ManualByParticipant(
        const dds::core::Duration& lease = dds::core::Duration::infinite())
    {
        return TLiveliness(
            dds::core::policy::LivelinessKind::MANUAL_BY_PARTICIPANT, lease);
    }

    /**
     * @brief Creates a Liveliness instance with LivelinessKind::MANUAL_BY_TOPIC
     * and the specified lease duration (infinite by default)
     */
    static TLiveliness ManualByTopic(
        const dds::core::Duration& lease = dds::core::Duration::infinite())
    {
        return TLiveliness(
            dds::core::policy::LivelinessKind::MANUAL_BY_TOPIC, lease);
    }
};

//==============================================================================

/**
 * @RTI_class_definition class Partition
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Set of strings that introduces a logical partition among the topics
 * visible by a dds::pub::Publisher and a dds::sub::Subscriber
 *
 * @details \dref_details_PartitionQosPolicy
 */
template<typename D>
class TPartition: public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TPartition, D)

    /**
     * @brief Creates a policy with the default partition
     */
    TPartition() : Value<D>() { }

    /**
     * @brief Creates a policy with a single partition with the specified name
     */
    explicit TPartition(const std::string& partition) : Value<D>(partition) { }

    /**
     * @brief Creates a policy with the partitions specified in a vector
     */
    explicit TPartition(const dds::core::StringSeq& partitions)
        : Value<D>(partitions)
    {
    }

    /**
     * @brief Sets the partition names specified in a vector
     *
     * @details \dref_details_PartitionQosPolicy_name
     */
    TPartition& name(const dds::core::StringSeq& partitions)
    {
        this->delegate().name(partitions);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::StringSeq name() const
    {
        return this->delegate().name();
    }

//  Spec error: this method is ambiguous with respect to the
//  first name() overload (the setter)
//
//    dds::core::StringSeq& name(dds::core::StringSeq& dst) const
//    {
//        return this->delegate().name(dst);
//    }
};

//==============================================================================

/** 
 * @RTI_class_definition class GroupData
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief
 *
 * @details \dref_details_GroupDataQosPolicy
 *
 * @see UserData
 */
template <typename D>
class TGroupData : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TGroupData, D)

    /**
     * @brief Create a GroupData instance.
     */
    TGroupData() : dds::core::Value<D>()
    {
    }

    /**
     * @brief Create a GroupData instance with a sequence of bytes
     */
    explicit TGroupData(const dds::core::ByteSeq& seq) 
      : dds::core::Value<D>(seq)
    {
    }

    /**
     * @brief Create a GroupData instance with a sequence of bytes
     */
    TGroupData(const uint8_t* value_begin, const uint8_t* value_end)
      : dds::core::Value<D>(value_begin, value_end)
    {
    }


    // Spec Error: CPPPSM-216: This setter conflicts with the getter which 
    // takes in a ByteSeq
    /* *
     * Set the value for this GroupData
     *
     * @param seq the group data value
     
    TGroupData& value(const dds::core::ByteSeq& seq)
    {
        this->delegate().value(seq);
        return *this;
    }
    */

    /**
     * @brief Sets the value for this GroupData
     */
    template <typename OCTET_ITER>
    TGroupData& value(OCTET_ITER the_begin, OCTET_ITER the_end)
    {
        this->delegate().value(the_begin, the_end);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::ByteSeq value() const
    {
        return this->delegate().value();
    }

    /**
     * @brief Sets the value for this GroupData
     */
    dds::core::ByteSeq& value(dds::core::ByteSeq& dst) const
    {
        return this->delegate().value(dst);
    }

    /**
     * @brief Beginning of the range of bytes
     */
    const uint8_t* begin() const
    {
        return this->delegate().begin();
    }

    /**
     * @brief End of the range of bytes
     */
    const uint8_t* end() const
    {
        return this->delegate().end();
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class TopicData
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief
 *
 * @details \dref_details_TopicDataQosPolicy
 *
 * @see UserData
 */
template <typename D>
class TTopicData : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TTopicData, D)

    /**
     * @brief Creates an empty sequence of bytes
     */
    TTopicData() : dds::core::Value<D>()
    {
    }

    /**
     * @brief Creates an instance from a vector of bytes
     */
    explicit TTopicData(const dds::core::ByteSeq& seq)
      : dds::core::Value<D>(seq)
    {
    }

    /**
     * @brief Creates an instance from a range of bytes
     */
    TTopicData(const uint8_t* value_begin, const uint8_t* value_end)
      : dds::core::Value<D>(value_begin, value_end)
    {
    }

public:

    // Spec Error: CPPPSM-216: This setter conflicts with the getter which 
    // takes in a ByteSeq
    /* *
     * Set the value for the topic data.
     *
     * @param seq a sequence of bytes representing the topic data.
     
    TTopicData& value(const dds::core::ByteSeq& seq)
    {
        this->delegate().value(seq);
        return *this;
    }
    */

    /**
     * @brief Set the value for the topic data.
     */
    template <typename OCTET_ITER>
    TTopicData& value(OCTET_ITER the_begin, OCTET_ITER the_end)
    {
        this->delegate().value(the_begin, the_end);
        return *this;
    }

    /**
     * @brief Get the topic data.
     */
    const dds::core::ByteSeq value() const
    {
        return this->delegate().value();
    }

    /**
     * @brief Get the topic data.
     */
    dds::core::ByteSeq& value(dds::core::ByteSeq& dst) const
    {
        return this->delegate().value(dst);
    }

    /**
     * @brief Beginning of the range of bytes
     */
    const uint8_t* begin() const
    {
        return this->delegate().begin();
    }

    /**
     * @brief End of the range of bytes
     */
    const uint8_t* end() const
    {
        return this->delegate().end();
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class EntityFactory
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Configures a dds::core::Entity that acts as factory of other entities
 *
 * @details \dref_details_EntityFactoryQosPolicy
 *
 * @see UserData
 */
template<typename D>
class TEntityFactory: public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TEntityFactory, D)

    /**
     * @brief Default policy
     */
    TEntityFactory() : dds::core::Value<D>(true) { }

    /**
     * @brief Specifies whether the entity acting as a factory automatically
     * enables the instances it creates.
     */
    explicit TEntityFactory(bool the_auto_enable)
        : dds::core::Value<D>(the_auto_enable)
    {
    }

    /**
     * @brief Specifies whether the entity acting as a factory automatically
     * enables the instances it creates.
     */
    TEntityFactory& autoenable_created_entities(bool on)
    {
        this->delegate().autoenable_created_entities(on);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool autoenable_created_entities() const
    {
        return this->delegate().autoenable_created_entities();
    }


    /**
     * @brief Creates \p EntityFactory(true)
     */
    static TEntityFactory AutoEnable()
    {
        return TEntityFactory(true);
    }

    /**
     * @brief Creates \p EntityFactory(false)
     */
    static TEntityFactory ManuallyEnable()
    {
        return TEntityFactory(false);
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class TransportPriority
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Allows applications to take advantage of transports capable of sending
 * messages with different priorities
 *
 * @details \dref_details_TransportPriorityQosPolicy
 */
template <typename D>
class TTransportPriority : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TTransportPriority, D)


    /**
     * @brief Creates a policy with priority 0
     */
    TTransportPriority() 
        : dds::core::Value<D>(0)
    {
    }

    /**
     * @brief Creates a policy with the specified priority
     */
    explicit TTransportPriority(int32_t priority)
        : dds::core::Value<D>(priority)
    {
    }

public:

    /**
     * @brief Sets the priority
     *
     * @details \dref_details_TransportPriorityQosPolicy_value
     */
    TTransportPriority& value(int32_t priority)
    {
        this->delegate().value(priority);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t value() const
    {
        return this->delegate().value();
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class Lifespan
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Specifies how long the data written by a dds::pub::DataWriter is
 * considered valid.
 *
 * @details \dref_details_LifespanQosPolicy
 */
template <typename D>
class TLifespan : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TLifespan, D)


    /**
     * @brief Creates the default policy with an infinite lifespan
     */
    TLifespan()
      : dds::core::Value<D>()
    {
    }

    /**
     * @brief Creates a policy with the specified lifespan duration
     */
    explicit TLifespan(const dds::core::Duration& d)
      : dds::core::Value<D>(d)
    {
    }

    /**
     * @brief Sets the maximum duration for which the data is valid
     *
     * @details \dref_details_LifespanQosPolicy_duration
     */
    TLifespan& duration(const dds::core::Duration& d)
    {
        this->delegate().duration(d);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::Duration duration() const
    {
        return this->delegate().duration();
    }

  };

//==============================================================================

/** 
 * @RTI_class_definition class TimeBasedFilter
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Allows a dds::sub::DataReader to indicate that it is not interested
 * in all the sample updates that occur within a time period
 *
 * @details \dref_details_TimeBasedFilterQosPolicy
 */
template <typename D>
class TTimeBasedFilter : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TTimeBasedFilter, D)

    /**
     * @brief Creates the default time-based filter
     */
    TTimeBasedFilter()
      : dds::core::Value<D>()
    {
    }

    /**
     * @brief Creates a policy with the specified minimum separation
     */
    explicit TTimeBasedFilter(const dds::core::Duration& the_min_separation)
      : dds::core::Value<D>(the_min_separation)
    {
    }

    /**
     * @brief Sets the minimum separation between subsequent samples
     *
     * @details \dref_details_TimeBasedFilterQosPolicy_minimum_separation
     */
    TTimeBasedFilter& minimum_separation(const dds::core::Duration& min_separation)
    {
        this->delegate().minimum_separation(min_separation);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::Duration minimum_separation() const
    {
        return this->delegate().minimum_separation();
    }
};

/** 
 * @RTI_class_definition class WriterDataLifecycle
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Controls how a dds::pub::DataWriter handles the lifecycle of the
 * instances (keys) that it writes.
 *
 * @details \dref_details_WriterDataLifecycleQosPolicy
 */
template <typename D>
class TWriterDataLifecycle : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TWriterDataLifecycle, D)

    /**
     * @brief Creates the default policy
     */
    TWriterDataLifecycle() : dds::core::Value<D>()
    {
    }

    /**
     * @brief Creates an instance with a value for auto-dispose unregistered instances
     * and default values for the rest of parameters.
     */
    explicit TWriterDataLifecycle(bool autodispose)
        : dds::core::Value<D>(autodispose)
    {
    }

    /**
     * @brief Indicates whether the DataWriter should automatically dispose an
     * instance when it unregisters it.
     *
     * @details \dref_details_WriterDataLifecycleQosPolicy_autodispose_unregistered_instances
     */
    TWriterDataLifecycle& autodispose_unregistered_instances(bool b)
    {
        this->delegate().autodispose_unregistered_instances(b);
        return *this;
    }


    /**
     * @brief Getter (see setter with the same name)
     */
    bool autodispose_unregistered_instances() const
    {
        return this->delegate().autodispose_unregistered_instances();
    }

    /**
     * @brief Creates \p WriterDataLifecycle(true)
     */
    static TWriterDataLifecycle AutoDisposeUnregisteredInstances()
    {
        return TWriterDataLifecycle(true);
    }

    /**
     * @brief Creates \p WriterDataLifecycle(false)
     */
    static TWriterDataLifecycle ManuallyDisposeUnregisteredInstances()
    {
        return TWriterDataLifecycle(false);
    }
};

/** 
 * @RTI_class_definition class ReaderDataLifecycle
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Controls how a DataReader manages the lifecycle of the data
 * that it has received.
 *
 * @details \dref_details_ReaderDataLifecycleQosPolicy
 */
template<typename D>
class TReaderDataLifecycle : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TReaderDataLifecycle, D)

    /**
     * @brief Creates the default policy
     */
    TReaderDataLifecycle() : dds::core::Value<D>()
    {
    }

    /**
     * @brief Creates an instance with the specified nowriter and
     * disposed-samples purge delays
     */
    TReaderDataLifecycle(
        const dds::core::Duration& the_nowriter_delay,
        const dds::core::Duration& the_disposed_samples_delay)
        : dds::core::Value<D>(the_nowriter_delay, the_disposed_samples_delay)
    {
    }

    /**
     * @brief Minimum duration for which the DataReader will maintain
     * information regarding an instance once its \p instance_state becomes
     * InstanceStateKind::NOT_ALIVE_NO_WRITERS.
     *
     * @details \dref_details_ReaderDataLifecycleQosPolicy_autopurge_nowriter_samples_delay
     */
    TReaderDataLifecycle& autopurge_nowriter_samples_delay(
        const dds::core::Duration& duration)
    {
        this->delegate().autopurge_nowriter_samples_delay(duration);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration autopurge_nowriter_samples_delay() const
    {
        return this->delegate().autopurge_nowriter_samples_delay();
    }

    /**
     * @brief Minimum duration for which the DataReader will maintain
     * information regarding an instance once its \p instance_state becomes
     * InstanceStateKind::NOT_ALIVE_DISPOSED.
     *
     * @details \dref_details_ReaderDataLifecycleQosPolicy_autopurge_disposed_samples_delay
     */
    TReaderDataLifecycle& autopurge_disposed_samples_delay(
        const dds::core::Duration& duration)
    {
        this->delegate().autopurge_disposed_samples_delay(duration);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration autopurge_disposed_samples_delay() const
    {
        return this->delegate().autopurge_disposed_samples_delay();
    }


    // Method not in the OMG PSM -- issue ID: CPPPSM-221
    /**
     * @brief Returns a policy where all purge delays are disabled (the default)
     */
    static TReaderDataLifecycle NoAutoPurge()
    {
        return TReaderDataLifecycle();
    }

    /**
     * @brief Returns a policy where only the disposed-samples purge delay is
     * enabled with a specified duration
     */
    static TReaderDataLifecycle AutoPurgeDisposedSamples(
        const dds::core::Duration& duration)
    {
        return TReaderDataLifecycle(dds::core::Duration::infinite(), duration);
    }

    // Method not in the OMG PSM -- issue ID: CPPPSM-221
    /**
     * @brief Returns a policy where only the no-writer purge delay is
     * enabled with a specified duration
     */
    static TReaderDataLifecycle AutoPurgeNoWriterSamples(
        const dds::core::Duration& d)
    {
        return TReaderDataLifecycle(d, dds::core::Duration::infinite());
    }
};

/** 
 * @RTI_class_definition class Reliability
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Indicates the level of reliability in sample delivered that a
 * dds::pub::DataWriter offers or a dds::sub::DataReader requests
 *
 * @details \dref_details_ReliabilityQosPolicy
 */
template <typename D>
class TReliability : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TReliability, D)

    /**
     * @brief Creates a best-effort policy.
     */
    TReliability()
    {
    }

    /**
     * @brief Creates an instance with the specified reliability kind an
     * optionally a specific maximum blocking time.
     *
     * The max blocking time only applies to reliable DataWriters.
     */
    TReliability(
        dds::core::policy::ReliabilityKind the_kind,
        // Spec issue CPPPSM-131: provide default value for max_blocking_time--
        // unused when kind is best effort
        const dds::core::Duration& the_max_blocking_time = dds::core::Duration::from_millisecs(100))
        : dds::core::Value<D>(the_kind, the_max_blocking_time)
    {
    }

    /**
     * @brief Sets the reliability kind
     *
     * @details \dref_details_ReliabilityQosPolicy_kind
     */
    TReliability& kind(dds::core::policy::ReliabilityKind the_kind)
    {
        this->delegate().kind(the_kind);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::policy::ReliabilityKind kind() const
    {
        return this->delegate().kind();
    }

    /**
     * @brief Sets the maximum time a DataWriter may block on a call to write().
     *
     * @details \dref_details_ReliabilityQosPolicy_max_blocking_time
     */
    TReliability& max_blocking_time(const dds::core::Duration& d)
    {
        this->delegate().max_blocking_time(d);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration max_blocking_time() const
    {
        return this->delegate().max_blocking_time();
    }

    /**
     * @brief Creates a policy with ReliabilityKind::RELIABLE and optionally
     * a max blocking time.
     */
    static TReliability Reliable(
        const dds::core::Duration& max_blocking_time = dds::core::Duration::from_millisecs(100))
    {
        return TReliability(
            dds::core::policy::ReliabilityKind::RELIABLE, max_blocking_time);
    }

    /**
     * @brief Creates a policy with ReliabilityKind::BEST_EFFORT
     */
    static TReliability BestEffort()
    {
        return TReliability(
            dds::core::policy::ReliabilityKind::BEST_EFFORT,
            dds::core::Duration::from_millisecs(100));
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class DestinationOrder
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Controls the logical order of updates to the same instance by a
 * dds::pub::Publisher
 *
 * @details \dref_details_DestinationOrderQosPolicy
 */
template <typename D>
class TDestinationOrder : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TDestinationOrder, D)

    /**
     * @brief Creates the default policy
     */
    TDestinationOrder() : dds::core::Value<D>()
    {
    }

    /**
     * @brief Creates a policy with the specified destination order kind
     */
    explicit TDestinationOrder(
       dds::core::policy::DestinationOrderKind the_kind)
      : dds::core::Value<D>(the_kind)
    {
    }

    /**
     * @brief Sets the destination order kind
     *
     * @details \dref_details_DestinationOrderQosPolicy_kind
     */
    TDestinationOrder& kind(dds::core::policy::DestinationOrderKind the_kind)
    {
        this->delegate().kind(the_kind);
        return *this;
    }

    /**
     * @brief Getter (see the setter with the same name)
     */
    dds::core::policy::DestinationOrderKind kind() const
    {
        return this->delegate().kind();
    }

    /**
     * @brief Creates a DestinationOrder with
     * DestinationOrderKind::BY_SOURCE_TIMESTAMP
     */
    static TDestinationOrder SourceTimestamp()
    {
        return TDestinationOrder(
           dds::core::policy::DestinationOrderKind::BY_SOURCE_TIMESTAMP);
    }

    /**
     * @brief Creates a DestinationOrder with
     * DestinationOrderKind::BY_RECEPTION_TIMESTAMP
     */
    static TDestinationOrder ReceptionTimestamp()
    {
        return TDestinationOrder(
           dds::core::policy::DestinationOrderKind::BY_RECEPTION_TIMESTAMP);
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class History
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Specifies how much historical data a dds::pub::DataWriter and a
 * dds::sub::DataReader can store.
 *
 * @details \dref_details_HistoryQosPolicy
 */
template <typename D>
class THistory : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(THistory, D)

    /**
     * @brief Creates a policy that keeps the last sample only.
     */
    THistory()
    {
    }

    // Spec error: KEEP_ALL doesn't require depth

    /**
     * @brief Creates a policy with a specific history kind and optionally a
     * history depth.
     *
     * The history depth doesn't apply to HistoryKind::KEEP_ALL
     */
    THistory(dds::core::policy::HistoryKind the_kind, int32_t the_depth = 1)
        : dds::core::Value<D> (the_kind, the_depth)
    {
    }

public:

    /**
     * @brief Sets the history kind
     *
     * @details \dref_HistoryQosPolicy_kind
     */
    THistory& kind(dds::core::policy::HistoryKind the_kind)
    {
        this->delegate().kind(the_kind);
        return *this;
    }

    /**
     * @brief Gets the history kind
     */
    dds::core::policy::HistoryKind  kind() const
    {
        return this->delegate().kind();
    }

    /**
     * @brief Gets the history depth
     */
    int32_t depth() const
    {
        return this->delegate().depth();
    }

    /**
     * @brief Sets the history depth
     *
     * @details \dref_HistoryQosPolicy_depth
     */
    THistory& depth(int32_t the_depth)
    {
        this->delegate().depth(the_depth);
        return *this;
    }

    /**
     * @brief Creates a History with HistoryKind::KEEP_ALL
     */
    static THistory KeepAll()
    {
        return THistory(dds::core::policy::HistoryKind::KEEP_ALL, 1 /* ignored */);
    }

    /**
     * @brief Creates a History with HistoryKind::KEEP_LAST and the specified
     * depth
     */
    static THistory KeepLast(uint32_t depth)
    {
        return THistory(dds::core::policy::HistoryKind::KEEP_LAST, depth);
    }
};

//==============================================================================

/** 
 * @RTI_class_definition class ResourceLimits
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Controls the memory usage of dds::pub::DataWriter or a
 * dds::sub::DataReader
 *
 * @details \dref_details_ResourceLimitsQosPolicy
 */
template <typename D>
class TResourceLimits : public dds::core::Value<D> {
  public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TResourceLimits, D)

    /**
     * @brief Creates the default policy
     */
    TResourceLimits()
    {
    }

    /**
     * @brief Creates an instance with the specified max_samples, max_instances
     * and max_samples_per instance and default values for the rest of parameters
     */
    TResourceLimits(int32_t the_max_samples, 
                    int32_t the_max_instances,
                    int32_t the_max_samples_per_instance) 
    : dds::core::Value<D> (the_max_samples, 
                           the_max_instances, 
                           the_max_samples_per_instance)
    {
    }

    /**
     * @brief Sets the maximum number of data samples that a DataWriter or a
     * DataReader can manage across all instances
     *
     * @details \dref_details_ResourceLimitsQosPolicy_max_samples
     */
    TResourceLimits& max_samples(int32_t the_max_samples)
    {
        this->delegate().max_samples(the_max_samples);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_samples() const
    {
        return this->delegate().max_samples(); 
    }

    /**
     * @brief Sets the maximum number of instances that a DataWriter or a
     * DataReader can manage
     *
     * @details \dref_details_ResourceLimitsQosPolicy_max_instances
     */
    TResourceLimits& max_instances(int32_t the_max_instances)
    {
        this->delegate().max_instances(the_max_instances);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_instances() const    
    {
        return this->delegate().max_instances(); 
    }

    /**
     * @brief Sets the maximum number of data samples per instance that a
     * DataWriter or a DataReader can manage
     *
     * @details \dref_details_ResourceLimitsQosPolicy_max_samples_per_instance
     */
    TResourceLimits& max_samples_per_instance(int32_t the_max_samples_per_instance) 
    {
        this->delegate().max_samples_per_instance(the_max_samples_per_instance);
        return *this; 
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_samples_per_instance() const
    {
        return this->delegate().max_samples_per_instance(); 
    }
};


//==============================================================================

/** @RTI_remove_lines 1 */
#ifdef OMG_DDS_PERSISTENCE_SUPPORT

/** 
 * @RTI_class_definition class DurabilityService
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Configures the external RTI Persistence Service used by
 * persistent and transient DataWriters
 *
 * @details \dref_details_DurabilityServiceQosPolicy
 */
template <typename D>
class TDurabilityService : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TDurabilityService, D)

    /**
     * @brief Creates the default policy
     */
    TDurabilityService()
     : dds::core::Value<D>()
    {
    }

    /**
     * @brief Creates an instance with all the parameters set
     */
    TDurabilityService(
        const dds::core::Duration& the_service_cleanup_delay,
        dds::core::policy::HistoryKind the_history_kind,
        int32_t the_history_depth,
        int32_t the_max_samples,
        int32_t the_max_instances,
        int32_t the_max_samples_per_instance)
      : dds::core::Value<D>(the_service_cleanup_delay, 
                            the_history_kind, 
                            the_history_depth, 
                            the_max_samples, 
                            the_max_instances, 
                            the_max_samples_per_instance)
    {
    }

    /**
     * \dref_DurabilityServiceQosPolicy_service_cleanup_delay
     */
    TDurabilityService& service_cleanup_delay(const dds::core::Duration& d)
    {
        this->delegate().service_cleanup_delay(d);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration service_cleanup_delay() const
    {
        return this->delegate().service_cleanup_delay();
    }

    /**
     * \dref_DurabilityServiceQosPolicy_service_cleanup_delay
     */
    TDurabilityService& history_kind(dds::core::policy::HistoryKind the_kind)
    {
        this->delegate().history_kind(the_kind);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::policy::HistoryKind history_kind() const
    {
        return this->delegate().history_kind();
    }

    /**
     * \dref_DurabilityServiceQosPolicy_service_cleanup_delay
     */
    TDurabilityService& history_depth(int32_t the_depth)
    {
        this->delegate().history_depth(the_depth);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t history_depth() const
    {
        return this->delegate().history_depth();
    }

    /**
     * \dref_DurabilityServiceQosPolicy_service_cleanup_delay
     */
    TDurabilityService& max_samples(int32_t the_max_samples)
    {
        this->delegate().max_samples(the_max_samples);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_samples() const
    {
        return this->delegate().max_samples();
    }

    /**
     * \dref_DurabilityServiceQosPolicy_service_cleanup_delay
     */
    TDurabilityService& max_instances(int32_t the_max_instances)
    {
        this->delegate().max_instances(the_max_instances);
        return *this;
    }

    int32_t max_instances() const
    {
        return this->delegate().max_instances();
    }

    /**
     * \dref_DurabilityServiceQosPolicy_service_cleanup_delay
     */
    TDurabilityService& max_samples_per_instance(int32_t the_max_samples_per_instance)
    {
        this->delegate().max_samples_per_instance(the_max_samples_per_instance);
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_samples_per_instance() const
    {
        return this->delegate().max_samples_per_instance();
    }
};
/** @RTI_remove_lines 1 */
#endif  // OMG_DDS_PERSISTENCE_SUPPORT


//==============================================================================

/** @RTI_remove_lines 1 */
#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

/** 
 * @RTI_class_definition class TypeConsistencyEnforcement
 * @headerfile dds/core/policy/CorePolicy.hpp
 * @brief Defines the rules for determining whether the type used to publish a
 * given topic is consistent with that used to subscribe to it.
 *
 * @details \dref_details_TypeConsistencyEnforcementQosPolicy
 */
template <typename D>
class TTypeConsistencyEnforcement : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TTypeConsistencyEnforcement, D)


    // Spec error: missing default constructor
    /**
     * @brief Creates the default policy
     */
    TTypeConsistencyEnforcement() : dds::core::Value<D>()
    {
    }

    /**
     * @brief Creates an instance with a specific enforcement kind
     */
    explicit TTypeConsistencyEnforcement(
       dds::core::policy::TypeConsistencyEnforcementKind the_kind)
      : dds::core::Value<D>(the_kind)
    {
    }

    /**
     * @brief Sets the enforcement kind
     *
     * @details \dref_details_TypeConsistencyEnforcementQosPolicy_kind
     */
    TTypeConsistencyEnforcement& kind(
       dds::core::policy::TypeConsistencyEnforcementKind  value)
    {
        this->delegate().kind(value);
        return *this;
    }

    /**
     * @brief Gets the enforcement kind
     */
    dds::core::policy::TypeConsistencyEnforcementKind  kind() const
    {
        return this->delegate().kind();
    }

    /**
     * @brief Creates an instance with
     * TypeConsistencyEnforcementKind::ALLOW_TYPE_COERCION
     */
    static TTypeConsistencyEnforcement AllowTypeCoercion()
    {
        return TTypeConsistencyEnforcement(
           dds::core::policy::TypeConsistencyEnforcementKind::ALLOW_TYPE_COERCION);
    }

    /**
     * @brief Creates an instance with
     * TypeConsistencyEnforcementKind::DISALLOW_TYPE_COERCION
     */
    static TTypeConsistencyEnforcement DisallowTypeCoercion()
    {
        return TTypeConsistencyEnforcement(
           dds::core::policy::TypeConsistencyEnforcementKind::DISALLOW_TYPE_COERCION);
    }
};
/** @RTI_remove_lines 1 */
#endif 


  //==============================================================================


} } } 

#endif /* OMG_TDDS_CORE_POLICY_CORE_POLICY_HPP_ */

