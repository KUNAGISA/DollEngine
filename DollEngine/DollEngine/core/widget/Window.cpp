//
//  Window.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Window.h"
#include "RTT.h"
#include "GLCanvas.h"

DE_BEGIN

static Window* s_instance=NULL;

Window* Window::GetInstance()
{
    return s_instance;
}

Window::Window()
:m_deviceWindow(NULL)
//,m_transNode(NULL)
//,m_transRTT(NULL)
//,m_transBlack(NULL)
,m_visible(true)
,m_fullScreen(false)
{
    s_instance = this;
}

Window::~Window()
{
//    SAFF_DELETE(m_transNode);
//    SAFF_DELETE(m_transBlack);
}

void Window::onInitFinished()
{
//    m_transRTT = new RTT();
//    m_transBlack = new Painter();
//    m_transBlack->loadSize(GLCanvas::GetInstance()->getLayerWidth(),
//                           GLCanvas::GetInstance()->getLayerHeight(), 0);
//    m_transNode = new GameObject();
//    m_transRTT->setObject(m_transNode);
//    m_transNode->setVisible(false);
}

void Window::visit()
{
    onVisit();
//    if (m_transNode&&m_transNode->getVisible()) {
//        m_transRTT->update();
//    }
}

//void Window::beginTransition(bool isblack)
//{
//    Painter* bg=NULL;
//    if (isblack) {
//        m_transBlack->setColor(0x000000ff);
//        bg = m_transBlack;
//    }
//    m_transRTT->loadRender(m_world,
//                           GLCanvas::GetInstance()->getLayerWidth(),
//                           GLCanvas::GetInstance()->getLayerHeight(),
//                           bg);
//    m_transNode->setColor(0xffffffff);
//    m_transNode->setOpacity(255);
//    m_transNode->setX(0);
//    m_transNode->setY(0);
//    m_transNode->setAnchorX(0);
//    m_transNode->setAnchorY(0);
//    m_transNode->transform();
//    m_transNode->setVisible(true);
//}
//
//void Window::transWithCrossFade(float dt)
//{
//    if(m_transNode){
//        if (dt>=1) {
//            dt = 1;
//        }
//        if (dt<=0) {
//            dt=0;
//        }
//        m_transNode->setOpacity((1.0f-dt)*255);
//        m_transNode->transform();
//    }
//}
//
//void Window::transFinished()
//{
//    m_transNode->setVisible(false);
//}

DE_END
