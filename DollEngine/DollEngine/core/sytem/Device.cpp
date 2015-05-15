//
//  Device.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Device.h"
#include "Storages.h"
#include "Canvas.h"

DE_BEGIN

Device::Device()
:m_currentCanvas(null)
{
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
        if (m_needRedraw) {
            m_currentCanvas->visit();
//            m_needRedraw = false;
        }
    }
}

void Device::startup()
{
    
}

void Device::setDeviceSize(float w,float h)
{
    m_deviceWidth = w;
    m_deviceHeight = h;
}

void Device::setCurrentCanvas(DE::Canvas *v)
{
    if (m_currentCanvas) {
        delete m_currentCanvas;
    }
    m_currentCanvas = v;
}

DE_END
