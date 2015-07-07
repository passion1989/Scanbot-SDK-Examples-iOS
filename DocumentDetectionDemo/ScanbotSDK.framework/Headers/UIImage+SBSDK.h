//
//  UIImage+SBSDK.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 29.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SBSDKImageFilterTypes.h"
#import "SBSDKPolygon.h"

/** 
 * An UIImage class extension to perform basic image processing operations.
 * Direct usage is not recommended for large images. Instead use SBSDKImageProcessor methods to employ
 * queues and proper memory management.
 **/
@interface UIImage (SBSDK)

/**
  Applies a filter to the receiver and returns the filtered image.
 @param filter The type of the filter to be applied.
 @return The filtered UIImage.
 **/
- (UIImage *)imageFilteredBy:(SBSDKImageFilterType)filter;

/**
  Applies a polygon to the receiver and returns the cropped and perspective corrected image.
 @param polygon The polygon used to crop and perspective correct the image.
 @return The cropped and perspective corrected UIImage.
 **/
- (UIImage *)imageCroppedByPolygon:(SBSDKPolygon *)polygon;

/**
  Applies a polygon and a filter to the receiver. Faster than two sequential operations.
 @param polygon The polygon used to crop and perspective correct the image.
 @param filter The type of the filter to be applied.
 @return The cropped and perspective corrected UIImage.
 **/
- (UIImage *)imageCroppedByPolygon:(SBSDKPolygon *)polygon andFilteredBy:(SBSDKImageFilterType)filter;

/**
  Applies clockwise 90 degree rotations to the receiver.
 @param times Number of 90 degree rotations to apply. Can be negative. Uses modulo arithmetics.
 @return The rotated UIImage.
 **/
- (UIImage *)imageRotatedClockwise:(NSInteger)times;

/**
  Applies counter-clockwise 90 degree rotations to the receiver.
 @param times Number of 90 degree rotations to apply. Can be negative. Uses modulo arithmetics.
 @return The rotated UIImage.
 **/
- (UIImage *)imageRotatedCounterClockwise:(NSInteger)times;

@end
