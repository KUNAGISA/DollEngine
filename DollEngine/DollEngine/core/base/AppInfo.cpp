//
//  AppInfo.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "AppInfo.h"
#include "ScriptEngine.h"

DE_BEGIN

void AppInfo::setDebugMode(int v)
{
    m_debugMode = v;
    if (v == 0) {
        ScriptEngine::GetInstance()->setConsoleVisible(false);
    }
    else {
        if(ScriptEngine::GetInstance()->getConsoleVisible()){
            ScriptEngine::GetInstance()->setConsoleVisible(true);
        }
    }
}


DE_END
