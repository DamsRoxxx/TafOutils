#ifndef OMG_DDS_CORE_DETAIL_MACROS_HPP_
#define OMG_DDS_CORE_DETAIL_MACROS_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <string.h>

#include <rtiboost/static_assert.hpp>
#include "rtiboost/config.hpp"

#ifdef NDDS_DLL_VARIABLE
    #define RTI_dds_cpp2_DLL_VARIABLE
    #define RTI_dds_cpp_DLL_VARIABLE
    #define RTI_dds_c_DLL_VARIABLE
    #define RTI_disc_DLL_VARIABLE
    #define RTI_pres_DLL_VARIABLE
    #define RTI_writer_history_DLL_VARIABLE
    #define RTI_commend_DLL_VARIABLE
    #define RTI_mig_DLL_VARIABLE
    #define RTI_netio_DLL_VARIABLE
    #define RTI_transport_DLL_VARIABLE
    #define RTI_event_DLL_VARIABLE
    #define RTI_cdr_DLL_VARIABLE
    #define RTI_reda_DLL_VARIABLE
    #define RTI_dl_driver_DLL_VARIABLE
    #define RTI_osapi_DLL_VARIABLE
    #define RTI_clock_DLL_VARIABLE
    #define RTI_log_DLL_VARIABLE
#endif
  
// DLL Export Macros
// This is defined for 32 and 64 bit Windows
#if defined(RTI_WIN32) || defined(RTI_WINCE)
  #if defined(RTI_dds_cpp2_DLL_EXPORT)
    #  define OMG_DDS_API_DETAIL __declspec( dllexport )
  #else
    #  define OMG_DDS_API_DETAIL
  #endif

  #if defined(RTI_dds_cpp2_DLL_VARIABLE) 
    #if defined(RTI_dds_cpp2_DLL_EXPORT)
      #define OMG_DDS_API_VARIABLE_DETAIL __declspec( dllexport )
      #define OMG_DDS_API_CLASS_VARIABLE_DETAIL
    #else
      #define OMG_DDS_API_VARIABLE_DETAIL __declspec( dllimport )
      #define OMG_DDS_API_CLASS_VARIABLE_DETAIL __declspec( dllimport )
    #endif /* RTI_dds_cpp2_DLL_EXPORT */
  #else 
    #define OMG_DDS_API_VARIABLE_DETAIL
    #define OMG_DDS_API_CLASS_VARIABLE_DETAIL
  #endif /* RTI_dds_cpp2_DLL_VARIABLE */
#else
  #define OMG_DDS_API_DETAIL
  #define OMG_DDS_API_VARIABLE_DETAIL
  #define OMG_DDS_API_CLASS_VARIABLE_DETAIL
#endif /* RTI_WIN32 || RTI_WINCE */

#include "dds_c/dds_c_string.h"
#include "dds_c/dds_c_log_impl.h"

// == Constants
#define OMG_DDS_DEFAULT_STATE_BIT_COUNT_DETAIL (size_t)16
#define OMG_DDS_DEFAULT_STATUS_COUNT_DETAIL    (size_t)32
// ==========================================================================

// Use __attribute((unused))__ in RTIBOOST_STATIC_ASSERT to avoid
// unused-local-typedef warning in compilers that support it (gcc >= 4.7 and clang)
#if (defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)))) \
    || defined(__clang__)
#define RTI_STATIC_ASSERT_UNUSED_ATTRIBUTE __attribute__((unused))
#else
#define RTI_STATIC_ASSERT_UNUSED_ATTRIBUTE
#endif

// == Static Assert
#ifdef RTIBOOST_NO_CXX11_STATIC_ASSERT
#define OMG_DDS_STATIC_ASSERT_DETAIL(EXPR, MSG) RTIBOOST_STATIC_ASSERT(EXPR) RTI_STATIC_ASSERT_UNUSED_ATTRIBUTE
#else
#define OMG_DDS_STATIC_ASSERT_DETAIL static_assert
#endif

// ==========================================================================

// Logging Macros
#define OMG_DDS_LOG_DETAIL(kind, msg) \
    std::cout << "[" << kind << "]: " << msg << std::endl;

#define DDS_CURRENT_SUBMODULE   DDS_SUBMODULE_MASK_ALL
// ==========================================================================

// Macros identifying C++11 features

#if __cplusplus >= 201103L
#define RTI_CXX11
#endif

#if defined(RTIBOOST_HAS_RVALUE_REFS)
#define RTI_CXX11_RVALUE_REFERENCES
#endif

#if defined(RTI_CXX11_RVALUE_REFERENCES) \
    && defined(_MSC_VER) && _MSC_VER <= 1800 // Visual Studio <= 2013
// Indicates that this platform supports rvalue references but the compiler
// doesn't generate the default move constructor and move assignment operator
#define RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
#endif

#if defined(RTIBOOST_NO_CXX11_NULLPTR)
#define RTI_NO_CXX11_NULLPTR
#endif

#if defined(RTIBOOST_NO_CXX11_RANGE_BASED_FOR)
#define RTI_NO_CXX11_RANGE_BASED_FOR
#endif

#if defined(RTIBOOST_NO_CXX11_HDR_ARRAY) || defined(RTI_USE_BOOST_ARRAY)
#define RTI_NO_CXX11_HDR_ARRAY
#endif

#if defined(RTIBOOST_NO_CXX11_HDR_TUPLE) || defined(RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES)
#define RTI_NO_CXX11_HDR_TUPLE
#endif

#if defined(RTIBOOST_NO_CXX11_HDR_FUNCTIONAL)
#define RTI_NO_CXX11_HDR_FUNCTIONAL
#endif

#if defined(RTIBOOST_NO_CXX11_HDR_CHRONO)
#if !(defined(_LIBCPP_VERSION) && _LIBCPP_VERSION >= 1101)
#define RTI_NO_CXX11_HDR_CHRONO
#endif
#endif

#if defined(RTIBOOST_NO_CXX11_HDR_TYPE_TRAITS)
#if !(defined(_LIBCPP_VERSION) && _LIBCPP_VERSION >= 1101)
#define RTI_NO_CXX11_HDR_TYPE_TRAITS
#endif
#endif

// QNX GCC 4.7.3: 
// - std::is_nothrow_move_assignable has strange behavior
// - initializer_list doesn't work
// - and some types in the std library don't specify noexcept
#if !defined(_MSC_VER) \
    && defined(_YVALS) && defined(_CPPLIB_VER) && _CPPLIB_VER <= 650
#define RTI_NO_CXX11_HDR_TYPE_TRAITS
#define RTI_NO_CXX11_HDR_INITIALIZER_LIST
#define RTI_NO_CXX11_NOEXCEPT
#endif

//QNX GCC 5.4.0 and C++0x features in GCC 5.4 and later 
//STD Lib version GNU libstdc++ version 20160603
//Filter added specific to QNX 7 arch armv8/x64 QNX7.0.0qcc_gpp5.4.0 for PLATFORMS-1079 Port.
#if defined(RTI_QNX) && defined(RTI_QNX7) && RTIBOOST_LIBSTDCXX_VERSION == 50400 && __GLIBCXX__ >= 20160603
#define RTI_NO_CXX11_HDR_TYPE_TRAITS
#define RTI_NO_CXX11_HDR_INITIALIZER_LIST
#define RTI_NO_CXX11_NOEXCEPT
#endif

#if defined(RTIBOOST_NO_CXX11_NOEXCEPT)
#define RTI_NO_CXX11_NOEXCEPT
#endif

#if defined(RTIBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#define RTI_NO_CXX11_HDR_INITIALIZER_LIST
#endif

// Visual Studio 2010 (1600) implementation has some problems
#if defined(RTIBOOST_NO_CXX11_SMART_PTR) || (defined(_MSC_VER) && _MSC_VER <= 1600)
#define RTI_NO_CXX11_SMART_PTR
#endif

// The std library on Lynx doesn't define std::wstring
#if defined(_GLIBCPP_LYNX_CXX)
#define RTI_NO_STD_WSTRING
#endif

//
// RTI_NO_CDR_TEMPLATES disables all the code in rti::topic::cdr. This code
// is only needed by the STL type plugin. Architectures that can't compile
// this code can't support the STL plugin.
//
// VxWorks 6.3 runs into internal compiler errors in many meta-programming
// constructs. Old versions of gcc can't compile enable_if.
//
#if ((_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR <= 3)) \
    || (defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ < 5)

#define RTI_NO_CDR_TEMPLATES
#endif

#define OMG_NOEXCEPT_DETAIL RTIBOOST_NOEXCEPT_OR_NOTHROW
#define OMG_NOEXCEPT_IF_DETAIL RTIBOOST_NOEXCEPT_IF

// This macro defines what the default compiler-generated move operations would
// do for a type T that inherits from B and doesn't have any other non-static
// member variables. We need to do this for compilers that support rvalue
// references but don't generate the default move operations (Visual Studio
// 2010-2013).
//
// Note: Per the C++11 standard, the compiler should delete the default
// copy operations when providing a user-defined move ctor or move-assignment.
// But since Visual Studio 2010-2013 doesn't enforce this rule, we don't
// define a copy ctor or copy-assignment operator
//
#ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
#define RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(T, B) \
    T(T&& other) OMG_NOEXCEPT : B(static_cast<B&&>(other)) {} \
    T& operator=(T&& other) OMG_NOEXCEPT { B::operator=(std::move(other)); return *this; }

#define OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(T, D) \
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(T, dds::core::Value<D>)

#else
#define RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(T, B)
#define OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(T, D)
#endif

// ==========================================================================



#endif /* OMG_DDS_CORE_MACROS_HPP_*/
