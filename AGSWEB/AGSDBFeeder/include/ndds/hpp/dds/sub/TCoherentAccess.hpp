#ifndef OMG_DDS_SUB_TCOHERENT_ACCESS_HPP_
#define OMG_DDS_SUB_TCOHERENT_ACCESS_HPP_

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
#include <dds/sub/subfwd.hpp>

namespace dds {
  namespace sub {
    template <typename DELEGATE>
    class TCoherentAccess;
  }
}

/** 
 * @ingroup DDSSubscriberModule 
 * @RTI_class_definition class dds::sub::CoherentAccess
 * @headerfile CoherentAccess.hpp "dds/sub/CoherentAccess.hpp"
 *  
 * @brief @st_value_type Controls whether \ndds will preserve the groupings of
 * changes made by the publishing application by means of begin_coherent_changes
 * and end_coherent_changes.
 */
template <typename DELEGATE>
class dds::sub::TCoherentAccess : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TCoherentAccess, DELEGATE)

  /** 
   * @brief Creating a CoherentAccess object indicates that the 
   * application is about to access the data samples 
   * in any of the DataReader objects attached to the provided Subscriber. 
   *
   * @details \dref_details_Subscriber_begin_access
   */
  explicit TCoherentAccess(const dds::sub::Subscriber& sub)
    :dds::core::Value<DELEGATE>(sub)
  {
  }

public:
  /**
   * @brief Explicitly indicate that the application has finished accessing 
   * the data samples in DataReader objects managed by the Subscriber.  
   *
   * @details \dref_details_Subscriber_end_access
   */
  void end()         // ends access explicitly
  {
      this->delegate().end();
  }

public:

  /**
   * @brief The destructor implicitly ends coherent access 
   *  
   * @see end() 
   */
  ~TCoherentAccess()  // ends access implicitly
  {
      // Will call delegate's destructor
  }

private:
  TCoherentAccess(const TCoherentAccess&);
  TCoherentAccess& operator=(const TCoherentAccess&);
};


#endif /* OMG_TDDS_SUB_TCOHERENT_ACCESS_HPP_ */
