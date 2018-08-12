/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0b,22oct14,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_DETAIL_QOS_POLICY_MACROS_HPP_
#define RTI_DDS_CORE_DETAIL_QOS_POLICY_MACROS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#define RTI_DECL_POLICY_GETTER(CLASS, POLICY, FIELD)                          \
template<>                                                                    \
OMG_DDS_API const POLICY& CLASS::policy<POLICY>() const;                      \
                                                                              \
template<>                                                                    \
OMG_DDS_API POLICY& CLASS::policy<POLICY>();                                  \

// ----------------------------------------------------------------------------

#define RTI_DEFINE_POLICY_GETTER(CLASS, POLICY, FIELD)                        \
template<>                                                                    \
OMG_DDS_API const POLICY& CLASS::policy<POLICY>() const                       \
{                                                                             \
    return FIELD;                                                             \
}                                                                             \
                                                                              \
template<>                                                                    \
OMG_DDS_API POLICY& CLASS::policy<POLICY>()                                   \
{                                                                             \
    return FIELD;                                                             \
}

#endif // RTI_DDS_CORE_DETAIL_QOS_POLICY_MACROS_HPP_

