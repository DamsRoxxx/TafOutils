/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)commend_writerStatistics_impl.h    generated by: makeheader    Fri Feb 16 13:51:37 2018
 *
 *		built from:	writerStatistics_impl.ifc
 */

#ifndef commend_writerStatistics_impl_h
#define commend_writerStatistics_impl_h


#ifdef __cplusplus
    extern "C" {
#endif



#define COMMENDWriterService_addLocalWriterStatistics(sum, in1, in2) { \
        (sum)->samplesPushedCount = (in1)->samplesPushedCount + (in2)->samplesPushedCount; \
        (sum)->samplesPushedCountChange = (in1)->samplesPushedCountChange + (in2)->samplesPushedCountChange; \
        (sum)->samplesPushedBytes = (in1)->samplesPushedBytes  + (in2)->samplesPushedBytes; \
        (sum)->samplesPushedBytesChange = (in1)->samplesPushedBytesChange  + (in2)->samplesPushedBytesChange; \
        (sum)->samplesFilteredCount = (in1)->samplesFilteredCount  + (in2)->samplesFilteredCount; \
        (sum)->samplesFilteredCountChange = (in1)->samplesFilteredCountChange  + (in2)->samplesFilteredCountChange; \
        (sum)->samplesFilteredBytes = (in1)->samplesFilteredBytes  + (in2)->samplesFilteredBytes; \
        (sum)->samplesFilteredBytesChange = (in1)->samplesFilteredBytesChange  + (in2)->samplesFilteredBytesChange; \
        (sum)->heartbeatsSentCount = (in1)->heartbeatsSentCount  + (in2)->heartbeatsSentCount; \
        (sum)->heartbeatsSentCountChange = (in1)->heartbeatsSentCountChange  + (in2)->heartbeatsSentCountChange; \
        (sum)->heartbeatsSentBytes = (in1)->heartbeatsSentBytes  + (in2)->heartbeatsSentBytes; \
        (sum)->heartbeatsSentBytesChange = (in1)->heartbeatsSentBytesChange  + (in2)->heartbeatsSentBytesChange; \
        (sum)->samplesPulledCount = (in1)->samplesPulledCount  + (in2)->samplesPulledCount; \
        (sum)->samplesPulledCountChange = (in1)->samplesPulledCountChange  + (in2)->samplesPulledCountChange; \
        (sum)->samplesPulledBytes = (in1)->samplesPulledBytes  + (in2)->samplesPulledBytes; \
        (sum)->samplesPulledBytesChange = (in1)->samplesPulledBytesChange  + (in2)->samplesPulledBytesChange; \
        (sum)->acksReceivedCount = (in1)->acksReceivedCount  + (in2)->acksReceivedCount; \
        (sum)->acksReceivedCountChange = (in1)->acksReceivedCountChange  + (in2)->acksReceivedCountChange; \
        (sum)->acksReceivedBytes = (in1)->acksReceivedBytes  + (in2)->acksReceivedBytes; \
        (sum)->acksReceivedBytesChange = (in1)->acksReceivedBytesChange  + (in2)->acksReceivedBytesChange; \
        (sum)->nacksReceivedCount = (in1)->nacksReceivedCount  + (in2)->nacksReceivedCount; \
        (sum)->nacksReceivedCountChange = (in1)->nacksReceivedCountChange  + (in2)->nacksReceivedCountChange; \
        (sum)->nacksReceivedBytes = (in1)->nacksReceivedBytes  + (in2)->nacksReceivedBytes; \
        (sum)->nacksReceivedBytesChange = (in1)->nacksReceivedBytesChange  + (in2)->nacksReceivedBytesChange; \
        (sum)->gapsSentCount = (in1)->gapsSentCount  + (in2)->gapsSentCount; \
        (sum)->gapsSentCountChange = (in1)->gapsSentCountChange  + (in2)->gapsSentCountChange; \
        (sum)->gapsSentBytes = (in1)->gapsSentBytes  + (in2)->gapsSentBytes; \
        (sum)->gapsSentBytesChange = (in1)->gapsSentBytesChange  + (in2)->gapsSentBytesChange; \
        (sum)->samplesRejectedCount = (in1)->samplesRejectedCount  + (in2)->samplesRejectedCount; \
        (sum)->samplesRejectedCountChange = (in1)->samplesRejectedCountChange  + (in2)->samplesRejectedCountChange; \
}

#define COMMENDWriterService_addMatchedReaderStatistics(sum, in1, in2) { \
        (sum)->samplesPushedCount = (in1)->samplesPushedCount + (in2)->samplesPushedCount; \
        (sum)->samplesPushedCountChange = (in1)->samplesPushedCountChange + (in2)->samplesPushedCountChange; \
        (sum)->samplesPushedBytes = (in1)->samplesPushedBytes  + (in2)->samplesPushedBytes; \
        (sum)->samplesPushedBytesChange = (in1)->samplesPushedBytesChange  + (in2)->samplesPushedBytesChange; \
        (sum)->samplesFilteredCount = (in1)->samplesFilteredCount  + (in2)->samplesFilteredCount; \
        (sum)->samplesFilteredCountChange = (in1)->samplesFilteredCountChange  + (in2)->samplesFilteredCountChange; \
        (sum)->samplesFilteredBytes = (in1)->samplesFilteredBytes  + (in2)->samplesFilteredBytes; \
        (sum)->samplesFilteredBytesChange = (in1)->samplesFilteredBytesChange  + (in2)->samplesFilteredBytesChange; \
        (sum)->heartbeatsSentCount = (in1)->heartbeatsSentCount  + (in2)->heartbeatsSentCount; \
        (sum)->heartbeatsSentCountChange = (in1)->heartbeatsSentCountChange  + (in2)->heartbeatsSentCountChange; \
        (sum)->heartbeatsSentBytes = (in1)->heartbeatsSentBytes  + (in2)->heartbeatsSentBytes; \
        (sum)->heartbeatsSentBytesChange = (in1)->heartbeatsSentBytesChange  + (in2)->heartbeatsSentBytesChange; \
        (sum)->samplesPulledCount = (in1)->samplesPulledCount  + (in2)->samplesPulledCount; \
        (sum)->samplesPulledCountChange = (in1)->samplesPulledCountChange  + (in2)->samplesPulledCountChange; \
        (sum)->samplesPulledBytes = (in1)->samplesPulledBytes  + (in2)->samplesPulledBytes; \
        (sum)->samplesPulledBytesChange = (in1)->samplesPulledBytesChange  + (in2)->samplesPulledBytesChange; \
        (sum)->acksReceivedCount = (in1)->acksReceivedCount  + (in2)->acksReceivedCount; \
        (sum)->acksReceivedCountChange = (in1)->acksReceivedCountChange  + (in2)->acksReceivedCountChange; \
        (sum)->acksReceivedBytes = (in1)->acksReceivedBytes  + (in2)->acksReceivedBytes; \
        (sum)->acksReceivedBytesChange = (in1)->acksReceivedBytesChange  + (in2)->acksReceivedBytesChange; \
        (sum)->nacksReceivedCount = (in1)->nacksReceivedCount  + (in2)->nacksReceivedCount; \
        (sum)->nacksReceivedCountChange = (in1)->nacksReceivedCountChange  + (in2)->nacksReceivedCountChange; \
        (sum)->nacksReceivedBytes = (in1)->nacksReceivedBytes  + (in2)->nacksReceivedBytes; \
        (sum)->nacksReceivedBytesChange = (in1)->nacksReceivedBytesChange  + (in2)->nacksReceivedBytesChange; \
        (sum)->gapsSentCount = (in1)->gapsSentCount  + (in2)->gapsSentCount; \
        (sum)->gapsSentCountChange = (in1)->gapsSentCountChange  + (in2)->gapsSentCountChange; \
        (sum)->gapsSentBytes = (in1)->gapsSentBytes  + (in2)->gapsSentBytes; \
        (sum)->gapsSentBytesChange = (in1)->gapsSentBytesChange  + (in2)->gapsSentBytesChange; \
        (sum)->samplesRejectedCount = (in1)->samplesRejectedCount  + (in2)->samplesRejectedCount; \
        (sum)->samplesRejectedCountChange = (in1)->samplesRejectedCountChange  + (in2)->samplesRejectedCountChange; \
}

#define COMMENDWriterService_addMatchedDestinationStatistics(sum, in1, in2) { \
        (sum)->samplesPushedCount = (in1)->samplesPushedCount + (in2)->samplesPushedCount; \
        (sum)->samplesPushedCountChange = (in1)->samplesPushedCountChange + (in2)->samplesPushedCountChange; \
        (sum)->samplesPushedBytes = (in1)->samplesPushedBytes  + (in2)->samplesPushedBytes; \
        (sum)->samplesPushedBytesChange = (in1)->samplesPushedBytesChange  + (in2)->samplesPushedBytesChange; \
        (sum)->samplesFilteredCount = (in1)->samplesFilteredCount  + (in2)->samplesFilteredCount; \
        (sum)->samplesFilteredCountChange = (in1)->samplesFilteredCountChange  + (in2)->samplesFilteredCountChange; \
        (sum)->samplesFilteredBytes = (in1)->samplesFilteredBytes  + (in2)->samplesFilteredBytes; \
        (sum)->samplesFilteredBytesChange = (in1)->samplesFilteredBytesChange  + (in2)->samplesFilteredBytesChange; \
        (sum)->heartbeatsSentCount = (in1)->heartbeatsSentCount  + (in2)->heartbeatsSentCount; \
        (sum)->heartbeatsSentCountChange = (in1)->heartbeatsSentCountChange  + (in2)->heartbeatsSentCountChange; \
        (sum)->heartbeatsSentBytes = (in1)->heartbeatsSentBytes  + (in2)->heartbeatsSentBytes; \
        (sum)->heartbeatsSentBytesChange = (in1)->heartbeatsSentBytesChange  + (in2)->heartbeatsSentBytesChange; \
        (sum)->samplesPulledCount = (in1)->samplesPulledCount  + (in2)->samplesPulledCount; \
        (sum)->samplesPulledCountChange = (in1)->samplesPulledCountChange  + (in2)->samplesPulledCountChange; \
        (sum)->samplesPulledBytes = (in1)->samplesPulledBytes  + (in2)->samplesPulledBytes; \
        (sum)->samplesPulledBytesChange = (in1)->samplesPulledBytesChange  + (in2)->samplesPulledBytesChange; \
        (sum)->gapsSentCount = (in1)->gapsSentCount  + (in2)->gapsSentCount; \
        (sum)->gapsSentCountChange = (in1)->gapsSentCountChange  + (in2)->gapsSentCountChange; \
        (sum)->gapsSentBytes = (in1)->gapsSentBytes  + (in2)->gapsSentBytes; \
        (sum)->gapsSentBytesChange = (in1)->gapsSentBytesChange  + (in2)->gapsSentBytesChange; \
}



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* commend_writerStatistics_impl_h */
