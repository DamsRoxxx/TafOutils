/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)event_log.h    generated by: makeheader    Fri Feb 16 13:51:30 2018
 *
 *		built from:	log.ifc
 */

#ifndef event_log_h
#define event_log_h


  #ifndef log_common_h
    #include "log/log_common.h"
  #endif
  #ifndef event_dll_h
    #include "event/event_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif


  #define SUBMODULE_EVENT_TIMER_POLLED                (0x1000)
  #define SUBMODULE_EVENT_TIMER_SMART                 (0x2000)
  #define SUBMODULE_EVENT_TIMER_GENERATOR             (0x3000)
  #define SUBMODULE_EVENT_TIMER_PASSIVE_GENERATOR     (0x4000)
  #define SUBMODULE_EVENT_TIMER_ACTIVE_GENERATOR      (0x5000)
  #define SUBMODULE_EVENT_TIMER_ACTIVE_DATABASE       (0x6000)
  #define SUBMODULE_EVENT_TIMER_JOB_DISPATCHER        (0x7000)


  #define RTI_EVENT_SUBMODULE_MASK_POLLED_TIMER       (0x0001)


  #define RTI_EVENT_SUBMODULE_MASK_SMART_TIMER        (0x0002)


  #define RTI_EVENT_SUBMODULE_MASK_GENERATOR          (0x0004)


  #define RTI_EVENT_SUBMODULE_MASK_PASSIVE_GENERATOR  (0x0008)


  #define RTI_EVENT_SUBMODULE_MASK_ACTIVE_GENERATOR   (0x0010)


  #define RTI_EVENT_SUBMODULE_MASK_ACTIVE_DATABASE    (0x0020)


  #define RTI_EVENT_SUBMODULE_MASK_JOB_DISPATCHER     (0x0040)


  #define RTI_EVENT_SUBMODULE_MASK_ALL                (0xFFFF)

extern RTIEventDllExport void RTIEventLog_setVerbosity(
    RTILogBitmap submoduleMask, int verbosity);

extern RTIEventDllExport void RTIEventLog_setBitmaps(
    RTILogBitmap submoduleMask, RTILogBitmap instrumentationMask);

extern RTIEventDllExport void RTIEventLog_getBitmaps(
    RTILogBitmap *submoduleMask, RTILogBitmap *instrumentationMask);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* event_log_h */
