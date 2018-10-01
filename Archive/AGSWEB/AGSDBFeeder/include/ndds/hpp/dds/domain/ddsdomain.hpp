#ifndef OMG_DDS_DOMAIN_PACKAGE_INCLUDE_HPP_
#define OMG_DDS_DOMAIN_PACKAGE_INCLUDE_HPP_

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
// -- QoS Includes
#include <dds/domain/qos/DomainParticipantQos.hpp>
#include <dds/domain/qos/DomainParticipantFactoryQos.hpp>

/////////////////////////////////////////////////////////////////////////////
// -- Domain Includes

/* Depends on:
 *   <dds/domain/qos/DomainParticipantFactoryQos.hpp>  
 *   <dds/domain/qos/DomainParticipantQos.hpp>         
 */
#include <dds/domain/DomainParticipant.hpp>

/* Depends on:
 *   <dds/domain/DomainParticipant.hpp>         
 */
#include <dds/domain/DomainParticipantListener.hpp>

/* Depends on:
 *   <dds/domain/DomainParticipant.hpp>         
 */
#include <dds/domain/find.hpp>

/* Depends on:
 *   <dds/domain/DomainParticipant.hpp>         
 */
#include <dds/domain/discovery.hpp>

// using namespace dds::domain::all will include all domain sub-namespaces
namespace dds {

/**
 * @brief The domain namespace contains types, classes, and functions related
 * to DomainParticipants.
 */
namespace domain {

namespace all {

using namespace dds::domain;
using namespace dds::domain::qos;

}  // namespace all

/**
 * @brief Contains DomainParticipantQos
 */
namespace qos {}

} // namespace domain

} // namespace dds

#endif /* OMG_DDS_DOMAIN_PACKAGE_INCLUDE_HPP_ */
