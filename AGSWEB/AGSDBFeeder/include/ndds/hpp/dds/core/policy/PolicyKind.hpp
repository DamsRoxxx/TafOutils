#ifndef OMG_DDS_CORE_POLICY_POLICYKIND_HPP_
#define OMG_DDS_CORE_POLICY_POLICYKIND_HPP_

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
#include <dds/core/SafeEnumeration.hpp>

namespace dds { namespace core { namespace policy {

/**
 * @ingroup DDSOwnershipQosModule
 * @brief The definition of the dds::core::safe_enum OwnershipKind
 */
struct OwnershipKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * \dref_OwnershipQosPolicyKind_SHARED_OWNERSHIP_QOS
         */
        SHARED,
        /**
         * \dref_OwnershipQosPolicyKind_EXCLUSIVE_OWNERSHIP_QOS
         */
        EXCLUSIVE
    };
};

/**
 * @ingroup DDSOwnershipQosModule
 * @brief @ref SafeEnumModule of @ref OwnershipKind_def
 * @see @ref OwnershipKind_def
 * */
typedef dds::core::safe_enum<OwnershipKind_def> OwnershipKind;

/**
 * @ingroup DDSDurabilityQosModule
 * @brief The definition of the dds::core::safe_enum DurabilityKind
 */
struct DurabilityKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * \dref_DurabilityQosPolicyKind_VOLATILE_DURABILITY_QOS
         */
        VOLATILE,
        /**
         * \dref_DurabilityQosPolicyKind_TRANSIENT_LOCAL_DURABILITY_QOS
         */
        TRANSIENT_LOCAL,
        /**
         * \dref_DurabilityQosPolicyKind_TRANSIENT_DURABILITY_QOS
         */
        TRANSIENT,
        /**
         * \dref_DurabilityQosPolicyKind_PERSISTENT_DURABILITY_QOS
         */
        PERSISTENT
    };
};

/**
 * @ingroup DDSDurabilityQosModule
 * @brief @ref SafeEnumModule of @ref DurabilityKind_def
 * @see @ref DurabilityKind_def
 * */
typedef dds::core::safe_enum<DurabilityKind_def> DurabilityKind;

/**
 * @ingroup DDSPresentationQosModule
 * @brief The definition of the dds::core::safe_enum PresentationAccessScopeKind
 */
struct PresentationAccessScopeKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * \dref_PresentationQosPolicyAccessScopeKind_INSTANCE_PRESENTATION_QOS
         */
        INSTANCE,
        /**
         * \dref_PresentationQosPolicyAccessScopeKind_TOPIC_PRESENTATION_QOS
         */
        TOPIC,
        /**
         * \dref_PresentationQosPolicyAccessScopeKind_GROUP_PRESENTATION_QOS
         */
        GROUP,
        /**
         * \dref_PresentationQosPolicyAccessScopeKind_HIGHEST_OFFERED_PRESENTATION_QOS
         */
        HIGHEST_OFFERED
    };
};

/**
 * @ingroup DDSPresentationQosModule
 * @brief @ref SafeEnumModule of @ref PresentationAccessScopeKind_def
 * @see @ref PresentationAccessScopeKind_def
 * */
typedef dds::core::safe_enum<PresentationAccessScopeKind_def> PresentationAccessScopeKind;

/**
 * @ingroup DDSReliabilityQosModule
 * @brief The definition of the dds::core::safe_enum ReliabilityKind
 */
struct ReliabilityKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * @brief Indicates that it is acceptable to not retry propagation of any samples.
         *
         * @details \dref_details_ReliabilityQosPolicyKind_BEST_EFFORT_RELIABILITY_QOS
         */
        BEST_EFFORT,
        /**
         * @brief Specifies that \ndds will attempt to deliver all samples in its history.
         * Missed samples may be retried.
         *
         * @details \dref_details_ReliabilityQosPolicyKind_RELIABLE_RELIABILITY_QOS
         */
        RELIABLE
    };
};

/**
 * @ingroup DDSReliabilityQosModule
 * @brief @ref SafeEnumModule of @ref ReliabilityKind_def
 * @see @ref ReliabilityKind_def
 */
typedef dds::core::safe_enum<ReliabilityKind_def> ReliabilityKind;

/**
 * @ingroup DDSDestinationOrderQosModule
 * @brief The definition of the dds::core::safe_enum DestinationOrderKind
 */
struct DestinationOrderKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * \dref_DestinationOrderQosPolicyKind_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS
         */
        BY_RECEPTION_TIMESTAMP,
        /**
         * \dref_DestinationOrderQosPolicyKind_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
         */
        BY_SOURCE_TIMESTAMP
    };
};

/**
 * @ingroup DDSDestinationOrderQosModule
 * @brief @ref SafeEnumModule of @ref DestinationOrderKind_def
 * @see @ref DestinationOrderKind_def
 * */
typedef dds::core::safe_enum<DestinationOrderKind_def> DestinationOrderKind;

/**
 * @ingroup DDSHistoryQosModule
 * @brief The definition of the dds::core::safe_enum HistoryKind
 */
struct HistoryKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * \dref_HistoryQosPolicyKind_KEEP_LAST_HISTORY_QOS
         */
        KEEP_LAST,

        /**
         * \dref_HistoryQosPolicyKind_KEEP_ALL_HISTORY_QOS
         */
        KEEP_ALL
    };
};

/**
 * @ingroup DDSHistoryQosModule
 * @brief @ref SafeEnumModule of @ref HistoryKind_def
 * @see @ref HistoryKind_def
 * */
typedef dds::core::safe_enum<HistoryKind_def> HistoryKind;

/**
 * @ingroup DDSLivelinessQosModule
 * @brief The definition of the dds::core::safe_enum LivelinessKind
 */
struct LivelinessKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * \dref_LivelinessQosPolicyKind_AUTOMATIC_LIVELINESS_QOS
         */
        AUTOMATIC,

        /**
         * \dref_LivelinessQosPolicyKind_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS
         */
        MANUAL_BY_PARTICIPANT,

        /**
         * \dref_LivelinessQosPolicyKind_MANUAL_BY_TOPIC_LIVELINESS_QOS
         */
        MANUAL_BY_TOPIC
    };
};

/**
 * @ingroup DDSLivelinessQosModule
 * @brief @ref SafeEnumModule of @ref LivelinessKind_def
 * @see @ref LivelinessKind_def
 */
typedef dds::core::safe_enum<LivelinessKind_def> LivelinessKind;

/**
 * @ingroup DDSTypeConsistencyEnforcementQosModule
 * @brief The definition of the dds::core::safe_enum TypeConsistencyEnforcementKind
 */
struct TypeConsistencyEnforcementKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * \dref_TypeConsistencyKind_DISALLOW_TYPE_COERCION
         */
        DISALLOW_TYPE_COERCION,

        /**
         * \dref_TypeConsistencyKind_ALLOW_TYPE_COERCION
         */
        ALLOW_TYPE_COERCION
    };
};

/**
 * @ingroup DDSTypeConsistencyEnforcementQosModule
 * @brief @ref SafeEnumModule of @ref TypeConsistencyEnforcementKind_def
 * @see @ref TypeConsistencyEnforcementKind_def
 * */
typedef dds::core::safe_enum<TypeConsistencyEnforcementKind_def> TypeConsistencyEnforcementKind;

} } }
#endif /* OMG_DDS_CORE_POLICY_POLICYKIND_HPP_ */
