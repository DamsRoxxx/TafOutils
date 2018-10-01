/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)disc_log.h    generated by: makeheader    Fri Feb 16 13:51:46 2018
 *
 *		built from:	log.ifc
 */

#ifndef disc_log_h
#define disc_log_h


  #ifndef disc_dll_h
    #include "disc/disc_dll.h"
  #endif
  #ifndef log_common_h
    #include "log/log_common.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif


/*e \ingroup DISCLogModule
  Submodule ID for builtin submodule
*/
  #define SUBMODULE_DISC_BUILTIN                 (0x0000)
/*e \ingroup DISCLogModule
  Submodule ID for pluggable submodule
*/
  #define SUBMODULE_DISC_PLUGGABLE               (0x1000)
/*e \ingroup DISCLogModule
  Submodule ID for SDP submodule
*/
  #define SUBMODULE_DISC_SIMPLE_DISCOVERY_PLUGIN (0x2000)


/*e \ingroup DISCLogModule
  Mask for turning on logging for only the builtin submodule
*/
  #define DISC_SUBMODULE_MASK_BUILTIN                 (0x0001)
/*e \ingroup DISCLogModule
  Mask for turning on logging for only the pluggable submodule
*/
  #define DISC_SUBMODULE_MASK_PLUGGABLE               (0x0002)
/*e \ingroup DISCLogModule
  Mask for turning on logging for only the SDP submodule
*/
  #define DISC_SUBMODULE_MASK_SIMPLE_DISCOVERY_PLUGIN (0x0004)

/*e \ingroup DISCLogModule
  Mask for turning on logging for all submodules
*/
  #define DISC_SUBMODULE_MASK_ALL                     (0xFFFF)

extern DISCDllExport
void DISCLog_setVerbosity(RTILogBitmap submoduleMask, int verbosity);

extern DISCDllExport void
DISCLog_setBitmaps(RTILogBitmap submoduleMask,
		     RTILogBitmap instrumentationMask);

extern DISCDllExport void DISCLog_getBitmaps(
    RTILogBitmap *submoduleMask, RTILogBitmap *instrumentationMask);

extern DISCDllVariable const struct RTILogMessage DISC_LOG_SERIALIZE_FAILURE_s;


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* disc_log_h */
