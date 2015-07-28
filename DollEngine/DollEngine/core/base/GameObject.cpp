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

DE_BEGIN

static list<GameObject*> s_iterEnd;

GameObject::GameObject()
:m_parent(null)
,m_needSortChildren(false)
,m_z(0)
,m_enabled(true)
,m_visible(true)
{
    m_transInWorld = new Transform();
    m_transform = new Transform();
}

GameObject::~GameObject()
{
    if (!m_parent) {
        if (DEApplication->getWorld() == this) {
            DEApplication->setWorld(null);
        }
    }
    for (Component* comp : m_unknowComps) {
        comp->release();
    }
    m_unknowComps.clear();
    for (Component* comp : m_paintComps) {
        comp->release();
    }
    if (m_paintComps.size() > 0) {
        NEED_REDRAW;
    }
    m_paintComps.clear();
    for (Component* comp : m_touchComps) {
        comp->release();
    }
    if (m_touchComps.size() > 0) {
        NEED_RETOUCH;
    }
    m_touchComps.clear();
    for (Component* comp : m_updateComps) {
        comp->release();
    }
    m_updateComps.clear();
    SAFF_DELETE(m_transform);
    SAFF_DELETE(m_transInWorld);
}

void GameObject::addComponent(DE::Component *comp)
{
    comp->setObject(this);
    switch (comp->getType()) {
        case COMP_UNKNOW:
            m_unknowComps.push_back(comp);
            break;
        case COMP_PAINT:
            m_paintComps.push_back(comp);
            break;
        case COMP_TOUCH:
            m_touchComps.push_back(comp);
            break;
        case COMP_UPDATE:
            m_updateComps.push_back(comp);
            break;
        default:
            break;
    }
}

void GameObject::onPaint()
{
    if (m_paintComps.size() > 0) {
        for(Component* comp: m_paintComps) {
            if (comp->getEnabled()) {
                comp->update();
            }
        }
    }
}

void GameObject::transform()
{
    m_transform->flush();
    if (getParent())
    {
        m_transInWorld->copy(getParent()->m_transInWorld);
        m_transInWorld->transform(m_transform);
    }
    else
    {
        m_transInWorld->copy(GLCanvas::GetInstance()->getGlobalTrans());
        m_transInWorld->transform(m_transform);
    }
    m_transInWorld->setWidth(m_transform->getWidth());
    m_transInWorld->setHeight(m_transform->getHeight());
}

void GameObject::updateTouchListener()
{
    if (getEnabled()) {
        for (Component* comp : m_touchComps) {
            CompManager::GetInstance()->addTouchComp(comp);
        }
    }
}

DE_END
