//
//  DemoNavigationViewController.m
//  PayFormScannerDemo
//
//  Created by Sebastian Husche on 24.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import "DemoNavigationViewController.h"

@interface DemoNavigationViewController ()

@end

@implementation DemoNavigationViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (BOOL)shouldAutorotate {
    return self.topViewController.shouldAutorotate;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return self.topViewController.supportedInterfaceOrientations;
}


@end
