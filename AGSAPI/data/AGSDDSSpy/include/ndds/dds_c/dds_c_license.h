/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dds_c_license.h    generated by: makeheader    Fri Feb 16 13:51:59 2018
 *
 *		built from:	license.ifc
 */

#ifndef dds_c_license_h
#define dds_c_license_h



#ifndef dds_c_infrastructure_h
  #include "dds_c/dds_c_infrastructure.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif
/* RTILM_LINE_LENGTH_MAX must be large enough to hold all the fields with
   length up to RTILM_FIELD_LENGTH_MAX and the option string with length
   up to RTILM_OPTION_LENGTH_MAX in a feature line
 */
#define RTILM_LINE_LENGTH_MAX (1536) 
#define RTILM_DATE_LENGTH_MAX (64)
#define RTILM_OPTION_LENGTH_MAX (1024)

/* Return codes */
typedef enum {
    /* Ok */
    RTILM_RETCODE_OK,
    /* Matching feature, but expired. */
    RTILM_RETCODE_EXPIRED,
    /* Matching feature, but something invalid */
    RTILM_RETCODE_INVALID,
    /* File doesn't contain feature/vendor */
    RTILM_RETCODE_NOT_FOUND,
    /* No file found. */
    RTILM_RETCODE_FILE_NOT_FOUND,
    /* Bad parameters. */
    RTILM_RETCODE_BAD_PARAMETERS,
    /* Null reponse. */
    RTILM_RETCODE_NULL_RESPONSE
} RTILMRetCode;

extern DDSCDllExport 
int NDDS_LM_validate(void* p_outParams, void* p_inOutParams, void* p_inParams);

extern DDSCDllExport
RTIBool NDDS_LM_get_value_from_option_string(
    char* optionValue, const char* optionString, const char* optionName);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* dds_c_license_h */
