//
//  AppDelegate.m
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "AppDelegate.h"
#include "Canvas.h"
#include "Console.h"
#include "GameObject.h"
#include "Device.h"

using namespace DE;

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    
    Device::GetInstance();
    DE::Canvas* canvas = new DE::Canvas();
    canvas->setVisible(true);
    
    GameObject* lay = new GameObject();
    canvas->setWorldObject(lay);
    
    
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

-(IBAction)on_console_click:(id)sender
{   
    DE::Console::GetInstance()->setVisible(!DE::Console::GetInstance()->getVisible());
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
        DE::Device::GetInstance()->initEnginePaths();
        [panel close];
    }
}

@end
