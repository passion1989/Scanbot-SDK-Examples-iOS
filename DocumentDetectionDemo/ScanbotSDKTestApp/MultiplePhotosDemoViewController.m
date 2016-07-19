//
//  MultiplePhotosDemoViewController.m
//  ScanbotSDKTestApp
//
//  Created by Andrew Petrus on 07.06.16.
//  Copyright © 2016 doo GmbH. All rights reserved.
//

#import "MultiplePhotosDemoViewController.h"
#import "ScanbotSDKInclude.h"

@interface MultiplePhotosDemoViewController () <SBSDKCameraSessionDelegate>

@property (nonatomic, strong) SBSDKCameraSession *cameraSession;
@property (nonatomic, strong) SBSDKMultipleDocumentsDetector *detector;
@property (nonatomic, strong) SBSDKPolygonLayer *polygonLayer;

@end

@implementation MultiplePhotosDemoViewController

- (SBSDKMultipleDocumentsDetector *)detector {
    if (!_detector) {
        _detector = [SBSDKMultipleDocumentsDetector new];
    }
    return _detector;
}

- (SBSDKCameraSession *)cameraSession {
    if (!_cameraSession) {
        _cameraSession = [[SBSDKCameraSession alloc] initForFeature:FeatureCreditCardRecognition];
        _cameraSession.videoDelegate = self;
    }
    return _cameraSession;
}

- (SBSDKPolygonLayer *)polygonLayer {
    if (!_polygonLayer) {
        UIColor *color = [UIColor colorWithRed:0.0f green:0.5f blue:1.0f alpha:1.0f];
        _polygonLayer = [[SBSDKPolygonLayer alloc] initWithLineColor:color];
    }
    return _polygonLayer;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor blackColor];
    [self.view.layer addSublayer:self.cameraSession.previewLayer];
    [self.view.layer addSublayer:self.polygonLayer];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.cameraSession startSession];
}

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    self.cameraSession.previewLayer.frame = self.view.bounds;
    self.polygonLayer.frame = self.view.bounds;
}

#pragma mark - SBSDKCameraSessionDelegate methods

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    SBSDKDocumentsDetectorResult *result = [self.detector detectDocumentPolygonsOnSampleBuffer:sampleBuffer];
    dispatch_async(dispatch_get_main_queue(), ^{
        [self showResult:result];
    });
}

- (void)showResult:(SBSDKDocumentsDetectorResult *)result {
    self.polygonLayer.path = nil;
    if (result.polygons.count != 0) {
        UIBezierPath *bezierPath = [UIBezierPath bezierPath];
        for (SBSDKPolygon *polygon in result.polygons) {
            [bezierPath appendPath:[polygon bezierPathForPreviewLayer:self.cameraSession.previewLayer]];
        }
        self.polygonLayer.path = bezierPath.CGPath;
    }
}



- (void)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection {
    
    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
    
    AVCaptureVideoOrientation videoOrientation = AVCaptureVideoOrientationPortrait;
    switch (orientation) {
            
        case UIInterfaceOrientationPortrait:
            videoOrientation = AVCaptureVideoOrientationPortrait;
            break;
            
        case UIInterfaceOrientationPortraitUpsideDown:
            videoOrientation = AVCaptureVideoOrientationPortraitUpsideDown;
            break;
            
        case UIInterfaceOrientationLandscapeLeft:
            videoOrientation = AVCaptureVideoOrientationLandscapeLeft;
            break;
            
        case UIInterfaceOrientationLandscapeRight:
            videoOrientation = AVCaptureVideoOrientationLandscapeRight;
            
        default:
            break;
    }
    self.cameraSession.videoOrientation = videoOrientation;
}

@end
