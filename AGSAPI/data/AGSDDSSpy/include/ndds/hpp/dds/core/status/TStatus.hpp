#ifndef OMG_TDDS_CORE_STATUS_STATUS_HPP_
#define OMG_TDDS_CORE_STATUS_STATUS_HPP_

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

#include <dds/core/Value.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <dds/core/policy/QosPolicyCount.hpp>
#include <dds/core/status/State.hpp>

namespace dds { namespace core { namespace status {

/**
 * @dref_StatusKindGroupDocs 
 */

/** 
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class InconsistentTopicStatus
 * @brief Information about the status dds::core::status::StatusMask::inconsistent_topic()
 *
 * @details \dref_details_InconsistentTopicStatus
 */
template<typename D>
class TInconsistentTopicStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TInconsistentTopicStatus, D)

    TInconsistentTopicStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_InconsistentTopicStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_InconsistentTopicStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class SampleLostStatus
 * @brief Information about the status dds::core::status::StatusMask::sample_lost()
 *
 * @details \dref_details_SampleLostStatus
 */
template<typename D>
class TSampleLostStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TSampleLostStatus, D)

    TSampleLostStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_SampleLostStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_SampleLostStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class SampleRejectedStatus
 * @brief Information about the status dds::core::status::StatusMask::sample_rejected()
 *
 * @details \dref_details_SampleRejectedStatus
 */
template<typename D>
class TSampleRejectedStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TSampleRejectedStatus, D)

    TSampleRejectedStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_SampleRejectedStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_SampleRejectedStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }

    /** \dref_SampleRejectedStatus_last_reason */
    const dds::core::status::SampleRejectedState last_reason() const
    {
        return this->delegate().last_reason();
    }

    /** \dref_SampleRejectedStatus_last_instance_handle */
    const dds::core::InstanceHandle last_instance_handle() const
    {
        return this->delegate().last_instance_handle();
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class LivelinessLostStatus
 * @brief Information about the status dds::core::status::StatusMask::liveliness_lost()
 *
 * @details \dref_details_LivelinessLostStatus
 */
template<typename D>
class TLivelinessLostStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TLivelinessLostStatus, D)

    TLivelinessLostStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_LivelinessLostStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_LivelinessLostStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class LivelinessChangedStatus
 * @brief Information about the status dds::core::status::StatusMask::liveliness_changed()
 *
 * @details \dref_details_LivelinessChangedStatus
 */
template<typename D>
class TLivelinessChangedStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TLivelinessChangedStatus, D)

    TLivelinessChangedStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_LivelinessChangedStatus_alive_count */
    int32_t alive_count() const
    {
        return this->delegate().alive_count();
    }

    /** \dref_LivelinessChangedStatus_not_alive_count */
    int32_t not_alive_count() const
    {
        return this->delegate().not_alive_count();
    }

    /** \dref_LivelinessChangedStatus_alive_count_change */
    int32_t alive_count_change() const
    {
        return this->delegate().alive_count_change();
    }

    /** \dref_LivelinessChangedStatus_not_alive_count_change */
    int32_t not_alive_count_change() const
    {
        return this->delegate().not_alive_count_change();
    }

    /** \dref_LivelinessChangedStatus_last_publication_handle */
    const dds::core::InstanceHandle last_publication_handle() const
    {
        return this->delegate().last_publication_handle();
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class OfferedDeadlineMissedStatus
 * @brief Information about the status dds::core::status::StatusMask::offered_deadline_missed()
 *
 * @details \dref_details_OfferedDeadlineMissedStatus
 */
template<typename D>
class TOfferedDeadlineMissedStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TOfferedDeadlineMissedStatus, D)

    TOfferedDeadlineMissedStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_OfferedDeadlineMissedStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_OfferedDeadlineMissedStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }

    /** \dref_OfferedDeadlineMissedStatus_last_instance_handle */
    const dds::core::InstanceHandle last_instance_handle() const
    {
        return this->delegate().last_instance_handle();
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class RequestedDeadlineMissedStatus
 * @brief Information about the status dds::core::status::StatusMask::requested_deadline_missed()
 *
 * @details \dref_details_RequestedDeadlineMissedStatus
 */
template<typename D>
class TRequestedDeadlineMissedStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TRequestedDeadlineMissedStatus, D)

    TRequestedDeadlineMissedStatus() :
        dds::core::Value<D>()
    {
    }
public:
    /** \dref_RequestedDeadlineMissedStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_RequestedDeadlineMissedStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }

    /** \dref_RequestedDeadlineMissedStatus_last_instance_handle */
    const dds::core::InstanceHandle last_instance_handle() const
    {
        return this->delegate().last_instance_handle();
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class OfferedIncompatibleQosStatus
 * @brief Information about the status dds::core::status::StatusMask::offered_incompatible_qos()
 *
 * @details \dref_details_OfferedIncompatibleQosStatus
 */
template<typename D>
class TOfferedIncompatibleQosStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TOfferedIncompatibleQosStatus, D)

    TOfferedIncompatibleQosStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_OfferedIncompatibleQosStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_OfferedIncompatibleQosStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }

    /** \dref_OfferedIncompatibleQosStatus_last_policy_id */
    dds::core::policy::QosPolicyId last_policy_id() const
    {
        return this->delegate().last_policy_id();
    }

    /** \dref_OfferedIncompatibleQosStatus_policies */
    const dds::core::policy::QosPolicyCountSeq policies() const
    {
        return this->delegate().policies();
    }

};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class RequestedIncompatibleQosStatus
 * @brief Information about the status dds::core::status::StatusMask::requested_incompatible_qos()
 *
 * @details \dref_details_RequestedIncompatibleQosStatus
 */
template<typename D>
class TRequestedIncompatibleQosStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TRequestedIncompatibleQosStatus, D)

    TRequestedIncompatibleQosStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_RequestedIncompatibleQosStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_RequestedIncompatibleQosStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }

    /** \dref_RequestedIncompatibleQosStatus_last_policy_id */
    dds::core::policy::QosPolicyId last_policy_id() const
    {
        return this->delegate().last_policy_id();
    }

    /** \dref_RequestedIncompatibleQosStatus_policies */
     const dds::core::policy::QosPolicyCountSeq policies() const
     {
         return this->delegate().policies();
     }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class PublicationMatchedStatus
 * @brief Information about the status dds::core::status::StatusMask::publication_matched()
 *
 * @details \dref_details_PublicationMatchedStatus
 */
template<typename D>
class TPublicationMatchedStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TPublicationMatchedStatus, D)

    TPublicationMatchedStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_PublicationMatchedStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_PublicationMatchedStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }

    /** \dref_PublicationMatchedStatus_current_count */
    int32_t current_count() const
    {
        return this->delegate().current_count();
    }

    /** \dref_PublicationMatchedStatus_current_count_change */
    int32_t current_count_change() const
    {
        return this->delegate().current_count_change();
    }

    /** \dref_PublicationMatchedStatus_last_subscription_handle */
    const dds::core::InstanceHandle last_subscription_handle() const
    {
        return this->delegate().last_subscription_handle();
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @RTI_class_definition class SubscriptionMatchedStatus
 * @brief Information about the status dds::core::status::StatusMask::subscription_matched()
 *
 * @details \dref_details_SubscriptionMatchedStatus
 */
template<typename D>
class TSubscriptionMatchedStatus : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TSubscriptionMatchedStatus, D)

    TSubscriptionMatchedStatus() :
        dds::core::Value<D>()
    {
    }

public:
    /** \dref_SubscriptionMatchedStatus_total_count */
    int32_t total_count() const
    {
        return this->delegate().total_count();
    }

    /** \dref_SubscriptionMatchedStatus_total_count_change */
    int32_t total_count_change() const
    {
        return this->delegate().total_count_change();
    }

    /** \dref_SubscriptionMatchedStatus_current_count */
    int32_t current_count() const
    {
        return this->delegate().current_count();
    }

    /** \dref_SubscriptionMatchedStatus_current_count_change */
    int32_t current_count_change() const
    {
        return this->delegate().current_count_change();
    }

    /** \dref_SubscriptionMatchedStatus_last_publication_handle */
    const dds::core::InstanceHandle last_publication_handle() const
    {
        return this->delegate().last_publication_handle();
    }
};

} } } // namespace dds::core::status

#endif /* OMG_TDDS_CORE_STATUS_STATUS_HPP_ */
