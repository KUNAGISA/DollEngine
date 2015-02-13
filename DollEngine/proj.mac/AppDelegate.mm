//
//  AppDelegate.m
//  DollEngine
//
//  Created by DollStudio on 14/12/6.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import "AppDelegate.h"
//#include "Scripts.h"
//#include "Storages.h"
//#include "System.h"
//#include "PaintEngine.h"
#import "WindowDelegate.h"

@interface AppDelegate ()
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application

    setlocale(LC_ALL, "zh_CN.UTF-8");
//    Storages::GetInstance()->addAutoPath(System::GetInstance()->getExePath());
//    Storages::GetInstance()->setResourcePath(System::GetInstance()->getAppDataPath());
//    Storages::GetInstance()->setDocumentPath(System::GetInstance()->getPersonalPath());
//    Storages::GetInstance()->setCachePath(get_cache_path());
//    System::GetInstance()->addFont(L"文泉驿微米黑.ttc");
    
    [[WindowDelegate getInstance]showConsole];
    
//    Scripts::GetInstance()->execStorage("startup.tjs");
//    
//    System::GetInstance()->setTransChanged(true);
//    System::GetInstance()->setOrderChanged(true);
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (IBAction) onDebugConsole:(id)sender
{
    
}

- (IBAction) onDebugRelaunch:(id)sender
{
    NSMutableArray* args = [NSMutableArray array];
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:args forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = [[NSError alloc] init];
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration error:&error];
    [[NSApplication sharedApplication] terminate:self];
}

- (IBAction) onSetRootPath:(id)sender
{
    NSString* rootPath = [[NSUserDefaults standardUserDefaults] stringForKey:@"ROOT_PATH"];
    NSOpenPanel* panel = [NSOpenPanel openPanel];
    [panel setTitle:@"Select engine root path"];
    panel.allowsMultipleSelection = NO;
    panel.canChooseDirectories = YES;
    panel.canChooseFiles = NO;
    panel.nameFieldLabel = rootPath;
    if ([panel runModal] == NSFileHandlingPanelOKButton)
    {
        NSString* path = [[panel.URLs objectAtIndex:0] path];
        [[NSUserDefaults standardUserDefaults]setValue:path forKey:@"ROOT_PATH"];
        [[NSUserDefaults standardUserDefaults]synchronize];
        [self onDebugRelaunch:nil];
    }
}

@end
