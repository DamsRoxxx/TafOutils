/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_cstReaderCollator_impl.h    generated by: makeheader    Fri Feb 16 13:51:42 2018
 *
 *		built from:	cstReaderCollator_impl.ifc
 */

#ifndef pres_cstReaderCollator_impl_h
#define pres_cstReaderCollator_impl_h


#ifdef __cplusplus
    extern "C" {
#endif



#define PRESCstReaderCollator_pruneLifespanExpiredEntries(me, now, \
        requiredEntryCount, alwaysCalculateState, \
        readConditionState, queryConditionState)  \
    (PRESCstReaderCollator_pruneAndUpdate(me, now, requiredEntryCount, \
        RTI_FALSE, NULL, PRES_INSTANCE_STATE_INVALID, NULL, \
        alwaysCalculateState, readConditionState, queryConditionState))



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_cstReaderCollator_impl_h */
