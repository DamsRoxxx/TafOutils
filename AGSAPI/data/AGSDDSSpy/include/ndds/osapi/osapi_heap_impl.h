/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_heap_impl.h    generated by: makeheader    Fri Feb 16 13:51:08 2018
 *
 *		built from:	heap_impl.ifc
 */

#ifndef osapi_heap_impl_h
#define osapi_heap_impl_h


  #include <stdlib.h>

#ifdef __cplusplus
    extern "C" {
#endif

 extern RTIOsapiDllVariable RTIBool RTIOsapiHeap_g_isMonitoringEnabled;


#ifdef RTI_PRECONDITION_TEST
#define RTIOsapiHeap_isMonitoringEnabled() RTIOsapiHeap_g_isMonitoringEnabled
#endif


#define RTIOsapiHeap_setHeapContextMacro( \
        oldContext, \
        topicNameParam, \
        activityParam) \
if (RTIOsapiHeap_isMonitoringEnabled()) { \
    struct RTIOsapiHeapContext *context = RTIOsapiHeap_getContext(); \
 \
    if (context != NULL) { \
        RTIOsapiHeap_copyContext((oldContext), context); \
        context->topicName = (topicNameParam); \
        context->activity = (activityParam); \
    } \
}

#define RTIOsapiHeap_restoreHeapContextMacro(oldContext) \
if (RTIOsapiHeap_isMonitoringEnabled()) { \
    struct RTIOsapiHeapContext *context = RTIOsapiHeap_getContext(); \
 \
    if (context != NULL) { \
        RTIOsapiHeap_copyContext(context, (oldContext)); \
    } \
}

#ifdef RTI_PRECONDITION_TEST
#define RTIOsapiHeap_restoreHeapContext RTIOsapiHeap_restoreHeapContextMacro
#define RTIOsapiHeap_setHeapContext RTIOsapiHeap_setHeapContextMacro
#endif



enum RTIOsapiHeapAllocatorKind {
    RTI_OSAPI_STRUCT_ALLOC       = 0x4E444441,
    RTI_OSAPI_STRING_ALLOC       = 0x4E444442,
    RTI_OSAPI_ARRAY_ALLOC        = 0x4E444443,
    RTI_OSAPI_BUFFER_ALLOC       = 0x4E444444,
    RTI_OSAPI_BUFFER_ALIGN_ALLOC = 0x4E444445,
    RTI_OSAPI_MALLOC_ALLOC       = 0x4E444446,
    RTI_OSAPI_FREED_BLOCK        = 0x7b9b9b9b
};

/*--------------------------------------------------------------------------*/
/* Helper function not to be used directly */
RTIOsapiDllExport char *
RTIOsapiHeap_reallocateMemoryInternal(
        void **ptr,
        size_t size,
        int alignment,
        RTIBool reallocPtr,
        RTIBool forceHeapHeader,
        const char *caller,
        enum RTIOsapiHeapAllocatorKind allocKind,
        const char *typeName);

/*--------------------------------------------------------------------------*/
/* Helper function not to be used directly */
RTIOsapiDllExport void
RTIOsapiHeap_freeMemoryInternal( void *ptr, RTIBool forceHeapHeader, const char *caller,
                                 enum RTIOsapiHeapAllocatorKind allocKind );


/*--------------------------------------------------------------------------*/
/* This needs to stay a MACRO; not for performance reasons but because
   it is the only way to pass a "type" into the "function" 
 */
#define RTIOsapiHeap_allocateStructure(destPointer, destType) \
    RTIOsapiHeap_reallocateMemoryInternal( \
            (void **)(destPointer), \
            sizeof(destType), \
            RTI_OSAPI_ALIGNMENT_DEFAULT, \
            RTI_FALSE, /* reallocPtr */ \
            RTI_FALSE, /* forceHeapHeader */ \
            "RTIOsapiHeap_allocateStructure", \
            RTI_OSAPI_STRUCT_ALLOC, \
            #destType) \
                ?(*(destPointer) = (destType *)*(destPointer)) \
                :NULL

/*--------------------------------------------------------------------------*/
/* This needs to stay a MACRO; not for performance reasons but because
   it is the only way to pass a "type" into the "function" 
 */
#define RTIOsapiHeap_allocateArray(destPointer, elementCount, elementType) \
    RTIOsapiHeap_reallocateMemoryInternal( \
            (void **)(destPointer), \
            (elementCount)*sizeof(elementType), \
            RTI_OSAPI_ALIGNMENT_DEFAULT, \
            RTI_FALSE, /* reallocPtr */ \
            RTI_FALSE, /* forceHeapHeader */ \
            "RTIOsapiHeap_allocateArray", \
            RTI_OSAPI_ARRAY_ALLOC, \
            #elementType) \
                ?(*(destPointer) = (elementType *)*(destPointer)) \
                :NULL

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_allocateString(stringStoragePointer, stringSize) \
     RTIOsapiHeap_reallocateMemoryInternal( \
             (void **)(stringStoragePointer), \
             (size_t)(stringSize)+1, \
             RTI_OSAPI_ALIGNMENT_DEFAULT, \
             RTI_FALSE, /* reallocPtr */ \
             RTI_FALSE, /* forceHeapHeader */ \
             "RTIOsapiHeap_allocateString", \
             RTI_OSAPI_STRING_ALLOC, \
             "char") \
                 ?(*(stringStoragePointer) = (char *)*(stringStoragePointer)) \
                 :NULL

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_allocateBufferNotAligned(buffer, size) \
    RTIOsapiHeap_reallocateMemoryInternal( \
            (void **)(buffer), \
            (size_t)(size), \
            RTI_OSAPI_ALIGNMENT_DEFAULT, \
            RTI_FALSE, /* reallocPtr */ \
            RTI_FALSE, /* forceHeapHeader */ \
            "RTIOsapiHeap_allocateBufferNotAligned", \
            RTI_OSAPI_BUFFER_ALLOC, \
            "unsigned char") \
                ?(*(buffer) = (char *)*(buffer)) \
                :NULL

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_allocateBufferAligned(buffer, size, alignment) \
    RTIOsapiHeap_reallocateMemoryInternal( \
            (void **)(buffer), \
            (size_t)(size), \
            (alignment), \
            RTI_FALSE, /* reallocPtr */ \
            RTI_TRUE, /* forceHeapHeader */ \
            "RTIOsapiHeap_allocateBufferAligned", \
            RTI_OSAPI_BUFFER_ALIGN_ALLOC, \
            "unsigned char") \
                ?(*(buffer) = (char *)*(buffer)) \
                :NULL

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_allocateBuffer RTIOsapiHeap_allocateBufferAligned


/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_freeStructure(dest) \
    RTIOsapiHeap_freeMemoryInternal((void *)(dest), RTI_FALSE, \
                                    "RTIOsapiHeap_freeStructure", RTI_OSAPI_STRUCT_ALLOC)

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_freeArray(dest) \
    RTIOsapiHeap_freeMemoryInternal((void *)(dest), RTI_FALSE, \
                                    "RTIOsapiHeap_freeArray", RTI_OSAPI_ARRAY_ALLOC)

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_freeString(stringStorage) \
    RTIOsapiHeap_freeMemoryInternal((void *)(stringStorage), RTI_FALSE, \
                                    "RTIOsapiHeap_freeString", RTI_OSAPI_STRING_ALLOC)

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_freeBuffer(buffer) \
    RTIOsapiHeap_freeMemoryInternal((void *)(buffer), RTI_TRUE, \
                                    "RTIOsapiHeap_freeBufferAligned", RTI_OSAPI_BUFFER_ALIGN_ALLOC)

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_freeBufferNotAligned(buffer) \
    RTIOsapiHeap_freeMemoryInternal((void *)(buffer), RTI_FALSE, \
                                    "RTIOsapiHeap_freeBufferNotAligned", RTI_OSAPI_BUFFER_ALLOC)

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_freeBufferAligned RTIOsapiHeap_freeBuffer

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_reallocateArray(destPointer, elementCount, elementType) \
     RTIOsapiHeap_reallocateMemoryInternal( \
             (void **)(destPointer), \
             (elementCount)*sizeof(elementType), \
             RTI_OSAPI_ALIGNMENT_DEFAULT, \
             RTI_TRUE, /* reallocPtr */ \
             RTI_FALSE, /* forceHeapHeader */ \
             "RTIOsapiHeap_reallocateArray", \
             RTI_OSAPI_ARRAY_ALLOC, \
             #elementType) \
                 ?(*(destPointer) = (elementType *)*(destPointer)), RTI_TRUE \
                 :RTI_FALSE

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_reallocateString(stringStoragePointer, stringSize) \
     RTIOsapiHeap_reallocateMemoryInternal( \
             (void **)(stringStoragePointer), \
             (size_t)(stringSize)+1, \
             RTI_OSAPI_ALIGNMENT_DEFAULT, \
             RTI_TRUE, /* reallocPtr */ \
             RTI_FALSE, /* forceHeapHeader */ \
             "RTIOsapiHeap_reallocateString",\
             RTI_OSAPI_STRING_ALLOC, \
             "char") \
                 ?(*(stringStoragePointer) = (char *)*(stringStoragePointer)), RTI_TRUE \
                 :RTI_FALSE

/*--------------------------------------------------------------------------*/
/* Default-aligned memory should not force a header */
#define RTIOsapiHeap_reallocateBufferNotAligned(buffer, size) \
    RTIOsapiHeap_reallocateMemoryInternal( \
            (void **)(buffer), \
            (size_t)(size), RTI_OSAPI_ALIGNMENT_DEFAULT, \
            RTI_TRUE, /* reallocPtr */ \
            RTI_FALSE, /* forceHeapHeader */ \
            "RTIOsapiHeap_reallocateBufferNotAligned", \
            RTI_OSAPI_BUFFER_ALLOC, \
            "unsigned char")  \
                ?(*(buffer) = (char *)*(buffer)), RTI_TRUE \
                :RTI_FALSE

/*--------------------------------------------------------------------------*/
/* Aligned memory always requires a header */
#define RTIOsapiHeap_reallocateBufferAligned(buffer, size, alignment) \
    RTIOsapiHeap_reallocateMemoryInternal( \
            (void **)(buffer), \
            (size_t)(size), \
            (alignment), \
            RTI_TRUE, /* reallocPtr */ \
            RTI_TRUE, /* forceHeapHeader */ \
            "RTIOsapiHeap_reallocateBufferAligned", \
            RTI_OSAPI_BUFFER_ALIGN_ALLOC, \
            "unsigned char ") \
                ?(*(buffer) = (char *)*(buffer)), RTI_TRUE \
                :RTI_FALSE

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_realloc(ptr, size) \
    RTIOsapiHeap_reallocateMemoryInternal( \
            (void **)&(ptr), \
            (size_t)(size), \
            RTI_OSAPI_ALIGNMENT_DEFAULT, \
            RTI_TRUE, /* reallocPtr */ \
            RTI_FALSE, /* forceHeapHeader */ \
            "RTIOsapiHeap_realloc", \
            RTI_OSAPI_MALLOC_ALLOC, \
            "unsigned char")

/*--------------------------------------------------------------------------*/
#define RTIOsapiHeap_free(ptr) \
    RTIOsapiHeap_freeMemoryInternal((void **)(ptr), RTI_FALSE, "RTIOsapiHeap_free",\
                                     RTI_OSAPI_MALLOC_ALLOC)



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_heap_impl_h */
