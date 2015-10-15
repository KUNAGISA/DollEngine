//
//  System.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "System.h"

DE_BEGIN

System::System()
:m_debugMode(0)
,m_isError(false)
,m_delegate(NULL)
{
    System::NeedRedraw = true;
    System::NeedSortTouches = true;
    //Data path
    m_dataPath = [[NSBundle mainBundle] resourcePath].UTF8String;
    m_dataPath += L"/data/";
    
    //App path
    m_appPath = [[NSBundle mainBundle] bundlePath].UTF8String;
    m_appPath += L"/";
    
    //SaveData path
    m_saveDataPath = [[NSBundle mainBundle] resourcePath].UTF8String;
    m_saveDataPath += L"/savedata/";
    
    //Patch path
    m_patchPath = [[NSBundle mainBundle] resourcePath].UTF8String;
    m_patchPath += L"/patch/";
}

float System::getDesktopWidth()
{
    return [[UIScreen mainScreen] bounds].size.width;
}
float System::getDesktopHeight()
{
    return [[UIScreen mainScreen] bounds].size.height;
}

DE_END
