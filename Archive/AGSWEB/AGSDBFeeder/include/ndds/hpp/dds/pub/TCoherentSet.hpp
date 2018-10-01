#ifndef OMG_TDDS_PUB_COHERENT_SET_HPP_
#define OMG_TDDS_PUB_COHERENT_SET_HPP_

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
    class TCoherentSet;
  }
}

/** 
 * @ingroup DDSPublisherModule 
 * @RTI_class_definition class dds::pub::CoherentSet
 * @headerfile CoherentSet.hpp "dds/pub/CoherentSet.hpp"
 *  
 * @brief @st_value_type A publishing application can request that a set of
 * DDS data-sample changes be propagated in such a way that they are
 * interpreted at the receivers' side as a cohesive set of modifications. 
 *  
 * @details In this case, the receiver will only be able to access the data 
 * after all the modifications in the set are available at the subscribing end.
 */
template <typename DELEGATE>
class dds::pub::TCoherentSet : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TCoherentSet, DELEGATE)

  /**
   * @brief Creating a CoherentSet object indicates that the application will 
   * begin a coherent set of modifications using dds::pub::DataWriter objects 
   * attached to the dds::pub::Publisher.
   *  
   * \dref_details_Publisher_begin_coherent_changes 
   *  
   * @param pub The Publisher 
   */
  explicit TCoherentSet(const dds::pub::Publisher& pub)
      : dds::core::Value<DELEGATE>(pub)
  {
  }

public:
  /**
   * @brief Explicitly terminate a coherent set initiated by the CoherentSet 
   * constructor 
   *  
   * \dref_details_Publisher_end_coherent_changes 
   */
  void end()
  {
      this->delegate().end();
  }

public:
  /**
   * @brief Implicitly terminate a coherent set 
   * @see end() 
   */
  ~TCoherentSet()
  {
      // Will call delegate's destructor
  }
};


#endif /* OMG_TDDS_PUB_COHERENT_SET_HPP_ */

