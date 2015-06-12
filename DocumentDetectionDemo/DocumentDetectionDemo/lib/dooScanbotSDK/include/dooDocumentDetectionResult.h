//
//  DetectionStatus.h
//  doo-ios
//
//  Created by Sebastian Husche on 09.01.14.
//  Copyright (c) 2014 doo GmbH. All rights reserved.
//

#ifndef doo_ios_DetectionStatus_h
#define doo_ios_DetectionStatus_h

typedef enum DetectionStatus
{
    //A good polygon was detected.
    DetectionStatusOK = 100,
    // A polygon was detected but was too small.
    DetectionStatusOK_SmallSize = 101,
    // A polygon was detected but it is distorted too much.
    DetectionStatusOK_BadAngles = 102,
    // A polygon was detected but its aspect ratio is wrong.
    DetectionStatusOK_BadAspectRatio = 103,

    //No polygon detected.
    DetectionStatusError_NothingDetected = 200,
    //No polygon detected, image too dark. (Not yet used)
    DetectionStatusError_Brightness = 201,
    //No polygon detected, image too noisy (background).
    DetectionStatusError_Noise = 202
} DetectionStatus;

inline bool isDetectionStatusOK(DetectionStatus status)
{

    return (status == DetectionStatusOK || status == DetectionStatusOK_BadAngles || status == DetectionStatusOK_BadAspectRatio
            || status == DetectionStatusOK_SmallSize);
}

#endif
