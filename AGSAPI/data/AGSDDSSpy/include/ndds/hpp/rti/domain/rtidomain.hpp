#ifndef RTI_DDS_DOMAIN_PACKAGE_INCLUDE_HPP_
#define RTI_DDS_DOMAIN_PACKAGE_INCLUDE_HPP_

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

#include <dds/domain/ddsdomain.hpp>
#include <rti/domain/find.hpp>

// using namespace rti::domain::all will include all domain sub-namespaces
namespace rti {

/**
 * @brief @extension Extensions to dds::domain
 */
namespace domain {

namespace all {

using namespace rti::domain::all;

using namespace rti::domain;
using namespace rti::domain::qos;

}  // namespace all

} // namespace domain

} // namespace dds

#endif // RTI_DDS_DOMAIN_PACKAGE_INCLUDE_HPP_
