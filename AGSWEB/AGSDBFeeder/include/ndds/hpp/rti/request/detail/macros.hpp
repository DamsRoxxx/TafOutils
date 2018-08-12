/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_REQUEST_DETAIL_MACROS_HPP_
#define RTI_REQUEST_DETAIL_MACROS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#if defined(RTI_WIN32) || defined(RTI_WINCE)
  #if defined(RTI_connext_cpp2_DLL_EXPORT)
    #define XMQCPP2DllExport __declspec( dllexport )
  #else
    #define XMQCPP2DllExport
  #endif /* RTI_connext_cpp2_DLL_EXPORT */

  #if defined(RTI_connext_cpp2_DLL_VARIABLE)
    #if defined(RTI_connext_cpp2_DLL_EXPORT)
      #define XMQCPP2DllVariable __declspec( dllexport )
      #define XMQCPP2DllClassVariable
    #else
      #define XMQCPP2DllVariable __declspec( dllimport )
      #define XMQCPP2DllClassVariable __declspec( dllimport )
    #endif /* RTI_connext_cpp_DLL_EXPORT */
  #else
    #define XMQCPP2DllVariable
    #define XMQCPP2DllClassVariable
  #endif /* RTI_connext_cpp_DLL_VARIABLE */
#else
  #define XMQCPP2DllExport
  #define XMQCPP2DllVariable
  #define XMQCPP2DllClassVariable
#endif /* RTI_WIN32 || RTI_WINCE */

#endif // RTI_REQUEST_DETAIL_MACROS_HPP_
