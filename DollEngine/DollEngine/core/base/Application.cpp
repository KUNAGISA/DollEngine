//
//  DEApplication.cpp
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Application.h"
#include "GameObject.h"
#include "Storages.h"
#include "CompManager.h"
#include "ScriptEngine.h"

DE_BEGIN

Application::Application()
:m_world(null)
{
}


Application::~Application()
{
    SAFF_DELETE(m_world);
}

void Application::initialize()
{
    initEnginePaths();
}

void Application::mainLoop()
{
    if (m_world) {
        if (m_needRedraw) {
            m_world->visit();
            m_needRedraw = false;
        }
        if (m_needRetouch) {
            CompManager::GetInstance()->clearTouches();
            m_world->updateTouchListener();
            m_needRetouch=false;
        }
    }
}

void Application::startup()
{
    initialize();
    string fullpath = Storages::GetInstance()->getFullPath("Startup.tjs");
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
}

void Application::setDeviceSize(float w,float h)
{
    m_deviceWidth = w;
    m_deviceHeight = h;
}

void Application::setWorld(DE::GameObject *v)
{
    if (!v) {
        m_world = v;
        return;
    }
    if (m_world) {
        delete m_world;
    }
    m_world = v;
}


DE_END
