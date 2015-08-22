//
//  Device-Mac.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "System.h"

DE_BEGIN

void System::initEnginePaths()
{
    //Data path
    
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
