//
//  DESystem.cpp
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "System.h"
#include "GameObject.h"
#include "Storages.h"
#include "CompManager.h"
#include "ScriptEngine.h"
#include "FontCache.h"
#include "GLCanvas.h"
#include "Character.h"
#include "Window.h"

DE_BEGIN

System::System()
:m_debugTime(0)
,m_debugFPS(null)
,m_debugFPSCOM(null)
,m_needRedraw(true)
,m_debugTimeCount(0)
,m_debugTime2(0)
,m_debugMode(0)
{
}


System::~System()
{
    SAFF_DELETE(m_debugFPS);
}

void System::mainLoop()
{
    CompManager::GetInstance()->updateComp();
    if (m_needRedraw) {
//        m_needRedraw = false;
        CompManager::GetInstance()->clearTouches();
        GLCanvas::GetInstance()->clearGL();
        if (m_debugFPS) {
            double ttime = GetSeconds();
            double dt = ttime - m_debugTime;
            m_debugTime = ttime;
            m_debugTime2 += dt;
            if (m_debugTimeCount >= 59) {
                m_debugTimeCount = 0;
                string tm = Utf8WithFormat("FPS: %f",60.0f/m_debugTime2);
                m_debugTime2 = 0;
                m_debugFPSCOM->setText(tm);
            }
            else {
                m_debugTimeCount++;
            }
        }
        if (Window::GetInstance()) {
            Window::GetInstance()->visit();
        }
        if (m_debugFPS) {
            m_debugFPSCOM->update();
        }
    }
    ScriptEngine::GetInstance()->doAsyncFunctions();
    CompManager::GetInstance()->releaseComp();
}

void System::initDebugInfo()
{
    if (!m_debugFPS) {
        m_debugFPS = new GameObject();
        m_debugFPSCOM = new Character();
        m_debugFPSCOM->setObject(m_debugFPS);
        m_debugFPS->setAnchorX(0);
        m_debugFPS->setAnchorY(0);
        m_debugFPS->setX(20);
        m_debugFPS->setY(20);
        m_debugFPSCOM->setFontSize(24);
        m_debugFPS->transform();
    }
}

void System::startup()
{
    initEnginePaths();
    FontCache::GetInstance()->getFont(DEFFONT);
    string fullpath = Storages::GetInstance()->getFullPath("Startup.tjs");
    m_debugTime = GetSeconds();
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
