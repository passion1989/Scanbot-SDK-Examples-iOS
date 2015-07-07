//
//  SBSDKScanbotSDKLicense.h
//  Scanbot SDK
//
//  Created by Sebastian Husche on 03.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 @class SBSDKScanbotSDKLicense
 Installs your Scanbot SDK license and activates all features covered by the license.
 This must be done before a class or function of Scanbot SDK is used in the project. Ideally the license is installed
 in your projects app delegates `applicationDidFinishLaunching:` method.
 Installing the license can be done automatically or by specifying the path to the license file.
 **/
@interface SBSDKScanbotSDKLicense : NSObject

/** 
 Installs the license from file at the given file path.
 @param licenseFilePath The path to the license file.
 @return YES, if the license was installed and is active, NO otherwise.
 **/
+ (BOOL)installLicenseFromFile:(NSString *)licenseFilePath;

/**
 Tries to automatically install a license. Searches your apps main bundle for any *.sbsdklic file and
 tries to install the first found.
 @return YES, if the license was installed and is active, NO otherwise.
 **/
+ (BOOL)autoInstallLicense;

@end
