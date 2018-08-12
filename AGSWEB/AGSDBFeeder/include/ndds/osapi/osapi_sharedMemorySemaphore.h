/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_sharedMemorySemaphore.h    generated by: makeheader    Fri Feb 16 13:51:09 2018
 *
 *		built from:	sharedMemorySemaphore.ifc
 */

#ifndef osapi_sharedMemorySemaphore_h
#define osapi_sharedMemorySemaphore_h


  #ifndef osapi_sharedMemory_h
    #include "osapi/osapi_sharedMemory.h"
  #endif

#include "osapi/osapi_sharedMemorySemMutex_impl.h"

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIOsapiSharedMemorySemaphoreHandle;

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySemaphore_create(
		struct RTIOsapiSharedMemorySemaphoreHandle *handle, 
		int * statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySemaphore_attach(
		struct RTIOsapiSharedMemorySemaphoreHandle *handle, 
		int *statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySemaphore_createOrAttach(
		struct RTIOsapiSharedMemorySemaphoreHandle *handle, 
		int * statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySemaphore_give(
		struct RTIOsapiSharedMemorySemaphoreHandle *handle, 
		int* statusOut);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySemaphore_take(
    struct RTIOsapiSharedMemorySemaphoreHandle *handle, int* statusOut);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySemaphore_detach(
		struct RTIOsapiSharedMemorySemaphoreHandle *handle);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySemaphore_delete(
		struct RTIOsapiSharedMemorySemaphoreHandle *handle);



#define RTIOsapiSharedMemorySemaphoreHandle	\
		RTIOsapiSharedMemorySemMutexHandle

#define RTIOsapiSharedMemorySemaphore_create(h, s, k) \
	RTIOsapiSharedMemorySemMutex_create(h, s, k, SEMMUTEX_TYPE_SEMAPHORE)

#define RTIOsapiSharedMemorySemaphore_attach(h, s, k) \
	RTIOsapiSharedMemorySemMutex_attach(h, s, k, SEMMUTEX_TYPE_SEMAPHORE)

#define RTIOsapiSharedMemorySemaphore_createOrAttach(h, s, k) \
	RTIOsapiSharedMemorySemMutex_createOrAttach(h, s, k, SEMMUTEX_TYPE_SEMAPHORE)

#define RTIOsapiSharedMemorySemaphore_give(h, s) \
	RTIOsapiSharedMemorySemMutex_give(h, s, SEMMUTEX_TYPE_SEMAPHORE)

#define RTIOsapiSharedMemorySemaphore_take(h, s) \
	RTIOsapiSharedMemorySemMutex_take(h, s, SEMMUTEX_TYPE_SEMAPHORE)

#define RTIOsapiSharedMemorySemaphore_detach(h) \
	RTIOsapiSharedMemorySemMutex_detach(h, SEMMUTEX_TYPE_SEMAPHORE)

#define RTIOsapiSharedMemorySemaphore_delete(h) \
	RTIOsapiSharedMemorySemMutex_delete(h, SEMMUTEX_TYPE_SEMAPHORE)



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_sharedMemorySemaphore_h */
