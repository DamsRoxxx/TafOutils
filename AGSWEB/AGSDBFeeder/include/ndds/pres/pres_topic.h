/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_topic.h    generated by: makeheader    Fri Feb 16 13:51:43 2018
 *
 *		built from:	topic.ifc
 */

#ifndef pres_topic_h
#define pres_topic_h


 #ifndef reda_database_h
    #include "reda/reda_database.h"
 #endif
 #ifndef pres_dll_h
    #include "pres/pres_dll.h"
 #endif
 #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
 #endif
 #ifndef pres_common_h
    #include "pres/pres_common.h"
 #endif
 #ifndef pres_participant_h
    #include "pres/pres_participant.h"
 #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct PRESTopic;

struct PRESContentFilteredTopic;

struct REDAWorker;

struct PRESInconsistentTopicStatus;

struct PRESTopicListener;

struct PRESTopicProperty;

struct PRESLocalEndpoint;

extern PRESDllExport
RTIBool PRESTopic_enable(
    struct PRESTopic *topic, int *failReason, struct REDAWorker *worker);

extern PRESDllExport
RTIBool PRESTopic_isEnabled(struct PRESTopic *topic);

extern PRESDllExport void
    PRESTopic_getInstanceHandle(
    struct PRESTopic *topic,
    struct PRESInstanceHandle *handle);

extern PRESDllExport
RTIBool PRESTopic_getInconsistentTopicStatus(
    struct PRESTopic *me,
    struct PRESInconsistentTopicStatus *status, RTIBool clearChange, struct REDAWorker *worker);

extern PRESDllExport
RTIBool PRESTopic_setInconsistentTopicStatus(
    struct PRESTopic *me, int *failReason,
    const struct PRESInconsistentTopicStatus *status, 
    struct REDAWorker *worker);

extern PRESDllExport
RTIBool PRESTopic_setProperty(struct PRESTopic *me, int *failReason,
			      const struct PRESTopicProperty *property,
			      struct REDAWorker *worker);

extern PRESDllExport
RTIBool PRESTopic_getProperty(const struct PRESTopic *me,
			      struct PRESTopicProperty *property,
			      struct REDAWorker *worker);

extern PRESDllExport
void PRESTopic_returnTopicProperty(
    struct PRESTopic * me, 
    struct PRESTopicProperty *property,
    struct REDAWorker* worker);

extern PRESDllExport
RTIBool PRESTopic_setListener(struct PRESTopic *me,
			      int *failReason,
			      const struct PRESTopicListener *listener,
			      PRESStatusKind mask,
			      struct REDAWorker *worker);

extern PRESDllExport
const struct PRESTopicListener * PRESTopic_getListener(
    const struct PRESTopic *me,
    struct REDAWorker *worker);

extern PRESDllExport
const char * PRESTopic_getTopicName(
    const struct PRESTopic *me, struct REDAWorker *worker);

extern PRESDllExport
const char * PRESTopic_getTopicNameFromWR(
    const struct REDAWeakReference *localTopicWR, 
    struct PRESParticipant *participant, 
    struct REDAWorker *worker);

extern PRESDllExport
const char * PRESTopic_getTypeName(
    const struct PRESTopic *me, struct REDAWorker *worker);

extern PRESDllExport PRESWord * PRESTopic_getUserObject(struct PRESTopic *me);

extern PRESDllExport
PRESStatusKind PRESTopic_getStatusChanges(
    struct PRESTopic *me, struct REDAWorker *worker);

extern PRESDllExport RTIBool
PRESTopic_callListener(struct PRESTopic *me, int *failReason,
		       PRESStatusKindMask mask, struct REDAWorker *worker);

extern PRESDllExport
const char * PRESContentFilteredTopic_getTopicName(
    const struct PRESContentFilteredTopic *me, struct REDAWorker *worker);

extern PRESDllExport
const char * PRESContentFilteredTopic_getTypeName(
    const struct PRESContentFilteredTopic *me, struct REDAWorker *worker);

extern PRESDllExport
const char* PRESContentFilteredTopic_getFilterName(
      struct PRESContentFilteredTopic* me,
      struct REDAWorker *worker);

extern PRESDllExport
RTIBool PRESTopic_getGuid(const struct PRESTopic *me,
                          struct MIGRtpsGuid *guid,
                          struct REDAWorker *worker);

extern PRESDllExport PRESWord * PRESContentFilteredTopic_getUserObject(struct PRESContentFilteredTopic *me);

extern PRESDllExport struct PRESLocalEndpoint* PRESContentFilteredTopic_lookupDataReader(
					struct PRESParticipant *participant,
  		    	                const char *topicName,
	          	                RTIBool *related,
	                                struct REDAWorker *worker);

extern PRESDllExport RTIBool PRESContentFilteredTopic_associateReader(
	struct PRESContentFilteredTopic *me,
	struct PRESLocalEndpoint *reader,
	int *failReason,
	struct REDAWorker *worker);

extern PRESDllExport RTIBool PRESContentFilteredTopic_disassociateReader(
        struct PRESParticipant *participant,
        struct PRESLocalEndpoint *reader,
        int *failReason,
        struct REDAWorker *worker);

extern PRESDllExport const struct PRESTopic* 
PRESContentFilteredTopic_getRelatedTopic (
    const struct PRESContentFilteredTopic* me,
    struct REDAWorker *worker);

extern PRESDllExport RTIBool PRESContentFilteredTopic_registerDefaultFilter(
                        struct PRESParticipant *me,
                      	struct REDAWorker *worker);

extern PRESDllExport RTIBool PRESContentFilteredTopic_updateFilterParameters(
    struct PRESContentFilteredTopic *topic,
    int *failReason,
    const char **filter_parameters,
    int parameter_length,
    struct REDAWorker *worker);

extern PRESDllExport RTIBool PRESContentFilteredTopic_updateFilterExpression(
    struct PRESContentFilteredTopic *topic,
    int *failReason,
    const char * filter_expression,
    const char **filter_parameters,
    int parameter_length,
    struct REDAWorker *worker);

extern PRESDllExport const char* PRESContentFilteredTopic_getFilterExpression(
    struct PRESContentFilteredTopic *self,
    struct REDAWorker *worker);

extern PRESDllExport const char** PRESContentFilteredTopic_getFilterParameters(
    struct PRESContentFilteredTopic *self,RTI_INT32 *parameter_length,int *failReason,
    struct REDAWorker *worker);

extern PRESDllExport unsigned int PRESParticipant_copyContentFilterProperty(
    struct PRESContentFilterProperty *out,
    const struct PRESContentFilterProperty *in);

extern PRESDllExport RTIBool
PRESParticipant_createContentFilteredTopicPolicy(
    struct PRESParticipant *me,
    int *failReason,
    struct PRESLocalEndpoint *endpoint,
    const struct PRESContentFilterProperty *property,
    struct PRESContentFilterQosPolicy *policy,
    struct PRESContentFilterQosPolicy *oldPolicy,
    void *typeCode,
    const char *typeCodeName,
    struct REDAWorker *worker);

typedef enum {
    PRES_FILTER_RESULT_OK             = 0x00,
    PRES_FILTER_RESULT_FAIL_EXCEPTION = 0x01,
    PRES_FILTER_RESULT_FAIL_WARNING   = 0x02
} PRESContentFilterResultKind;


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_topic_h */
