#ifndef OMG_TDDS_PUB_SUSPENDED_PUBLICATION_HPP_
#define OMG_TDDS_PUB_SUSPENDED_PUBLICATION_HPP_

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

#include <dds/pub/Publisher.hpp>

namespace dds {
  namespace pub {
    template <typename DELEGATE>
    class TSuspendedPublication;
  }
}


/**
 * @ingroup DDSPublisherModule
 * @RTI_class_definition class dds::pub::SuspendedPublication
 * @headerfile dds/pub/SuspendedPublication.hpp
 *
 * @brief @st_value_type Indicates that the application is about to make
 * multiple modifications using several dds::pub::DataWriter's belonging to
 * the same dds::pub::Publisher
 *
 * @details \dref_details_Publisher_suspend_publications
 *
 * @see \ref DDSWriterExampleModule
 * @see \ref DDSEntityExampleModuleForCpp2
 */
template <typename DELEGATE>
class dds::pub::TSuspendedPublication : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TSuspendedPublication, DELEGATE)

  /**
   * @brief Suspends the publications of the publisher
   */
  explicit TSuspendedPublication(const dds::pub::Publisher& pub)
      : dds::core::Value<DELEGATE>(pub)
  {
  }

  /**
   * @brief Indicates that the application has completed these changes
   */
  void resume() // resumes publications explicitly
  {
      this->delegate().resume();
  }

  /**
   * @brief Calls resume()
   */
  ~TSuspendedPublication() {}
};


#endif /* OMG_TDDS_PUB_SUSPENDED_PUBLICATION_HPP_ */
