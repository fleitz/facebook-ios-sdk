//
//  SFSocialFacebook.h
//  POCShareComponent
//
//  Created by Bruno Toshio Sugano on 2/16/11.
//  Copyright 2011 I.ndigo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FBConnect.h"
#import "SFSimplePost.h"
#import "SFUser.h"
#import "SFSimpleEvent.h"
#import "SFSimpleEventInvite.h"

#define SF_FEEDS @"feed"

@class SFFacebookRequest;

typedef void (^SFDidNotLoginBlock)(BOOL cancelled);
typedef void (^SFFeedsBlock)(NSArray *posts, NSString *nextPageURL);
typedef void (^SFFailureBlock)(NSError *error);
typedef void (^SFBasicBlock)(void);


@protocol SFPostDatasource;

@class SFURLRequest;

@interface SFSocialFacebook : NSObject <FBSessionDelegate, UIAlertViewDelegate> {
    
    Facebook            *_facebook;
    NSArray             *_permissions;
    NSString            *_appId;
    NSString            *_appSecret;
    NSString            *_appAccessToken;
    
    SFURLRequest        *_urlRequest;
    
    SFBasicBlock        _loginBlock;
    SFDidNotLoginBlock  _notLoginBlock;
    SFBasicBlock        _logoutBlock;
    
    
	NSString *facebookUserId;
    int areaId;
	
	NSString *nextPageFriends;
	NSString *nextPageInvited;
	
    NSString *shingleServerPath;
	
	SEL pendingAction;
	NSMutableDictionary *pendingActionParams;
	
    BOOL auxFeedsLastPost;
}

+ (SFSocialFacebook *)sharedInstance;
+ (SFSocialFacebook *)sharedInstanceWithAppId:(NSString *)appId appSecret:(NSString *)appSecret urlSchemeSuffix:(NSString *)urlSchemeSuffix andPermissions:(NSArray *)permissions;


@property (nonatomic, assign) id<SFPostDatasource> delegate;

@property (nonatomic, retain) NSString *facebookUserId;
@property (nonatomic, retain) NSString *loggedUserId;

- (BOOL)handleOpenURL:(NSURL *)url;
- (BOOL)isSessionValid:(BOOL)needsLogin;

- (void)getAppAccessTokenWithSuccess:(void (^)(NSString *accessToken))successBlock failure:(SFFailureBlock)failureBlock;

- (void)loginWithSuccess:(SFBasicBlock)successBlock failure:(SFDidNotLoginBlock)failureBlock;
- (void)logoutWithSuccess:(SFBasicBlock)successsBlock;
- (SFFacebookRequest *)uninstallApp:(SFBasicBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

- (SFFacebookRequest *)listProfileFeed:(NSString *)profileId pageSize:(int)postsPerPage needsLogin:(BOOL)needsLogin success:(SFFeedsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;
- (SFFacebookRequest *)listProfileFeedNextPage:(NSString *)nextPageURL success:(SFFeedsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

- (void)shareFeed:(SFSimplePost *)post;
- (void)shareFeed:(SFSimplePost *)post WithComment: (NSString *)comment;


//- (id) initWithAppId: (NSString *) applicationId
//andAuthorizationSingleton: (SFAuthorization *) authorizationSingleton
//         andDelegate:(id)_delegate;
//
//- (id) initWithAppId: (NSString *) applicationId
//           andAreaId: (int) area_Id
//andAuthorizationSingleton: (SFAuthorization *) authorizationSingleton
//andShingleServerPath: (NSString *) shinglePath
//         andDelegate:(id)_delegate;
//- (void) setAppId: (NSString *) applicationId
//        andAreaId: (int) area_Id
//andAuthorizationSingleton: (SFAuthorization *) authorizationSingleton
//andShingleServerPath: (NSString *) shinglePath
//      andDelegate:(id)_delegate;


- (void) listAreaFeedsWithPostsPerPage: (int)postsPerPage;

- (void) handleLike: (NSString *) postId;
//- (void) handleComment: (NSString *) comment InPost: (NSString *) postId;
//- (void) handleUnlike: (NSString *) postId;
- (void) fillUser: (SFUser *)user WithId: (NSString *)userId Target:(id)target AndSelector:(SEL)didFinish;
- (void) fillUser: (SFUser *)user Target:(id)target AndSelector:(SEL)didFinish;

- (void) createEvent: (SFSimpleEvent *)event;
- (void) inviteFriendsToEvent: (SFSimpleEventInvite *)invite;
- (void) performPendingAction;
- (void) listFriendsOfLoggedUser: (int) pageSize;
- (void) listNextPageUser;
- (void) getEvent: (NSString*) eventId;
- (void) getInvitedUsersForEvent: (NSString *) eventId PageSize: (int) pageSize;
- (void) listNextPageInvited;
- (void) eventMarkAttending: (NSString *)eventId;
- (void) getNumLikesFromPage: (NSString *)pageId;
- (void) getAccessTokenWithClientId:(NSString*)client_id andClientSecret:(NSString*)client_secret;

- (NSDate*) parseToDate:(NSString *) string;

@end


@protocol SFPostDatasource<NSObject>

@optional

- (void) socialFacebook: (SFSocialFacebook *)facebook ReceivedListOfFriends: (NSArray *)friends;
- (void) socialFacebook: (SFSocialFacebook *)facebook DidSharePost: (NSString *)postId;
- (void) socialFacebook: (SFSocialFacebook *)facebook DidCreateEventWithId: (NSString *)eventId;
- (void) socialFacebookDidSendInvitationToEvent: (SFSocialFacebook *)facebook;
- (void) socialFacebookDidAttendingEvent: (SFSocialFacebook *)facebook;
- (void) socialFacebookDidLike: (SFSocialFacebook *)facebook;
- (void) socialFacebook: (SFSocialFacebook *)facebook DidReceiveEvent: (SFSimpleEvent *)event;
- (void) socialFacebook: (SFSocialFacebook *)facebook DidReceivedInvitedUsersList: (NSArray *)invitedUsers;
- (void) socialFacebook: (SFSocialFacebook *)facebook DidReceiveNumberOfLikes: (NSString *)likes;
- (void) socialFacebookDidLogin;
- (void) socialFacebookDidCancelLogin;
- (void) socialFacebookDidReceiveConfiguration;
- (void) socialFacebookDidFailReceivingConfiguration;
@end