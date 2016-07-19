//
//  SBSDKImageMetadata.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 01.07.16.
//  Copyright © 2016 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @class SBSDKImageMetadata
 * Encapsulates image metadata, e.g. EXIF, TIFF, JFIF in a convenient way.
 * Use SBSDKImageMetadataProcessor to extract metadata from and inject changed metadata into image data.
 */
@interface SBSDKImageMetadata : NSObject

/** The raw metadata dictionary as it gets extracted from CGImageSourceCopyPropertiesAtIndex. Readonly. **/
@property(nonatomic, readonly) NSDictionary *metadataDictionary;

/** The orientation flag of the image. **/
@property(nonatomic, assign) NSUInteger orientation;

/** The width of the image in pixels. **/
@property(nonatomic, assign) NSUInteger imageWidth;

/** The height of the image in pixels. **/
@property(nonatomic, assign) NSUInteger imageHeight;

/** The date of when the image was captured. **/
@property(nonatomic, strong) NSDate *originalDate;

/** The date of when the image was digitized. **/
@property(nonatomic, strong) NSDate *digitalizationDate;

/** The model of the lens used to capture the image. Readonly. **/
@property(nonatomic, readonly, strong) NSString *lensModel;

/** The manufacturer of the lens used to capture the image. Readonly. **/
@property(nonatomic, readonly, strong) NSString *lensMaker;

/** The real focal length of the lens used to capture the image. Measured in millimeters. Readonly. **/
@property(nonatomic, readonly, strong) NSNumber *focalLength;

/** The 35mm equivalent focal length of the lens used to capture the image. Measured in millimeters. Readonly. **/
@property(nonatomic, readonly, strong) NSNumber *focalLength35mm;

/** The f-stop number or aperture of the lens used to capture the image. Readonly. **/
@property(nonatomic, readonly, strong) NSNumber *aperture;

/** The duration the sensor was exposed during capturing the image. Equals to 1.0 / shutter speed. Readonly. **/
@property(nonatomic, readonly, strong) NSNumber *exposureTime;

/** The ISO value used to capture the image. Readonly. **/
@property(nonatomic, readonly, strong) NSNumber *ISOValue;

/** Designated initializer. 
 * @param metadata Takes the the raw metadata dictionary as it gets extracted from CGImageSourceCopyPropertiesAtIndex.
 * @return A new SBSDKImageMetadata object or nil, if the metadata dictionary does not contain valid metadata.
 **/
- (instancetype)initWithMetadataDictionary:(NSDictionary *)metadata;

@end
