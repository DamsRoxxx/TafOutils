#ifndef RTI_DDS_SUB_PACKAGE_INCLUDE_HPP_
#define RTI_DDS_SUB_PACKAGE_INCLUDE_HPP_

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

#include <dds/sub/ddssub.hpp>

#include <rti/sub/TopicQuery.hpp>
#include <rti/sub/status/DataStateEx.hpp>

// using namespace rti::sub::all will include all sub sub-namespaces
namespace rti {

/**
 * @brief @extension Extensions to dds::sub
 */
namespace sub {

namespace all {

using namespace dds::sub::all;

using namespace rti::sub;
using namespace rti::sub::cond;
using namespace rti::sub::qos;
using namespace rti::sub::status;

}

}

} // namespace rti::sub::all


#endif /* RTI_DDS_SUB_PACKAGE_INCLUDE_HPP_ */
