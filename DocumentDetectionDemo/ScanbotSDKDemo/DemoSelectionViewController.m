//
//  DemoSelectionViewController.m
//  ScanbotSDKDemo
//
//  Created by Sebastian Husche on 17.02.16.
//  Copyright © 2016 doo GmbH. All rights reserved.
//

#import "DemoSelectionViewController.h"

@interface DemoSelectionViewController ()
@property (strong, nonatomic) IBOutlet UIButton *documentDemoButton;
@property (strong, nonatomic) IBOutlet UIButton *payformDemoButton;
@property (strong, nonatomic) IBOutlet UIButton *creditCardDemoButton;
@property (strong, nonatomic) IBOutlet UIButton *chequeDemoButton;
@end

@implementation DemoSelectionViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.navigationItem.title = self.title;
    [self applyButtonAppearance:self.documentDemoButton];
    [self applyButtonAppearance:self.payformDemoButton];
    [self applyButtonAppearance:self.creditCardDemoButton];
    [self applyButtonAppearance:self.chequeDemoButton];
}

- (void)applyButtonAppearance:(UIButton *)button {
    button.layer.cornerRadius = 8.0f;
    button.layer.borderColor = [button titleColorForState:UIControlStateNormal].CGColor;
    button.layer.borderWidth = 1.0f;
    button.contentEdgeInsets = UIEdgeInsetsMake(0, 20, 0, 20);
}

- (NSString *)title {
    return @"ScanbotSDK Sample App";
}

@end
