#ifndef __OMG_RTI_RTI_HPP__
#define __OMG_RTI_RTI_HPP__

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

#include <dds/dds.hpp>

#include <rti/core/rticore.hpp>
#include <rti/domain/rtidomain.hpp>
#include <rti/topic/rtitopic.hpp>
#include <rti/sub/rtisub.hpp>
#include <rti/pub/rtipub.hpp>
#include <rti/config/Logger.hpp>
#include <rti/config/Version.hpp>
#include <rti/util/util.hpp>

// using namespace rti::all will include all dds and rti namespaces

/**
 * @brief @extension The namespace that contains the extension types and
 * functions to the DDS standard.
 *
 * The rti namespace mirrors the structure of the dds namespace with the same
 * sub-namespaces and two more: rti::config and rti::util.
 */
namespace rti {

/**
 * @brief @extension A single namespace where all symbols are included.
 *
 * This is similar to dds::all but it also includes the extension symbols. This
 * namespace is defined in "rti/rti.hpp".
 *
 * @see dds::all
 */
namespace all {

using namespace ::dds::all;

using namespace ::rti::core::all;
using namespace ::rti::domain::all;
using namespace ::rti::topic::all;
using namespace ::rti::pub::all;
using namespace ::rti::sub::all;
using namespace ::rti::util;
using namespace ::rti::config;

}

}

#endif // __OMG_RTI_RTI_HPP__
