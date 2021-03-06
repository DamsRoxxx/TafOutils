/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)clock_monotonic.h    generated by: makeheader    Fri Feb 16 13:51:13 2018
 *
 *		built from:	monotonic.ifc
 */

#ifndef clock_monotonic_h
#define clock_monotonic_h


  #ifndef clock_interface_h
    #include "clock/clock_interface.h"
  #endif
  #ifndef clock_dll_h
    #include "clock/clock_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIMonotonicClock; /* forward declare to appease compiler */

extern RTIClockDllExport void RTIMonotonicClock_delete(struct RTIClock *me);

extern RTIClockDllExport struct RTIClock *RTIMonotonicClock_new();

extern RTIClockDllExport RTIBool RTIMonotonicClockUtility_isSupported();


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* clock_monotonic_h */
