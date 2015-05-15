//
//  AppDelegate.m
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"
#include "Canvas.h"
#include "Console.h"
#include "GameObject.h"
#include "Device.h"
#include "Painter.h"
#include "Label.h"

using namespace DE;

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    Device::GetInstance()->initEnginePaths();
    Device::GetInstance()->setDeviceSize(512, 384);
    
    DE::Canvas* canvas = new DE::Canvas();
    canvas->setLayerWidth(1024);
    canvas->setLayerHeight(768);
    canvas->setVisible(true);
    
    GameObject* lay = new GameObject();
    canvas->setWorldObject(lay);
    
    lay->setLeft(100);
    lay->setTop(200);
    
    Painter* paint = new Painter();
    lay->addComponent(paint);
    paint->loadImages("bgimage/bg1.png");
    
    Label* label = new Label();
    lay->addComponent(label);
    label->setText("测测试蚊子hadfoaimesf 3roiew^345qvv√¬˚…∆˙˙®∫µµ∫˚reb");
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
