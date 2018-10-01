/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,07mar13,acr Created
===================================================================== */

#ifndef RTI_DDS_TOPIC_ANY_TOPIC_DESCRIPTION_IMPL_HPP_
#define RTI_DDS_TOPIC_ANY_TOPIC_DESCRIPTION_IMPL_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/domain/DomainParticipant.hpp>

namespace rti { namespace topic {

class TDHolderBase {
public:
    virtual ~TDHolderBase()
    {
    }

    virtual dds::domain::DomainParticipant domain_participant() const = 0;
    virtual const std::string name() const = 0;
    virtual const std::string type_name() const = 0;
};

template<typename T>
class TDHolder: public virtual TDHolderBase {
public:

    TDHolder(const dds::topic::TopicDescription<T>& topic_description)
        : topic_description_(topic_description)
    {
    }

    virtual ~TDHolder()
    {
    }

public:

    virtual dds::domain::DomainParticipant domain_participant() const
    {
        return topic_description_.domain_participant();
    }

    virtual const std::string name() const
    {
        return topic_description_.name();
    }

    virtual const std::string type_name() const
    {
        return topic_description_.type_name();
    }

protected:
    dds::topic::TopicDescription<T> topic_description_;
};

} } // namespace rti::topic

#endif // RTI_DDS_TOPIC_ANY_TOPIC_DESCRIPTION_IMPL_HPP_
