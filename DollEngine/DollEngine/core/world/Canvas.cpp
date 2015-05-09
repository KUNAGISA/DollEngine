//
//  Canvas.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Canvas.h"
#include "GameObject.h"
#include "PaintEngine.h"

DE_BEGIN

Canvas::Canvas()
:m_worldObject(null)
,m_window(null)
,m_visible(false)
,m_layerHeight(0)
,m_layerWidth(0)
,m_layerLeft(0)
,m_layerTop(0)
,m_layerZoom(0)
//,m_winWidth(0)
//,m_winHeight(0)
{
}

Canvas::~Canvas()
{
}

void Canvas::visit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (m_worldObject) {
        m_worldObject->visit();
    }
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