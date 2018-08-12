/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dl_driver_odbcSetup.h    generated by: makeheader    Fri Feb 16 13:51:12 2018
 *
 *		built from:	odbcSetup.ifc
 */

#ifndef dl_driver_odbcSetup_h
#define dl_driver_odbcSetup_h



#include "osapi/osapi_type.h"
#include "dl_driver/dl_driver_dll.h"

#if defined(RTI_WIN32) || defined(RTI_WINCE)
#include <windows.h>
#endif


extern DLDRIVERDllExport
RTIBool DLDRIVEROdbcSetup_testSetup(const char * user, const char * odbcIniPath,const char * database);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* dl_driver_odbcSetup_h */
