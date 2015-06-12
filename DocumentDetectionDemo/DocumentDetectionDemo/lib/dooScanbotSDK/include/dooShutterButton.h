//
//  dooShutterButton.h
//  SnapIos
//
//  Created by Sebastian Husche on 09.07.13.
//  Copyright (c) 2014 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/** 
 @enum ShutterButtonStatus
 @description This enum describes the possible states of a dooShutterButton object.
 **/
typedef NS_ENUM(NSInteger, ShutterButtonStatus) {
    /** 
     @description Indicates to the user, we are currently searching a document. 
     The dooShutterButton plays some animations.
     **/
    ShutterButtonStatusSearching,

    /** @description
     Indicates to the user, we are currently tracking a document. The dooShutterButton plays some animations. 
     **/
    ShutterButtonStatusDetected,

    /** @description We are currently not able to detect a document. The dooShutterButton returns to a static look
     indicating that he might press the button manually. 
     **/
    ShutterButtonStatusIdle
};

/** 
 @class dooShutterButton
 @description The button class used in the camera view controller to take a snapshot. 
 Animates itself depending on its status.**/
@interface dooShutterButton : UIButton

/** 
 @description Indicates, whether a still image is currently being taken or not.
 If YES a UIActivityIndicator is shown in the center. 
 **/
@property(nonatomic, assign) BOOL takingPhoto;

/**
 @description
 The current status of the receiver. See above. 
 **/
@property(nonatomic, assign) ShutterButtonStatus buttonStatus;
@end


/** Appearance setters. **/
@interface dooShutterButton(Appearance)
- (void)setButtonSearchingColor:(UIColor *)color UI_APPEARANCE_SELECTOR;
- (void)setButtonDetectedColor:(UIColor *)color UI_APPEARANCE_SELECTOR;
@end
