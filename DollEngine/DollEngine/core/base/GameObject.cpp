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
        DEApplication->setWorld(null);
    }
    else {
        removeFromParent(false);
    }
    releaseAllChild();
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

void GameObject::visit()
{
    if (!m_visible) {
        return;
    }
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
        if (m_paintComps.size() > 0) {
            for(Component* comp: m_paintComps) {
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
        if (m_paintComps.size() > 0) {
            for(Component* comp: m_paintComps) {
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

void GameObject::updateTouchListener()
{
    if (getEnabled()) {
        for (Component* comp : m_touchComps) {
            CompManager::GetInstance()->addTouchComp(comp);
        }
        for (GameObject* child : m_children) {
            child->updateTouchListener();
        }
    }
}

void GameObject::addChild(GameObject* lay)
{
    if (lay->getParent()) {
        lay->removeFromParent(false);
    }
    lay->setParent(this);
    int lastZ=0;
    if (m_children.size() > 0) {
        lastZ = m_children.back()->getZ();
    }
    m_children.push_back(lay);
    if (lastZ != lay->getZ()) {
        m_needSortChildren=true;
    }
    NEED_REDRAW;
}

void GameObject::removeChild(GameObject* lay,bool isRelease)
{
    if(lay->getParent() == this)
    {
        std::remove(m_children.begin(), m_children.end(), lay);
        lay->setParent(null);
        if (isRelease) {
            delete lay;
        }
        NEED_REDRAW;
    }
}

void GameObject::releaseAllChild()
{
    for (auto iter=m_children.begin();
         iter != m_children.end(); ++iter)
            delete *iter;
    m_children.clear();
}

GameObject* GameObject::childAtIndex(int idx)
{
    if (m_children.size()>idx) {
        int i=0;
        for (auto iter=m_children.begin();
             iter != m_children.end(); ++iter,++i) {
            if (i == idx) {
                return *iter;
            }
        }
    }
    return null;
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
        std::sort(m_children.begin(), m_children.end(), [](GameObject* a,GameObject* b){
            return a->getZ() < b->getZ();
        });
    }
}

DE_END
