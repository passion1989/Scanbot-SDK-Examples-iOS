//
//  dooCameraSession.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 22.04.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "dooFeatures.h"

/**
 @protocol dooCameraSessionDelegate
 @description A delegate protocol that gathers AVCaptureVideoDataOutputSampleBufferDelegate 
 and AVCaptureMetadataOutputObjectsDelegate protocols.
 **/
@protocol dooCameraSessionDelegate <AVCaptureVideoDataOutputSampleBufferDelegate,
AVCaptureMetadataOutputObjectsDelegate>
@end

/**
 @class dooCameraSession
 @description An easy-to-use wrapper around the AVFoundations video capture session. Sets up and configures the
 camera device and the preview layer. Provides functionality to capture still images.
 */
@interface dooCameraSession : NSObject

/** 
 @description The preview layer that the camera device uses to ouput the current video frames. 
 Can be added to any superlayer.
 **/
@property (nonatomic, readonly) AVCaptureVideoPreviewLayer *previewLayer;

/** 
 @description The delegate object for camera output. 
 Its receives the video frames, still image captures and meta data capture, like QR code.
 Delegates can implement all functions from AVCaptureVideoDataOutputSampleBufferDelegate and
 AVCaptureMetadataOutputObjectsDelegate protocols.
 **/
@property (nonatomic, weak) id<dooCameraSessionDelegate> videoDelegate;

/**
 @description Returns YES if the camera is currenty in the process of taking a still image, NO otherwise.
 **/
@property (nonatomic, readonly) BOOL isCapturingStillImage;

/** 
 @description The designated initializer of the class. Does not start the capture session.
 @param feature The feature you want to use the camera for. Relevant features are Document Detection,
 Payform Detection and QR Codes.
 @return Newly created and configured instance.
 **/
- (instancetype)initForFeature:(dooFeature)feature;

/**
 @description Starts the camera capture session. Does nothing if the session is already running.
 **/
- (void)startSession;

/**
 @description Stops the camera capture session. Does nothing if the session is already stopped.
 **/
- (void)stopSession;

/**
 @description Returns YES if the camera session has already been started, NO otherwise.
 **/
- (BOOL)isSessionRunning;

/** 
 @description Captures a still image asynchronously and passes the CMSampleBufferRef and if needed an error to the
 completion handler. The CMSampleBufferRef can be converted to any image format/object like UIImage. 
 @param completion The completion handler that is called when the still image has been captured.
 **/
- (void)captureStillImageWithCompletionHandler:(void (^)(CMSampleBufferRef, NSError *))completion;

/**
 @description Returns YES, if the camera is currently adjusting autofocus, exposure or white balance, NO otherwise. 
 **/
- (BOOL)isCameraAdjusting;

/**
 @description Sets the video frame orientiation to the given value.
 **/
- (void)setVideoOrientation:(AVCaptureVideoOrientation) videoOrientation;

@end
