//
//  AppDelegate.m
//  SFSocialFacebookExample
//
//  Created by Massaki on 1/3/12.
//  Copyright (c) 2012 I.ndigo. All rights reserved.
//

#import "AppDelegate.h"
#import "APICallViewController.h"
#import "SFSocialFacebook.h"

@implementation AppDelegate

@synthesize window = _window;

- (void)dealloc
{
    [_window release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSArray *permissions = [[NSArray alloc] initWithObjects:@"create_event", @"user_events", @"rsvp_event", @"publish_stream", nil];
    _socialFacebook = [SFSocialFacebook sharedInstanceWithAppId:@"YOUR_APP_ID" appSecret:@"YOUR_APP_SECRET" urlSchemeSuffix:nil andPermissions:permissions];
    [permissions release];
    
    UIViewController *rootController = [[APICallViewController alloc] initWithMenu:@"main"];
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:rootController];
    [rootController release];
    [navController setDelegate:self];
    
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    self.window.rootViewController = navController;
    [navController release];
    [self.window makeKeyAndVisible];
    return YES;
    
}

// Pre 4.2 support
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    return [_socialFacebook handleOpenURL:url];
}

// For 4.2+ support
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    return [_socialFacebook handleOpenURL:url];
}

#pragma mark - UINavigationControllerDelegate

- (void)navigationController:(UINavigationController *)navigationController didShowViewController:(UIViewController *)viewController animated:(BOOL)animated
{
    [navigationController setToolbarHidden:([viewController.toolbarItems count] == 0) animated:YES];
}

@end
