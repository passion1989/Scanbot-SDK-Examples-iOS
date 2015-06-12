//
//  ImageViewController.m
//  DocumentDetectionDemo
//
//  Created by Sebastian Husche on 12.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import "ImageViewController.h"

@interface ImageViewController ()

@property (strong, nonatomic) IBOutlet UIImageView *imageView;

@end

@implementation ImageViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self updateImage];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:NO animated:YES];
}

- (void)setImage:(UIImage *)image {
    _image = image;
    [self updateImage];
}

- (void)updateImage {
    if (self.isViewLoaded) {
        self.imageView.image = self.image;
    }
}


@end
