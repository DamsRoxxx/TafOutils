/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_type.h    generated by: makeheader    Fri Feb 16 13:51:08 2018
 *
 *		built from:	type.ifc
 */

#ifndef osapi_type_h
#define osapi_type_h



#define RTIBool int
#define RTI_FALSE (0)
#define RTI_TRUE  (1)

#ifndef NULL
  #define NULL (0)
#endif

/*
 * ALPHA's long is 64 bits
 */
#ifdef RTI_64BIT
    typedef signed long long  RTI_INT64;
    typedef unsigned long long RTI_UINT64;
#elif defined(_WIN32) || defined(_WIN32_WCE)
    typedef __int64 RTI_INT64;
    typedef unsigned __int64 RTI_UINT64;
#elif defined(RTI_SOL2)
    typedef signed long long  RTI_INT64;
    typedef unsigned long long  RTI_UINT64;
#elif defined(RTI_LINUX) || defined(RTI_DARWIN)
    typedef signed long long  RTI_INT64;
    typedef unsigned long long  RTI_UINT64;
#elif defined(RTI_AIX)
  typedef long long  RTI_INT64;
  typedef unsigned long long  RTI_UINT64;
#else 
    typedef long long RTI_INT64;
    typedef unsigned long long RTI_UINT64;
#endif

#if defined(RTI_UNIX) || defined(RTI_VXWORKS) || defined(RTI_OPENVMS)
  /**
    Atomic type that is 32 bits.
  */
    typedef signed int  RTI_INT32;
    typedef unsigned int RTI_UINT32;
  /**
    Atomic type that is 16 bit integer.
  */
    typedef signed short  RTI_INT16;
    typedef unsigned short RTI_UINT16;
  /**
    Atomic type that is 8 bit integer.
  */
    typedef signed char   RTI_INT8;
    typedef unsigned char RTI_UINT8;
  /**
    Atomic type that is 32 bit float.
  */
  typedef float  RTI_FLOAT32;
  /**
    Atomic type that is 64 bit float.
  */
  typedef double RTI_DOUBLE64;
#endif

#if defined(RTI_PSOS)
    typedef signed int     RTI_INT32;
    typedef unsigned int   RTI_UINT32;
    typedef signed short   RTI_INT16;
    typedef unsigned short RTI_UINT16;
    typedef char           RTI_INT8;
    typedef unsigned char  RTI_UINT8;
    typedef float          RTI_FLOAT32;
    typedef double         RTI_DOUBLE64;
#endif

#if defined(RTI_NETOS)
    typedef signed int     RTI_INT32;
    typedef unsigned int   RTI_UINT32;
    typedef signed short   RTI_INT16;
    typedef unsigned short RTI_UINT16;
    typedef char           RTI_INT8;
    typedef unsigned char  RTI_UINT8;
    typedef float          RTI_FLOAT32;
    typedef double         RTI_DOUBLE64;
#endif

#if defined(RTI_LYNX)
    typedef signed int     RTI_INT32;
    typedef unsigned int   RTI_UINT32;
    typedef signed short   RTI_INT16;
    typedef unsigned short RTI_UINT16;
    typedef char           RTI_INT8;
    typedef unsigned char  RTI_UINT8;
    typedef float          RTI_FLOAT32;
    typedef double         RTI_DOUBLE64;
#endif

#if defined(RTI_QNX)
    typedef signed int     RTI_INT32;
    typedef unsigned int   RTI_UINT32;
    typedef signed short   RTI_INT16;
    typedef unsigned short RTI_UINT16;
    typedef char           RTI_INT8;
    typedef unsigned char  RTI_UINT8;
    typedef float          RTI_FLOAT32;
    typedef double         RTI_DOUBLE64;
#endif

#if defined(RTI_INTY)
    typedef signed int     RTI_INT32;
    typedef unsigned int   RTI_UINT32;
    typedef signed short   RTI_INT16;
    typedef unsigned short RTI_UINT16;
    typedef char           RTI_INT8;
    typedef unsigned char  RTI_UINT8;
    typedef float          RTI_FLOAT32;
    typedef double         RTI_DOUBLE64;
#endif

#ifdef RTI_WIN32
    typedef signed int     RTI_INT32;
    typedef unsigned int   RTI_UINT32;
    typedef char           RTI_INT8;
    typedef unsigned char  RTI_UINT8;
    typedef signed short   RTI_INT16;
    typedef unsigned short RTI_UINT16;
    typedef float          RTI_FLOAT32;
    typedef double         RTI_DOUBLE64;
#endif /* RTI_WIN32 */

#if defined(RTI_WINCE)
    typedef int            RTI_INT32;
    typedef unsigned int   RTI_UINT32;
    typedef char           RTI_INT8;
    typedef unsigned char  RTI_UINT8;
    typedef short          RTI_INT16;
    typedef unsigned short RTI_UINT16;
    typedef float          RTI_FLOAT32;
    typedef double         RTI_DOUBLE64;
#endif /* RTI_WINCE */

#if defined(RTI_WISP)
    typedef signed int     RTI_INT32;
    typedef unsigned int   RTI_UINT32;
    typedef double         RTI_DOUBLE64;
#endif

    
#define RTI_INT32_MAX  2147483647
/* This is not defined as -2147483648 because that value is processed in
   two stages. From https://msdn.microsoft.com/en-us/library/4kh09110.aspx
   1. The number 2147483648 is evaluated. Because it is greater than the                                                                                         .
      maximum integer value of 2147483647, the type of 2147483648 is not int,                                                                                    .
      but unsigned int                                                                                                                                           .
   2. Unary minus is applied to the value, with an unsigned result, which also                                                                                                                                                                                        .
      happens to be 2147483648.                                                                                                                                                              .
*/
#define RTI_INT32_MIN  (-2147483647 - 1)
#define RTI_UINT32_MAX 4294967295U
#define RTI_UINT32_MIN 0
#define RTI_INT64_MAX  9223372036854775807LL
#define RTI_INT64_MIN  (-RTI_INT64_MAX - 1LL)
#define RTI_UINT64_MAX 18446744073709551615ULL   
#define RTI_UINT64_MIN 0ULL   

#if defined(RTI_WIN32) || defined(RTI_INTY) || defined(__DCC__)
    #define RTI_FUNCTION_NAME __FUNCTION__
#else
    #define RTI_FUNCTION_NAME __func__
#endif

#ifdef __cplusplus
    extern "C" {
#endif


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_type_h */
