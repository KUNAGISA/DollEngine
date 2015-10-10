//
//  AppInfo.h
//  DollEngine
//
//  Created by DollStudio on 15/10/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__AppInfo__
#define __DollEngine__AppInfo__

#include "CoreUnits.h"

DE_BEGIN

class AppInfo
{
public:
    AppInfo();
    Shared(AppInfo)
    
    //debug mode:0不显示console 1显示但不打印tag 2打印tag但不打印macro 3所有都打印
    PROPERTY(int,DebugMode,m_debugMode);
    
    PROPERTY_CONST(String,AppPath,m_appPath){m_appPath=v;}
    PROPERTY_CONST(String,DataPath,m_dataPath){m_dataPath=v;}
    PROPERTY_CONST(String,SaveDataPath,m_saveDataPath){m_saveDataPath=v;}
    PROPERTY_CONST(String,PatchPath,m_patchPath){m_patchPath=v;}
    
    float getDesktopWidth();
    float getDesktopHeight();
    
};

DE_END

#endif /* defined(__DollEngine__AppInfo__) */
