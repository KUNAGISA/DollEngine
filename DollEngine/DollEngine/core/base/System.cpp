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
    try{
        AppInfo::GetInstance();
        ScriptEngine::GetInstance();
        FontInterface::GetInstance()->addFont("WenQuanYiMicroHei.ttc");
        String fullpath = Storages::GetInstance()->getFullPath("Startup.tjs");
        
        IOData* data = Storages::GetFileString(fullpath);
        String code;
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

DE_END
