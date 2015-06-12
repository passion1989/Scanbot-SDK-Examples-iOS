//
//  dooDocumentScannerViewController.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 08.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "dooPolygon.h"
#import "dooDocumentDetectionStatus.h"

/** Forward declaration to be used in protocol declaration. **/
@class dooDocumentScannerViewController;

/** 
 @protocol dooDocumentScannerViewControllerDelegate
 @description A delegate protocol to customize the behaviour, look and feel of the dooDocumentScannerViewController.
 **/
@protocol dooDocumentScannerViewControllerDelegate <NSObject>

@required

/**
 @description Tells the delegate that a document image has been cropped out of an orientation corrected still image.
 @param controller The calling dooDocumentScannerViewController.
 @param documentImage The cropped and perspective corrected documents image.
 **/
- (void)scannerController:(dooDocumentScannerViewController *)controller
  didCaptureDocumentImage:(UIImage *)documentImage;

@optional

/**
 @description Tells the delegate that a still image has been captured and its orientation has been corrected. Optional.
 @param controller The calling dooDocumentScannerViewController.
 @param image The captured image.
 **/
- (void)scannerController:(dooDocumentScannerViewController *)controller didCaptureImage:(UIImage *)image;

/**
 @description Tells the delegate that capturing a still image has been failed The underlying error is provided. Optional.
 @param controller The calling dooDocumentScannerViewController.
 @param error The reason for the failure.
 **/
- (void)scannerController:(dooDocumentScannerViewController *)controller didFailCapturingImage:(NSError *)error;

/**
 @description Tells the delegate that a document detection has been occured on the current video frame. Optional.
 @param controller The calling dooDocumentScannerViewController.
 @param polygon The polygon data describing where in the image the document was detected if any. Otherwise nil.
 @param status The status of the detection.
 **/
- (void)scannerController:(dooDocumentScannerViewController *)controller
         didDetectPolygon:(dooPolygon *)polygon
               withStatus:(dooDocumentDetectionStatus)status;



/**
 @description Asks the delegate for a view to visualize the current detection status. Optional.
 @param status The status of the detection.
 @param controller The calling dooDocumentScannerViewController.
 @return A view object visualizing the detection status, e.g. a label with localized text or an image view with an icon.
 if you return nil the standard label is displayed. If you want to show nothing just return an empty view ([UIView new]).
 @discussion If possible reuse the views per status or just use one single configurable view. 
 The scanner view controller takes care of adding and removing your view from/to the view hierarchy.
 **/
- (UIView *)viewForDetectionStatus:(dooDocumentDetectionStatus)status
              forScannerController:(dooDocumentScannerViewController *)controller;

/**
 @description Asks the delegate for a color to use for displaying the detected documents polygon. Optional.
 @param status The status of the detection.
 @param controller The calling dooDocumentScannerViewController.
 @return An UIColor representing the state of detections. 
 You could for example return green for DetectionStateOK and red otherwise.
 **/
- (UIColor *)polygonColorForDetectionStatus:(dooDocumentDetectionStatus)status
                       forScannerController:(dooDocumentScannerViewController *)controller;
@end


/**
 @class dooDocumentScannerViewController
 @description UIViewController subclass showing a camera screen and running a user guiding Document detector.
 Detection result is visualized using a polygonal bezier path. 
 This class cannot be instanced from a storyboard.
 Instead it is installing itself as a child view controller onto a given parent view controller.
 **/
@interface dooDocumentScannerViewController : UIViewController

/** 
 @description The delegate. See dooDocumentScannerViewControllerDelegate protocol. 
 **/
@property (nonatomic, weak) id<dooDocumentScannerViewControllerDelegate> delegate;

/**
 @description Desginated initializer. Installs the receiver as child view controller onto the parent view controllers
 view using its entire bounds area.
 **/
- (instancetype)initWithParentViewController:(UIViewController *)parentViewController;

@end
