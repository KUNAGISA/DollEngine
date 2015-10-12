//
//  AppInfo.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "AppInfo.h"
#include "Console.h"

DE_BEGIN

bool AppInfo::NeedRedraw=true;
bool AppInfo::NeedSortTouches=true;

void AppInfo::setDebugMode(int v)
{
    m_debugMode = v;
    if (v == 0) {
        Console::GetInstance()->setVisible(false);
    }
    else {
        if(Console::GetInstance()->getVisible()){
            Console::GetInstance()->setVisible(true);
        }
    }
}


DE_END
