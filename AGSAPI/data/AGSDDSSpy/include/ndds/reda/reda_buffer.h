/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)reda_buffer.h    generated by: makeheader    Fri Feb 16 13:51:17 2018
 *
 *		built from:	buffer.ifc
 */

#ifndef reda_buffer_h
#define reda_buffer_h


  #ifndef reda_dll_h
    #include "reda/reda_dll.h"
  #endif
  #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
  #endif
  #ifndef osapi_alignment_h
    #include "osapi/osapi_alignment.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct REDABuffer {
    /*e Length of the buffer pointed to by pointer. */
    int length;
    /*e Pre-allocated (by the caller) buffer.  */
    char *pointer;
};

struct REDABufferManager {
    /*e The buffer: its length and starting position */
    struct REDABuffer buffer;
    /*e Where in the buffer is the next available memory to use */
    char *currentPosition;

    /*e Increased every time getBuffer fails. */
    unsigned int errorCount;
};

struct REDADynamicBufferManagerProperty {
    /*e The size of the initial buffer. That is, the minimum size that
     *  a DynamicBufferManager will allocate.
     */
    unsigned int initialSize;

    /*e Whether to trim to the intial size or not. When enabled, after calling
     * reset or ensureCapacity with a size <= initialSize, the auxiliary buffer
     * is deleted. When set to false, the auxiliary buffer never shrinks and
     * will always be as big as the largest size ever requested with
     * ensureCapacity.
     */
    RTIBool trim;
};


#define REDADynamicBufferManagerProperty_INITIALIZER \
{                                                    \
    4092,                                            \
    RTI_FALSE                                        \
}

struct REDADynamicBufferManager {
    /*e */
    struct REDABufferManager _bufferManager;
    struct REDADynamicBufferManagerProperty _property;

    struct REDABuffer _initialBuffer;
    struct REDABuffer _largeBuffer;
};

extern REDADllExport void
REDABufferArray_getSize(int *answer, const struct REDABuffer *array,
			int arrayCount);

extern REDADllExport void
REDABuffer_set(struct REDABuffer *me, char *pointer, int length);

extern REDADllExport void REDABuffer_reset(struct REDABuffer *me);


  #define REDA_BUFFER_INVALID {0, NULL}

typedef char
*(*REDAToStringBufferFunction)(const void *ptr, struct REDABuffer *buffer);

extern REDADllExport RTIBool
REDABufferManager_init(struct REDABufferManager *me, char *ptr, int len);

extern REDADllExport
RTIBool REDABufferManager_createBuffer(
    struct REDABufferManager *me, int length);

extern REDADllExport
void REDABufferManager_deleteBuffer(struct REDABufferManager *me);

extern REDADllExport
void REDABufferManager_reset(struct REDABufferManager *me);

extern REDADllExport char *
REDABufferManager_getBuffer(struct REDABufferManager *me, unsigned int sizeInBytes, RTIOsapiAlignment alignment);

extern REDADllExport
unsigned int REDABufferManager_getErrorCount(struct REDABufferManager *me);

extern REDADllExport
RTIBool REDADynamicBufferManager_initialize(
    struct REDADynamicBufferManager * self,
    const struct REDADynamicBufferManagerProperty * property);

extern REDADllExport
RTIBool REDADynamicBufferManager_ensureCapacity(
    struct REDADynamicBufferManager * self,
    unsigned int capacity);

extern REDADllExport
unsigned int REDADynamicBufferManager_getCapacity(
    struct REDADynamicBufferManager * self);

extern REDADllExport
void REDADynamicBufferManager_trim(struct REDADynamicBufferManager * self);

extern REDADllExport
char * REDADynamicBufferManager_getBuffer(
    struct REDADynamicBufferManager * self,
    unsigned int sizeInBytes,
    RTIOsapiAlignment alignment);

extern REDADllExport
void REDADynamicBufferManager_reset(
    struct REDADynamicBufferManager * self);

extern REDADllExport
void REDADynamicBufferManager_finalize(
    struct REDADynamicBufferManager * self);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

/* pick up hidden performance boosting macros and optimizations */
  #include "reda/reda_buffer_impl.h"

#endif /* reda_buffer_h */
