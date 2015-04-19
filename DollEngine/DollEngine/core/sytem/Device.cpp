//
//  Device.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Device.h"
#include "Storages.h"

DE_BEGIN

Device::Device()
:m_currentCanvas(null)
,m_frameInterval(60)
,m_mainLoopTimerId(0)
{
    m_deviceTrans = new Transform();
}


Device::~Device()
{
    
}

void Device::initialize()
{
    initEnginePaths();
}

void Device::mainLoop()
{
    if (m_currentCanvas) {
        m_currentCanvas->paintGL();
    }
}

void Device::startup()
{
    
}

void Device::setCanvasSize(float w,float h)
{
    
}

void Device::setWinSize(float w,float h)
{
    
}

void Device::onResize()
{
    
}

DE_END
