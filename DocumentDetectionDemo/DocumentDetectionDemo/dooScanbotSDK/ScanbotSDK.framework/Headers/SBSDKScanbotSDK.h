//
//  SBSDKScanbotSDK.h
//  Scanbot SDK
//
//  Created by Sebastian Husche on 05.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//


#import "SBSDKScanbotSDKConstants.h"

#import "SBSDKDocumentDetector.h"
#import "SBSDKDocumentDetectionStatus.h"
#import "SBSDKImageFilterTypes.h"
#import "SBSDKDeviceInformation.h"
#import "SBSDKGeometryUtilities.h"
#import "SBSDKPolygon.h"
#import "SBSDKPolygonEdge.h"

#import "SBSDKCameraSession.h"
#import "SBSDKScannerViewController.h"
#import "SBSDKPolygonLayer.h"
#import "SBSDKShutterButton.h"
#import "SBSDKDetectionStatusLabel.h"

#import "SBSDKImageProcessor.h"

#import "SBSDKOpticalTextRecognizer.h"
#import "SBSDKOCRResult.h"
#import "SBSDKPageAnalyzerResult.h"

#import "SBSDKPayFormScanner.h"

#import "SBSDKPDFRenderer.h"

#import "UIImageSBSDK.h"
#import "SBSDKImageStorage.h"
#import "SBSDKProcessingQueueFactory.h"
#import "SBSDKProgress.h"

#import <Foundation/Foundation.h>

/**
 * @class ScanbotSDK
 * Main class of Scanbot SDK. Lets you install the license and allows basic configuration.
 */
@interface ScanbotSDK : NSObject

/** 
 * Enables or disables the Scanbot SDK logging. If enabled Scanbot SDK logs various warnings, 
 * errors and info to the console. By default logging is off.
 * @param enabled YES, if Scanbot SDK should log, NO otherwise.
 */
+ (void)setLoggingEnabled:(BOOL)enabled;

/**
 * Installs the Scanbot SDK license from a string.
 * @param licenseString The string containing the license.
 * @return YES, if the license was installed and is active, NO otherwise.
 */
+ (BOOL)setLicense:(NSString *)licenseString;

@end
