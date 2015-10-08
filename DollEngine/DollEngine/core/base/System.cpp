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
        GLCanvas::GetInstance()->clearGL();
        if (Window::GetInstance()) {
            Window::GetInstance()->visit();
        }
    }
    ScriptEngine::GetInstance()->doAsyncFunctions();
    CompManager::GetInstance()->releaseComp();
}

void System::startup()
{
    initEnginePaths();
    FontInterface::GetInstance()->addFont(DEFFONT);
    String fullpath = Storages::GetInstance()->getFullPath("Startup.tjs");
    try{
        IOData* data = Storages::GetFileString(fullpath);
        wstring code;
        data->convertToUnicode(code);
        if (!ScriptEngine::GetInstance()) {
            DM("请初始化脚本引擎！");
        }
        else {
            ScriptEngine::GetInstance()->pushFile("【GLOBAL】");
            ScriptEngine::GetInstance()->pushFile(fullpath);
            ScriptEngine::GetInstance()->exec(code, null);
            ScriptEngine::GetInstance()->popFile();
        }
        m_needRedraw=true;
    }
    catch(...) {
        
    }
}

void System::setDeviceSize(float w,float h)
{
    m_deviceWidth = w;
    m_deviceHeight = h;
}

void System::setDebugMode(int v)
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
