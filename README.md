# Scanbot SDK Documentation {#mainpage}

## 1. Introduction and requirements

Scanbot SDK for iOS is a simple to use high level API, providing a collection of classes and functions 
for scanning and processing documents from your mobile device's camera or other image sources like your photo library.

Boost your iOS app with the powerful and convenient document scanning and processing features that also drive the #1
scanning app in the iOS app store: Scanbot Pro.

Scanbot SDK consists of a bunch of modules, each individually licensable or avalaible in license packages.

Currently the following modules are available
- Document detection in digital images
- User interface for guided, automatic document scanning using the document detection module
- Image processing for rotating, cropping, filtering and perspective correction, optimized for the needs of document 
scanning
- PDF creation, merge a collection of processed or unprocessed document images and write them into a PDF document with 
one page per image
- Optical character recognition, recognize text in document images and create searchable PDF documents with 
selectable text
- Payform recognition, detect and recognize SEPA payforms on images and extract the important data fields via OCR
- Beta software for invoice, cheque and credit card recognition

Scanbot SDK supports iOS 8 and higher.

If you need further information or are interested in licensing Scanbot SDK please contact us: sdk@scanbot.io

\n
## 2. Installation

Scanbot SDK is delivered as an embedded framework, containing all iOS supported 32 and 64 bit simulator and device 
architectures, bitcode and crash symbols. 

For invoice and credit card recognition additional data is required in your project. 
You can include this data by adding the optional data bundles to your apps bundle. 

Scanbot SDK also contains a little script that prepares the framework and your app when archiving your app for App Store
submission. It strips the unnecessary architectures from the frameworks binary, code signs the framework and adds 
the crash symbols (dSYM) file to your apps archive.

Installing the Scanbot SDK embedded framework is really easy. 

[For detailed instructions click here](@ref install_framework)
\n

- 1. Copy ScanbotSDK folder into your apps project folder
- 2. Open your app project in Xcode
- 3. Select your apps build target and add an embedded framework
- 4. Select 'Add Other...'
- 5. Locate and select ScanbotSDK.framework
- 6. Check 'Copy items if needed' and 'Create groups' and hit 'Finish' 
- 7. Add a runscript build phase that runs the strip-script and set the dSYM file as input file to this runscript phase
- 8. Optional: Add the data bundles for invoice and credit card recognition and/or the additional OCR languages to your project
- 9. Import the frameworks umbrella header in your source code files:

\code{.m}
#import <ScanbotSDK/ScanbotSDK.h>
\endcode

or 

\code{.m}
@import ScanbotSDK;
\endcode

You are now ready to use Scanbot SDK in your code. 
\n 
\n
[For detailed instructions click here](@ref install_framework)

\n
\n

### 3. License

In order to run Scanbot SDK functionality within your app you must purchase and install a Scanbot SDK license.

Not installing a license will let you test all Scanbot SDK features for a trial period of 1 minute. After the trial
period is over your app will be terminated immediately.
Installing an invalid license will also terminate your application immediately. 
Installing an expired but valid license will not terminate your app immediately but when using Scanbot SDK API.
If the license expires during the apps life cycle Scanbot SDK will continue to work normally until the next start
of the application.

If an expiration date is given for the license the license will expire at that day at 11:59:59 PM o'clock.
The timezone of the license is UTC. Any logging of the SDK converts the UTC expiration date to your local timezone.

The license also defines which modules you are allowed to use. 
The usage of unlicensed modules will log an error to the console and terminate the app.

Each license is valid only to your apps bundle identifier. So no other app can highjack your license and reuse it.
Any modification of the license will render it invalid. Make sure that you store your license in a safe 
location.

You can purchase Scanbot SDK licenses here: <https://scanbot.io/sdk.html>. 

In order to activate the license in code use the method `-setLicense:` method in the ScanbotSDK class. 
Execute this code as early as possible during your apps runtime, but at least before using any Scanbot SDK 
functionality, e.g. in your application delegates `-application:didFinishLaunchingWithOptions:` method.

If your license has expired any invocation of the Scanbot SDK API will terminate your app. To prevent this you should 
check for license expiration during runtime by calling [ScanbotSDK isLicenseValid]. 
If this method returns NO, you should disable Scanbot-SDK-using features or UI.


Example code for using the license string
\code{.m}
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // Override point for customization after application launch.
  [ScanbotSDK setLicense:
  @"P73ZaxJ3VG08E+0sUqcbf+BPmKoCDVmWZthAS/FmYsh2I"
  "DT9AJbIKbBRfaDSzjZed4+py7suMYDq++TuzkqVc9CYwGb"
  "3VL68OhsOEpUAJ/GOdVfZnSTFvDo1JQvq54nY2+EChviwM"
  "CkBXCDO7YSMB/Rp42dlu7x3a/EFbor+PmlBpZhfdwveyWX"
  "5MasHiMzgNicdb33hVgyWgcv74NpxL1XyZkcvn7wQrzgzq"
  "JtJ63YUI6SPmTZtJB2M+0IMYeQXj1HltWX5mcohEIFPme7"
  "hU0BZB3S476QMceeL4bPCZjgu1vjL7kxKurIqmJGT6juGu"
  "kFQFJWPoccmgtJnHxI0Cg==\nU2NhbmJvdFNESwpuZXQuZ"
  "G9vLlBheUZvcm1TY2FubmVyRGVtbwowCjEyOA==\n"];
  
  return YES;
}
\endcode

Example code for checking the license status
\code{.m}
if ([ScanbotSDK isLicenseValid]) {
    //Making your call into ScanbotSDK API is safe now.
    ...
}
\endcode



\n
\n

### 4. Logging

Scanbot SDK comes with its own console logging. 
By default the logging is turned on. 
You can turn off logging of Scanbot SDK:
\code{.m}
[ScanbotSDK setLoggingEnabled:NO];
\endcode

This will also silence information about the Scanbot SDK license.

\n
\n

## 5. Scanbot SDK Modules in Detail

\n
### 5.1 Document Detection

See SBSDKDocumentDetector.

SBSDKDocumentDetector uses digital image processing algorithms to find rectangular, document like, polygons in a 
digital image.

\code{.m}
- (SBSDKDocumentDetectorResult *)detectDocumentPolygonOnImage:(UIImage *)image
                                             visibleImageRect:(CGRect)visibleRect
                                             smoothingEnabled:(BOOL)smooth
                                   useLiveDetectionParameters:(BOOL)liveDetection
\endcode

As input an UIImage object or a CMSampleBufferRef is accepted. Typically the camera API in Apples AVFoundation framework 
returns CMSampleBufferRef objects. This way you can easily detect document polygons on a live camera video stream or 
still image shot. Images from the photo library are usually converted to UIImage objects before being passed to 
the detector.

The visibleRect parameter lets you limit the detection area on the image. If you pass CGRectZero or an a rectangle
with zero width or height the whole image is used for detection. The rectangle must be provided in unit coordinate 
system { 0.0f, 0.0f } - { 1.0f, 1.0f }, where { 0.0f, 0.0f } is the top left and { 1.0f, 1.0f } the bottom right corner
of the image. The detector ignores edges that are outside the visibleRect.

The smooth parameter is typically used for realtime detection using the same detector instance all the time. 
When set to YES, consecutive detected document polygons within a certain timeframe are cumulated into a 
single dampened polygon. It prevents jumping polygons in situations where the recognized edges changes from video 
frame to video frame. If you use smoothing you should also observe the devices motion and clear the consecutive 
polygon buffer if significant motion was detected. This is done by calling the detectors -resetSmoothingData method.

The liveDetection flag you tpyically set to YES when you need the fastest detection possible for e.g. realtime detection.
The results are a little bit less accurate than when set to NO but the performance significantly rises.
With liveDetection enabled an iPhone 6 can detect up to 20 video frames per second, depending on the video frame resolution.
It is recommended to turn off liveDetection if you want to detect only once on a static image.

The result contains an SBSDKPolygon (or nil if nothing was found) and 
an [SBSDKDocumentDetectionStatus](@ref SBSDKDocumentDetectionStatus.h) enum member.
For user guidance during live detection the status can be used. It tells you whether the detected polygon is too small, 
the perspective is insufficient or the orientation is not optimal. If there was no polygon detected the status 
might contain information about why there was no polygon detected (too noisy background, too dark).

For manual realtime detection with the device's camera also take a look at the following classes:
- SBSDKCameraSession
- SBSDKPolygonLayer

Example code for document detection on a video frame
\code{.m}
- (void)captureOutput:(AVCaptureOutput *)captureOutput
didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
       fromConnection:(AVCaptureConnection *)connection {

    // Create an SBSDKDocumentDetector.
    // Note: Usually you store it in a property, for demo purposes we create a new one for each frame.
    SBSDKDocumentDetector *detector = [[SBSDKDocumentDetector alloc] init];

    // Detect a documents outlines on the sample buffer
    SBSDKDocumentDetectorResult *result = [detector detectDocumentPolygonOnSampleBuffer:sampleBuffer
                                                                       visibleImageRect:CGRectZero
                                                                       smoothingEnabled:YES
                                                             useLiveDetectionParameters:YES];

    // If we have an acceptable polygon...
    if (result.status == SBSDKDocumentDetectionStatusOK && result.polygon != nil) {
        // We take a still shot from the camera.
        // Create an UIImage from the still shot sample buffer.
        // Warp the image into the polygon.
        [self.cameraSession captureStillImageWithCompletionHandler:^(CMSampleBufferRef sampleBuffer, NSError *error) {
            UIImage *image = [UIImage sbsdk_imageFromSampleBuffer:sampleBuffer]; 
            image = [image sbsdk_imageWarpedByPolygon:result.polygon imageScale:1.0];
        }];
    }
}
\endcode


\n
### 5.2 User Interface for guided, automatic Document Scanning

See SBSDKScannerViewController.

For your convenience Scanbot SDK comes with a view controller subclass that handles all the camera and 
detection implementation details for you. 
Additionally it provides UI for Scanbots document scanning guidance as well as the functionality and UI for manual 
and automatic shutter release.

The controllers delegate can customize the appearance and behavior of the guidance UI. 
Further SBSDKScannerViewController gives its delegate control over how and when frames are analyzed and, most important, 
it delivers the scanned (and perspective corrected, cropped document) images to its delegate.

See SBSDKScannerViewControllerDelegate for customization of UI and behavior.

Example code

\code{.m}
#import "SBSDKScanbotSDK.h"

@interface DemoViewController : UIViewController
@end

@interface DemoViewController() <SBSDKScannerViewControllerDelegate>
@property (strong, nonatomic) SBSDKImageStorage *imageStorage;
@property (strong, nonatomic) SBSDKScannerViewController *scannerViewController;
@property (assign, nonatomic) BOOL viewAppeared;
@end

@implementation DemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Create an image storage to save the captured document images to
    self.imageStorage = [[SBSDKImageStorage alloc] init];

    // Create the SBSDKScannerViewController.
    // We want it to be embedded into self.
    // As we do not want automatic image storage we pass nil here for the image storage.
    self.scannerViewController 
    = [[SBSDKScannerViewController alloc] initWithParentViewController:self imageStorage:nil];
    
    // Set the delegate to self.
    self.scannerViewController.delegate = self;

    // We want unscaled images in full 5 or 8 MPixel size.
    self.scannerViewController.imageScale = 1.0f;
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    self.viewAppeared = NO;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    self.viewAppeared = YES;
}

- (BOOL)shouldAutorotate {
    // No autorotations.
    return NO;
}

- (NSUInteger)supportedInterfaceOrientations {
    // Only portrait.
    return UIInterfaceOrientationMaskPortrait;
}

- (UIStatusBarStyle)preferredStatusBarStyle {
    // White statusbar.
    return UIStatusBarStyleLightContent;
}

#pragma mark - SBSDKScannerViewControllerDelegate

- (BOOL)scannerControllerShouldAnalyseVideoFrame:(SBSDKScannerViewController *)controller {
    // We want to only process video frames when self is visible on screen and front most view controller
    return self.viewAppeared && self.presentedViewController == nil;
}

- (void)scannerController:(SBSDKScannerViewController *)controller
  didCaptureDocumentImage:(UIImage *)documentImage {
    // Here we get the perspective corrected and cropped document image after the shutter was (auto)released.
    // We store it into our image storage.
    [self.imageStorage addImage:documentImage];
}

- (void)scannerController:(SBSDKScannerViewController *)controller didCaptureImage:(CMSampleBufferRef)sampleBuffer {
    // Here we get the full image from the camera. We could run another manual detection here or use the latest
    // detected polygon from the video stream to process the image with.
}

- (void)scannerController:(SBSDKScannerViewController *)controller
         didDetectPolygon:(SBSDKPolygon *)polygon
               withStatus:(SBSDKDocumentDetectionStatus)status {
    // Everytime the document detector finishes detection it calls this delegate method.

}

- (UIView *)scannerController:(SBSDKScannerViewController *)controller 
       viewForDetectionStatus:(SBSDKDocumentDetectionStatus)status {

    // Here we can return a custom view that we want to use to visualize the latest detection status.
    // We return nil for now to use the standard label.
    return nil;
}

- (UIColor *)scannerController:(SBSDKScannerViewController *)controller 
polygonColorForDetectionStatus:(SBSDKDocumentDetectionStatus)status {

    // If the detector has found an acceptable polygon we show it with green color
    if (status == SBSDKDocumentDetectionStatusOK) {
        return [UIColor greenColor];
    }
    // Otherwise red colored.
    return [UIColor redColor];
}

@end
\endcode

See SBSDKScannerViewControllerDelegate for details.


\n
### 5.3 Image Processing

See SBSDKImageProcessor

Digital image processing is a core part of Scanbot SDK. Basically there are three operations on images:
- Rotation
- Image filtering
- Image warping (perspective correction and cropping) into a 4-sided polygons shape

All of these image operations can be called either synchronously in any thread or queue or asynchronously on a special 
serial image processing queue. When working with large images it is highly recommended to make use of the asynchronous 
API as here no parallel processing of images is possible. Processing large images concurrently easily causes memory 
warnings and crashes.

Synchronous API can be found in the [UIImageSBSDK](@ref UIImageSBSDK.h) class extension.

The asynchronous API is implemented as static class SBSDKImageProcessor.
Additionally to the three standard operations SBSDKImageProcessor provides a method to apply custom image processing by 
specifying an SBSDKImageProcessingHandler block. Execution is also dispatched to the image processing queue.
The operations completion handlers are called in main thread.

Each call into the asynchronous API returns a SBSDKProgress object to you. This NSProgress subclass can be used to
observe the progress of the operation but also it can be used to cancel the operation via the `-(void)cancel` method.


Example code for custom asynchronous image filter
\code{.m}
// Specify the file URL for the input image
NSURL *inputImageURL = ...;

// Specify the file URL the output image is written to. Set to nil, if you dont want to save the output image
NSURL *outputImageURL = ...;

// Create the image processing block
SBSDKImageProcessingHandler processingHandler = ^UIImage *(UIImage *sourceImage, NSError **outError) {
    // Apply a color filter to the input image,
    UIImage *filteredImage = [sourceImage imageFilteredBy:SBSDKImageFilterTypeColor];

    // and return the filtered image.
    return filteredImage;
};

// Call the asynchronous image processing API. The returned progress object can be used to to cancel the operation.
// Once the operation has been completed extract the image from resultInfo dictionary and do whatever you want with the image.
SBSDKProgress *progress
= [SBSDKImageProcessor customFilterImage:inputImageURL
                         processingBlock:processingHandler
                          outputImageURL:outputImageURL
                              completion:^(BOOL finished, NSError *error, NSDictionary *resultInfo) {
                                  UIImage *outputImage = resultInfo[SBSDKResultInfoDestinationImageKey];
                              }];
\endcode


Example code for detecting and applying a polygon to an image
\code{.m} 

// Specify the input image URL.
NSURL *inputImageURL = ...;

// Specify the output image URL. Set to nil, if you dont want to save the output image.
NSURL *outputImageURL = ...;

// Create a document detector.
SBSDKDocumentDetector *detector = [[SBSDKDocumentDetector alloc] init];

// Let the document detector run on our input image.
SBSDKDocumentDetectorResult *result
= [detector detectDocumentPolygonOnImage:[UIImage imageWithContentsOfFile:inputImageURL.path]
                        visibleImageRect:CGRectZero
                        smoothingEnabled:NO
              useLiveDetectionParameters:NO];

// Check the result.
if (result.status == SBSDKDocumentDetectionStatusOK && result.polygon != nil) {

    // If the result is an acceptable polygon, we warp the image into the polygon asynchronously.
    // When warping is done we check the result and on success we pick up the output image.
    // Then do whatever you want with the warped image.
    [SBSDKImageProcessor warpImage:inputImageURL
                           polygon:result.polygon
                    outputImageURL:outputImageURL
                        completion:^(BOOL finished, NSError *error, NSDictionary *resultInfo) {
                            if (finished && !error) {
                                UIImage *outputImage = resultInfo[SBSDKResultInfoDestinationImageKey];
                            }
                        }];
    } else {
        // No acceptable polygon found.
    }
}
\endcode

\n
### 5.4 PDF Creation

See SBSDKPDFRenderer.

The SBSDKPDFRenderer static class takes an image storage (SBSDKImageStorage) and renders them into a PDF.
For each image a page is generated. The generated pages have sizes that correspond to DIN A4, US Letter or Custom.
As the images are embedded unscaled the resolution for each page depends on its image.
When rendering into a DIN A4 or US Letter format the orientation of the page; landscape or portrait; is derived from
the images aspect ratio. 

See [SBSDKPDFRendererPageSize](@ref SBSDKPDFRendererPageSize) for further information.

The operations completion handler is called in main thread.

Example code for creating a standard PDF from an image storage
\code{.m}
// Create or use an exisiting image storage.
SBSDKImageStorage *imageStorage = [SBSDKImageStorage temporaryStorageWithImages:...];

// Define the indices of the images in the image storage you want to render to the PDF, e.g. the first 3.
// To include all images you can simply pass nil for the indexSet. The indexSet internally is validated.
// You dont need to take care if all indices are valid.
NSIndexSet *indexSet = [NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, 2)];

// Specify the file URL where the PDF will be saved to. Nil here makes no sense.
NSURL *outputPDFURL = ...;

// Enqueue the operation and store the SBSDKProgress to watch the progress or cancel the operation.
// After completion the PDF is stored at the URL specified in outputPDFURL.
// You can also extract the image store and the PDF URL from the resultInfo.

SBSDKProgress *progress = 
[SBSDKPDFRenderer renderImageStorage:imageStorage
                    copyImageStorage:YES
                            indexSet:indexSet
                        withPageSize:SBSDKPDFRendererPageSizeAutoLocale
                              output:outputPDFURL
                   completionHandler:^(BOOL finished, NSError *error, NSDictionary *resultInfo) {
                       if (finished && error != nil) {
                           SBSDKImageStorage *completedImageStore = resultInfo[SBSDKResultInfoImageStorageKey];
                           NSURL *completedPDFURL = resultInfo[SBSDKResultInfoDestinationFileURLKey];
                       }
                   }];
\endcode

\n
### 5.5 Optical Character Recognition

See SBSDKOpticalTextRecognizer.

SBSDKOpticalTextRecognizer takes one or more images and performs various text related operations on each of the images:
- Page layout analysis
- Text recognizing
- Creation of searchable PDF documents with selectable text

The page layout analysis returns information about page orientation, an angle the image should be rotated to deskew it,
the text writing direction or the text line order.

The text recognizing operations take either a collection of images (SBSDKImageStorage) and optionally create a PDF
of it, or a single image. The single image operation also can take a rectangle describing which area of the image 
should be text-recognized. The results found in the completion handlers resultsDictionary contain information 
about the found text, where the text was found (boundingBox) and what kind of text it is (word, line, paragraph).

All SBSDKOpticalTextRecognizer operations run in a separate serial queue.

The operations completion handlers are called in main thread.

Example code for performing a page layout analysis.
\code{.m}
// The file URL of the image we want to analyse.
NSURL *imageURL = ...;

// Start the page layout analysis and store the returned SBSDKProgress object. This object can be used to cancel
// the operation or to observe the progress. See NSProgress.
// In completion check if we finished without error and extract the analyzer result from the resultInfo dictionary.
// Now we can work with the result.
SBSDKProgress *progress =
[SBSDKOpticalTextRecognizer analyseImagePageLayout:imageURL
                                        completion:^(BOOL finished, NSError *error, NSDictionary *resultInfo) {
    if (finished && !error) {

        SBSDKPageAnalyzerResult *result = resultInfo[SBSDKResultInfoPageAnalyzerResultsKey];

        if (result.orientation != SBSDKPageOrientationUp) {
        
        }
    }
}];
\endcode

Example code for performing text recognition in an image.
\code{.m}
// The file URL of the image we want to analyse.
NSURL *imageURL = nil;

// Enqueue the text recognition operation.
// We limit detection to the center area of the image leaving margins of 25% on each side.
// Only use english language to be recognized.
// The returned SBSDKProgress object can be used to cancel the operation or observer the progress.
// Upon completion we extract the result from the resultsDictionary and log the whole recognized text.
// The we enumerate all words and log them to the console together with their confidence values and bounding boxes.
SBSDKProgress *progress =
[SBSDKOpticalTextRecognizer recognizeText:imageURL
                                rectangle:CGRectMake(0.25f, 0.25f, 0.5f, 0.5f)
                           languageString:@"eng"
                               completion:^(BOOL finished, NSError *error, NSDictionary *resultInfo) {
    
    SBSDKOCRResult *result = resultInfo[SBSDKResultInfoOCRResultsKey];
    NSLog(@"Recognized Text: %@", result.recognizedText);
    for (SBSDKOCRResultBlock *word in result.words) {
        NSLog(@"Word: %@, Confidence: %0.0f, Box: %@",
            word.text,
            word.confidenceValue,
            NSStringFromCGRect(word.boundingBox));
    }
}];
\endcode



\n
### 5.6 Payform Recognition

See SBSDKPayFormScanner.

The SBSDKPayFormScanner class provides functionality to detect and recognize SEPA payforms. It extracts relevant 
information fields by performing optical text recognition on certain areas of the image, 
e.g. IBAN, BIC, receiver, amount of money and reference. 

This module needs the german language package. See SBSDKOpticalTextRecognizer for language addition.

For performance reasons the scanner is divided into two parts: detection and recognition. 
The detection only tests whether the scanned image contains a payform or not. The recognizer performs the 
text extraction and fills the fields.

The common usage is to configure the iPhones camera for full HD video capturing and run the detection part on each 
incoming frame synchronously in the video capture queue. When the detector returns a positive result the 
recognizing part runs on the same full HD frame in the same video capture queue and returns the recognizers result.

Example code on how to detect and recognize payforms in the video delegate 
\code{.m}
- (void)captureOutput:(AVCaptureOutput *)captureOutput
didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
       fromConnection:(AVCaptureConnection *)connection {

    // Create an SBSDKPayFormScanner.
    // Note: Usually you store it in a property, for demo purposes we create a new one for each frame.
    SBSDKPayFormScanner *scanner = [[SBSDKPayFormScanner alloc] init];

    // Get the video orientation from the camera session (of the SBSDKScannerViewController).
    AVCaptureVideoOrientation videoOrientation = self.scannerViewController.cameraSession.videoOrientation;

    // Detect bank transfer form in the sample buffer.
    SBSDKPayFormDetectionResult *detectionResult = [scanner detectInSampleBuffer:sampleBuffer 
                                                                     orientation:videoOrientation];

    // If we have detected a valid payform
    if (detectionResult.isValidPayForm) {

        // We perform the recognition step.
        SBSDKPayFormRecognitionResult *recognitionResult = [scanner recognizeFieldsInSampleBuffer:sampleBuffer
                                                                                      orientation:videoOrientation];

        dispatch_async(dispatch_get_main_queue(), ^{
            // Present the recognition results alert on main thread.
        });
    }
}
\endcode
\n

## 6. Used third-party libraries and their licenses  

ScanbotSDK uses the following third-party libraries:

### OpenCV 3.1

Copyright © 2014, Itseez. All rights reserved.
This library is distributed under the terms of the following license: http://opencv.org/license.html.
\n
\n
### G8Tesseract

Copyright @ 2014 Daniele Galiotto. https://github.com/gali8/Tesseract-OCR-iOS
This library is distributed under the terms of a MIT License (https://github.com/gali8/Tesseract-OCR-iOS/blob/master/LICENSE.md).
\n
\n
### Tesseract 3.04 modified by doo GmbH

Tesseract, maintained by Google (http://code.google.com/p/tesseract-ocr/),
is distributed under the Apache 2.0 license (see http://www.apache.org/licenses/LICENSE-2.0).
\n
\n
### Leptonica 1.72

Copyright @ 2001-2015, Leptonica, (http://leptonica.org),
is distributed under a Creative Commons Attribution 3.0 United States License (see http://creativecommons.org/licenses/by/3.0/us/).
\n
\n
### OpenSSL 1.0.2d

Copyright @ 1998-2011 The OpenSSL Project. All rights reserved. (https://www.openssl.org)
This library is distributed under the terms of the following license: https://github.com/openssl/openssl/blob/master/LICENSE
\n
\n


## 7. Release history
##### Changelog version 1.0.6:

###### SBSDKScannerViewController
- Fixed a bug that prevented displaying the detection statuses for poor light and noise
- Added properties acceptedSizeScore and acceptedAngleScore, allowing you to alter the acceptance parameters for automatic shutter release (e.g. more perspective distortion or smaller document size)



##### Changelog version 1.0.7:

###### SBSDKScannerViewController
- Fixed wrong orientation of original image when capturing a document image



##### Changelog version 1.0.8:

###### SBSDKScannerViewController
- Added new method -(BOOL)captureStillImage to allow manual capturing using the delegate interface



##### Changelog version 1.0.9:

###### SBSDKScannerViewController
- Added new delegate method (void)scannerControllerDidChangeDeviceOrientation:to:transform:



##### Changelog version 1.0.10:

###### SBSDKScannerViewController
- Significantly improved peak memory usage when capturing images (~ 50%)
- Added new delegate method - (BOOL)scannerController:shouldRotateInterfaceForDeviceOrientation:transform:(CGAffineTransform)transform



##### Changelog version 1.0.11:

###### SBSDKScannerViewController
- Fixed an orientation issue on iPad



##### Changelog version 1.0.12:

- Rebuilt with Xcode 7 final
- Updated some documentation



##### Changelog version 1.0.13:

- Improved accuracy of automatic document detection
- Introduced new colored document image filter



##### Changelog version 1.0.14:

- New color filter now working correctly
- Fixed a bug in the binarization filter



##### Changelog version 1.0.15:

- Added new delegate method  -(NSString *)scannerController:(SBSDKScannerViewController *)controller localizedTextForDetectionStatus:(SBSDKDocumentDetectionStatus)status to help you localizing the detection status strings



##### Changelog version 1.1.1:

- Beta: Added brand new credit card recognizer: SBSDKCreditCardRecognizer
- Refactored Demo app: now contains Document Detection, Payform Detection and Credit Card detection
- Fixed some bugs in SBSDKScannerViewController, e.g. automatic crop after manual snap
- Added imageMode flag to SBSDKScannerViewController, can be set to grayscale mode to capture all images in grayscale mode for better memory footprint
- Added API to SBSDImageProcessor to pass UIImage objects directly instead of NSURLs



##### Changelog version 1.1.2:

- Improved credit card recognizer (SBSDKCreditCardRecognizer)



##### Changelog version 1.1.4:

- Added cheque recognizer (SBSDKChequeRecognizer)



##### Changelog version 1.2.0:

- Improved all detectors accuracy
- Added SBSDImageMetadata and SBSDKImageMetadataProcessor to extract EXIF data etc. from image
- Added SBSDKLensCameraProperties which can be passed to polygon based warping functions to improve the aspect ratio
of the cropped image and let it be very close to the original documents aspect ratio 
- SBSDKLensCameraProperties can be extracted from SBSDKImageMetadata
- Added 3 new filters: SBSDKImageFilterTypePhoto, SBSDKImageFilterTypePhotoBW1, SBSDKImageFilterTypePhotoBW2
- The photo filter is useful to correct strong color tints, the 2 other new filters create different color-to-gray mappings 
- Added SBSDKMultipleDocumentsDetector (Beta) to detect multiple photos or documents on an image
- Minor fixes and optimizations



##### Changelog version 1.2.1:

- Fixed crash in sample app by adding `NSCameraUsageDescription` and `NSPhotoLibraryUsageDescription`.



##### Changelog version 1.3.0:

- Removed static libraries
- Changed distribution model to single embeddable framework containing all architectures and bitcode



##### Changelog version 1.4.0:

- Added SBSDKCropViewController, a Scanbot-like UI for manual cropping of images, including magnetic snapping of
edges to found contours
\n
\n
