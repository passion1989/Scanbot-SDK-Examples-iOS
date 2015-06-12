//
//  dooPolygon.h
//  doo-ios
//
//  Created by Sebastian Husche on 28.11.13.
//  Copyright (c) 2013 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "dooDocumentDetectionStatus.h"
#import "dooPolygonEdge.h"

/** 
 @class dooPolygon
 @description This class represents a 4-gon, a polygon with 4 edges. The polygons points are stored in
 a normalized unit coordinate system from {0, 0} to {1, 1}. 
 To convert to absolute coordinates use the methods that take a size and return absolute values.
 An absolute space can be any 2-dimensional space with a size, e.g. an image.
 */
@interface dooPolygon : NSObject <NSCopying>

@property(nonatomic, assign)dooDocumentDetectionStatus detectionStatus;
@property(nonatomic, assign) double widthPercentage;
@property(nonatomic, assign) double heightPercentage;

/**
 @description One of the desinated initializer methods.
 @param a The first point of the polygon in unit coordinates.
 @param b The second point of the polygon in unit coordinates.
 @param c The third point of the polygon in unit coordinates.
 @param d The fourth point of the polygon in unit coordinates.
 @return A new instance of dooPolygon class.
 */
- (instancetype)initWithNormalizedPointA:(CGPoint)a pointB:(CGPoint)b pointC:(CGPoint)c pointD:(CGPoint)d;


- (instancetype)initWithNormalizedRect:(CGRect)rect;

/**
 @description One of the desinated initializer methods.
 @param a The first point of the polygon in absolute coordinates.
 @param b The second point of the polygon in absolute coordinates.
 @param c The third point of the polygon in absolute coordinates.
 @param d The fourth point of the polygon in absolute coordinates.
 @param size The size to use to convert the points to unit coordinates.
 @return A new instance of dooPolygon class.
 */
- (instancetype)initWithAbsolutePointA:(CGPoint)a pointB:(CGPoint)b pointC:(CGPoint)c pointD:(CGPoint)d forSize:(CGSize)size;

/** 
 @description Compares the receiver to another instance of dooPolygon.
 @param The polygon instance the receiver is compared to.
 @return YES, if the points of polygon are equal to the points of the receiver, NO otherwise.
 */
- (BOOL)isEqualToPolygon:(dooPolygon *)polygon;


- (BOOL)isSimilarToPolygon:(dooPolygon *)polygon;

/**
 @description Calculates the standard deviation in the corresponding points of the receiver and the given dooPolygon.
 @param The polygon instance the receiver is compared to.
 @return Standard deviation.
 */
- (double)standardDeviationToPolygon:(dooPolygon *)polygon;

/**
 @description Clips the receiver the unit space {0, 0} - {1, 1}.
 */
- (void)normalize;

/** 
 @description Orders the receivers points in clockwise order. The first point is the point right next to 12 o'clock.
 This method uses the atan2 operator to sort the points clockwise.
 */
- (void)sortClockwise;

/** 
 @description Creates a UIBezierPath instance of the receiver for drawing purposes.
 @param size The size to use to convert the normalized points of the receiver to absolute coordinates.
 @return An UIBezierPath instance representing the polygon converted to absolute space.
 */
- (UIBezierPath *)bezierPathForSize:(CGSize)size;

/**
 @description Creates a UIBezierPath instance of the receiver for drawing purposes.
 @param previewLayer The preview layer the path is going to be presented on.
 @return An UIBezierPath instance representing the polygon.
 */
- (UIBezierPath *)bezierPathForPreviewLayer:(AVCaptureVideoPreviewLayer *)previewLayer;

/**
 @description Helper method to transform a normalized point to an absolute coordinate system with given size.
 @param point The absolute point to convert into normalized space.
 @param size The size of the absolute coordinate system.
 @return The normalized point.
 */
+ (CGPoint)normalizedPointFromAbsolutePoint:(CGPoint)point withSize:(CGSize)size;

/**
 @description Helper method to transform an absolute point to the normalized unit coordinate system with given size.
 @param point The normalized point to convert into absolute space.
 @param size The size of the absolute coordinate system.
 @return The converted point.
 */
+ (CGPoint)absolutePointFromNormalizedPoint:(CGPoint)point withSize:(CGSize)size;

/**
 @description Returns the normalized point at the given index.
 @param index The index of the point in the receiver. Must be in range {0-3}.
 @return The normalized point.
 */
- (CGPoint)normalizedPointWithIndex:(NSUInteger)index;

/**
 @description Returns the absolute point at the given index.
 @param index The index of the point in the receiver. Must be in range {0-3}.
 @param size The size of the absolute coordinate system to transform the point to.
 @return The converted point.
 */
- (CGPoint)absolutePointWithIndex:(NSUInteger)index forSize:(CGSize)size;

/**
 @description Returns the normalized edge at the given index. 
 The edge at index n is built from points at indices n and (n+1) % 4.
 @param index The index of the edge in the receiver. Must be in range {0-3}.
 @return The normalized edge.
 */
- (dooPolygonEdge *)normalizedEdgeWithIndex:(NSUInteger)index;

/**
 @description Returns the absolute edge at the given index.
 The edge at index n is built from points at indices n and (n+1) % 4.
 @param index The index of the edge in the receiver. Must be in range {0-3}.
 @param size The size of the absolute coordinate system to transform the edge to.
 @return The absolute edge.
 */
- (dooPolygonEdge *)absoluteEdgeWithIndex:(NSUInteger)index forSize:(CGSize)size;

/** 
 @description Sets the receivers point at the given index to the value of point.
 @param point The normalized point.
 @param index The index of the point the set within the receiver in range {0-3}.
 */
- (void)setNormalizedPoint:(CGPoint)point forIndex:(NSUInteger)index;

/**
 @description Sets the receivers point at the given index to the normalized value of point.
 @param point The absolute point.
 @param size The size of the absolute coordinate system.
 @param index The index of the point the set within the receiver in range {0-3}.
 */
- (void)setAbsolutePoint:(CGPoint)point withSize:(CGSize)size forIndex:(NSUInteger)index;

/**
 @description Rotates the points of the receiver 90 degrees clockwise, 
 transforming it from one absolute space to another.
 @param oldSize The size of the absolute coordinate system before rotating it.
 @param newSize The size of the absolute coordinate system after rotating it.
 */
- (void)rotate90CWWithOldSize:(CGSize)oldSize newSize:(CGSize)newSize;

/**
 @description Rotates the points of the receiver 90 degrees counterclockwise,
 transforming it from one absolute space to another.
 @param oldSize The size of the absolute coordinate system before rotating it.
 @param newSize The size of the absolute coordinate system after rotating it.
 */
- (void)rotate90CCWWithOldSize:(CGSize)oldSize newSize:(CGSize)newSize;

/**
 @description Rotates the points of the receiver 180 degrees,
 transforming it from one absolute space to another.
 @param oldSize The size of the absolute coordinate system before rotating it.
 @param newSize The size of the absolute coordinate system after rotating it.
 */
- (void)rotate180WithOldSize:(CGSize)oldSize newSize:(CGSize)newSize;

- (CGRect)boundingBoxWithSize:(CGSize)size;

- (CGPoint)center;

- (void)calculatePercentageForSize:(CGSize)size;

@end
