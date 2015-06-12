//
//  dooScanbotSDKLicense.h
//  Scanbot SDK
//
//  Created by Sebastian Husche on 03.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 @class dooScanbotSDKLicense
 @description Installs your license and enabled all features listed in the license.
 **/
@interface dooScanbotSDKLicense : NSObject

/** 
 @description Installs the license from file at the given file path. 
 @param licenseFilePath The path to the license file.
 @return YES, if the license was installed and is active, NO otherwise.
 **/
+ (BOOL)installLicenseFromFile:(NSString *)licenseFilePath;

/**
 @description Tries to automatically install a license. Searches your apps main bundle for any *.sbsdklic file and 
 tries to install the first found.
 @return YES, if the license was installed and is active, NO otherwise.
 **/
+ (BOOL)autoInstallLicense;

@end
