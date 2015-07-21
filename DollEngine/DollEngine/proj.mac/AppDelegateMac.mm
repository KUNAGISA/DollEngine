//
//  AppDelegate.m
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "AppDelegateMac.h"
#include "Console.h"
#include "Application.h"
#include "TjsEngine.h"
#include "Window.h"

using namespace DE;

@interface AppDelegateMac ()

@end

@implementation AppDelegateMac

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    new TjsEngine();
    DEApplication->startup();
    
    
//    Window* window = new Window();
//    window->initialize(1024, 768);
//    Device::GetInstance()->initEnginePaths();
//    Device::GetInstance()->setDeviceSize(1024, 768);
//    
//    DE::Canvas* canvas = new DE::Canvas();
//    canvas->setLayerWidth(1024);
//    canvas->setLayerHeight(768);
//    canvas->setVisible(true);
//    
//    GameObject* lay = new GameObject();
//    canvas->setWorldObject(lay);
//    
////    lay->setLeft(100);
////    lay->setTop(200);
//    
//    Painter* paint = new Painter();
//    lay->addComponent(paint);
//    paint->loadImages("bgimage/bg1.png");
//    lay->setSizeToPaintSize();
//    
//    GameObject* lay2 = new GameObject();
//    lay->addChild(lay2);
//    
//    Painter* paint2 = new Painter();
//    lay2->addComponent(paint2);
//    paint2->loadImages("image/configb4_1.png");
//    lay2->setSizeToPaintSize();
////    
////    Label* label = new Label();
////    lay2->addComponent(label);
////    label->setText("测试文字hadfoaimesf 3roiew^345qvv√¬˚…∆˙˙®∫µµ∫˚reb");
////    label->setFontSize(48);
////    label->updateText();
//    lay2->setLeft(200);
//    lay2->setTop(50);
//    lay2->setRotation(45);
//    lay2->setScaleX(0.5);
//    lay2->setScaleY(2);
////    lay2->setSizeToPaintSize();
//    
//    TouchListener* event = new TouchListener();
//    lay2->addComponent(event);

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
        DEApplication->initEnginePaths();
        [panel close];
    }
}

@end
