//
//  AppDelegate.m
//  Krkr_GL
//
//  Created by DollStudio on 14-7-29.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import "AppDelegate.h"
#include "CanvasManager.h"
#include "Window.h"
#include "System.h"
#include "Storages.h"
#include "Object.h"
#include "Canvas.h"
#include "Functions.h"
#include "ncbind.hpp"
#include "KAGParser.h"
#include "MouseHandler.h"
#include "AsyncTrigger.h"

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    System::GetInstance()->initialize(640, 960);
    
    CGRect rect = [[UIScreen mainScreen] bounds];
    window = [[UIWindow alloc] initWithFrame: rect];
    
    viewController = [[ViewController alloc] initWithNibName:nil bundle:nil];
    [window setRootViewController:viewController];
    [window makeKeyAndVisible];
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    DM("App UnActive");
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    DM("App Enter Background");
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    DM("App Enter Foreground");
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    DM("App Active");
    CanvasManager::GetInstance()->setTransChanged(true);
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    DM("App Terminate");
}

@end
