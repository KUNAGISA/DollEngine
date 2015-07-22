//
//  Device-Mac.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "Application.h"

DE_BEGIN

void Application::initEnginePaths()
{
    //Data path
//    NSString* rootPath = [[NSUserDefaults standardUserDefaults] stringForKey:@"DATA_PATH"];
//    if (rootPath == nil || [rootPath compare:@""] == NSOrderedSame)
//    {
//        NSOpenPanel* panel = [NSOpenPanel openPanel];
//        [panel setTitle:@"选择 data 目录"];
//        panel.directoryURL = [NSURL URLWithString:NSHomeDirectory()];
//        panel.allowsMultipleSelection = NO;
//        panel.canChooseDirectories = YES;
//        panel.canChooseFiles = NO;
//        NSInteger ret = [panel runModal];
//        if (ret == NSFileHandlingPanelOKButton)
//        {
//            NSString* path = [[panel.URLs objectAtIndex:0] path];
//            [[NSUserDefaults standardUserDefaults]setValue:path forKey:@"DATA_PATH"];
//            [[NSUserDefaults standardUserDefaults]synchronize];
//            m_dataPath = path.UTF8String;
//            [panel close];
//        }
//        else
//        {
//            exit(0);
//        }
//    }
//    else {
//        m_dataPath = rootPath.UTF8String;
//    }
    
    m_dataPath = [[NSBundle mainBundle] resourcePath].UTF8String;
    m_dataPath += "/data/";
    
    //App path
    m_appPath = [[NSBundle mainBundle] bundlePath].UTF8String;
    m_appPath += "/";
    
    //SaveData path
    m_saveDataPath = [[NSBundle mainBundle] resourcePath].UTF8String;
    m_saveDataPath += "/savedata/";
    
    //Patch path
    m_patchPath = [[NSBundle mainBundle] resourcePath].UTF8String;
    m_patchPath += "/patch/";
}

DE_END
