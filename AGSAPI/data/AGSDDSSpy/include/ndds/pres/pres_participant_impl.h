/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_participant_impl.h    generated by: makeheader    Fri Feb 16 13:51:42 2018
 *
 *		built from:	participant_impl.ifc
 */

#ifndef pres_participant_impl_h
#define pres_participant_impl_h


#ifdef __cplusplus
    extern "C" {
#endif



 #define PRESReducedLocatorDerivableQosPolicy_asLocatorDerivableQosPolicy(qos) \
        ((struct PRESLocatorDerivableQosPolicy *) (qos))

#define PRESParticipant_calculateTotalSize(testType, userObjectSize, userObjectAlignment) \
  (((userObjectSize) <= 0) ? sizeof(testType) : \
    (RTIOsapiAlignment_alignSizeUp(sizeof(testType), (userObjectAlignment)) + (userObjectSize)))

#define PRESParticipant_calculateTotalAlignment(testType, userObjectSize, userObjectAlignment) \
  (((userObjectSize) <= 0) ? RTIOsapiAlignment_getAlignmentOf(testType) : \
   ((RTIOsapiAlignment_getAlignmentOf(testType) < (userObjectAlignment)) ? \
     (userObjectAlignment) : RTIOsapiAlignment_getAlignmentOf(testType)))

#define PRESParticipant_calculateUserObjectPointer(entityPtr, testType, userObjectSize, userObjectAlignment) \
  (((userObjectSize) <= 0) ? (void *)NULL : \
   (void *)((char *)(entityPtr) + RTIOsapiAlignment_alignSizeUp(sizeof(testType), (userObjectAlignment))))

#define PRESInstanceHandle_compare(handle1, handle2)                           \
 (((handle1)->isValid - (handle2)->isValid)                                    \
  ? ((handle1)->isValid - (handle2)->isValid)                                  \
  : (MIGRtpsKeyHash_compare(&(handle1)->keyHash,                        \
      &(handle2)->keyHash)))

/* TODO: this should be enough as PRES_INSTANCE_HANDLE_NIL should be used
    everywhere and it sets the boolean to false */
#define PRESInstanceHandle_isNil(__me)                         \
		(!(__me)->isValid)

/*
 * If a remote participant has an identity token, then it is able to do
 * authentication, which is the foundation for the rest of security. Without
 * authentication, it can do no security.
 */
#define PRESRemoteParticipant_isAuthenticationEnabled( \
    /* struct PRESParticipantParameter * */parameter) \
    (!PRESDataHolder_isNil((parameter)->securityTokens.identity))


extern PRESDllExport
RTIBool PRESParticipant_assertRemoteParticipantI(
    struct PRESParticipant *me,
    int *failReason, /* out */
    struct PRESRemoteParticipantProperty *verifiedProperty, /* out */
    struct PRESReducedLocatorQosPolicy *oldMetatrafficMulticastLocator, /* out */
    struct PRESLocatorQosPolicy *oldMetatrafficUnicastLocator, /* out */
    const PRESSampleHash *sampleHash,
    const struct PRESSampleSignature *sampleSignature,
    const struct PRESParticipantParameter *participantParameter, /* Used only if called from disc.2.0 */
    const MIGRtpsParticipantId *remoteParticipantId /*RTPS.2.0*/,
    const struct PRESRemoteParticipantProperty *property,
    struct REDAWorker *worker);

extern PRESDllExport
RTIBool PRESParticipant_verifyRemoteParticipantSignedDataI(
    struct PRESParticipant *me,
    const MIGRtpsParticipantId *remoteParticipantId,
    const struct REDABuffer *signedData,
    const struct REDABuffer *signature,
    struct REDAWorker *worker);

extern PRESDllExport
RTIBool PRESParticipant_verifyRemoteParticipantDiscoverySampleSignatureI(
    struct PRESParticipant *me,
    const MIGRtpsParticipantId *remoteParticipantId,
    const struct PRESSampleSignature *sampleSignature,
    MIGRtpsStatusInfo signatureStatusInfo,
    const PRESSampleHash *sampleHash,
    struct REDAWorker *worker);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_participant_impl_h */