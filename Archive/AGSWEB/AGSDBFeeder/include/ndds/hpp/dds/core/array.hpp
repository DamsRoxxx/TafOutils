#ifndef  ORG_OMG_DDS_CORE_ARRAY_HPP_
#define  ORG_OMG_DDS_CORE_ARRAY_HPP_

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

#ifdef RTI_NO_CXX11_HDR_ARRAY
  #include <rtiboost/array.hpp>
#else
  #include <array>
#endif

namespace dds { namespace core {

#ifdef RTI_NO_CXX11_HDR_ARRAY
  using ::rtiboost::array; // For pre-C++11 systems, use boost array
#else
  using ::std::array; // Otherwise use the standard-library array
#endif

#ifdef DOXYGEN_DOCUMENTATION_ONLY
  /**
   * @ingroup DDSCPP2SupportingTypes
   *
   * @brief Represents an IDL array
   *
   * An \ref DDSTypesModule "IDL" array maps to this C++ type.
   *
   * This type is \p std::array if supported or \p boost::array otherwise.
   */
  typedef boost_or_std_array array;
#endif

#ifdef RTI_NO_CXX11_HDR_ARRAY
/**
 * Returns an iterator to the beginning of the given container
 */
template<typename Container>
typename Container::iterator begin(Container& t)
{
    return t.begin();
}

/**
 * Returns an iterator to the end of the given container
 */
template<typename Container>
typename Container::iterator end(Container& t)
{
    return t.end();
}

/**
 * Returns an const iterator to the beginning of the given container
 */
template<typename Container>
typename Container::const_iterator begin(const Container& t)
{
    return t.begin();
}

/**
 * Returns an const iterator to the end of the given container
 */
template<typename Container>
typename Container::const_iterator end(const Container& t)
{
    return t.end();
}

#else

using ::std::end;
using ::std::begin;

#endif

} }

#endif /* ORG_OMG_DDS_CORE_ARRAY_HPP_  */
