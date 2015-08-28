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

/**
 * @enum SBSDKShutterMode
 * This enum describes the possible modes of the cameras shutter. 
 * Automatic shutter means, a photo is taken automatically if a document was detected in the video stream.
 * The smart mode is the default mode. Whenever the automatic shutter is toggled the delegate of 
 * SBSDKScannerViewController is informed. You can also the query the autoShutterEnabled property.
 * The default shutter button reflects this mode.
 */
typedef NS_ENUM(NSInteger, SBSDKShutterMode) {
    
    /** 
     * Toggles the automatic shutter in a smart way. If there, for 3 seconds, is no significant device motion and 
     * no document was detected the automatic snapping is turned off. Significant device motion turns it on again.
     */
    SBSDKShutterModeSmart = 0,

    /** The camera will always take a photo automatically when a document was detected. */
    SBSDKShutterModeAlwaysAuto = 1,

    /** The camera will never take a photo automatically. */
    SBSDKShutterModeAlwaysManual = 2
};


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
 * Informs the delegate that the scanner has toggled automatic shutter release on or off.
 * @param controller The calling SBSDKScannerViewController.
 * @param enable YES, if the auto shutter was turned on, NO otherwise.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller didToggleAutoShutter:(BOOL)enable;

/**
 * Tells the delegate that a still image is about to be captured. Here you can change the appearance of you custom 
 * shutter button or HUD to reflect in the UI that we are now busy taking an image.
 * @param controller The calling SBSDKScannerViewController.
 */
- (void)scannerControllerWillCaptureStillImage:(SBSDKScannerViewController *)controller;

/**
 * Tells the delegate that a document image has been cropped out of an orientation corrected still image.
 * @param controller The calling SBSDKScannerViewController.
 * @param documentImage The cropped and perspective corrected documents image, rotated depending on the device orientation.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller
  didCaptureDocumentImage:(UIImage *)documentImage;

/**
 * Tells the delegate that a still image has been captured and its orientation has been corrected. Optional.
 * @param controller The calling SBSDKScannerViewController.
 * @param image The captured original image, rotated depending on the device orientation.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller didCaptureImage:(UIImage *)image;

/**
 * Tells the delegate that capturing a still image has been failed The underlying error is provided. Optional.
 * @param controller The calling SBSDKScannerViewController.
 * @param error The reason for the failure.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller didFailCapturingImage:(NSError *)error;

/**
 * Tells the delegate that a document detection has been occured on the current video frame. Optional.
 * Here you can update your custom shutter button if needed and your HUD data.
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
 * @return Your custom view to visualize the detection status, e.g. a label with localized text or 
 * an image view with an icon.
 * If you return nil the standard label is displayed. If you want to show nothing just return an empty view ([UIView new]).
 * If possible reuse the views per status or just use one single configurable view.
 * The scanner view controller takes care of adding and removing your view from/to the view hierarchy.
 */
- (UIView *)scannerController:(SBSDKScannerViewController *)controller
       viewForDetectionStatus:(SBSDKDocumentDetectionStatus)status;


/** 
 * Asks the delegate for custom shutter release button.
 * @param controller The calling SBSDKScannerViewController.
 * @return An instance of your custom shutter release button. Target and action are set automatically by controller.
 * If you return nil, the built-in standard button is used.
 */
- (UIButton *)scannerControllerCustomShutterButton:(SBSDKScannerViewController *)controller;


/**
 * Implement this method to customize the detected documents polygon drawing. If you implement this method you are 
 * responsible for correct configuration of the shape layer and setting the shape layers path property.
 * Implementing this method also disables calling of the delegate 
 * method -(UIColor *)scannerController:polygonColorForDetectionStatus:
 * @param controller The calling SBSDKScannerViewController.
 * @param pointValues NSArray of 4 NSValues, containing CGPointValues. Or nil if there was no polygon detected. 
 * Extract each point: CGPoint point = [pointValues[index] CGPointValue]. The points are already converted to 
 * layer coordinate system and therefore can directly be used for drawing or creating a bezier path.
 * @param detectionStatus The current detection status.
 * @param layer The shape layer that draws the bezier path of the polygon points. 
 * You can configure the layers stroke and fill color, the line width and other parameters. 
 * See the documentation for CAShapeLayer.
 */
- (void)scannerController:(SBSDKScannerViewController *)controller
        drawPolygonPoints:(NSArray *)pointValues
      withDetectionStatus:(SBSDKDocumentDetectionStatus)detectionStatus
                  onLayer:(CAShapeLayer *)layer;

/**
 * Asks the delegate for a color to use for displaying the detected documents polygon. Optional.
 * Note: This method is not called if the delegate 
 * implements -(void)scannerController:drawPolygonPoints:withDetectionStatus:onLayer:
 * @param status The status of the detection.
 * @param controller The calling SBSDKScannerViewController.
 * @return An UIColor representing the state of detections.
 * You could for example return green for DetectionStateOK and red otherwise.
 */
- (UIColor *)scannerController:(SBSDKScannerViewController *)controller polygonColorForDetectionStatus:(SBSDKDocumentDetectionStatus)status;


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
 * Scaling factor being applied to captured still shots before processing. Must be in the range 0.0 < imageScale <= 1.0.
 * Invalid values are threated as 1.0. Defaults to 0.8.
 * Used to scale images before processing them. Lower numbers reduce memory pressure.
 */
@property (nonatomic, assign) CGFloat imageScale;

/**
 * The minimum size in percent (0 - 100) of the screen size to accept a detected document.
 * It is sufficient that height or width match the score. Default is 80.0.
 * Warning: Lower values result in low resolution document images.
 **/
@property(nonatomic, assign) double acceptedSizeScore;

/**
 * The minimum score in percent (0 - 100) of the perspective distortion to accept a detected document.
 * Default is 75.0. Set lower values to accept more perspective distortion.
 * Warning: Lower values result in more blurred document images.
 **/
@property(nonatomic, assign) double acceptedAngleScore;

/**
 * Hides or unhides the shutter button.
 */
@property (nonatomic, assign) BOOL shutterButtonHidden;

/**
 * Hides or unhides the detection status label and polygon layer.
 **/
@property (nonatomic, assign) BOOL detectionStatusHidden;


/** 
 * The receivers shutter mode. See SBSDKShutterMode. Defaults to SBSDKShutterModeSmart.
 */
@property (nonatomic, assign) SBSDKShutterMode shutterMode;

/** 
 * Whether the receiver automatically releases the shutter or not.
 * Powerful energy saver if combined with the delegate method 
 * (BOOL)scannerControllerShouldAnalyseVideoFrame:(SBSDKScannerViewController *)controller.
 * If you return controller.autoShutterEnabled here the document detection is toggled off until you re-enable 
 * the auto shutter or significantly move your device.
  **/
@property (nonatomic, readonly) BOOL autoShutterEnabled;

/**
 * A transparent view that lies over the preview layer. You can add custom UI here. Read-only.
 */
@property (nonatomic, strong, readonly) UIView *HUDView;

/**
 * Desginated initializer. Installs the receiver as child view controller onto the parent view controllers
 * view using its entire bounds area.
 * @param parentViewController The view controller the newly created instance is embedded into. Nil is not recommended.
 * If parentViewController conforms to SBSDKScannerViewControllerDelegate, it is automatically set as delegate.
 * @param storage The image storage to persist the shot document images. Can be nil.
 */
- (instancetype)initWithParentViewController:(UIViewController *)parentViewController
                                imageStorage:(SBSDKImageStorage *)storage;

/** 
 * Captures a still image manually and calls the delegate methods.
 * @return YES, if the capture process has been initiated successfully. NO otherwise. 
 * Note: NO is returned if the device is currently capturing another image or if the camera session is not yet setup or broken.
 **/
- (BOOL)captureStillImage;

@end
