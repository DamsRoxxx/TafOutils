/* $Id$

 (c) Copyright, Real-Time Innovations, 2013-2016. 
 All rights reserved.
 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

===================================================================== */

#ifndef RTI_TEST_ABSTRACTDOMAINTESTER_HPP_
#define RTI_TEST_ABSTRACTDOMAINTESTER_HPP_

#include <stdio.h>
#include <stdlib.h>

#include "log/log_makeheader.h"

#include "test/test_setting.h"
#include <rti/test/Tester.hpp>

#include <dds/domain/DomainParticipant.hpp>

namespace rti { namespace test {

/*
 * Provides a common way of creating a test domain participant with the right
 * ID and QoS.
 *
 * It also automatically finalizes the domain participant factory on
 * destruction.
 *
 * Testers that create domain participants should inherit from this class
 */
class AbstractDomainTester : public Tester {
public:
    static const dds::domain::qos::DomainParticipantQos& test_qos()
    {
        using namespace dds::core;
        static dds::domain::qos::DomainParticipantQos qos;
      #if defined(RTI_ANDROID) || defined(RTI_IOS)
        const bool acceptUnknownPeers = true;
      #else
        const bool acceptUnknownPeers = false;
      #endif

        qos << rti::core::policy::Database().shutdown_cleanup_period(
            dds::core::Duration::from_millisecs(10));

        StringSeq initial_peers_list;
        initial_peers_list.push_back("1@localhost");
      #ifdef RTI_SHARED_MEMORY
        initial_peers_list.push_back("shmem://");
      #endif

        qos << rti::core::policy::Discovery()
            .initial_peers(initial_peers_list)
            .multicast_receive_addresses(StringSeq())
            .accept_unknown_peers(acceptUnknownPeers);

        return qos;
    }

protected:
    AbstractDomainTester(
        const std::string& name,
        RTITestLevel test_level = RTI_TEST_LEVEL_UNIT,
        bool tests_require_file_system = false)
    : Tester(name, test_level, tests_require_file_system)
    {
    }

    virtual ~AbstractDomainTester() {}

    dds::domain::DomainParticipant create_participant()
    {
        return dds::domain::DomainParticipant(domain_id(), test_qos());
    }
};

} } // namespace rti::test

#endif

// --------------------------------------------------------------------

/* End $Id$ */
