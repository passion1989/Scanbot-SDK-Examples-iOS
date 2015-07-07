//
//  SBSDKShutterButton.h
//  SnapIos
//
//  Created by Sebastian Husche on 09.07.13.
//  Copyright (c) 2014 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/** 
 @enum ShutterButtonStatus
  This enum describes the possible states of a SBSDKShutterButton object.
 **/
typedef NS_ENUM(NSInteger, ShutterButtonStatus) {
    /** Indicates to the user, we are currently searching a document. The SBSDKShutterButton plays some animations. **/
    ShutterButtonStatusSearching,

    /** Indicates to the user, we are currently tracking a document. The SBSDKShutterButton plays some animations. **/
    ShutterButtonStatusDetected,

    /** We are currently not able to detect a document. The SBSDKShutterButton returns to a static look
     indicating that the user might manually release the shutter by hitting the button. **/
    ShutterButtonStatusIdle
};

/** 
 @class SBSDKShutterButton
  The button class used in the camera view controller to take a snapshot. 
 Animates itself depending on its status.**/
@interface SBSDKShutterButton : UIButton

/** 
  Indicates, whether a still image is currently being taken or not.
 If YES a UIActivityIndicator is shown in the center. 
 **/
@property(nonatomic, assign) BOOL takingPhoto;

/**
  The current status of the receiver. See ShutterButtonStatus.
 **/
@property(nonatomic, assign) ShutterButtonStatus buttonStatus;

@end
