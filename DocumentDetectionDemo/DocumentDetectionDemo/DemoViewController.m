//
//  DemoViewController.m
//  PayFormScannerDemo
//
//  Created by Sebastian Husche on 08.06.15.
//  Copyright (c) 2015 doo GmbH. All rights reserved.
//

#import "DemoViewController.h"
#import "TextViewController.h"
#import "PDFViewController.h"

@interface DemoViewController ()
@property (strong, nonatomic) SBSDKImageStorage *imageStorage;
@property (strong, nonatomic) IBOutlet UIButton *actionsButton;
@property (strong, nonatomic) IBOutlet UIButton *cancelButton;
@property (strong, nonatomic) IBOutlet UIButton *clearButton;
@property (strong, nonatomic) IBOutlet UILabel *pageLabel;
@property (strong, nonatomic) SBSDKProgress *currentProgress;
@property (strong, nonatomic) IBOutlet UIProgressView *progressView;
@property (strong, nonatomic) IBOutlet UILabel *progressLabel;
@property (strong, nonatomic) SBSDKOpticalTextRecognizer *textRecognizer;
@property (strong, nonatomic) SBSDKScannerViewController *scannerViewController;
@property (strong, nonatomic) UIAlertController *actionController;
@property (assign, nonatomic) BOOL viewAppeared;
@end

@implementation DemoViewController

/**
 Subclass overrides
 **/
#pragma mark - Subclass overrides

- (void)viewDidLoad {
    [super viewDidLoad];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appTerminates:)
                                                 name:UIApplicationWillTerminateNotification
                                               object:nil];
    
    self.imageStorage = [[SBSDKImageStorage alloc] init];
    self.scannerViewController
    = [[SBSDKScannerViewController alloc] initWithParentViewController:self
                                                          imageStorage:nil];
    self.scannerViewController.delegate = self;
    self.scannerViewController.imageScale = 1.0f;
    
    [self updateUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES animated:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    self.viewAppeared = NO;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    self.viewAppeared = YES;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)appTerminates:(NSNotification *)notification {
    self.imageStorage = nil;
}

- (BOOL)shouldAutorotate {
    return NO;
}

- (NSUInteger)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}

- (UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleLightContent;
}




/** 
 SBSDKScannerViewControllerDelegate 
 **/
#pragma mark - SBSDKScannerViewControllerDelegate

- (BOOL)scannerControllerShouldAnalyseVideoFrame:(SBSDKScannerViewController *)controller {
    return self.viewAppeared && self.presentedViewController == nil && self.currentProgress == nil;
}

- (void)scannerController:(SBSDKScannerViewController *)controller
  didCaptureDocumentImage:(UIImage *)documentImage
{
    [self.imageStorage addImage:documentImage];
    [self updateUI];
}

- (void)scannerController:(SBSDKScannerViewController *)controller didCaptureImage:(UIImage *)image {
    
}

- (void)scannerController:(SBSDKScannerViewController *)controller
         didDetectPolygon:(SBSDKPolygon *)polygon
               withStatus:(SBSDKDocumentDetectionStatus)status
{
    
}

- (UIView *)viewForDetectionStatus:(SBSDKDocumentDetectionStatus)status
              forScannerController:(SBSDKScannerViewController *)controller
{
    return nil;
}

- (UIColor *)polygonColorForDetectionStatus:(SBSDKDocumentDetectionStatus)status
                       forScannerController:(SBSDKScannerViewController *)controller
{
    if (status == SBSDKDocumentDetectionStatusOK) {
        return [UIColor greenColor];
    }
    return [UIColor redColor];
}




/**
 UI updating
 **/
#pragma mark - UI updating

- (void)setCurrentProgress:(SBSDKProgress *)currentProgress {
    if (_currentProgress != currentProgress) {
        _currentProgress.updateHandler = nil;
        _currentProgress = currentProgress;
        __weak DemoViewController *weakSelf = self;
        _currentProgress.updateHandler = ^void(SBSDKProgress *progress) {
            [weakSelf updateProgress];
        };
    }
    [self updateProgress];
    [self updateUI];
}

- (void)updateUI {
    self.pageLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)self.imageStorage.imageCount];
    BOOL hasImages = self.imageStorage.imageCount > 0;
    BOOL operationRunning = self.currentProgress != nil;
    self.actionsButton.hidden = operationRunning || !hasImages;
    self.progressView.hidden = !operationRunning;
    self.progressLabel.hidden = !operationRunning;
    self.cancelButton.hidden = !operationRunning;
    self.clearButton.hidden = !hasImages;
    self.scannerViewController.cameraControlsHidden = operationRunning;
}

- (void)updateProgress {
    self.progressView.progress = self.currentProgress.fractionCompleted;
    self.progressLabel.text = [self.currentProgress.localizedDescription stringByAppendingFormat:@"\n%@",
                               self.currentProgress.localizedAdditionalDescription];
}




/**
 User initiated actions
 **/
#pragma mark - User initiated actions

- (IBAction)clearImageStorage:(id)sender {
    self.imageStorage = [[SBSDKImageStorage alloc] init];
    [self updateUI];
}

- (IBAction)cancelOperation:(id)sender {
    if (!self.currentProgress.isCancelled) {
        [self.currentProgress cancel];
        [self updateUI];
    }
}

- (IBAction)openActionsMenu:(id)sender {
    if (!self.actionController) {
        self.actionController = [[UIAlertController alloc] init];
        self.actionController.title = @"Scanbot SDK - Choose an action";
        __weak DemoViewController *weakSelf = self;
        
        [self.actionController addAction:[UIAlertAction actionWithTitle:@"PDF - No OCR"
                                                                  style:UIAlertActionStyleDefault
                                                                handler:^(UIAlertAction *action)
                                          {
                                              [weakSelf createPDF:action];
                                              [weakSelf dismissViewControllerAnimated:YES completion:nil];
                                          }]];

        [self.actionController addAction:[UIAlertAction actionWithTitle:@"PDF - With OCR"
                                                                  style:UIAlertActionStyleDefault
                                                                handler:^(UIAlertAction *action)
                                          {
                                              [weakSelf createOCRPDF:action];
                                              [weakSelf dismissViewControllerAnimated:YES completion:nil];
                                          }]];

        [self.actionController addAction:[UIAlertAction actionWithTitle:@"OCR text - Image storage"
                                                                  style:UIAlertActionStyleDefault
                                                                handler:^(UIAlertAction *action)
                                          {
                                              [weakSelf performOCR:action];
                                              [weakSelf dismissViewControllerAnimated:YES completion:nil];
                                          }]];

        [self.actionController addAction:[UIAlertAction actionWithTitle:@"OCR text - Single image"
                                                                  style:UIAlertActionStyleDefault
                                                                handler:^(UIAlertAction *action)
                                          {
                                              [weakSelf performSingleImageOCR:action];
                                              [weakSelf dismissViewControllerAnimated:YES completion:nil];
                                          }]];

        
        [self.actionController addAction:[UIAlertAction actionWithTitle:@"Page analysis - Single image"
                                                                  style:UIAlertActionStyleDefault
                                                                handler:^(UIAlertAction *action)
                                          {
                                              [weakSelf performPageAnalysis:action];
                                              [weakSelf dismissViewControllerAnimated:YES completion:nil];
                                          }]];

        [self.actionController addAction:[UIAlertAction actionWithTitle:@"Cancel"
                                                                  style:UIAlertActionStyleCancel
                                                                handler:^(UIAlertAction *action)
                                          {
                                              [weakSelf dismissViewControllerAnimated:YES completion:nil];
                                          }]];
    }
    
    [self presentViewController:self.actionController animated:YES completion:nil];
}

- (IBAction)createPDF:(id)sender {
    if (self.currentProgress) {
        return;
    }
    
    if (self.imageStorage.imageCount == 0) {
        return;
    }
    
    NSString *filename = @"ScanbotSDK_PDF.pdf";
    NSURL *pdfURL = [SBSDKImageStorage applicationDocumentsFolderURL];
    pdfURL = [pdfURL URLByAppendingPathComponent:filename];
    
    self.currentProgress = [SBSDKPDFRenderer renderImageStorage:self.imageStorage
                                               copyImageStorage:YES
                                                       indexSet:nil
                                                   withPageSize:SBSDKPDFRendererPageSizeAuto
                                                         output:pdfURL
                                              completionHandler:^(BOOL finished, NSError *error, NSDictionary *resultInfo)
    {
        if (finished && error == nil) {
            NSURL *outputURL = resultInfo[SBSDKResultInfoDestinationFileURLKey];
            PDFViewController *pdfController = [PDFViewController pdfControllerWithURL:outputURL];
            [self.navigationController pushViewController:pdfController animated:YES];
        } else {
            NSLog(@"%@", error);
        }
        self.currentProgress = nil;
        [self updateUI];
    }];
    
    [self updateUI];
}

- (IBAction)performOCR:(id)sender {
    if (self.currentProgress) {
        return;
    }
    
    if (self.imageStorage.imageCount == 0) {
        return;
    }
    
    self.currentProgress =
    [SBSDKOpticalTextRecognizer recognizeText:self.imageStorage
                             copyImageStorage:YES
                                     indexSet:nil
                               languageString:@"en+de"
                                 pdfOutputURL:nil
                                   completion:^(BOOL finished, NSError *error, NSDictionary *resultInfo)
     {
         if (error == nil && finished) {
             SBSDKOCRResult *result = resultInfo[SBSDKResultInfoOCRResultsKey];
             TextViewController *textController = [TextViewController textControllerWithText:result.recognizedText];
             [self.navigationController pushViewController:textController animated:YES];
         } else {
             NSLog(@"%@", error);
         }
         self.currentProgress = nil;
         [self updateUI];
     }];
    
    [self updateUI];
}

- (IBAction)createOCRPDF:(id)sender {
    if (self.currentProgress) {
        return;
    }
    
    if (self.imageStorage.imageCount == 0) {
        return;
    }
    
    NSString *filename = @"ScanbotSDK_PDF_OCR.pdf";
    NSURL *pdfURL = [SBSDKImageStorage applicationDocumentsFolderURL];
    pdfURL = [pdfURL URLByAppendingPathComponent:filename];
    
    
    self.currentProgress =
    [SBSDKOpticalTextRecognizer recognizeText:self.imageStorage
                             copyImageStorage:YES
                                     indexSet:nil
                               languageString:@"en+de"
                                 pdfOutputURL:pdfURL
                                   completion:^(BOOL finished, NSError *error, NSDictionary *resultInfo)
     {
         if (error == nil && finished) {
             PDFViewController *pdfController = [PDFViewController pdfControllerWithURL:pdfURL];
             [self.navigationController pushViewController:pdfController animated:YES];
         }
         if (error) {
             NSLog(@"%@", error);
         }
         self.currentProgress = nil;
         [self updateUI];
     }];
    
    [self updateUI];
}

- (IBAction)performSingleImageOCR:(id)sender {
    if (self.currentProgress) {
        return;
    }
    
    if (self.imageStorage.imageCount == 0) {
        return;
    }
    
    NSURL *imageURL = [self.imageStorage imageURLAtIndex:0];
    
    self.currentProgress =
    [SBSDKOpticalTextRecognizer recognizeText:imageURL
                                    rectangle:CGRectMake(0, 0, 1, 1)
                               languageString:@"en+de"
                                   completion:^(BOOL finished, NSError *error, NSDictionary *resultInfo)
    {
        if (error == nil && finished) {
            SBSDKOCRResult *result = resultInfo[SBSDKResultInfoOCRResultsKey];
            TextViewController *textController = [TextViewController textControllerWithText:result.recognizedText];
            [self.navigationController pushViewController:textController animated:YES];
        } else {
            NSLog(@"%@", error);
        }
        self.currentProgress = nil;
        [self updateUI];
    }];
    [self updateUI];
}

- (IBAction)performPageAnalysis:(id)sender {
    if (self.currentProgress) {
        return;
    }
    
    if (self.imageStorage.imageCount == 0) {
        return;
    }
    
    NSURL *imageURL = [self.imageStorage imageURLAtIndex:0];
    
    self.currentProgress =
    [SBSDKOpticalTextRecognizer analyseImagePageLayout:imageURL
                                            completion:^(BOOL finished, NSError *error, NSDictionary *resultInfo)
    {
        if (error == nil && finished) {
            SBSDKPageAnalyzerResult *result = resultInfo[SBSDKResultInfoPageAnalyzerResultsKey];
            UIAlertController *resultsController
            = [UIAlertController alertControllerWithTitle:@"Page layout analysis"
                                                  message:result.description
                                           preferredStyle:UIAlertControllerStyleAlert];
            
            [resultsController addAction:[UIAlertAction actionWithTitle:@"OK"
                                                                  style:UIAlertActionStyleDefault
                                                                handler:^(UIAlertAction *action)
            {
                [self dismissViewControllerAnimated:YES completion:nil];
            }]];
            
            [self presentViewController:resultsController animated:YES completion:nil];
        } else {
            NSLog(@"%@", error);
        }
        self.currentProgress = nil;
        [self updateUI];
     }];
    [self updateUI];
}


@end
