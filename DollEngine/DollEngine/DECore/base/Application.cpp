//
//  DEApplication.cpp
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Application.h"

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
//            InputEventPool::GetInstance()->clearTouches();
//            m_currentCanvas->updateInputEvent();
//            m_needRetouch=false;
//        }
//    }
}

void Application::startup()
{
    
}

void Application::setDeviceSize(float w,float h)
{
    m_deviceWidth = w;
    m_deviceHeight = h;
}

//void Device::setCurrentCanvas(DE::Canvas *v)
//{
//    if (m_currentCanvas) {
//        delete m_currentCanvas;
//    }
//    m_currentCanvas = v;
//}

DE_END
