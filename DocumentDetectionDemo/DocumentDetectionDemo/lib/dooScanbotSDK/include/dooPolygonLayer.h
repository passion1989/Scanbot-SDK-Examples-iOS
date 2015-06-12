//
//  dooPolygonLayer.h
//  Scanbot SDK
//
//  Created by Sebastian Husche on 23.04.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

/** 
 @class dooPolygonLayer
 @description A CAShapeLayer subclass that is used to draw bezier paths with fluid animation. 
 The paths stroke color can be customized.
 **/
@interface dooPolygonLayer : CAShapeLayer

/** 
 @description The color to draw the paths lines. 
 **/
@property (nonatomic, strong) UIColor *lineColor;

/**
 @description Designated initializer.
 @param lineColor The initial color for the path drawing color.
 **/
- (instancetype)initWithLineColor:(UIColor *)lineColor;

@end
