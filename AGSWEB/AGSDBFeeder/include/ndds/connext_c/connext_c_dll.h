/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)connext_c_dll.h    generated by: makeheader    Fri Feb 16 13:52:54 2018
 *
 *		built from:	dll.ifc
 */

#ifndef connext_c_dll_h
#define connext_c_dll_h



#if defined(RTI_WIN32) || defined(RTI_WINCE)
  #if defined(RTI_connext_c_DLL_EXPORT)
    #define XMQCDllExport __declspec( dllexport )
  #else
    #define XMQCDllExport
  #endif /* RTI_connext_c_DLL_EXPORT */

  #if defined(RTI_connext_c_DLL_VARIABLE) 
    #if defined(RTI_connext_c_DLL_EXPORT)
      #define XMQCDllVariable __declspec( dllexport )
    #else
      #define XMQCDllVariable __declspec( dllimport )
    #endif /* RTI_connext_c_DLL_EXPORT */
  #else 
    #define XMQCDllVariable
  #endif /* RTI_connext_c_DLL_VARIABLE */
#else
  #define XMQCDllExport
  #define XMQCDllVariable
#endif /* RTI_WIN32 || RTI_WINCE */


#endif /* connext_c_dll_h */
