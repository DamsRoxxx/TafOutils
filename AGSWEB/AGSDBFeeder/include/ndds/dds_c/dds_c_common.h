/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dds_c_common.h    generated by: makeheader    Fri Feb 16 13:51:58 2018
 *
 *		built from:	common.ifc
 */

#ifndef dds_c_common_h
#define dds_c_common_h



#ifndef osapi_type_h
  #include "osapi/osapi_type.h"   /* for RTI_UINT32 */
#endif

/* TODO: The dependency on CDR should be removed in the future.
 *       See bug #7910.
 */
#ifndef osapi_type_h
  #include "osapi/osapi_type.h"
#endif
#ifndef cdr_stream_h
  #include "cdr/cdr_stream.h"
#endif
#ifndef cdr_type_h
  #include "cdr/cdr_type.h"
#endif
#ifndef event_activeDatabase_h
  #include "event/event_activeDatabase.h"
#endif
#ifndef netio_common_h
  #include "netio/netio_common.h"
#endif
#ifndef netio_configurator_h
  #include "netio/netio_configurator.h"
#endif
#ifndef mig_rtps_h
  #include "mig/mig_rtps.h"
#endif
#ifndef mig_generator_h
  #include "mig/mig_generator.h"
#endif
#ifndef commend_facade_h
  #include "commend/commend_facade.h"
#endif
#ifndef commend_activeFacade_h
  #include "commend/commend_activeFacade.h"
#endif

#ifndef pres_participant_h
  #include "pres/pres_participant.h"
#endif
#ifndef pres_psService_h
  #include "pres/pres_psService.h"
#endif
#ifndef pres_psReaderWriter_h
  #include "pres/pres_psReaderWriter.h"
#endif

#ifndef dds_c_dll_h
  #include "dds_c/dds_c_dll.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif


#define DDS_DOMAINID_TYPE_NATIVE    RTI_INT32

typedef struct PRESInstanceHandle DDS_HANDLE_TYPE_NATIVE;


#define DDS_HANDLE_NIL_NATIVE PRES_INSTANCE_HANDLE_NIL


#define DDS_BUILTIN_TOPIC_KEY_TYPE_NATIVE    RTI_UINT32

 
typedef PRESSampleHash DDS_SAMPLE_HASH_TYPE_NATIVE;


typedef struct PRESSampleSignature DDS_SAMPLE_SIGNATURE_TYPE_NATIVE;

typedef RTICdrChar DDS_Char;

typedef RTICdrWchar DDS_Wchar;

typedef RTICdrOctet DDS_Octet;

typedef RTICdrShort DDS_Short;

typedef RTICdrUnsignedShort DDS_UnsignedShort;

typedef RTICdrLong DDS_Long;

typedef RTICdrUnsignedLong DDS_UnsignedLong;

typedef RTICdrLongLong DDS_LongLong;

typedef RTICdrUnsignedLongLong DDS_UnsignedLongLong;

typedef RTICdrFloat DDS_Float;

typedef RTICdrDouble DDS_Double;

typedef RTICdrLongDouble DDS_LongDouble;

typedef RTICdrBoolean DDS_Boolean;

typedef RTICdrEnum DDS_Enum;


#define DDS_BOOLEAN_TRUE    ((DDS_Boolean) 1)


#define DDS_BOOLEAN_FALSE   ((DDS_Boolean) 0)

struct RTIClock;

struct DDS_RegistryConfiguration;

struct NDDS_InternalDefaults {
    /*i @brief	If this field is non-NULL, NDDS will use this clock. */
    struct RTIClock* custom_clock;
    /*i @brief	If this field is non-NULL and custom_clock is NULL,
      NDDS will use this clock for public timestamping. */
    struct RTIClock* custom_external_clock;
    /*i @brief	If this field is non-NULL and custom_clock is NULL,
      NDDS will use this clock for internal timekeeping. */
    struct RTIClock* custom_internal_clock;
    /*i @brief The configuration of the DDS registry */
    struct DDS_RegistryConfiguration *registry_configuration;
};

 extern DDSCDllVariable const struct NDDS_InternalDefaults
        NDDS_INTERNAL_DEFAULTS_PROFILE_DEFAULT;

 extern DDSCDllVariable volatile RTI_INT32 NDDS_g_internalDefaultsInitialized;

 extern DDSCDllVariable struct NDDS_InternalDefaults NDDS_g_internalDefaults;



#define DDSC_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT(T) \
 struct T; \
 DDSCDllExport void T ## _initialize(struct T* self); \
 DDSCDllExport void T ## _finalize(struct T* self); \
 DDSCDllExport struct T* T ## _copy(struct T* self, const struct T* from)

#define DDSC_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT_W_ERROR_CHECKING(T) \
 struct T; \
 DDSCDllExport RTIBool T ## _initialize(struct T* self); \
 DDSCDllExport void T ## _finalize(struct T* self); \
 DDSCDllExport RTIBool T ## _copy(struct T* self, const struct T* from)
 
#ifdef RTI_CPP
#define DDSCPP_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT(T)      \
     T() { T ## _initialize(this); }                      \
     T(const struct T& from) { T ## _initialize(this); T ## _copy(this, &from); } \
    ~T() { T ## _finalize(this); }                        \
    struct T& operator=(const struct T& from) {           \
        T ## _copy(this, &from); return *this;            \
    }
#else
#define DDSCPP_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT(T)
#endif 

/*i @defgroup DDSVarLenType Variable Length Type Support
 * 
 * @brief A variation of the variable length type macro that only declares
 * the C++ operation without implementing them.
 * 
 * This is useful when the type definition contains one or more members which
 * also are variable length types. In this situation, these inner members
 * may be initialized twice, due to the default C++ constructor call and our
 * default constructor implementation that calls ## _initialize(this).
 * 
 */
#ifdef RTI_CPP
#define DDSCPP_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT_NO_IMPL(T)      \
    DDSCPPDllExport T();                     \
    DDSCPPDllExport T(const struct T& from); \
    DDSCPPDllExport ~T(); \
    DDSCPPDllExport struct T& operator=(const struct T& from);
#else
#define DDSCPP_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT_NO_IMPL(T)
#endif 



DDSC_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT(DDS_TypeAllocationParams_t);

struct DDS_TypeAllocationParams_t {
    /*e \dref_TypeAllocationParams_allocate_pointers
     */
    DDS_Boolean allocate_pointers;
    /*e \dref_TypeAllocationParams_allocate_optional_members
     */
    DDS_Boolean allocate_optional_members;
    /*i
     * \dref_TypeAllocationParams_allocate_memory
     */
    DDS_Boolean allocate_memory;
    
    DDSCPP_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT(DDS_TypeAllocationParams_t)
  #ifdef RTI_CPP
    /*e
     * Whether to allocate pointer members or not
     */
    struct DDS_TypeAllocationParams_t & set_allocate_pointers(DDS_Boolean allocate)
    {
        this->allocate_pointers = allocate;
        return *this;
    }
    /*e
     * Whether to allocate optional members or not
     */
    struct DDS_TypeAllocationParams_t & set_allocate_optional_members(DDS_Boolean allocate) {
        this->allocate_optional_members = allocate;
        return *this;        
    }
  #endif
};

 extern DDSCDllVariable const struct DDS_TypeAllocationParams_t
DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;


DDSC_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT(DDS_TypeDeallocationParams_t);

struct DDS_TypeDeallocationParams_t {
    /*e
     * \dref_TypeDeallocationParams_delete_pointers
     */
    DDS_Boolean delete_pointers;
    /*e
     * \dref_TypeDeallocationParams_delete_optional_members
     */
    DDS_Boolean delete_optional_members;

    DDSCPP_VARIABLE_LENGTH_VALUE_TYPE_SUPPORT(DDS_TypeDeallocationParams_t)
#ifdef RTI_CPP
    /*e
     * Whether to delete pointer members or not
     */
    struct DDS_TypeDeallocationParams_t & set_delete_pointers(DDS_Boolean do_delete) {
        this->delete_pointers = do_delete;
        return *this;        
    }
    /*e
     * Whether to delete optional members or not
     */
    struct DDS_TypeDeallocationParams_t & set_delete_optional_members(DDS_Boolean do_delete) {
        this->delete_optional_members = do_delete;
        return *this;                
    }
#endif
};

 extern DDSCDllVariable const struct DDS_TypeDeallocationParams_t
DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;


#ifdef NDEBUG
 #define DDS_DEBUG(code)
 #define dbgprintf
 #define dbgout
#else
 #define DDS_DEBUG(code)   code
 #define dbgprintf         fprintf
 #define dbgout		   stdout
#endif


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* dds_c_common_h */
