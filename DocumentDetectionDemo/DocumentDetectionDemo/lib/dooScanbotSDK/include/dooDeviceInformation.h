//
//  dooDeviceInformation.h
//  DooTheSnap
//
//  Created by Sebastian Husche on 20.03.15.
//  Copyright (c) 2015 doo. All rights reserved.
//

#import <Foundation/Foundation.h>

/** 
 @class dooDeviceInformation
 @description Delivers information about the iOS device.
 */
@interface dooDeviceInformation : NSObject

/** @description The name of the device. **/
+ (NSString *)deviceName;

/** @description The full name of the device including the iOS version. **/
+ (NSString *)fullDeviceName;

/** @description Returns YES if the device should use medium scan quality, NO otherwise. **/
+ (BOOL)deviceUsesMediumScanQuality;

/** @description Returns YES if the device is able to perform live video processing, NO otherwise. **/
+ (BOOL)deviceUsesVideoProcessing;

/** @description Returns YES if the device should use low performance document detection, NO otherwise. **/
+ (BOOL)deviceUsesLowPerformanceDetection;

@end
