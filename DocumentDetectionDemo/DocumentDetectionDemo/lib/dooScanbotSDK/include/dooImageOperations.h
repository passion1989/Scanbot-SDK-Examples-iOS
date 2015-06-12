//
//  dooImageOperations.h
//  Scanbot SDK
//
//  Created by Sebastian Husche on 27.05.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "dooImageFilterTypes.h"
#import "dooPolygon.h"

/**
 @class dooImageOperations
 @description Factory class to perform various operations on UIImage objects, 
 such as applying filters and cropping by polygon.
 */
@interface dooImageOperations : NSObject

/** 
 @description Applies a filter to the given image and returns the filtered image.
 @param filter The type of the filter to be applied.
 @param image The UIImage the filter will be applied to.
 @return The filtered UIImage.
 **/
+ (UIImage *)applyFilter:(dooImageFilterType)filter onImage:(UIImage *)image;

/** 
 @description Applies a polygon to the given image and returns the cropped and perspective corrected image.
 @param polygon The polygon used to crop and perspective correct the image.
 @param image The UIImage to be cropped and perspective corrected.
 @return The cropped and perspective corrected UIImage.
 **/
+ (UIImage *)applyPolygon:(dooPolygon *)polygon onImage:(UIImage *)image;

/** 
 @description Applies a polygon and a filter to the given image. Faster than two sequential operations.
 @param polygon The polygon used to crop and perspective correct the image.
 @param filter The type of the filter to be applied.
 @param image The UIImage to be cropped and perspective corrected.
 @return The cropped and perspective corrected UIImage.
**/
+ (UIImage *)applyPolygon:(dooPolygon *)polygon andFilter:(dooImageFilterType)filter onImage:(UIImage *)image;

@end


/**
 @category dooImageOperations
 @description A category on UIImage to apply filters and polygons on the receiver.
 **/
@interface UIImage (dooImageOperations)

/**
 @description Applies a filter to the receiver and returns the filtered image.
 @param filter The type of the filter to be applied.
 @return The filtered UIImage.
 **/
- (UIImage *)imageFilteredBy:(dooImageFilterType)filter;

/**
 @description Applies a polygon to the receiver and returns the cropped and perspective corrected image.
 @param polygon The polygon used to crop and perspective correct the image.
 @return The cropped and perspective corrected UIImage.
 **/
- (UIImage *)imageCroppedByPolygon:(dooPolygon *)polygon;

/**
 @description Applies a polygon and a filter to the receiver. Faster than two sequential operations.
 @param polygon The polygon used to crop and perspective correct the image.
 @param filter The type of the filter to be applied.
 @return The cropped and perspective corrected UIImage.
 **/
- (UIImage *)imageCroppedByPolygon:(dooPolygon *)polygon andFilteredBy:(dooImageFilterType)filter;

@end