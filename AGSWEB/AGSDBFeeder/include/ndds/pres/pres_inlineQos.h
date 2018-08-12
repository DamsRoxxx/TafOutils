/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_inlineQos.h    generated by: makeheader    Fri Feb 16 13:51:43 2018
 *
 *		built from:	inlineQos.ifc
 */

#ifndef pres_inlineQos_h
#define pres_inlineQos_h


#ifndef osapi_type_h
    #include "osapi/osapi_type.h"
#endif
#ifndef pres_common_h
    #include "pres/pres_common.h"
#endif
#ifndef pres_psService_h
    #include "pres/pres_psService.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif


#define PRES_INLINE_QOS_IMMUTABLE_FILTER_SIGNATURE_SIZE 16 
    /* sizeof(struct PRESInlineParameterHeader) + sizeof(signatureBitmapLength)
     +  sizeof(signatureBitmap) + sizeof(signatureLength) */

struct PRESInlineParameterHeader {
    RTI_UINT16  pid;
    RTI_UINT16  paramLength;
};

struct PRESExtendedInlineQos {
    /* original data writer */
    struct PRESInlineParameterHeader originalWriterHeader;
    struct MIGRtpsGuid originalWriterGuid;
    struct REDASequenceNumber originalWriterSequenceNumber;
    /* coherent set */
    struct PRESInlineParameterHeader coherency_header;
    struct REDASequenceNumber coherentSetFirstSn;
    /* keyHash */
    struct PRESInlineParameterHeader keyHash_header;
    RTICdrOctet keyHash[MIG_RTPS_KEY_HASH_MAX_LENGTH];
    /* filter signature */
    struct PRESInlineParameterHeader  signature_pid;
    RTI_INT32    signatureBitmapLength;
    RTI_INT32    signatureBitmap[PRES_FILTER_SIGNATURE_BITMAP_LENGTH];
    RTI_INT32    signatureLength;
    struct PRESContentFilterSignature signature[PRES_FILTER_SIGNATURE_LENGTH_MAX];
    /* related original data writer */
    struct PRESInlineParameterHeader relatedOriginalWriterHeader;
    struct MIGRtpsGuid relatedOriginalWriterGuid;
    struct REDASequenceNumber relatedOriginalWriterSequenceNumber;
    struct PRESInlineParameterHeader sourceGuidHeader;
    struct MIGRtpsGuid sourceGuid;
    struct PRESInlineParameterHeader relatedSourceGuidHeader;
    struct MIGRtpsGuid relatedSourceGuid;
    struct PRESInlineParameterHeader relatedReaderGuidHeader;
    struct MIGRtpsGuid relatedReaderGuid;
    struct PRESInlineParameterHeader topicQueryGuidHeader;
    struct MIGRtpsGuid topicQueryGuid;
    struct PRESInlineParameterHeader sampleSignatureHeader;
    struct PRESSampleSignature sampleSignature;
};

struct PRESImmutableInlineQos {
    /* topic name */
    
    /* DURABILITY */
    struct PRESInlineParameterHeader durability_header;
    struct PRESDurabilityQosPolicy durabilityQos;
    /* PRESENTATION */
    struct PRESInlineParameterHeader presentation_header;
    struct PRESPresentationQosPolicy presentationQos;
    /* LIVELINESS */
    struct PRESInlineParameterHeader liveliness_header;
    struct PRESLivelinessQosPolicy livelinessQos;
    /* RELIABILITY */
    struct PRESInlineParameterHeader reliability_header;
    struct PRESReliabilityQosPolicy reliablityQos;
    /* DESTINATION_ORDER */
    struct PRESInlineParameterHeader destinationOrder_header;
    struct PRESDestinationOrderQosPolicy destinationOrderQos;
    /* OWNERSHIP */
    struct PRESInlineParameterHeader ownership_header;
    struct PRESOwnershipQosPolicy ownershipQos;
    /* transport priority (should be MUTABLE) */
    struct PRESInlineParameterHeader transportPriority_header;
    struct PRESTransportPriorityQosPolicy transportPriority;
};

struct PRESMutableSampleInlineQos {
    /* PARTITION */
    struct PRESInlineParameterHeader partition_header;
    RTI_INT32 parititionMaxLength;
    RTI_INT32 parititionLogicalLength;
    char partitionString[PRES_PS_PARTITION_MAXIMUM_CUMULATIVE_LENGTH_LIMIT];
    /* OWNERSHIP_STRENGTH */    
    struct PRESInlineParameterHeader ownershipStrengh_header;
    struct PRESOwnershipStrengthQosPolicy ownershipStrengthQos;
    /* LIFESPAN */
    struct PRESInlineParameterHeader lifespan_header;
    struct PRESLifespanQosPolicy lifespanQos;
};

struct PRESMutableWriterInlineQos {
    /* DEADLINE */
    struct PRESInlineParameterHeader deadline_header;
    struct PRESDeadlineQosPolicy deadlineQos;
    /* LATENCY_BUDGET */
    struct PRESInlineParameterHeader latencyBudget_header;
    struct PRESLatencyBudgetQosPolicy latencyBudgetQos;
};

struct PRESExpectedInlineQosBuffer {
    struct PRESImmutableInlineQos immutableQos;
    struct PRESMutableWriterInlineQos mutableWriterQos;
    struct PRESMutableSampleInlineQos mutableSampleQos;
    struct PRESInlineParameterHeader sentinel;
};

struct PRESAllInlineQosBuffer {
    struct PRESImmutableInlineQos immutableQos;
    struct PRESMutableWriterInlineQos mutableWriterQos;
    struct PRESMutableSampleInlineQos mutableSampleQos;
    struct PRESExtendedInlineQos extendedQos;
    struct PRESInlineParameterHeader sentinel;
};

struct PRESMutableInlineQosBuffer {
    struct PRESMutableWriterInlineQos mutableWriterQos;
    struct PRESMutableSampleInlineQos mutableSampleQos;
    struct PRESExtendedInlineQos extendedQos;
    struct PRESInlineParameterHeader sentinel;
};


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_inlineQos_h */
