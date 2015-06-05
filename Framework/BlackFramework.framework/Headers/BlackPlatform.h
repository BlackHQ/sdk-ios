//
//  Black.h
//  Black
//
//  Created by Bosko Petreski on 5/28/14.
//  Copyright (c) 2014 Bosko Petreski. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol BlackPlatformDelegate <NSObject>

@required
/*!
 @brief required Protocol is called when call is started
 */
-(void)blackBridgeCallStarted;

/*!
 @brief required Protocol is called when call is ended
 */
-(void)blackBridgeCallEnded;

/*!
 @brief required Protocol is called when timeout call
 */
-(void)blackBridgeCallTimeout;

/*!
 @brief required Protocol is called when get some error
 @param  pErrors Is error returned in JSON format
 */
-(void)blackBridgeError:(NSDictionary *)pErrors;

/*!
 @brief required Protocol is called when call is received
 @param  pData Is data sended from caller side
 */
-(void)blackBridgeCallReceived:(NSDictionary *)pData;

/*!
 @brief optional Protocol is called when get some error
 @param  pInformation Is information returned
 */
-(void)blackBridgeInformation:(NSString *)pInformation;

@optional

/*!
 @brief optional Protocol is called when call is on hold
 */
-(void)blackBridgeCallOnHold;

/*!
 @brief optional Protocol is called when call is unholded
 */
-(void)blackBridgeCallOnUnHold;

/*!
 @brief optional Protocol is called when call notice silent
 */
-(void)blackBridgeCallSilent;

/*!
 @brief optional Protocol is called when call is accepted
 */
-(void)blackBridgeCallAccepted;

/*!
 @brief optional Protocol is called when call is rejected
 */
-(void)blackBridgeCallRejected;

/*!
 @brief "EXPERIMENTAL DONT USE IT" Protocol is called when video data is received
 @param  pDataVideo Is data of video, and should be presented in UIImageView
 @code
 -(void)blackBridgeVideo:(NSData *)pDataVideo{
    preview.image = [UIImage imageWithData:pDataVideo];
 }
 @endcode
 */
-(void)blackBridgeVideo:(NSData *)pDataVideo;

@end

@interface BlackPlatform : NSObject

/*!
 @brief It uses to register delegates to UIViewController where you want to implement protocol
 @param  delegate Should be UIViewController
 @code
[[BlackPlatform sharedBridge] setDelegate:self];
 @endcode
 */
@property (nonatomic, assign) id <BlackPlatformDelegate> delegate;

/*!
 @brief Returns the singleton app instance.
 @return The app instance is created in the UIApplicationMain function.
 @code
 BlackPlatform *platform = [BlackPlatform sharedBridge];
 @endcode
 */
+(BlackPlatform *)sharedBridge;

/*!
 @brief It uses to register application
 @param  pKey API Key from dashboard.
 @code 
 [[BlackPlatform sharedBridge] blackAuthorization:@"API_KEY_HERE"];
 @endcode
 */
-(void)blackAuthorization:(NSString *)pKey;

/*!
 @brief It uses to call someone
 @param  pCallerID Is device ID from that user you want to call.
 @param  pData This is optional data, and is used to send some small JSON data to recipient call
 @code
 NSString *callID = @"10";
 NSDictionary *dictData = @{@"first_name":@"Bosko",@"last_name":@"Petreski"};
 [[BlackPlatform sharedBridge] call:callID withData:dictData];
 @endcode
 */
-(void)call:(NSString *)pCallerID withData:(NSDictionary *)pData;

/*!
 @brief It uses to answer call
 @code
 [[BlackPlatform sharedBridge] answerCall];
 @endcode
 */
-(void)answerCall;

/*!
 @brief It uses to reject call
 @code
 [[BlackPlatform sharedBridge] rejectCall];
 @endcode
 */
-(void)rejectCall;

/*!
 @brief It uses to cancel call
 @code
 [[BlackPlatform sharedBridge] cancelCall];
 @endcode
 */
-(void)cancelCall;

/*!
 @brief It uses to end call
 @code
 [[BlackPlatform sharedBridge] endCall];
 @endcode
 */
-(void)endCall;

/*!
 @brief It uses to hold call
 @code
 [[BlackPlatform sharedBridge] holdCall];
 @endcode
 */
-(void)holdCall;

/*!
 @brief It uses to unhold call
 @code
 [[BlackPlatform sharedBridge] unHoldCall];
 @endcode
 */
-(void)unHoldCall;

/*!
 @brief It uses to control background stuff on platform
 @code
 [[BlackPlatform sharedBridge] enterBackground];
 @endcode
 */
-(void)enterBackground;

/*!
 @brief It uses to handle push notifications, this should be added in AppDelegate.m class
 @param  userInfo Is passing from didReceiveRemoteNotification in handleNotifications method.
 @code
 -(void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo{
 [[BlackPlatform sharedBridge] handleNotifications:userInfo];
 }
 @endcode
 */
-(void)handleNotifications:(NSDictionary *)userInfo;

/*!
 @brief It uses to handle push notifications, this should be added in AppDelegate.m class
 @param  launchOptions Is passing from didFinishLaunchingWithOptions in handleOnStartNotifications method.
 @code
 [[BlackPlatform sharedBridge] handleOnStartNotifications:launchOptions];
 @endcode
 */
-(void)handleOnStartNotifications:(NSDictionary *)launchOptions;

/*!
 @brief It uses to register device to platform, this should be added in AppDelegate.m class
 @param  deviceToken is NSData passed object from didRegisterForRemoteNotificationsWithDeviceToken
 @return NSString *device_id This is registered device id on platform
 @return NSString *message This is error message returned from platform
 @code
 [[BlackPlatform sharedBridge] registerNotificationService:deviceToken success:^(NSString *device_id) {
    NSLog(@"This is your device id: %@",device_id);
    } failed:^(NSString *message) {
    NSLog(@"failed to register device ID: %@",message);
 }];
 @endcode
 */
-(void)registerNotificationService:(NSData *)deviceToken success:(void(^)(NSString *device_id))pSuccess failed:(void(^)(NSString *message))pFailed;

/*!
 @brief "EXPERIMENTAL DONT USE IT" It uses to deactivate video call
 @param  pViewController Is UIViewController where you want to show video call
 @code
 [[BlackPlatform sharedBridge] activateVideo:self];
 @endcode
 */
 -(void)activateVideo:(UIViewController *)pViewController;

/*!
 @brief "EXPERIMENTAL DONT USE IT" It uses to deactivate video call
 @code
 [[BlackPlatform sharedBridge] deactivateVideo];
 @endcode
 */
 -(void)deactivateVideo;


@end
