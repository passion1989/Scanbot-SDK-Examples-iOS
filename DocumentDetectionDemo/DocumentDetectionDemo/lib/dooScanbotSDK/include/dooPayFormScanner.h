//
//  dooPayFormScanner.h
//  Scanbot SDK
//
//  Created by Sebastian Husche on 21.04.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

// SWIFT 1.2 NONNULL REGION: REMOVE IF NOT USING XCODE 6.3
NS_ASSUME_NONNULL_BEGIN

#pragma mark - dooPayFormTokenType

/** An enumeration describing the types of tokens the dooPayFormScanner can detect and recognize. **/
typedef NS_ENUM(NSInteger, dooPayFormTokenType) {
    /** The name of the payments receiver. **/
    dooPayFormTokenTypeReceiver,

    /** The IBAN of the payments receiver. **/
    dooPayFormTokenTypeIBAN,

    /** The BIC of the payments receiver. **/
    dooPayFormTokenTypeBIC,

    /** The amount of money being transferred. **/
    dooPayFormTokenTypeAmount,

    /** The reference number or text. **/
    dooPayFormTokenTypeReferenceNo
};





#pragma mark - dooPayFormToken

/** Describes the position and the type of a text box within the image being detected or recognized. **/
@interface dooPayFormToken : NSObject

/** The rectangle of the receiver marking the area on the perspective corrected and cropped image. **/
@property (nonatomic, assign, readonly) CGRect rect;

/** The receivers type. **/
@property (nonatomic, assign, readonly) dooPayFormTokenType type;

@end





#pragma mark - dooPayFormRecognizedField

/** 
 Resulting element of the dooPayFormScanners recognizer.
 Holds a token and its recognized text value after recognition. 
 **/
@interface dooPayFormRecognizedField : NSObject

/** The receivers token. **/
@property (nonatomic, strong, readonly) dooPayFormToken *token;

/** The recognized text for the receivers token. **/
@property (nonatomic, copy, readonly) NSString *value;

@end





#pragma mark - dooPayFormPolygon

/** 
 Describes an ordered collection of geometric points in the images coordinate system.
 Used to express boxes and rectangles in non-perspective-corrected images.
 **/
@interface dooPayFormPolygon : NSObject

/** An UIBezierPath instance describing a closed path along the receivers points. **/
@property (nonatomic, strong, readonly) UIBezierPath *path;

/** The number of points the receiver holds. **/
@property (nonatomic, assign, readonly) NSUInteger pointCount;

/** Convenience initializer taking a C-style array of CGPoints and the number of points. **/
- (instancetype)initWithPoints:(CGPoint *)points count: (NSUInteger)pointCount;

/** Convenience initializer taking a NSArray of NSValue objects, e.g. [NSValue valueWithCGPoint:point]. **/
- (instancetype)initWithPointValues:(NSArray *)pointValues;

/** Returns the CGPoint at the given index. Does not perform bounds check. **/
- (CGPoint)pointAtIndex:(NSUInteger)index;

@end





#pragma mark - dooPayFormDetectedBox

/** Part of the detector result. Gathers a polygon and a token type. **/
@interface dooPayFormDetectedBox : NSObject

/** The token type of the detected text box. **/
@property (nonatomic, assign, readonly) dooPayFormTokenType type;

/** Polygon, holding the geometry of one detected text box in non-perspective-corrected images coordinate system. **/
@property (nonatomic, strong, readonly) dooPayFormPolygon *polygon;

@end





#pragma mark - dooPayFormResult
/** Common super class for the result classes of the detector and the recognizer. **/
@interface dooPayFormResult : NSObject

/** The size of the image the detector/recognizer has been run on. **/
@property (nonatomic, readonly) CGSize imageSize;

/** Helper method to convert a polygon from image coordinate system to unit coordinates ([0..1], [0..1]). **/
- (dooPayFormPolygon *)convertPolygonToUnitSpace:(dooPayFormPolygon *)polygon;

/** Helper method to convert a polygon from image coordinate system to a cameras preview layer coordinate system. **/
- (dooPayFormPolygon *)convertPolygon:(dooPayFormPolygon *)polygon
               toPreviewLayerSpace:(AVCaptureVideoPreviewLayer *)previewLayer;

@end





#pragma mark - dooPayFormDetectionResult

/** 
 Result class of dooPayFormScanners detector part. Describes wether the image contains a bank transfer form,
 and if so it also holds the bounding polygon of the form as well as the detected text boxes. 
 **/
@interface dooPayFormDetectionResult : dooPayFormResult

/** YES if a valid bank transfer form was found, NO otherwise. **/
@property (nonatomic, readonly) BOOL isValidPayForm;

/** The boundary polygon whithin the boxes have been detected. **/
@property (nonatomic, readonly) dooPayFormPolygon *polygon;

/** The detected text boxes. NSArray of dooPayFormDetectedBox objects. **/
@property (nonatomic, readonly) NSArray *detectedBoxes;

@end





#pragma mark - dooPayFormRecognitionResult

/** Result class of dooPayFormScanners recognizer part. Encapsulates the recognized text fields. **/
@interface dooPayFormRecognitionResult : dooPayFormResult

/** NSArray ofdooPayFormRecognizedField objects as the result of the recognizer. **/
@property (nonatomic, readonly) NSArray *recognizedFields;

@end





#pragma mark - dooPayFormScanner

/** 
 The main scanner class that performs detection and recognition on either UIImage or CMSampleBufferRef (from camera).
 Usually start with detection on a smaller image (video frame) and if detection was successful (isValidForm == YES)
 run recognition on either the same or a larger image (camera still shot). The larger the image
 the better the recognition results. Images are rotated accordingly to either the UIImage imageOrientation property
 or the given video orientation. 
 Detection and recognition are successful only if the rotated image has natural orientation.
  **/
@interface dooPayFormScanner : NSObject

/** 
 Detects whether an image contains a bank transfer form or not on the given UIImage.
 Orientation is taken from the image itself. Returns nil if image is empty or nil.
 **/
- (nullable dooPayFormDetectionResult *)detectOnImage:(UIImage *)image;

/** 
 Detects whether an image contains a bank transfer form or not on the given CMSampleBufferRef.
 Pass the current video connections videoOrientation here. Returns nil if image is empty or nil.
 **/
- (nullable dooPayFormDetectionResult *)detectInSampleBuffer:(CMSampleBufferRef)sampleBuffer
                                     orientation:(AVCaptureVideoOrientation)videoOrientation;

/** 
 Recognizes the bank transfer form fields in the given UIImage. Orientation is taken from the image itself.
 Returns nil if image is empty or nil.
 **/
- (nullable dooPayFormRecognitionResult *)recognizeFieldsOnImage:(UIImage *)image;


/** 
 Recognizes the bank transfer form fields in the given CMSampleBufferRef.
 Pass the current video connections videoOrientation here. Returns nil if image is empty or nil.
 **/
- (nullable dooPayFormRecognitionResult *)recognizeFieldsInSampleBuffer:(CMSampleBufferRef)sampleBuffer
                                                orientation:(AVCaptureVideoOrientation)videoOrientation;

@end

// SWIFT 1.2 NONNULL REGION: REMOVE IF NOT USING XCODE 6.3
NS_ASSUME_NONNULL_END

