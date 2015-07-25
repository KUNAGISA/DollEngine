//
//  AppDelegate.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegateMac : NSObject <NSApplicationDelegate>

-(IBAction)onConsoleClick:(id)sender;
-(IBAction)onRelaunchClick:(id)sender;
-(IBAction)openDocument:(id)sender;

@end

