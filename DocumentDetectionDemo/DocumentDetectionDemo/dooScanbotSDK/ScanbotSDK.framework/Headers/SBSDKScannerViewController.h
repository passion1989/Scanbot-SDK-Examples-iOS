//
//  SBSDKScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 08.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKPolygon.h"
#import "SBSDKCameraSession.h"
#import "SBSDKDocumentDetectionStatus.h"
#import "SBSDKImageStorage.h"

/** Forward declaration to be used in protocol declaration. */
@class SBSDKScannerViewController;

/** 
 * @protocol SBSDKScannerViewControllerDelegate
 * A delegate protocol to customize the behaviour, look and feel of the SBSDKScannerViewController.
 */
@protocol SBSDKScannerViewControllerDelegate <NSObject>

@optional

/**
 * Asks the delegate whether to detect on the next video frame or not.
 * Return NO if you dont want detection on video frames, e.g. when a view controller is presented modally or when your
 * view contollers view currently is not in the view hierarchy.
 * @param controller The calling SBSDKScannerViewController.
 * @return YES if the video frame should be analyzed, NO otherwise.
 */
- (BOOL)scannerControllerShouldAnalyseVideoFrame:(SBSDKScannerViewController *)controller;

/**
 * Tells the delegate that a document image has been cropped out of an orientation corrected still image.
 * @param controller The calling SBSDKScannerViewController.
 * @param documentImage The cropped and perspective corrected documents image.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller
  didCaptureDocumentImage:(UIImage *)documentImage;

/**
 * Tells the delegate that a still image has been captured and its orientation has been corrected. Optional.
 * @param controller The calling SBSDKScannerViewController.
 * @param sampleBuffer The captured sample buffer.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller didCaptureSampleBuffer:(CMSampleBufferRef)sampleBuffer;

/**
 * Tells the delegate that capturing a still image has been failed The underlying error is provided. Optional.
 * @param controller The calling SBSDKScannerViewController.
 * @param error The reason for the failure.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller didFailCapturingImage:(NSError *)error;

/**
 * Tells the delegate that a document detection has been occured on the current video frame. Optional.
 * @param controller The calling SBSDKScannerViewController.
 * @param polygon The polygon data describing where in the image the document was detected if any. Otherwise nil.
 * @param status The status of the detection.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller
         didDetectPolygon:(SBSDKPolygon *)polygon
               withStatus:(SBSDKDocumentDetectionStatus)status;



/**
 * Asks the delegate for a view to visualize the current detection status. Optional.
 * @param status The status of the detection.
 * @param controller The calling SBSDKScannerViewController.
 * @return A view object visualizing the detection status, e.g. a label with localized text or an image view with an icon.
 * if you return nil the standard label is displayed. If you want to show nothing just return an empty view ([UIView new]).
 * If possible reuse the views per status or just use one single configurable view.
 * The scanner view controller takes care of adding and removing your view from/to the view hierarchy.
 */
- (UIView *)viewForDetectionStatus:(SBSDKDocumentDetectionStatus)status
              forScannerController:(SBSDKScannerViewController *)controller;

/**
 * Asks the delegate for a color to use for displaying the detected documents polygon. Optional.
 * @param status The status of the detection.
 * @param controller The calling SBSDKScannerViewController.
 * @return An UIColor representing the state of detections.
 * You could for example return green for DetectionStateOK and red otherwise.
 */
- (UIColor *)polygonColorForDetectionStatus:(SBSDKDocumentDetectionStatus)status
                       forScannerController:(SBSDKScannerViewController *)controller;
@end


/**
 * @class SBSDKScannerViewController
 * UIViewController subclass showing a camera screen and running a user guiding Document detector.
 * Detection result is visualized using a polygonal bezier path.
 * This class cannot be instanced from a storyboard.
 * Instead it is installing itself as a child view controller onto a given parent view controller.
 */
@interface SBSDKScannerViewController : UIViewController

/** 
 * The delegate. See SBSDKScannerViewControllerDelegate protocol. Weak.
 */
@property (nonatomic, weak) id<SBSDKScannerViewControllerDelegate> delegate;

/** 
 * The controllers camera session.
 */
@property (nonatomic, strong, readonly) SBSDKCameraSession *cameraSession;

/**
 * The image storage. If not nil, cropped document images will be saved there,
 * independently from what the delegate is doing. Weak.
 */
@property (nonatomic, weak) SBSDKImageStorage *imageStorage;

/**
 * Scaling factor being applied to captured still shots before processing. Defaults to 0.8.
 * Used to scale images before processing them. Lower numbers reduce memory pressure.
 */
@property (nonatomic, assign) CGFloat imageScale;

/**
 * Hides or unhides the camera controls (shutter button).
 */
@property (nonatomic, assign) BOOL cameraControlsHidden;

/**
 * Desginated initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into. Nil is not recommended.
 * @param storage The image storage to persist the shot document images. Can be nil.
 */
- (instancetype)initWithParentViewController:(UIViewController *)parentViewController
                                imageStorage:(SBSDKImageStorage *)storage;

@end
