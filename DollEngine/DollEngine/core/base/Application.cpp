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
#include "ScriptEngine.h"

DE_BEGIN

Application::Application()
//:m_currentCanvas(null)
{
}


Application::~Application()
{
    
}

void Application::initialize()
{
    initEnginePaths();
}

void Application::mainLoop()
{
//    if (m_currentCanvas) {
//        if (m_needRedraw) {
//            m_currentCanvas->visit();
//            //            m_needRedraw = false;
//        }
//        if (m_needRetouch) {
//            TouchListenerPool::GetInstance()->clearTouches();
//            m_currentCanvas->updateTouchListener();
//            m_needRetouch=false;
//        }
//    }
}

void Application::startup()
{
    initialize();
    string fullpath = Storages::GetInstance()->getFullPath("data/startup.tjs");
    IOData* data = Storages::GetFileString(fullpath);
    wstring code;
    data->convertToUnicode(code);
    if (!ScriptEngine::GetInstance()) {
        DM("请初始化脚本引擎！");
    }
    else {
        ScriptEngine::GetInstance()->exec(code, null);
    }
}

void Application::setDeviceSize(float w,float h)
{
    m_deviceWidth = w;
    m_deviceHeight = h;
}

void Application::setWorld(DE::GameObject *v)
{
    if (m_world) {
        delete m_world;
    }
    m_world = v;
}


DE_END
