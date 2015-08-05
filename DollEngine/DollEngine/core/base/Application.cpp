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
#include "FontCache.h"
#include "GLCanvas.h"
#include "Character.h"
#include "Window.h"

DE_BEGIN

Application::Application()
:m_debugTime(0)
,m_debugFPS(null)
,m_debugFPSCOM(null)
,m_needRedraw(true)
,m_debugPrintTime(0)
{
}


Application::~Application()
{
    SAFF_DELETE(m_debugFPS);
}

void Application::mainLoop()
{
    CompManager::GetInstance()->updateComp();
    if (m_needRedraw) {
//        m_needRedraw = false;
        CompManager::GetInstance()->clearTouches();
        GLCanvas::GetInstance()->clearGL();
        if (Window::GetInstance()) {
            Window::GetInstance()->visit();
//            if (m_debugFPS) {
//                double ttime = GetSeconds();
//                double dt = ttime - m_debugTime;
//                m_debugTime = ttime;
//                if (m_debugPrintTime == 0) {
//                    m_debugPrintTime = ttime;
//                }
//                if (m_debugTime > m_debugPrintTime) {
//                    ++m_debugPrintTime;
//                    string tm = Utf8WithFormat("FPS: %f",round(10/dt)/10);
//                    m_debugFPSCOM->setText(tm);
//                }
//                m_debugFPS->onPaint();
//            }
        }
    }
    ScriptEngine::GetInstance()->evalAsyncScripts();
    CompManager::GetInstance()->releaseComp();
}

void Application::initDebugInfo()
{
    if (!m_debugFPS) {
        m_debugFPS = new GameObject();
        m_debugFPSCOM = new Character();
        m_debugFPS->addComponent(m_debugFPSCOM);
        m_debugFPS->setAnchorX(0);
        m_debugFPS->setAnchorY(0);
        m_debugFPS->setX(20);
        m_debugFPS->setY(20);
        m_debugFPSCOM->setFontSize(24);
        m_debugFPS->transform();
    }
}

void Application::startup()
{
    initEnginePaths();
    FontCache::GetInstance()->getFont(DEFFONT);
    string fullpath = Storages::GetInstance()->getFullPath("Startup.tjs");
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

void Application::setDeviceSize(float w,float h)
{
    m_deviceWidth = w;
    m_deviceHeight = h;
}



DE_END
