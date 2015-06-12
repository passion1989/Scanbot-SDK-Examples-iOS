//
//  dooPolygonEdge.h
//  doo-ios
//
//  Created by Sebastian Husche on 02.12.13.
//  Copyright (c) 2013 doo GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "dooGeometryUtilities.h"

typedef NS_ENUM(NSUInteger, PolygonEdgeOrientation) {
    PolygonEdgeOrientationHorizontal = 0,
    PolygonEdgeOrientationVertical = 1,
    PolygonEdgeOrientationUndefined = 2
};

/** 
 @class dooPolygonEdge
 @description Small helper class that encapsulates an edge of a polygon and provides geometric helper methods.
 */
@interface dooPolygonEdge : NSObject <NSCopying>

/** The start point of the edge. */
@property(nonatomic, assign) CGPoint p1;

/** The end point of the edge. */
@property(nonatomic, assign) CGPoint p2;

/** The center of the edge. **/
@property(nonatomic, assign) CGPoint center;


/** 
 @description Designated initializer.
 @param p1 The start point of the edge.
 @param p2 The end point of the edge.
 @return Newly created instance of dooPolygonEdge.
 */
- (instancetype)initWithPoint:(CGPoint)p1 andPoint:(CGPoint)p2;

/** 
 @return The length of the receiver. In other words the distance between p1 and p2.
 */
- (CGFloat)length;

/**
 @return The axis-aligned bounding box of the receiver.
 */
- (CGRect)boundingBox;

- (PolygonEdgeOrientation)orientation;


@end
