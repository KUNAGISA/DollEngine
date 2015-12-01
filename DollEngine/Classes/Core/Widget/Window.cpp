//
//  Window.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Window.h"
#include "RTT.h"
#include "PaintEngine.h"

DE_BEGIN

static Window* s_instance=NULL;

Window* Window::GetInstance()
{
    return s_instance;
}

Window::Window()
:m_visible(false)
,m_fullScreen(false)
,m_height(1)
,m_width(1)
{
    s_instance = this;
}

Window::~Window()
{
}

void Window::setLayerSize(int w,int h)
{
    PaintEngine::GetInstance()->setLayerWidth(w);
    PaintEngine::GetInstance()->setLayerHeight(h);
}

float Window::getLayerWidth()
{
    return PaintEngine::GetInstance()->getLayerWidth();
}

float Window::getLayerHeight()
{
    return PaintEngine::GetInstance()->getLayerHeight();
}

void Window::beforeMainLoop()
{
    PaintEngine::GetInstance()->beforeMainLoop();
}

void Window::afterMainLoop()
{
    PaintEngine::GetInstance()->afterMainLoop();
}

void Window::setSize(int w, int h)
{
    m_width = w;
    m_height = h;
}

DE_END


#include "TjsBind.h"


