#ifndef OMG_DDS_CORE_INSTANCE_HANDLE_HPP_
#define OMG_DDS_CORE_INSTANCE_HANDLE_HPP_

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

#include <vector>
#include <dds/core/detail/InstanceHandle.hpp>


namespace dds { namespace core {
  typedef dds::core::detail::InstanceHandle InstanceHandle;

  /**
   * @ingroup DDSUserDataModule
   * @brief A sequence of dds::core::InstanceHandle
   */
  typedef std::vector<InstanceHandle> InstanceHandleSeq;
} }

/**
 * @relatesalso dds::core::InstanceHandle
 * 
 * @brief Prints an instance handle
 * 
 * The format is 16 2-digit contiguous hexadecimal numbers, for example:
 * 
 * \code
 * 0000004d000000000000000000000000
 * \endcode
 * 
 */
inline std::ostream& operator << (std::ostream& os, const dds::core::InstanceHandle& h)
{
    return (os << h.delegate());
}


#endif /* !defined(OMG_DDS_CORE_INSTANCE_HANDLE_HPP_) */
