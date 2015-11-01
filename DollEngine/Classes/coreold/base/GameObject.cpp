//
//  GameObject.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GameObject.h"
#include "GLCanvas.h"
#include "Component.h"
#include "CompManager.h"
#include "Window.h"

DE_BEGIN

static list<GameObject*> s_iterEnd;

GameObject::GameObject()
:m_parent(null)
,m_needSortChildren(false)
,m_z(0)
,m_enabled(true)
,m_visible(true)
,m_opacity(0xff)
,m_realColor(0xffffffff)
,m_color(0xffffffff)
,m_transform(null)
,m_transInWorld(null)
{
    m_transInWorld = new Transform();
    m_transform = new Transform();
}

GameObject::~GameObject()
{
    if (!m_parent) {
        if (Window::GetInstance()->getWorld() == this) {
            Window::GetInstance()->setWorld(null);
        }
    }
    NEED_REDRAW;
    SAFF_DELETE(m_transform);
    SAFF_DELETE(m_transInWorld);
}

void GameObject::transform()
{
    m_transform->flush();
    if (getParent())
    {
        m_transInWorld->copy(getParent()->m_transInWorld);
        m_transInWorld->transform(m_transform);
        m_realColor.set(m_color);
        m_realColor.a = (GLubyte)m_opacity;
        m_realColor.multiply(getParent()->m_realColor);
    }
    else
    {
        m_realColor.set(m_color);
        m_realColor.a = (GLubyte)m_opacity;
        m_transInWorld->init();
        m_transInWorld->transform(m_transform);
    }
    m_transInWorld->setWidth(m_transform->getWidth());
    m_transInWorld->setHeight(m_transform->getHeight());
}

DE_END
