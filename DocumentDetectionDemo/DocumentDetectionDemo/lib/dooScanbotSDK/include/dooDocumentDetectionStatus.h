//
// dooDocumentDetectionStatus.h
//  doo-ios
//
//  Created by Sebastian Husche on 09.01.14.
//  Copyright (c) 2014 doo GmbH. All rights reserved.
//

#ifndef doo_ios_DocumentDetectionStatus_h
#define doo_ios_DocumentDetectionStatus_h

typedef enum dooDocumentDetectionStatus {

    //A good polygon was detected.
   dooDocumentDetectionStatusOK = 100,
    // A polygon was detected but was too small.
   dooDocumentDetectionStatusOK_SmallSize = 101,
    // A polygon was detected but it is distorted too much.
   dooDocumentDetectionStatusOK_BadAngles = 102,
    // A polygon was detected but its aspect ratio is wrong.
   dooDocumentDetectionStatusOK_BadAspectRatio = 103,

    //No polygon detected.
   dooDocumentDetectionStatusError_NothingDetected = 200,
    //No polygon detected, image too dark. (Not yet used)
   dooDocumentDetectionStatusError_Brightness = 201,
    //No polygon detected, image too noisy (background).
   dooDocumentDetectionStatusError_Noise = 202
} dooDocumentDetectionStatus;

inline bool isDetectionStatusOK(dooDocumentDetectionStatus status) {

    return (status == dooDocumentDetectionStatusOK
            || status == dooDocumentDetectionStatusOK_BadAngles
            || status == dooDocumentDetectionStatusOK_BadAspectRatio
            || status == dooDocumentDetectionStatusOK_SmallSize);
}

#endif
