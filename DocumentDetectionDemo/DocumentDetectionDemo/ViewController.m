//
//  ViewController.m
//  DocumentDetectionDemo
//
//  Created by Sebastian Husche on 12.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import "ViewController.h"
#import "ImageViewController.h"

@implementation ViewController

- (UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleLightContent;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    // We create our dooDocumentScannerViewController and pass self as parentViewController.
    dooDocumentScannerViewController *scannerViewController
    = [[dooDocumentScannerViewController alloc] initWithParentViewController:self];

    // We also set the scanner controllers delegate to self as we want to handle and customize the scanner.
    scannerViewController.delegate = self;
    
    // Lets hide navigation bar here. We are the navigation stacks root controller. So we dont need the bar.
    [self.navigationController setNavigationBarHidden:YES animated:NO];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    // Make sure that we hide the navigation bar again.
    [self.navigationController setNavigationBarHidden:YES animated:YES];
}

/** The dooDocumentScannerViewController delegate methods **/

- (void)scannerController:(dooDocumentScannerViewController *)controller
  didCaptureDocumentImage:(UIImage *)documentImage {
    
    // We captured a documents image, lets push a controller that shows the image.
    if (documentImage != nil) {
        
        ImageViewController *imageController
        = [self.storyboard instantiateViewControllerWithIdentifier:@"imageViewController"];
        
        imageController.image = documentImage;
        
        [self.navigationController pushViewController:imageController animated:YES];
    }
}

- (UIColor *)polygonColorForDetectionStatus:(dooDocumentDetectionStatus)status
                       forScannerController:(dooDocumentScannerViewController *)controller
{
    // We found a good document structure with nice angles and good size, so we draw the polygon in green.
    if (status == dooDocumentDetectionStatusOK) {
        return [UIColor greenColor];
    } else {
        // Nothing found or bad document structure found, lets draw polygon in red.
        return [UIColor redColor];
    }
}

/**
- (void)scannerController:(dooDocumentScannerViewController *)controller didCaptureImage:(UIImage *)image {
    
}
**/

/**
- (void)scannerController:(dooDocumentScannerViewController *)controller
         didDetectPolygon:(dooPolygon *)polygon
               withStatus:(dooDocumentDetectionStatus)status
{
    
}
**/

/**
- (void)scannerController:(dooDocumentScannerViewController *)controller didFailCapturingImage:(NSError *)error {
    
}
**/

/**
- (UIView *)viewForDetectionStatus:(dooDocumentDetectionStatus)status
              forScannerController:(dooDocumentScannerViewController *)controller
{
    if (status == dooDocumentDetectionStatusError_NothingDetected) {
        return [UIView new];
    }
    return nil;
    
}
 **/

@end
