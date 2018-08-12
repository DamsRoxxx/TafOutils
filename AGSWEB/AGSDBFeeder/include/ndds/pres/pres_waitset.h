/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_waitset.h    generated by: makeheader    Fri Feb 16 13:51:43 2018
 *
 *		built from:	waitset.ifc
 */

#ifndef pres_waitset_h
#define pres_waitset_h


 #ifndef pres_dll_h
    #include "pres/pres_dll.h"
 #endif
 #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
 #endif
 #ifndef osapi_ntptime_h
    #include "osapi/osapi_ntptime.h"
 #endif
 #ifndef reda_sequenceNumber_h
    #include "reda/reda_sequenceNumber.h"
 #endif
 #ifndef pres_common_h
    #include "pres/pres_common.h"
 #endif

#ifdef __cplusplus
    extern "C" {
#endif


struct PRESCondition;

struct ConditionNode {
    struct REDAInlineListNode _node;
    struct PRESCondition *_presConditionPtr;
    /* Current trigger state of the condition */
    RTIBool isActive; 
    /* Remembers whether condition has become active while
       waitset is 'taken'. Used to avoid counting
       the same condition multiple times in the _snapShotActiveConditionsCount
       when a condition becomes inactive and then active again
     */
    RTIBool wasActive; 
    /* Indicates whether the Condition is considered for activity */
    RTIBool isMasked;
};

struct PRESWaitSetIterator {
    struct ConditionNode* _conditionNode;
};

typedef RTIBool (*PRESWaitSetWakeupFilterFnc)(void *param, int activeConditionCount);


struct PRESWaitSetBatchedEventsState {
    /* ReadOnly: Max number of evenst to batch. value==0 indicates no batching */
    int _maxEventBatchCount; 
    /* ReadOnly: Maximum delay in the event batch */
    RTINtpTime _maxEventDelay;
    /* Current count of events batched */
    int _currentEventBatchCount;
};

struct PRESWaitSet {
    struct RTIOsapiSemaphore* _bSem;
    struct REDAInlineList _conditionList;
    unsigned int _activeConditionsCount;
    /* Represents a high-watermark of active conditions
       reached while the waitset is "taken" (i.e. somebody has called wait()) on it.
       Initialized to the activeConditions when wait() is first called and
       incremented whenever a condition that was not active becomes active. It is
       not decremented if a condition becomes inactive
       */
    unsigned int _snapShotActiveConditionsCount;
    RTIBool _waitSetTaken; 
    RTIBool _isActive;
    RTIBool _waitingOnSemaphore;
    struct REDAExclusiveArea* _ea;
    struct PRESWaitSetIterator iter;
    struct PRESWaitSetBatchedEventsState _batchedEventsState;
};

extern PRESDllExport
struct PRESWaitSet* PRESWaitSet_new(struct REDAExclusiveArea* ea,
                                    struct REDAWorker* worker);

extern PRESDllExport
struct PRESWaitSet* PRESWaitSet_new_ex(int maxEventBatchCount,
                                       const struct RTINtpTime *maxEventDelay,
                                       struct REDAExclusiveArea* ea,
                                       struct REDAWorker* worker);

extern PRESDllExport
RTIBool PRESWaitSet_delete(struct PRESWaitSet *self, struct REDAWorker* worker);

extern PRESDllExport int PRESWaitSet_setWakeupOptions(
    struct PRESWaitSet *self,
    int maxEventCount,
    const struct RTINtpTime *maxEventDelay,
    struct REDAWorker* worker);

extern PRESDllExport int PRESWaitSet_getWakeupOptions(
    struct PRESWaitSet *self,
    int *maxEventCount,
    struct RTINtpTime *maxEventDelay,
    struct REDAWorker* worker);

extern PRESDllExport
int PRESWaitSet_wait(struct PRESWaitSet *self,
           struct RTINtpTime* timeout, struct REDAWorker* worker);

extern PRESDllExport
int PRESWaitSet_attach_condition(struct PRESWaitSet *self,
           struct PRESCondition* condition, struct REDAWorker* worker);

extern PRESDllExport
int PRESWaitSet_detach_condition(struct PRESWaitSet *self,
           struct PRESCondition* condition, struct REDAWorker* worker);

extern PRESDllExport
int PRESWaitSet_start_conditions_iterator(struct PRESWaitSet *self,
                                          RTIBool activeCondition,
                                          struct REDAWorker* worker);

extern PRESDllExport
void PRESWaitSet_end_conditions_iterator(struct PRESWaitSet *self,
                                         struct REDAWorker* worker);

extern PRESDllExport
struct PRESWord* PRESWaitSet_get_next_condition(struct PRESWaitSet *self,
                                                RTIBool activeCondition,
                                                struct REDAWorker* worker);

extern PRESDllExport
void  PRESWaitSet_end_wait(struct PRESWaitSet *self, 
                                  struct REDAWorker* worker);

extern PRESDllExport
int PRESWaitSet_mask_condition(
        struct PRESWaitSet *self,
        struct PRESCondition *condition,       
        RTIBool masked,
        struct REDAWorker *worker);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_waitset_h */
