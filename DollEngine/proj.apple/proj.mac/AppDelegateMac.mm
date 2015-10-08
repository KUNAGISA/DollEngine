//
//  AppDelegate.m
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "AppDelegateMac.h"
#include "System.h"
#include "ScriptEngine.h"
#include "Window.h"
#include "TjsConsole.h"

using namespace DE;

@interface AppDelegateMac ()

@end

@implementation AppDelegateMac

enum TEST{
    test1 =0,
    test2,
    test3,
    test4,
    test5
};

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    new ScriptEngine();
    DE::TjsConsole::GetInstance()->setVisible(true);
    DESystem->startup();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

-(IBAction)onConsoleClick:(id)sender
{
    bool v = DE::TjsConsole::GetInstance()->getVisible();
    DE::TjsConsole::GetInstance()->setVisible(!v);
}

-(void)applicationProtectedDataWillBecomeAvailable {
    
}

-(IBAction)onRelaunchClick:(id)sender
{
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:@{} forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error;
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration error:&error];
    [[NSApplication sharedApplication] terminate:self];
}

-(IBAction)openDocument:(id)sender
{
    NSOpenPanel* panel = [NSOpenPanel openPanel];
    [panel setTitle:@"选择 data 目录"];
    panel.allowsMultipleSelection = NO;
    panel.canChooseDirectories = YES;
    panel.canChooseFiles = NO;
    if ([panel runModal] == NSFileHandlingPanelOKButton)
    {
        NSString* path = [[panel.URLs objectAtIndex:0] path];
        [[NSUserDefaults standardUserDefaults]setValue:path forKey:@"DATA_PATH"];
        [[NSUserDefaults standardUserDefaults]synchronize];
        [panel close];
        [self onRelaunchClick:sender];
    }
}

@end
