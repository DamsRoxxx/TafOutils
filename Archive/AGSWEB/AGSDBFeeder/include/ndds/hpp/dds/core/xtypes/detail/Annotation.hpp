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
#ifndef OMG_DDS_CORE_XTYPES_DETAIL_ANNOTATIONS_HPP_
#define OMG_DDS_CORE_XTYPES_DETAIL_ANNOTATIONS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace dds {
  namespace core {
    namespace xtypes {
      namespace detail {
        class Annotation { };

        class IdAnnotation : public  Annotation { };

        class KeyAnnotation : public  Annotation { };

        class SharedAnnotation : public  Annotation  { };

        class NestedAnnotation : public  Annotation  { };

        class ExtensibilityAnnotation : public  Annotation  { };

        class MustUnderstandAnnotation : public  Annotation { };

        class VerbatimAnnotation : public  Annotation { };

        class BitsetAnnotation : public  Annotation { };

        class BitBoundAnnotation : public  Annotation  { };
      }
    }
  }
}
#endif /* OMG_DDS_CORE_XTYPES_DETAIL_ANNOTATIONS_HPP_ */
