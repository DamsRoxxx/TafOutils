/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_alignment.h    generated by: makeheader    Fri Feb 16 13:51:08 2018
 *
 *		built from:	alignment.ifc
 */

#ifndef osapi_alignment_h
#define osapi_alignment_h


  #ifndef osapi_dll_h
    #include "osapi/osapi_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

typedef int RTIOsapiAlignment;


#define RTI_OSAPI_ALIGNMENT_DEFAULT (-1)


#define RTI_OSAPI_ALIGNMENT_ERROR (0)

extern RTIOsapiDllExport RTIOsapiAlignment
RTIOsapiAlignment_getDefaultAlignment();

extern RTIOsapiDllExport void *RTIOsapiAlignment_alignAddressUp(void *location,
                               RTIOsapiAlignment alignment);

extern RTIOsapiDllExport int RTIOsapiAlignment_alignSizeUp(int size,
                             RTIOsapiAlignment alignment);

extern RTIOsapiDllExport int RTIOsapiAlignment_isAligned(void *location,
                             RTIOsapiAlignment alignment);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

  #include "osapi/osapi_alignment_impl.h"

#endif /* osapi_alignment_h */
