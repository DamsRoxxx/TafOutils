/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dds_c_infrastructure_impl.h    generated by: makeheader    Fri Feb 16 13:51:57 2018
 *
 *		built from:	infrastructure_impl.ifc
 */

#ifndef dds_c_infrastructure_impl_h
#define dds_c_infrastructure_impl_h



/* Must be explicitly included to include the definition of size_t when
 * compiling under gcc 2.71 (e.g. Vx 5.4 architectures).
 */
#include <stddef.h>

#include "log/log_makeheader.h"

#ifndef pres_common_h
  #include "pres/pres_common.h"
#endif
#ifndef dds_c_infrastructure_h
  #include "dds_c/dds_c_infrastructure.h"
#endif
#ifndef dds_c_dll_h
  #include "dds_c/dds_c_dll.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif

extern DDSCDllExport void * DDS_Entity_get_participant_factoryI(DDS_Entity* self);

extern DDSCDllExport void* DDS_Entity_get_user_dataI(DDS_Entity* self);

extern DDSCDllExport void DDS_Entity_set_user_dataI(DDS_Entity* self,
        void* userData);

extern DDSCDllExport void DDS_Condition_set_user_objectI(DDS_Condition* self,
        void *userObject);

extern DDSCDllExport void* DDS_Condition_get_user_objectI(DDS_Condition* self);

extern DDSCDllExport DDS_GuardCondition* DDS_GuardCondition_newI(
    void * factory,
    void *userObject);

extern DDSCDllExport struct REDAExclusiveArea * 
DDS_GuardCondition_get_exclusive_areaI(DDS_GuardCondition * self);

 extern DDSCDllVariable const int DDS_WAITSET_EXCLUSIVE_AREA_LEVEL;

 extern DDSCDllVariable const int DDS_CONDITION_EXCLUSIVE_AREA_LEVEL;

extern DDSCDllExport DDS_WaitSet* DDS_WaitSet_newI(
    void * factory,
    long max_event_count, 
    const struct DDS_Duration_t *max_event_delay);

extern DDSCDllExport
DDS_ReturnCode_t DDS_WaitSet_initialize(DDS_WaitSet * self);

extern DDSCDllExport
DDS_ReturnCode_t DDS_WaitSet_finalize(DDS_WaitSet * self);

extern DDSCDllExport void DDS_WaitSet_set_user_objectI(DDS_WaitSet* self,
                                                         void *userObject);

/*i @ingroup DDSWaitSetModule
 * 
 * @brief   set user object pointer
 */    
extern DDSCDllExport void* DDS_WaitSet_get_user_objectI(DDS_WaitSet* self);

extern  DDSCDllExport
DDS_ReturnCode_t DDS_WaitSet_waitI(DDS_WaitSet* self,
        struct DDS_ConditionSeq* active_conditions,
        const struct DDS_Duration_t* timeout);

extern DDSCDllExport
int DDS_WaitSet_start_conditions_iteratorI(DDS_WaitSet* self,
                                           RTIBool activeConditions);

extern DDSCDllExport
void DDS_WaitSet_end_conditions_iteratorI(DDS_WaitSet* self);

extern DDSCDllExport
DDS_Condition* DDS_WaitSet_get_next_conditionI(DDS_WaitSet*self,
                                     RTIBool activeConditions);

extern DDSCDllExport
void DDS_WaitSet_end_waitI(DDS_WaitSet *self);

extern DDSCDllExport
size_t DDS_WaitSet_sizeof();

typedef struct DDS_CountingConditionImpl DDS_CountingCondition;


#define DDS_CountingCondition_as_condition(countingConditionPtr) \
            ((DDS_Condition*) countingConditionPtr)

extern DDSCDllExport 
DDS_CountingCondition * DDS_CountingCondition_newI(
        void *factory);

extern DDSCDllExport 
DDS_CountingCondition * DDS_CountingCondition_new();

extern DDSCDllExport 
DDS_ReturnCode_t DDS_CountingCondition_delete(DDS_CountingCondition *self);

extern DDSCDllExport 
DDS_ReturnCode_t DDS_CountingCondition_increment(
        DDS_CountingCondition *self, 
        DDS_Long count);

extern DDSCDllExport 
DDS_ReturnCode_t DDS_CountingCondition_decrement(
        DDS_CountingCondition *self, 
        DDS_Long count);

extern DDSCDllExport 
DDS_Long DDS_CountingCondition_get_count(DDS_CountingCondition *self);

struct REDAWorker;

extern DDSCDllExport struct REDAWorker* DDS_DomainEntity_get_workerI(
    DDS_Entity* self);

extern DDSCDllExport DDS_Boolean DDS_Entity_is_enabled(DDS_Entity* self);

extern DDSCDllExport DDS_Boolean DDS_Entity_is_vendor_specific(DDS_Entity* self);

extern DDSCDllExport void* DDS_Entity_get_reserved_dataI(DDS_Entity* self);

extern DDSCDllExport DDS_ReturnCode_t DDS_Entity_set_reserved_dataI(DDS_Entity* self, void* reserved_data);

extern DDSCDllExport void DDS_Entity_get_guid(
    DDS_Entity* self, struct DDS_GUID_t* guid);

extern DDSCDllExport DDS_Boolean
DDS_ProtocolVersion_equals(const DDS_ProtocolVersion_t *a, const DDS_ProtocolVersion_t *b);

extern DDSCDllExport DDS_Boolean
DDS_VendorId_equals(const struct DDS_VendorId_t *a, const struct DDS_VendorId_t *b);

extern DDSCDllExport
DDS_Boolean DDS_VendorId_is_rti(const struct DDS_VendorId_t *self);

extern DDSCDllExport DDS_Boolean 
DDS_ContentFilterProperty_equals(
    const struct DDS_ContentFilterProperty_t* left,
    const struct DDS_ContentFilterProperty_t* right);

extern DDSCDllExport DDS_Boolean 
DDS_DeadlineQosPolicy_equals(
    const struct DDS_DeadlineQosPolicy* left,
    const struct DDS_DeadlineQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_DestinationOrderQosPolicy_equals(
    const struct DDS_DestinationOrderQosPolicy* left,
    const struct DDS_DestinationOrderQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_DomainParticipantProtocolQosPolicy_equals(
    const struct DDS_DomainParticipantProtocolQosPolicy* left,
    const struct DDS_DomainParticipantProtocolQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_DurabilityQosPolicy_equals(
    const struct DDS_DurabilityQosPolicy* left,
    const struct DDS_DurabilityQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_DurabilityServiceQosPolicy_equals(
    const struct DDS_DurabilityServiceQosPolicy* left,
    const struct DDS_DurabilityServiceQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_TransportEncapsulationQosPolicy_equals(
   const struct DDS_TransportEncapsulationQosPolicy* left,
   const struct DDS_TransportEncapsulationQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_PublisherProtocolQosPolicy_equals(
   const struct DDS_PublisherProtocolQosPolicy* left,
   const struct DDS_PublisherProtocolQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_SubscriberProtocolQosPolicy_equals(
   const struct DDS_SubscriberProtocolQosPolicy* left,
   const struct DDS_SubscriberProtocolQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_EntityNameQosPolicy_equals(
    const struct DDS_EntityNameQosPolicy* left,
    const struct DDS_EntityNameQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_GroupDataQosPolicy_equals(
    const struct DDS_GroupDataQosPolicy* left,
    const struct DDS_GroupDataQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_EntityFactoryQosPolicy_equals(
    const struct DDS_EntityFactoryQosPolicy* left,
    const struct DDS_EntityFactoryQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_ExclusiveAreaQosPolicy_equals(
    const struct DDS_ExclusiveAreaQosPolicy* left,
    const struct DDS_ExclusiveAreaQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_TransportBuiltinQosPolicy_equals(
    const struct DDS_TransportBuiltinQosPolicy* left,
    const struct DDS_TransportBuiltinQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_LifespanQosPolicy_equals(
    const struct DDS_LifespanQosPolicy* left,
    const struct DDS_LifespanQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_LivelinessQosPolicy_equals(
    const struct DDS_LivelinessQosPolicy* left,
    const struct DDS_LivelinessQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_LocatorSeq_equals(
    const struct DDS_LocatorSeq* left,
    const struct DDS_LocatorSeq* right);

extern DDSCDllExport DDS_Boolean 
DDS_OwnershipQosPolicy_equals(
    const struct DDS_OwnershipQosPolicy* left,
    const struct DDS_OwnershipQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_OwnershipStrengthQosPolicy_equals(
    const struct DDS_OwnershipStrengthQosPolicy* left,
    const struct DDS_OwnershipStrengthQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_PartitionQosPolicy_equals(
    const struct DDS_PartitionQosPolicy* left,
    const struct DDS_PartitionQosPolicy* right);

extern DDSCDllExport DDS_Boolean DDS_PresentationQosPolicy_equals(
    const struct DDS_PresentationQosPolicy* left,
    const struct DDS_PresentationQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_ProductVersion_equals(
    const struct DDS_ProductVersion_t* left,
    const struct DDS_ProductVersion_t* right);

extern DDSCDllExport void 
DDS_ProductVersion_copyI(
    struct DDS_ProductVersion_t* self, 
    const struct DDS_ProductVersion_t* src);

extern DDSCDllExport void 
DDS_ProductVersion_get_rtidds_version(
    struct DDS_ProductVersion_t *self);

extern DDSCDllExport DDS_Boolean 
DDS_PropertyQosPolicy_equals(
    const struct DDS_PropertyQosPolicy* left,
    const struct DDS_PropertyQosPolicy* right,
    DDS_Boolean remote);

extern DDSCDllExport DDS_Boolean 
DDS_ReliabilityQosPolicy_equals(
    const struct DDS_ReliabilityQosPolicy* left,
    const struct DDS_ReliabilityQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_ServiceQosPolicy_equals(
    const struct DDS_ServiceQosPolicy* left,
    const struct DDS_ServiceQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_TimeBasedFilterQosPolicy_equals(
    const struct DDS_TimeBasedFilterQosPolicy* left,
    const struct DDS_TimeBasedFilterQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_TopicDataQosPolicy_equals(
    const struct DDS_TopicDataQosPolicy* left,
    const struct DDS_TopicDataQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_UserDataQosPolicy_equals(
    const struct DDS_UserDataQosPolicy* left,
    const struct DDS_UserDataQosPolicy* right);

extern DDSCDllExport DDS_Boolean
DDS_LatencyBudgetQosPolicy_equalI(
    const struct DDS_LatencyBudgetQosPolicy *dst,
    const struct DDS_LatencyBudgetQosPolicy *src);

extern DDSCDllExport DDS_Boolean
DDS_LocatorFilterQosPolicy_equals(
    const struct DDS_LocatorFilterQosPolicy *left,
    const struct DDS_LocatorFilterQosPolicy *right);

extern DDSCDllExport struct DDS_LocatorFilterQosPolicy*
DDS_LocatorFilterQosPolicy_copy(
    struct DDS_LocatorFilterQosPolicy *out,
    const struct DDS_LocatorFilterQosPolicy *in);

extern DDSCDllExport void
DDS_LocatorFilterQosPolicy_initialize(
    struct DDS_LocatorFilterQosPolicy* self);

extern DDSCDllExport void
DDS_LocatorFilterQosPolicy_finalize(
   struct DDS_LocatorFilterQosPolicy *self);

extern DDSCDllExport void 
DDS_LocatorFilter_t_initialize(
    struct DDS_LocatorFilter_t* locator_filter);

extern DDSCDllExport void 
DDS_LocatorFilter_t_finalize(
    struct DDS_LocatorFilter_t* locator_filter);

extern DDSCDllExport struct DDS_LocatorFilter_t*
DDS_LocatorFilter_t_copy(
    struct DDS_LocatorFilter_t* self,
    const struct DDS_LocatorFilter_t* from);

extern DDSCDllExport DDS_Boolean 
DDS_LocatorFilter_t_equals(
    const struct DDS_LocatorFilter_t* left,
    const struct DDS_LocatorFilter_t* right);

extern DDSCDllExport void 
DDS_EventQosPolicy_finalize(struct DDS_EventQosPolicy* self);

extern DDSCDllExport void 
DDS_EventQosPolicy_initialize(struct DDS_EventQosPolicy* self);

extern DDSCDllExport DDS_Boolean
DDS_EventQosPolicy_equals(
    const struct DDS_EventQosPolicy* left,
    const struct DDS_EventQosPolicy* right);

extern DDSCDllExport
struct DDS_EventQosPolicy* DDS_EventQosPolicy_copy(
    struct DDS_EventQosPolicy* self,
    const struct DDS_EventQosPolicy* src);

extern DDSCDllExport DDS_Boolean
DDS_ReceiverPoolQosPolicy_equals(
    const struct DDS_ReceiverPoolQosPolicy * left,
    const struct DDS_ReceiverPoolQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_DomainParticipantResourceLimitsQosPolicy_equals(
    const struct DDS_DomainParticipantResourceLimitsQosPolicy * left,
    const struct DDS_DomainParticipantResourceLimitsQosPolicy * right);

extern DDSCDllExport DDS_ReturnCode_t
DDS_DiscoveryQosPolicy_get_default(
    struct DDS_DiscoveryQosPolicy* self);

extern DDSCDllExport DDS_Boolean
DDS_DiscoveryConfigQosPolicy_equals(
    const struct DDS_DiscoveryConfigQosPolicy * left,
    const struct DDS_DiscoveryConfigQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_HistoryQosPolicy_equals(
    const struct DDS_HistoryQosPolicy * left,
    const struct DDS_HistoryQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_ResourceLimitsQosPolicy_equals(
    const struct DDS_ResourceLimitsQosPolicy * left,
    const struct DDS_ResourceLimitsQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_TransportPriorityQosPolicy_equals(
    const struct DDS_TransportPriorityQosPolicy * left,
    const struct DDS_TransportPriorityQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_WriterDataLifecycleQosPolicy_equals(
    const struct DDS_WriterDataLifecycleQosPolicy * left,
    const struct DDS_WriterDataLifecycleQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_DataWriterResourceLimitsQosPolicy_equals(
    const struct DDS_DataWriterResourceLimitsQosPolicy * left,
    const struct DDS_DataWriterResourceLimitsQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_DataWriterProtocolQosPolicy_equals(
    const struct DDS_DataWriterProtocolQosPolicy * left,
    const struct DDS_DataWriterProtocolQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_TypeSupportQosPolicy_equals(
    const struct DDS_TypeSupportQosPolicy * left,
    const struct DDS_TypeSupportQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_UserObjectQosPolicy_equals(
    const struct DDS_UserObjectQosPolicy * left,
    const struct DDS_UserObjectQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_ReaderDataLifecycleQosPolicy_equals(
    const struct DDS_ReaderDataLifecycleQosPolicy * left,
    const struct DDS_ReaderDataLifecycleQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_DataReaderResourceLimitsQosPolicy_equals(
    const struct DDS_DataReaderResourceLimitsQosPolicy * left,
    const struct DDS_DataReaderResourceLimitsQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_DataReaderProtocolQosPolicy_equals(
    const struct DDS_DataReaderProtocolQosPolicy * left,
    const struct DDS_DataReaderProtocolQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_TopicProtocolQosPolicy_equals(
    const struct DDS_TopicProtocolQosPolicy * left,
    const struct DDS_TopicProtocolQosPolicy * right);

extern DDSCDllExport DDS_Boolean
DDS_TypeConsistencyEnforcementQosPolicy_equals(
    const struct DDS_TypeConsistencyEnforcementQosPolicy* self,
    const struct DDS_TypeConsistencyEnforcementQosPolicy* other);

extern DDSCDllExport DDS_Boolean 
DDS_MultiChannelQosPolicy_equals(
    const struct DDS_MultiChannelQosPolicy *left,
    const struct DDS_MultiChannelQosPolicy *right);

extern DDSCDllExport void 
DDS_MultiChannelQosPolicy_initialize(
    struct DDS_MultiChannelQosPolicy* self);

extern DDSCDllExport struct DDS_MultiChannelQosPolicy* 
DDS_MultiChannelQosPolicy_copy(
    struct DDS_MultiChannelQosPolicy *out,
    const struct DDS_MultiChannelQosPolicy *in);

extern DDSCDllExport void 
DDS_MultiChannelQosPolicy_finalize(struct DDS_MultiChannelQosPolicy *self);

extern DDSCDllExport void 
DDS_ChannelSettings_t_initialize(
    struct DDS_ChannelSettings_t* channel_settings);

extern DDSCDllExport void 
DDS_ChannelSettings_t_finalize(
    struct DDS_ChannelSettings_t* channel_settings);

extern DDSCDllExport struct DDS_ChannelSettings_t*
DDS_ChannelSettings_t_copy(
    struct DDS_ChannelSettings_t* self,
    const struct DDS_ChannelSettings_t* from);

extern DDSCDllExport DDS_Boolean DDS_ChannelSettings_t_equals(
    const struct DDS_ChannelSettings_t* left,
    const struct DDS_ChannelSettings_t* right);

extern DDSCDllExport void 
DDS_TransportMulticastSettings_t_initialize(
	struct DDS_TransportMulticastSettings_t* self);

extern DDSCDllExport void 
DDS_TransportMulticastSettings_t_finalize(
	struct DDS_TransportMulticastSettings_t* self);

extern DDSCDllExport struct DDS_TransportMulticastSettings_t*
DDS_TransportMulticastSettings_t_copy(
               struct DDS_TransportMulticastSettings_t* self, 
               const struct DDS_TransportMulticastSettings_t* from);

extern DDSCDllExport RTIBool
DDS_TransportMulticastSettings_equals(
    const struct DDS_TransportMulticastSettings_t* left, 
    const struct DDS_TransportMulticastSettings_t* right);

extern DDSCDllExport
DDS_Boolean DDS_PublishModeQosPolicy_equals(
    const struct DDS_PublishModeQosPolicy* self,
    const struct DDS_PublishModeQosPolicy* other);

extern DDSCDllExport
void DDS_PublishModeQosPolicy_free_name(struct DDS_PublishModeQosPolicy * self);

extern DDSCDllExport RTIBool 
DDS_WireProtocolQosPolicy_equals(
    const struct DDS_WireProtocolQosPolicy* left,
    const struct DDS_WireProtocolQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_SystemResourceLimitsQosPolicy_equals(
   const struct DDS_SystemResourceLimitsQosPolicy *left, 
   const struct DDS_SystemResourceLimitsQosPolicy *right);

extern DDSCDllExport RTIBool
DDS_TransportSelectionQosPolicy_equals(
    const struct DDS_TransportSelectionQosPolicy* left,
    const struct DDS_TransportSelectionQosPolicy* right);

extern DDSCDllExport struct DDS_TransportSelectionQosPolicy*
DDS_TransportSelectionQosPolicy_copy(
                struct DDS_TransportSelectionQosPolicy* self,
                const struct DDS_TransportSelectionQosPolicy* from);

extern DDSCDllExport void 
DDS_TransportSelectionQosPolicy_initialize(
                struct DDS_TransportSelectionQosPolicy* self);

extern DDSCDllExport void 
DDS_TransportSelectionQosPolicy_finalize(
                struct DDS_TransportSelectionQosPolicy* self);

extern DDSCDllExport
RTIBool DDS_RtpsReliableReaderProtocol_equals(
    const struct DDS_RtpsReliableReaderProtocol_t* left,
    const struct DDS_RtpsReliableReaderProtocol_t* right);

extern DDSCDllExport
void DDS_RtpsReliableReaderProtocol_copy(
    struct DDS_RtpsReliableReaderProtocol_t *dst,
    const struct DDS_RtpsReliableReaderProtocol_t *src);

extern DDSCDllExport
DDS_Boolean DDS_AsynchronousPublisherQosPolicy_equals(
        const struct DDS_AsynchronousPublisherQosPolicy* self,
        const struct DDS_AsynchronousPublisherQosPolicy* other);

extern DDSCDllExport
void DDS_AsynchronousPublisherQosPolicy_initialize(
    struct DDS_AsynchronousPublisherQosPolicy* self);

extern DDSCDllExport void 
DDS_AsynchronousPublisherQosPolicy_finalize(
    struct DDS_AsynchronousPublisherQosPolicy* self);

extern DDSCDllExport void
DDS_EndpointGroup_t_finalize(struct DDS_EndpointGroup_t* self);

extern DDSCDllExport void
DDS_EndpointGroup_t_initialize(struct DDS_EndpointGroup_t* self);

extern DDSCDllExport struct DDS_EndpointGroup_t *
DDS_EndpointGroup_t_copy(struct DDS_EndpointGroup_t* self,
                         const struct DDS_EndpointGroup_t* from);

extern DDSCDllExport DDS_Boolean 
DDS_EndpointGroup_t_equals(
    const struct DDS_EndpointGroup_t* left,
    const struct DDS_EndpointGroup_t* right);

extern DDSCDllExport DDS_Boolean 
DDS_EndpointGroupSeq_equals(
    const struct DDS_EndpointGroupSeq* left,
    const struct DDS_EndpointGroupSeq* right);

extern DDSCDllExport void 
DDS_AvailabilityQosPolicy_initialize(struct DDS_AvailabilityQosPolicy* self);

extern DDSCDllExport void 
DDS_AvailabilityQosPolicy_finalize(struct DDS_AvailabilityQosPolicy *self);

extern DDSCDllExport struct DDS_AvailabilityQosPolicy* 
DDS_AvailabilityQosPolicy_copy(
    struct DDS_AvailabilityQosPolicy *out,
    const struct DDS_AvailabilityQosPolicy *in);

extern DDSCDllExport DDS_Boolean 
DDS_AvailabilityQosPolicy_equals(
    const struct DDS_AvailabilityQosPolicy* left,
    const struct DDS_AvailabilityQosPolicy* right);

extern DDSCDllExport void 
DDS_RtpsReliableWriterProtocol_copy(
    struct DDS_RtpsReliableWriterProtocol_t *dst,
    const struct DDS_RtpsReliableWriterProtocol_t *src);

extern DDSCDllExport RTIBool 
DDS_RtpsReliableWriterProtocol_equals(
    const struct DDS_RtpsReliableWriterProtocol_t* self,
    const struct DDS_RtpsReliableWriterProtocol_t* other);

extern DDSCDllExport void 
DDS_ReceiverPoolQosPolicy_initialize(struct DDS_ReceiverPoolQosPolicy* self);

extern DDSCDllExport void
DDS_ReceiverPoolQosPolicy_finalize(struct DDS_ReceiverPoolQosPolicy* self);

extern DDSCDllExport struct DDS_ReceiverPoolQosPolicy* 
DDS_ReceiverPoolQosPolicy_copy(
    struct DDS_ReceiverPoolQosPolicy* self,
    const struct DDS_ReceiverPoolQosPolicy* src);

extern DDSCDllExport DDS_Boolean 
DDS_ReceiverPoolQosPolicy_equals(
    const struct DDS_ReceiverPoolQosPolicy * left,
    const struct DDS_ReceiverPoolQosPolicy * right);

extern DDSCDllExport void 
DDS_DiscoveryConfigQosPolicy_initialize(
    struct DDS_DiscoveryConfigQosPolicy* self);

extern DDSCDllExport void 
DDS_DiscoveryConfigQosPolicy_finalize(
    struct DDS_DiscoveryConfigQosPolicy* self);

extern DDSCDllExport struct DDS_DiscoveryConfigQosPolicy*
DDS_DiscoveryConfigQosPolicy_copy(
    struct DDS_DiscoveryConfigQosPolicy* dst,
    const struct DDS_DiscoveryConfigQosPolicy* src);

extern DDSCDllExport DDS_Boolean 
DDS_DiscoveryConfigQosPolicy_equals(
    const struct DDS_DiscoveryConfigQosPolicy * left,
    const struct DDS_DiscoveryConfigQosPolicy * right);

extern DDSCDllExport void 
DDS_WriterDataLifecycleQosPolicy_copy(
    struct DDS_WriterDataLifecycleQosPolicy *dst,
    const struct DDS_WriterDataLifecycleQosPolicy *src);

extern DDSCDllExport void 
DDS_TransportMulticastQosPolicy_initialize(
    struct DDS_TransportMulticastQosPolicy* self);

extern DDSCDllExport void 
DDS_TransportMulticastQosPolicy_finalize(
    struct DDS_TransportMulticastQosPolicy* self);

extern DDSCDllExport struct DDS_TransportMulticastQosPolicy*
DDS_TransportMulticastQosPolicy_copy(
                struct DDS_TransportMulticastQosPolicy* self,
                const struct DDS_TransportMulticastQosPolicy* from);

extern DDSCDllExport RTIBool
DDS_TransportMulticastQosPolicy_equals(
    const struct DDS_TransportMulticastQosPolicy* left, 
    const struct DDS_TransportMulticastQosPolicy* right);

extern DDSCDllExport void 
DDS_TransportMulticastMappingQosPolicy_initialize(
    struct DDS_TransportMulticastMappingQosPolicy* self);

extern DDSCDllExport void 
DDS_TransportMulticastMappingQosPolicy_finalize(
    struct DDS_TransportMulticastMappingQosPolicy* self);

extern DDSCDllExport struct DDS_TransportMulticastMappingQosPolicy*
DDS_TransportMulticastMappingQosPolicy_copy(
                struct DDS_TransportMulticastMappingQosPolicy* self,
                const struct DDS_TransportMulticastMappingQosPolicy* from);

extern DDSCDllExport RTIBool
DDS_TransportMulticastMappingQosPolicy_equals(
    const struct DDS_TransportMulticastMappingQosPolicy* left,
    const struct DDS_TransportMulticastMappingQosPolicy* right);

extern DDSCDllExport void 
DDS_TransportMulticastMapping_t_initialize(
	struct DDS_TransportMulticastMapping_t* self);

extern DDSCDllExport void 
DDS_TransportMulticastMapping_t_finalize(
	struct DDS_TransportMulticastMapping_t* self);

extern DDSCDllExport struct DDS_TransportMulticastMapping_t*
DDS_TransportMulticastMapping_t_copy(
               struct DDS_TransportMulticastMapping_t* self, 
               const struct DDS_TransportMulticastMapping_t* from);

extern DDSCDllExport RTIBool
DDS_TransportMulticastMapping_t_is_equal(
    const struct DDS_TransportMulticastMapping_t* left, 
    const struct DDS_TransportMulticastMapping_t* right);

extern DDSCDllExport void 
DDS_TransportMulticastMappingFunction_t_initialize(
	struct DDS_TransportMulticastMappingFunction_t* self);

extern DDSCDllExport void 
DDS_TransportMulticastMappingFunction_t_finalize(
	struct DDS_TransportMulticastMappingFunction_t* self);

extern DDSCDllExport struct DDS_TransportMulticastMappingFunction_t*
DDS_TransportMulticastMappingFunction_t_copy(
               struct DDS_TransportMulticastMappingFunction_t* self, 
               const struct DDS_TransportMulticastMappingFunction_t* from);

extern DDSCDllExport RTIBool
DDS_TransportMulticastMappingFunction_t_is_equal(
    const struct DDS_TransportMulticastMappingFunction_t* left, 
    const struct DDS_TransportMulticastMappingFunction_t* right);

extern DDSCDllExport void 
DDS_AckResponseData_t_initialize(struct DDS_AckResponseData_t* self);

extern DDSCDllExport void 
DDS_AckResponseData_t_finalize(struct DDS_AckResponseData_t* self);

extern DDSCDllExport struct DDS_AckResponseData_t* 
DDS_AckResponseData_t_copy(
        struct DDS_AckResponseData_t* self,
        const struct DDS_AckResponseData_t* src);

extern DDSCDllExport DDS_Boolean 
DDS_AckResponseData_equals(
    const struct DDS_AckResponseData_t* left,
    const struct DDS_AckResponseData_t* right);

extern DDSCDllExport DDS_ReturnCode_t 
DDS_StringSeq_from_delimited_string(
    struct DDS_StringSeq* self, const char* src, char delim);

extern DDSCDllExport
RTIBool DDS_StringSeq_equals(
        const struct DDS_StringSeq * self, 
        const struct DDS_StringSeq * other);

extern DDSCDllVariable
const struct DDS_StringSeq DDS_STRING_SEQUENCE_EMPTY;

extern DDSCDllExport
DDS_Boolean DDS_OctetSeq_equals(
            const struct DDS_OctetSeq *left,
            const struct DDS_OctetSeq *right);

extern DDSCDllExport
void DDS_OctetSeq_print(const struct DDS_OctetSeq *self);

extern DDSCDllExport 
DDS_Boolean DDS_BatchQosPolicy_equals(
    const struct DDS_BatchQosPolicy* self,
    const struct DDS_BatchQosPolicy* other);

extern DDSCDllExport DDS_Boolean 
DDS_AvailabilityQosPolicy_equals(
    const struct DDS_AvailabilityQosPolicy* left,
    const struct DDS_AvailabilityQosPolicy* right);

extern DDSCDllExport
DDS_Boolean DDS_AllocationSettings_equalsI(
    const struct DDS_AllocationSettings_t* left,
    const struct DDS_AllocationSettings_t* right);

extern DDSCDllExport void 
DDS_DomainParticipantConfigParams_t_initialize(
        struct DDS_DomainParticipantConfigParams_t * self);

extern DDSCDllExport void 
DDS_DomainParticipantConfigParams_t_finalize(
        struct DDS_DomainParticipantConfigParams_t * self);

extern DDSCDllExport RTIBool 
DDS_DomainParticipantConfigParams_t_copyStringMember(
        char ** stringMemberPtr,
        const char * newStringValue);

extern DDSCDllExport struct DDS_DomainParticipantConfigParams_t *
DDS_DomainParticipantConfigParams_t_copy(
        struct DDS_DomainParticipantConfigParams_t * self,
        const struct DDS_DomainParticipantConfigParams_t * src);

extern DDSCDllExport DDS_Boolean 
DDS_DomainParticipantConfigParams_t_equals(
        const struct DDS_DomainParticipantConfigParams_t * left,
        const struct DDS_DomainParticipantConfigParams_t * right);

extern DDSCDllExport void
DDS_TopicQueryDispatchQosPolicy_initialize(struct
    DDS_TopicQueryDispatchQosPolicy* self);

extern DDSCDllExport struct DDS_TopicQueryDispatchQosPolicy*
DDS_TopicQueryDispatchQosPolicy_copy(
        struct DDS_TopicQueryDispatchQosPolicy* self,
        const struct DDS_TopicQueryDispatchQosPolicy* src);

extern DDSCDllExport DDS_Boolean
DDS_TopicQueryDispatchQosPolicy_equals(
        const struct DDS_TopicQueryDispatchQosPolicy* self,
        const struct DDS_TopicQueryDispatchQosPolicy* other);



#define DDS_ProtocolVersion_equals(a, b)   \
    ((a)->major == (b)->major && \
     (a)->minor == (b)->minor)

#define DDS_VendorId_equals(a, b)   \
    ((a)->vendorId[0] == (b)->vendorId[0] && \
     (a)->vendorId[1] == (b)->vendorId[1])

#define DDS_VendorId_is_rti(self) \
    ((self)->vendorId[0] == MIG_RTPS_VENDOR_ID_MAJOR \
            && (self)->vendorId[1] == MIG_RTPS_VENDOR_ID_MINOR)


extern DDSCDllExport
void DDS_GUID_copy_to_pres_guid(const struct DDS_GUID_t* self,
                                struct MIGRtpsGuid * other);

extern DDSCDllExport
void DDS_GUID_copy_from_pres_guid(struct DDS_GUID_t* self,
                                  const struct MIGRtpsGuid * other);

extern DDSCDllExport
void DDS_GUID_copy_from_pres_octet_guid(struct DDS_GUID_t* self,
                                  const struct PRESOctetGuid * other);

extern DDSCDllExport
void DDS_GUID_copy_to_key_hash(const struct DDS_GUID_t* self,
                               struct MIGRtpsKeyHash *keyHash);

extern DDSCDllExport
void DDS_GUID_copy_from_key_hash(struct DDS_GUID_t* self,
                                 const struct MIGRtpsKeyHash *keyHash);

extern DDSCDllExport
void DDS_GUID_to_instance_handle(
        const struct DDS_GUID_t *self,
        DDS_InstanceHandle_t * instanceHandle);

extern DDSCDllExport
void DDS_GUID_from_instance_handle(
        struct DDS_GUID_t *self,
        const DDS_InstanceHandle_t * instanceHandle);


/* Forward declaration */
struct DDS_SampleInfo;

extern DDSCDllExport
void DDS_WriteParams_from_sample_info(
        struct DDS_WriteParams_t *self,
        const struct DDS_SampleInfo *info);

extern DDSCDllExport
void DDS_BuiltinTopicKey_set_object_idI(
        DDS_BuiltinTopicKey_t *self,
        MIGRtpsObjectId objectId);

extern DDSCDllExport
void DDS_BuiltinTopicKey_set_host_idI(
        DDS_BuiltinTopicKey_t *self,
        MIGRtpsHostId hostId);

extern DDSCDllExport
void DDS_BuiltinTopicKey_set_app_idI(
        DDS_BuiltinTopicKey_t *self,
        MIGRtpsAppId appId);

extern DDSCDllExport
void DDS_BuiltinTopicKey_set_instance_idI(
        DDS_BuiltinTopicKey_t *self,
        MIGRtpsInstanceId instanceId);

extern DDSCDllExport
MIGRtpsObjectId DDS_BuiltinTopicKey_get_object_idI(
        const DDS_BuiltinTopicKey_t *self);

extern DDSCDllExport
void DDS_BuiltinTopicKey_to_mig_rtps_guidI(
        const DDS_BuiltinTopicKey_t *self,
        struct MIGRtpsGuid *dst);

extern DDSCDllExport
void DDS_BuiltinTopicKey_from_mig_rtps_guidI(
        DDS_BuiltinTopicKey_t* self,
        const struct MIGRtpsGuid *src);


#define DDS_SHARED_SUBSCRIBER_NAME_PROPERTY "dds.data_reader.shared_subscriber_name"


#ifdef __cplusplus
    }   /* extern "C" */
#endif

#endif /* dds_c_infrastructure_impl_h */
