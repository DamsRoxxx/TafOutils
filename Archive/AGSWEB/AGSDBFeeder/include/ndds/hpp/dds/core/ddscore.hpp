#ifndef OMG_DDS_CORE_PACKAGE_INCLUDE_HPP_
#define OMG_DDS_CORE_PACKAGE_INCLUDE_HPP_

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

/////////////////////////////////////////////////////////////////////////////
// -- Status Includes

/*
 * Depends on:
 *  <dds/core/macros.hpp> 
 */
#include <dds/core/status/State.hpp> 

/*
 * Depends on:
 *  <dds/core/status/State.hpp>
 *  <dds/core/InstanceHandle.hpp>
 */
#include <dds/core/status/Status.hpp> 

/////////////////////////////////////////////////////////////////////////////
// -- Condition Includes

/*
 * Depends on:
 *  <dds/core/Exception.hpp> 
 */
#include <dds/core/cond/Condition.hpp>

/*
 * Depends on:
 *  <dds/core/status/State.hpp> 
 */
#include <dds/core/cond/GuardCondition.hpp>

/*
 * Depends on:
 *  <dds/core/status/State.hpp>
 *  <dds/core/cond/Condition.hpp>
 */
#include <dds/core/cond/StatusCondition.hpp>

/*
 * Depends on:
 *  forward declaration of Duration
 */
#include <dds/core/cond/WaitSet.hpp>

/////////////////////////////////////////////////////////////////////////////
// -- Policy Includes

/*
 * Depends on:
 *  <dds/core/SafeEnumeration.hpp>
 */
#include <dds/core/policy/PolicyKind.hpp> 

/*
 * Depends on:
 *  <dds/core/types.hpp>
 *  <dds/core/Value.hpp>
 */
#include <dds/core/policy/QosPolicyCount.hpp> 

/*
 * Depends on:
 *  <dds/core/policy/QosPolicyCount.hpp> 
 *  <dds/core/policy/PolicyKind.hpp> 
 */
#include <dds/core/policy/CorePolicy.hpp> 

/////////////////////////////////////////////////////////////////////////////
// -- Xtypes Includes
#include <dds/core/xtypes/AliasType.hpp> 
#include <dds/core/xtypes/Annotations.hpp> 
#include <dds/core/xtypes/CollectionTypes.hpp> 
#include <dds/core/xtypes/DynamicData.hpp> 
#include <dds/core/xtypes/DynamicType.hpp> 
#include <dds/core/xtypes/EnumType.hpp> 
#include <dds/core/xtypes/MemberType.hpp> 
#include <dds/core/xtypes/PrimitiveTypes.hpp> 
#include <dds/core/xtypes/StructType.hpp> 
#include <dds/core/xtypes/TypeKind.hpp> 
#include <dds/core/xtypes/TypeProvider.hpp> 
#include <dds/core/xtypes/UnionType.hpp> 

/////////////////////////////////////////////////////////////////////////////
// -- Core Includes

/*
 * Depends on:
 *  <dds/core/macros.hpp> 
 */
#include <dds/core/Exception.hpp>

/*
 * Depends on:
 *  <dds/core/macros.hpp> 
 */
#include <dds/core/array.hpp> 

/*
 * Depends on:
 *  <dds/core/String.hpp> 
 */
#include <dds/core/BuiltinTopicTypes.hpp> 

/*
 * Depends on:
 *  <dds/core/types.hpp>
 */
#include <dds/core/Duration.hpp> 

/*
 * Depends on:
 *  <dds/core/ref_traits.hpp>
 *  <dds/core/status/Status.hpp>
 *  <dds/core/cond/StatusCondition.hpp>
*/
#include <dds/core/Entity.hpp>

/*
 * Depends on:
 *  <dds/core/types.hpp>
 *  <dds/core/Value.hpp>
 */
#include <dds/core/InstanceHandle.hpp>

#include <dds/core/LengthUnlimited.hpp> 

/*
 * Depends on:
 *  <dds/core/Exception.hpp>
 *  <dds/core/Value.hpp>
 */
#include <dds/core/Optional.hpp> 

/*
 * Depends on:
 *  <dds/core/Reference.hpp>
 *  <dds/core/ref_traits.hpp>
 *  <dds/core/Exception.hpp>
 */
#include <dds/core/QosProvider.hpp> 

#include <rti/core/BuiltinProfiles.hpp>

#include <dds/core/String.hpp>

/*
 * Depends on:
 *  <dds/core/types.hpp>
 */
#include <dds/core/Time.hpp> 

#include <dds/core/vector.hpp>

// using namespace dds::core::all will include all core sub-namespaces
namespace dds {

 /**
  * @brief The core namespace contains infrastructure types and functions.
  */
namespace core {

namespace all {

using namespace dds::core;
using namespace dds::core::policy;
using namespace dds::core::cond;
using namespace dds::core::status;
using namespace dds::core::xtypes;

} // namespace all

/**
 * @brief Contains the standard Qos policy classes.
 */
namespace policy {}

/**
 * @brief Contains the Condition classes
 */
namespace cond {}

/**
 * @brief Contains the Status and State classes
 */
namespace status {}


/**
 * @brief Contains the types and functions to support Extensible Types
 */
namespace xtypes {}


} // namespace core

} // namespace dds

#endif /* OMG_DDS_CORE_PACKAGE_INCLUDE_HPP_ */
