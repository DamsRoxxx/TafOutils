/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_guard_condition.h    generated by: makeheader    Fri Feb 16 13:51:43 2018
 *
 *		built from:	guard_condition.ifc
 */

#ifndef pres_guard_condition_h
#define pres_guard_condition_h


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
 #ifndef pres_condition_h
  #include "pres/pres_condition.h"
 #endif

#ifdef __cplusplus
    extern "C" {
#endif



/*e \ingroup PRESGuardConditionModule
 * \brief A GuardCondition.
 */
struct PRESGuardCondition {
     struct PRESCondition _base;
};


extern PRESDllExport
struct PRESGuardCondition* PRESGuardCondition_new(void *userObject,
                                               struct REDAExclusiveArea* ea,
                                               struct REDAWorker* worker);

extern PRESDllExport
int PRESGuardCondition_delete(struct PRESGuardCondition *self,
                               struct REDAWorker* worker);

extern PRESDllExport
void PRESGuardCondition_set_trigger_value(struct PRESGuardCondition *self,
                                          RTIBool value,
                                          struct REDAWorker* worker);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_guard_condition_h */
