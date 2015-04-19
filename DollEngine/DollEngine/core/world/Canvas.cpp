//
//  Canvas.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Canvas.h"

DE_BEGIN

Canvas::Canvas()
:m_worldObject(null)
,m_window(null)
,m_visible(false)
,m_LayerHeight(0)
,m_LayerWidth(0)
,m_LayerLeft(0)
,m_LayerTop(0)
,m_LayerZoom(0)
//,m_winWidth(0)
//,m_winHeight(0)
{
    
}

void Canvas::initializeGL()
{
    glClearColor(0, 0, 0, 0);
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (m_worldObject) {
        m_worldObject->visit();
    }
}

void Canvas::resizeGL(float width,float height)
{
    
}


void Canvas::setWorldObject(GameObject* lay)
{
    SAFF_DELETE(m_worldObject);
    if(m_worldObject) {
        delete m_worldObject;
        m_worldObject = null;
    }
//    if(lay->getParent()) {
//        lay->removeFromParent(false);
//    }
    m_worldObject = lay;
}

DE_END