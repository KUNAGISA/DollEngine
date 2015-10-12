//
//  DESystem.cpp
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "System.h"
#include "Storages.h"
#include "CompManager.h"
#include "FontInterface.h"
#include "GLCanvas.h"
#include "Character.h"
#include "ScriptEngine.h"
#include "Window.h"
#include "AppInfo.h"
#include "IOData.h"
#include "TjsBind.h"

DE_BEGIN

System::System()
:m_needRedraw(true)
,m_isError(false)
{
}


System::~System()
{
}

void System::mainLoop()
{
    if (m_isError) {
        return;
    }
    CompManager::GetInstance()->updateComp();
    if (m_needRedraw) {
//        m_needRedraw = false;
        CompManager::GetInstance()->clearTouches();
        DI->clearColor(GL_COLOR_BUFFER_BIT,0,0,0,0);
        if (Window::GetInstance()) {
            Window::GetInstance()->visit();
        }
    }
    ScriptEngine::GetInstance()->doAsyncFunctions();
    CompManager::GetInstance()->releaseComp();
}

void System::startup()
{
    AppInfo::GetInstance();
    ScriptEngine::GetInstance();
    try{
        FontInterface::GetInstance()->addFont("WenQuanYiMicroHei.ttc");
        
        String code;
        code.loadFromFile("startup.tjs");
        ScriptEngine::GetInstance()->pushFile("【GLOBAL】");
        ScriptEngine::GetInstance()->pushFile("startup.tjs");
        ScriptEngine::GetInstance()->exec(code, NULL);
        ScriptEngine::GetInstance()->popFile();
        
        m_needRedraw=true;
    }
    TJS_CATCH
}

int64_t System::getMilliSeconds()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

double System::getSeconds()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec/1000000.0f;
}

DE_END
