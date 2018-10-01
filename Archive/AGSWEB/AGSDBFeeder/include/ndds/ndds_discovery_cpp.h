/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)ndds_discovery_cpp.h    generated by: makeheader    Fri Feb 16 13:52:08 2018
 *
 *		built from:	ndds_discovery_cpp.ifcxx
 */

#ifndef ndds_discovery_cpp_h
#define ndds_discovery_cpp_h


#ifndef dds_cpp_dll_h
  #include "dds_cpp/dds_cpp_dll.h"
#endif
#ifndef ndds_transport_c_h
  #include "ndds/ndds_discovery_c.h"
#endif
#ifndef dds_cpp_domain_h
  #include "dds_cpp/dds_cpp_domain.h"
#endif

class DDSCPPDllExport NDDSDiscoverySupport {
  public:
    /*e \dref_Discovery_Support_register_participant_plugin */
    static DDS_ReturnCode_t register_participant_plugin(
    DDSDomainParticipant *disabled_participant,
    struct NDDS_Discovery_ParticipantPlugin& discovery_plugin);

    /*e \dref_Discovery_Support_register_endpoint_plugin */
    static DDS_ReturnCode_t register_endpoint_plugin(
    DDSDomainParticipant *disabled_participant,
    struct NDDS_Discovery_EndpointPlugin& discovery_plugin);
};

#endif /* ndds_discovery_cpp_h */