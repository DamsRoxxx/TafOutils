/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dds_c_builtin_impl.h    generated by: makeheader    Fri Feb 16 13:51:57 2018
 *
 *		built from:	builtin_impl.ifc
 */

#ifndef dds_c_builtin_impl_h
#define dds_c_builtin_impl_h


  #ifndef dds_c_dll_h
    #include "dds_c/dds_c_dll.h"
  #endif
  #ifndef dds_c_topic_impl_h
    #include "dds_c/dds_c_topic_impl.h"
  #endif
  #ifndef dds_c_builtin_h
    #include "dds_c/dds_c_builtin.h"
  #endif
  #ifndef cdr_stream_impl_h
    #include "cdr/cdr_stream_impl.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

 extern DDSCDllVariable const char *DDS_PARTICIPANT_TYPE_NAME;

extern DDSCDllExport struct PRESTypePlugin* 
DDS_ParticipantBuiltinTopicDataPlugin_new();

extern DDSCDllExport void 
DDS_ParticipantBuiltinTopicDataPlugin_delete(struct PRESTypePlugin *self);

extern DDSCDllExport void 
DDS_ParticipantBuiltinTopicDataPluginSupport_print_data(
    const struct DDS_ParticipantBuiltinTopicData* userData,
    const char* desc, int indent);

extern DDSCDllExport struct DDS_ParticipantBuiltinTopicData *
DDS_ParticipantBuiltinTopicDataPluginSupport_create_data();

extern DDSCDllExport struct DDS_ParticipantBuiltinTopicData*
DDS_ParticipantBuiltinTopicDataPluginSupport_create_data_ex(
    RTIBool allocatePointers);

extern DDSCDllExport struct DDS_ParticipantBuiltinTopicData*
DDS_ParticipantBuiltinTopicDataPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void 
DDS_ParticipantBuiltinTopicDataPluginSupport_destroy_data(
    struct DDS_ParticipantBuiltinTopicData* userData);

extern DDSCDllExport void 
DDS_ParticipantBuiltinTopicDataPluginSupport_destroy_data_ex(
    struct DDS_ParticipantBuiltinTopicData* userData,
    RTIBool deletePointers);

extern DDSCDllExport void 
DDS_ParticipantBuiltinTopicDataPluginSupport_destroy_data_w_params(
    struct DDS_ParticipantBuiltinTopicData* userData,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport void
DDS_ParticipantBuiltinTopicData_initialize_ex(
    struct DDS_ParticipantBuiltinTopicData* self,
    RTIBool allocatePointers,
    RTIBool allocateMemory);

extern DDSCDllExport void 
DDS_ParticipantBuiltinTopicData_finalize_ex(
    struct DDS_ParticipantBuiltinTopicData* self,
    RTIBool deletePointers);

extern DDSCDllExport void
DDS_ParticipantBuiltinTopicData_initialize_w_params(
    struct DDS_ParticipantBuiltinTopicData* self,
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void 
DDS_ParticipantBuiltinTopicData_finalize_w_params(
    struct DDS_ParticipantBuiltinTopicData* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

 extern DDSCDllVariable const char *DDS_TOPIC_TYPE_NAME;

extern DDSCDllExport struct PRESTypePlugin* 
DDS_TopicBuiltinTopicDataPlugin_new();

extern DDSCDllExport void 
DDS_TopicBuiltinTopicDataPlugin_delete(struct PRESTypePlugin *self);

extern DDSCDllExport void 
DDS_TopicBuiltinTopicData_initialize_ex(
    struct DDS_TopicBuiltinTopicData* self,
    RTIBool allocatePointers,
    RTIBool allocateMemory);

extern DDSCDllExport void 
DDS_TopicBuiltinTopicData_finalize_ex(
    struct DDS_TopicBuiltinTopicData* self,
    RTIBool deletePointers);

extern DDSCDllExport void
DDS_TopicBuiltinTopicData_initialize_w_params(
    struct DDS_TopicBuiltinTopicData* self,
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void 
DDS_TopicBuiltinTopicData_finalize_w_params(
    struct DDS_TopicBuiltinTopicData* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport struct DDS_TopicBuiltinTopicData * 
DDS_TopicBuiltinTopicDataPluginSupport_create_data();

extern DDSCDllExport struct DDS_TopicBuiltinTopicData *
DDS_TopicBuiltinTopicDataPluginSupport_create_data_ex(
    RTIBool allocatePointers);

extern DDSCDllExport struct DDS_TopicBuiltinTopicData*
DDS_TopicBuiltinTopicDataPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void 
DDS_TopicBuiltinTopicDataPluginSupport_destroy_data(
    struct DDS_TopicBuiltinTopicData* userData);

extern DDSCDllExport void 
DDS_TopicBuiltinTopicDataPluginSupport_destroy_data_ex(
    struct DDS_TopicBuiltinTopicData* userData,
    RTIBool allocatePointers);

extern DDSCDllExport void 
DDS_TopicBuiltinTopicDataPluginSupport_destroy_data_w_params(
    struct DDS_TopicBuiltinTopicData* userData,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport void 
DDS_TopicBuiltinTopicDataPluginSupport_print_data(
    const struct DDS_TopicBuiltinTopicData* p,
    const char* desc, int indent);

 extern DDSCDllVariable const char *DDS_PUBLICATION_TYPE_NAME;

extern DDSCDllExport struct PRESTypePlugin* 
DDS_PublicationBuiltinTopicDataPlugin_new();

extern DDSCDllExport void
DDS_PublicationBuiltinTopicData_initialize_w_params(
    struct DDS_PublicationBuiltinTopicData* self,
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void 
DDS_PublicationBuiltinTopicData_finalize_w_params(
    struct DDS_PublicationBuiltinTopicData* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport void 
DDS_PublicationBuiltinTopicDataPluginSupport_destroy_data_w_params(
    struct DDS_PublicationBuiltinTopicData* userData,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport struct DDS_PublicationBuiltinTopicData*
DDS_PublicationBuiltinTopicDataPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void
DDS_PublicationBuiltinTopicDataPlugin_delete(struct PRESTypePlugin *self);

extern DDSCDllExport void 
DDS_PublicationBuiltinTopicData_initialize_ex(
    struct DDS_PublicationBuiltinTopicData* self,
    RTIBool allocatePointers,
    RTIBool allocateMemory);

extern DDSCDllExport void 
DDS_PublicationBuiltinTopicData_finalize_ex(
    struct DDS_PublicationBuiltinTopicData* self,
    RTIBool deletePointers);

extern DDSCDllExport struct DDS_PublicationBuiltinTopicData * 
DDS_PublicationBuiltinTopicDataPluginSupport_create_data();

extern DDSCDllExport struct DDS_PublicationBuiltinTopicData*
DDS_PublicationBuiltinTopicDataPluginSupport_create_data_ex(
    RTIBool allocatePointers);

extern DDSCDllExport void 
DDS_PublicationBuiltinTopicDataPluginSupport_destroy_data(
    struct DDS_PublicationBuiltinTopicData* userData);

extern DDSCDllExport void 
DDS_PublicationBuiltinTopicDataPluginSupport_destroy_data_ex(
    struct DDS_PublicationBuiltinTopicData* userData,
    RTIBool allocatePointers);

extern DDSCDllExport void 
DDS_PublicationBuiltinTopicDataPluginSupport_print_data(
    const struct DDS_PublicationBuiltinTopicData* p,
    const char* desc, int indent);

 extern DDSCDllVariable const char *DDS_SUBSCRIPTION_TYPE_NAME;

extern DDSCDllExport struct PRESTypePlugin* 
DDS_SubscriptionBuiltinTopicDataPlugin_new();

extern DDSCDllExport void
DDS_SubscriptionBuiltinTopicData_initialize_w_params(
    struct DDS_SubscriptionBuiltinTopicData* self,
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void 
DDS_SubscriptionBuiltinTopicData_finalize_w_params(
    struct DDS_SubscriptionBuiltinTopicData* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport void 
DDS_SubscriptionBuiltinTopicDataPluginSupport_destroy_data_w_params(
    struct DDS_SubscriptionBuiltinTopicData* userData,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport struct DDS_SubscriptionBuiltinTopicData*
DDS_SubscriptionBuiltinTopicDataPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void
DDS_SubscriptionBuiltinTopicDataPlugin_delete(struct PRESTypePlugin *self);

extern DDSCDllExport void 
DDS_SubscriptionBuiltinTopicData_initialize_ex(
    struct DDS_SubscriptionBuiltinTopicData* self,
    RTIBool allocatePointers,
    RTIBool allocateMemory);

extern DDSCDllExport void
DDS_SubscriptionBuiltinTopicData_finalize_ex(
    struct DDS_SubscriptionBuiltinTopicData* self,
    RTIBool deletePointers);

extern DDSCDllExport struct DDS_SubscriptionBuiltinTopicData *
DDS_SubscriptionBuiltinTopicDataPluginSupport_create_data();

extern DDSCDllExport struct DDS_SubscriptionBuiltinTopicData *
DDS_SubscriptionBuiltinTopicDataPluginSupport_create_data_ex(
    RTIBool allocatePointers);

extern DDSCDllExport void 
DDS_SubscriptionBuiltinTopicDataPluginSupport_destroy_data(
    struct DDS_SubscriptionBuiltinTopicData* userData);

extern DDSCDllExport void 
DDS_SubscriptionBuiltinTopicDataPluginSupport_destroy_data_ex(
    struct DDS_SubscriptionBuiltinTopicData* userData,
    RTIBool allocatePointers);

extern DDSCDllExport void 
DDS_SubscriptionBuiltinTopicDataPluginSupport_print_data(
    const struct DDS_SubscriptionBuiltinTopicData* p,
    const char* desc, int indent);

 extern DDSCDllVariable const char *DDS_VIRTUAL_SUBSCRIPTION_TYPE_NAME;

extern DDSCDllExport struct PRESTypePlugin* 
DDS_VirtualSubscriptionBuiltinTopicDataPlugin_new();

extern DDSCDllExport void
DDS_VirtualSubscriptionBuiltinTopicData_initialize_w_params(
    struct DDS_VirtualSubscriptionBuiltinTopicData* self,
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void 
DDS_VirtualSubscriptionBuiltinTopicData_finalize_w_params(
    struct DDS_VirtualSubscriptionBuiltinTopicData* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport void 
DDS_VirtualSubscriptionBuiltinTopicDataPluginSupport_destroy_data_w_params(
    struct DDS_VirtualSubscriptionBuiltinTopicData* userData,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

extern DDSCDllExport struct DDS_VirtualSubscriptionBuiltinTopicData*
DDS_VirtualSubscriptionBuiltinTopicDataPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * allocParams);

extern DDSCDllExport void 
DDS_VirtualSubscriptionBuiltinTopicDataPlugin_delete(struct PRESTypePlugin *self);

extern DDSCDllExport void 
DDS_VirtualSubscriptionBuiltinTopicDataPluginSupport_print_data(
    const struct DDS_VirtualSubscriptionBuiltinTopicData* userData,
    const char* desc, int indent);

extern DDSCDllExport struct DDS_VirtualSubscriptionBuiltinTopicData *
DDS_VirtualSubscriptionBuiltinTopicDataPluginSupport_create_data();

extern DDSCDllExport struct DDS_VirtualSubscriptionBuiltinTopicData*
DDS_VirtualSubscriptionBuiltinTopicDataPluginSupport_create_data_ex(
    RTIBool allocatePointers);

extern DDSCDllExport void 
DDS_VirtualSubscriptionBuiltinTopicDataPluginSupport_destroy_data(
    struct DDS_VirtualSubscriptionBuiltinTopicData* userData);

extern DDSCDllExport void 
DDS_VirtualSubscriptionBuiltinTopicDataPluginSupport_destroy_data_ex(
    struct DDS_VirtualSubscriptionBuiltinTopicData* userData,
    RTIBool deletePointers);

extern DDSCDllExport void
DDS_VirtualSubscriptionBuiltinTopicData_initialize_ex(
    struct DDS_VirtualSubscriptionBuiltinTopicData* self,
    RTIBool allocatePointers,
    RTIBool allocateMemory);

extern DDSCDllExport void 
DDS_VirtualSubscriptionBuiltinTopicData_finalize_ex(
    struct DDS_VirtualSubscriptionBuiltinTopicData* self,
    RTIBool deletePointers);

 extern DDSCDllVariable const char *DDS_SERVICE_REQUEST_TYPE_NAME;

 extern DDSCDllVariable const char *DDS_PARTICIPANT_GENERIC_MESSAGE_TYPE_NAME;

extern DDSCDllExport DDS_Boolean DDS_Builtin_is_builtin_topicI(
    const char* topic_name);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* dds_c_builtin_impl_h */
