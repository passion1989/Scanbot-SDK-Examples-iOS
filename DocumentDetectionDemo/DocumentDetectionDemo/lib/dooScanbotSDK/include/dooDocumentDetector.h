//
//  dooDocumentDetector.h
//  doo-ios
//
//  Created by Sebastian Husche on 28.11.13.
//  Copyright (c) 2013 doo GmbH. All rights reserved.
//

#import "dooDocumentDetectionStatus.h"
#import <AVFoundation/AVFoundation.h>
#import "dooPolygon.h"
#import "dooDeviceInformation.h"
#import "dooGeometryUtilities.h"

@interface dooDocumentDetectorResult : NSObject

@property(nonatomic, readonly) dooDocumentDetectionStatus status;
@property(nonatomic, readonly) dooPolygon *polygon;
@property(nonatomic, readonly) CGSize detectedImageSize;

@end


/** 
 @class dooDocumentDetector
 @description This class provides methods for detecting a documents outline polygon in an UIImage or CMSampleBuffer.
 */
@interface dooDocumentDetector : NSObject

/**
 @description Executes an edge detection algorithm on the given image and returns
 a polygon describing the extends of the detected box.
 @discussion For a short period of time the uncompressed image data is hold twice in memory. Use with attention.
 @param image The image to analyze.
 @param visibleRect The unified image rectangle that should be analyzed.
 (0, 0)-(1, 1) or an empty rect means the whole image is being analyzed.
 @param smooth Set to YES if you want the polygon output to be smoothed with latest frames. If you choose to use smooting
 you should call resetSmoothingData regularly.
 @param liveDetection Set YES if you want to use faster live detection. Live detection is less reliable than normal detection.
 @return The detection result containing the status and a polygon.
 */
- (dooDocumentDetectorResult *)detectDocumentPolygonOnImage:(UIImage *)image
                                           visibleImageRect:(CGRect)visibleRect
                                           smoothingEnabled:(BOOL)smooth
                                 useLiveDetectionParameters:(BOOL)liveDetection;


/**
 @description Executes an edge detection algorithm on the given sample buffer and returns
 a polygon describing the extends of the detected box.
 @discussion For a short period of time the uncompressed image data is hold twice in memory. Use with attention.
 @param sampleBuffer The CMSampleBufferRef to analyze.
 @param visibleRect The unified image rectangle that should be analyzed.
 (0, 0)-(1, 1) or an empty rect means the whole image is being analyzed.
 @param smooth Set to YES if you want the polygon output to be smoothed with latest frames. If you choose to use smooting
 you should call resetSmoothingData regularly.
 @param liveDetection Set YES if you want to use faster live detection. Live detection is less reliable than normal detection.
 @return The detection result containing the status and a polygon.
 */
- (dooDocumentDetectorResult *)detectDocumentPolygonOnSampleBuffer:(CMSampleBufferRef)sampleBuffer
                                                  visibleImageRect:(CGRect)visibleRect
                                                  smoothingEnabled:(BOOL)smooth
                                        useLiveDetectionParameters:(BOOL)liveDetection;

/**
 @description Resets the smootingData. If smoothing is enabled the polygon detector smoothes the result with results from
 previous detections. You should call this method once per second or if the device has been moved.
 */
- (void)resetSmoothingData;

@property(readonly) double currentTotalScore;
@property(readonly) double currentSizeScore;
@property(readonly) double currentWidthScore;
@property(readonly) double currentHeightScore;
@property(readonly) double currentAngleScore;
@property(nonatomic, strong, readonly) NSArray *detectedHorizontalEdges;
@property(nonatomic, strong, readonly) NSArray *detectedVerticalEdges;

@end
