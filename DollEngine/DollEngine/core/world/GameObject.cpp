//
//  GameObject.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GameObject.h"
#include "Device.h"
#include "Canvas.h"
#include "Painter.h"
#include "GLCanvas.h"

DE_BEGIN

static list<GameObject*> s_iterEnd;

GameObject::GameObject()
:m_parent(null)
,m_iterInParent(s_iterEnd.end())
,m_needSortChildren(false)
,m_z(0)
{
    m_transInWorld = new Transform();
    m_transform = new Transform();
}

GameObject::~GameObject()
{
    for (BaseComp* comp : m_unknowComp) {
        comp->release();
    }
    m_unknowComp.clear();
    if (m_paintComp.size() > 0) {
        NEED_REDRAW;
    }
    for (BaseComp* comp : m_paintComp) {
        comp->release();
    }
    m_paintComp.clear();
    if (m_touchComp.size() > 0) {
        NEED_RETOUCH;
    }
    for (BaseComp* comp : m_touchComp) {
        comp->release();
    }
    m_touchComp.clear();
    for (BaseComp* comp : m_updateComp) {
        comp->release();
    }
    m_updateComp.clear();
    SAFF_DELETE(m_transform);
    SAFF_DELETE(m_transInWorld);
}

void GameObject::addComponent(BaseComp* comp)
{
    comp->setObject(this);
    switch (comp->getType()) {
        case COMP_UNKNOW:
            m_unknowComp.push_back(comp);
            break;
        case COMP_PAINT:
            m_paintComp.push_back(comp);
            break;
        case COMP_TOUCH:
            m_touchComp.push_back(comp);
            break;
        case COMP_UPDATE:
            m_updateComp.push_back(comp);
            break;
        default:
            break;
    }
}

void GameObject::visit()
{
    sortChildren();
    transform();
    if (m_children.size() > 0) {
        auto iter = m_children.begin();
        for (; iter != m_children.end(); ++iter) {
            if ((*iter)->getZ() < 0) {
                (*iter)->visit();
            }
            else {
                break;
            }
        }
        if (m_paintComp.size() > 0) {
            for(BaseComp* comp: m_paintComp) {
                if (comp->getEnabled()) {
                    comp->update();
                }
            }
        }
        for (; iter != m_children.end(); ++iter) {
            (*iter)->visit();
        }
    }
    else {
        if (m_paintComp.size() > 0) {
            for(BaseComp* comp: m_paintComp) {
                if (comp->getEnabled()) {
                    comp->update();
                }
            }
        }
    }
}

void GameObject::transform()
{
    m_transform->flush();
    if (getParent())
    {
//        setRealyOpacity(getParent()->getRealyOpacity() * getOpacity() / 255.0f);
        m_transInWorld->copy(getParent()->m_transInWorld);
        m_transInWorld->transform(m_transform);
    }
    else
    {
//        m_realyOpacity = m_opacity/255.0f;
        m_transInWorld->copy(GLCanvas::GetInstance()->getGlobalTrans());
        m_transInWorld->transform(m_transform);
    }
    m_transInWorld->setWidth(m_transform->getWidth());
    m_transInWorld->setHeight(m_transform->getHeight());
}

void GameObject::addChild(GameObject* lay)
{
    if (lay->getParent()) {
        lay->removeFromParent(false);
    }
    lay->setParent(this);
    int lastZ = m_children.back()->getZ();
    m_children.push_back(lay);
    if (lastZ != lay->getZ()) {
        m_needSortChildren=true;
    }
    m_iterInParent = m_children.end();
    m_iterInParent--;
    NEED_REDRAW;
}

void GameObject::removeChild(GameObject* lay,bool isRelease)
{
    if(lay->getParent() == this)
    {
        m_children.erase(lay->m_iterInParent);
        lay->m_iterInParent = s_iterEnd.end();
        lay->setParent(null);
        if (isRelease) {
            delete lay;
        }
        NEED_REDRAW;
    }
}

void GameObject::removeFromParent(bool isRelease)
{
    if (m_parent) {
        m_parent->removeChild(this, isRelease);
    }
}

void GameObject::sortChildren()
{
    if (m_needSortChildren) {
        m_needSortChildren = false;
        m_children.sort([](GameObject* a,GameObject* b){
            return a->getZ() < b->getZ();
        });
    }
}

DE_END
