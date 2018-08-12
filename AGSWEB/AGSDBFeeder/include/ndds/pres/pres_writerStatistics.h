/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_writerStatistics.h    generated by: makeheader    Fri Feb 16 13:51:43 2018
 *
 *		built from:	writerStatistics.ifc
 */

#ifndef pres_writerStatistics_h
#define pres_writerStatistics_h


#include "osapi/osapi_type.h"
#include "commend/commend_writerStatistics.h"

#ifdef __cplusplus
    extern "C" {
#endif

struct PRESPsDataWriterCacheStatus {
    RTI_INT64 entryCount;
    RTI_INT64 entryCountPeak;
};


#define PRES_PS_DATAWRITER_CACHE_STATUS_INITIALIZER { \
    0, 0 \
}

struct PRESPsWriterLocalWriterStatistics {
    struct PRESPsDataWriterCacheStatus presStats;
    struct COMMENDWriterServiceLocalWriterStatistics commendStats;
};


#define PRES_PS_WRITER_LOCAL_WRITER_STATISTICS_INITIALIZER { \
PRES_PS_DATAWRITER_CACHE_STATUS_INITIALIZER, \
COMMEND_WRITER_SERVICE_LOCAL_WRITER_STATISTICS_INITIALIZER \
}

struct PRESPsWriterMatchedReaderStatistics {
    struct COMMENDWriterServiceMatchedReaderStatistics commendStats;
};

struct PRESPsWriterMatchedDestinationStatistics {
    struct COMMENDWriterServiceMatchedDestinationStatistics commendStats;
};


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_writerStatistics_h */
