//
//  de-device-window.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-device-window.h"
#include "de-device-interface.h"

NAMESPACE_DE_DEVICE

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
    setInnerWidth(v-get_window_edge_width());
}

void Window::setHeight(float v)
{
    setInnerHeight(v-get_window_edge_height());
}

void Window::setInnerWidth( float v)
{
    m_innerWidth = v;
    m_width = v+get_window_edge_width();
    m_needReViewPort=true;
}

void Window::setInnerHeight(float v)
{
    m_innerHeight = v;
    m_height = v+get_window_edge_height();
    m_needReViewPort=true;
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

void Window::visit()
{
//    COMManager::GetInstance()->update();
//    if (System::GetInstance()->getTransChanged() ||
//        System::GetInstance()->getOrderChanged() ||
//        m_needReViewPort )
//    {
//        if (m_needReViewPort)
//        {
//            reViewport();
//            m_needReViewPort=false;
//        }
//        glClear(GL_COLOR_BUFFER_BIT);
//        if (m_primaryLayer) {
//            m_primaryLayer->visit();
//        }
//        
//        if (System::GetInstance()->getOrderChanged())
//        {
//            if (m_primaryLayer) {
//                m_primaryLayer->priority();
//            }
//            COMManager::GetInstance()->sortTouch();
//        }
//    }
//    COMManager::GetInstance()->release();
    //    System::GetInstance()->setTransChanged(false);
    //    System::GetInstance()->setOrderChanged(false);
}

NAMESPACE_DE_END2