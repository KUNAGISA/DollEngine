//
//  Window.cpp
//  DollEngine
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Window.h"
#include "Object.h"
#include "PaintEngine.h"
#include "System.h"
#include "COMManager.h"

#define WINDOW_HEIGHT_DIFF 0
#define WINDOW_WIDTH_DIFF 0

static Window* s_window=null;
Window* Window::GetInstance()
{
    return s_window;
}

Window::Window()
:m_height(0)
,m_width(0)
//,m_left(0)
//,m_top(0)
,m_primaryLayer(null)
,m_needReViewPort(false)
{
    s_window = this;
}


Window::~Window()
{
    s_window = null;
//    SAFF_DELETE_NULL(m_primaryLayer);
}

void Window::hideMouseCursor()
{
	//隐藏鼠标（ios中为隐藏点击时出现的小动画）
}

void Window::setInnerSize(float width, float height)
{
	//设置逻辑宽高
    setInnerWidth(width);
    setInnerHeight(height);
}

void Window::setLayerSize(float w, float h)
{
    //根节点坐标（ios是设置glview的坐标
    setLayerWidth(w);
    setLayerHeight(h);
}

void Window::setSize(float width, float height)
{
	//设置窗口大小（ios和setInnerSize相同用途
    setWidth(width);
    setHeight(height);
}

void Window::reViewport()
{
//    m_needReViewPort = false;
    Transform* device = PaintEngine::GetInstance()->getDeviceTrans();
    device->refresh();
    
    float p = m_layerWidth/m_layerHeight;
    float sc_p = m_innerWidth/m_innerHeight;
    float layZoom=1,layX=0,layY=0;
    if (p > sc_p)
    {
        //上下留边
        layZoom = m_innerWidth/m_layerWidth;
        layX = 0;
        layY = (m_innerHeight - m_layerHeight * layZoom)/2;
    }
    else
    {
        //左右留边
        layZoom = m_innerHeight/m_layerHeight;
        layX = (m_innerWidth - m_layerWidth * layZoom)/2;
        layY = 0;
    }
    m_layerZoom = layZoom;
    m_layerLeft = layX;
    m_layerTop = layY;
    
    device->setX(layX*2/m_innerWidth-1);
    device->setY(-layY*2/m_innerHeight+1);
    device->setScaleX(2/m_innerWidth * layZoom);
    device->setScaleY(-2/m_innerHeight * layZoom);
    
#ifdef OS_MAC
    glViewport(0,0,m_innerWidth,m_innerHeight);
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#endif
}

void Window::visit()
{
    COMManager::GetInstance()->update();
    if (System::GetInstance()->getTransChanged() ||
        System::GetInstance()->getOrderChanged() ||
        m_needReViewPort )
    {
        if (m_needReViewPort)
        {
            reViewport();
            m_needReViewPort=false;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        if (m_primaryLayer) {
            m_primaryLayer->visit();
        }
        
        if (System::GetInstance()->getOrderChanged())
        {
            if (m_primaryLayer) {
                m_primaryLayer->priority();
            }
            COMManager::GetInstance()->sortTouch();
        }
    }
    COMManager::GetInstance()->release();
//    System::GetInstance()->setTransChanged(false);
//    System::GetInstance()->setOrderChanged(false);
}

void Window::setLayerWidth(float v)
{
    m_layerWidth = v;
    m_needReViewPort = true;
}

void Window::setLayerHeight(float v)
{
    m_layerHeight = v;
    m_needReViewPort = true;
}

void Window::setWidth(float v)
{
    setInnerWidth(v-get_winframe_width());
}

void Window::setHeight(float v)
{
    setInnerHeight(v-get_winframe_height());
}

void Window::setInnerWidth( float v)
{
    m_innerWidth = v;
    m_width = v+get_winframe_width();
    m_needReViewPort=true;
}

void Window::setInnerHeight(float v)
{
    m_innerHeight = v;
    m_height = v+get_winframe_height();
    m_needReViewPort=true;
}

