#ifndef __OMG_DDS_DDS_HPP__
#define __OMG_DDS_DDS_HPP__

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

#include <dds/core/ddscore.hpp>
#include <dds/domain/ddsdomain.hpp>
#include <dds/topic/ddstopic.hpp>
#include <dds/sub/ddssub.hpp>
#include <dds/pub/ddspub.hpp>

/**
 * @brief The dds namespace.
 * The dds namespace includes all of the standard types, classes,
 * and functions.
 */
namespace dds {

/**
 * @brief @extension A single namespace where all standard symbols are included.
 *
 * The namespace \p dds::all brings all symbols to a single namespace as an
 * alternative way of using the different namespaces such as \p dds::core,
 * \p dds::core::cond, \p dds::sub, etc.
 *
 * For example:
 *
 * \code
 * #include <dds/dds.hpp>
 *
 * void test_namespace()
 * {
 *     using namespace dds::all;
 *
 *     DomainParticipant participant(MY_DOMAIN_ID); // dds::domain
 *     Topic<StringTopicType> topic(participant, "My Topic"); // dds::topic and dds::core
 * }
 * \endcode
 *
 */
namespace all {

using namespace ::dds::core::all;
using namespace ::dds::domain::all;
using namespace ::dds::topic::all;
using namespace ::dds::pub::all;
using namespace ::dds::sub::all;

} }

#endif // __OMG_DDS_DDS_HPP__
