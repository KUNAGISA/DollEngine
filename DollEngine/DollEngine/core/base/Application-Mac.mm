//
//  Device-Mac.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "Application.h"

DE_BEGIN

void Application::initEnginePaths()
{
    //Data path
    NSString* rootPath = [[NSUserDefaults standardUserDefaults] stringForKey:@"DATA_PATH"];
    if (rootPath == nil || [rootPath compare:@""] == NSOrderedSame)
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
            m_dataPath = path.UTF8String;
            [panel close];
        }
        else
        {
            exit(0);
        }
    }
    else {
        m_dataPath = rootPath.UTF8String;
    }
    
    m_dataPath += "/";
    
    //App path
    m_appPath = [[NSBundle mainBundle] bundlePath].UTF8String;
    m_appPath += "/";
    
    //SaveData path
    m_saveDataPath = [[NSBundle mainBundle] resourcePath].UTF8String;
    m_saveDataPath += "/";
    
    //Patch path
    m_patchPath = m_saveDataPath;
    
}

DE_END
