//
//  Object.cpp
//  Krkr_GL
//
//  Created by ios开发－b on 14/12/25.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Object.h"
#include "Krkr_GL.h"
#include "TouchEvent.h"
#include "COMManager.h"
#include "Action.h"
#include "ActionManager.h"
#include "FadeTo.h"

static list<Object*> s_child_iter_end;

Object::Object()
:m_worldTrans(null)
,m_visible(true)
,m_iterInParent(s_child_iter_end.end())
,m_needSortChild(false)
,m_parent(null)
,m_transform(null)
,m_priorityMax(0)
,m_priority(0)
,m_enabled(false)
,m_opacity(255)
,m_realyOpacity(1)
,m_z(0)
{
    m_worldTrans = new Transform();
    m_transform = new Transform();
}

Object::~Object()
{
    setVisible(false);
    
    for (auto action : m_actions) {
        action->setTarget(null);
        delete action;
    }
    m_actions.clear();
    
    if (m_parent) {
        m_parent->removeChild(this);
        m_iterInParent = s_child_iter_end.end();
    }
    for (auto obj : m_children) {
        obj->m_iterInParent = s_child_iter_end.end();
        delete obj;
    }
    m_children.clear();
    SAFF_DELETE_NULL(m_transform);
    SAFF_DELETE_NULL(m_worldTrans);
    System::GetInstance()->setTransChanged(true);
    System::GetInstance()->setOrderChanged(true);
}

void Object::setParent(Object* v)
{
    if (m_parent)
    {
        m_parent->removeChild(this);
        m_parent = null;
    }
    if (v == null)
    {
        return;
    }
    v->addChild(this);
}

void Object::assign(Object *src)
{
    if (m_transform && src->m_transform)
    {
        m_transform->set(src->m_transform);
    }
    m_visible = src->m_visible;
    m_z = src->m_z;
    m_opacity = src->m_opacity;
    m_enabled = src->m_enabled;
}

void Object::transform()
{
    if (m_children.size() > 0 && m_needSortChild)
    {
        m_children.sort([](Object* a,Object* b){
            return a->getZ() < b->getZ();
        });
    }
    if (m_worldTrans && m_transform)
    {
        m_transform->refresh();
        if (getParent())
        {
            setRealyOpacity(getParent()->getRealyOpacity() * getOpacity() / 255.0f);
            m_worldTrans->set(getParent()->m_worldTrans, m_transform);
        }
        else
        {
            m_realyOpacity = m_opacity/255.0f;
            m_worldTrans->set(PaintEngine::GetInstance()->getDeviceTrans(),m_transform);
        }
        m_worldTrans->setWidth(m_transform->getWidth());
        m_worldTrans->setHeight(m_transform->getHeight());
    }
}

static int s_priority = 0;

void Object::priority(bool v)
{
    if (getParent() == null) {
        s_priority = 0;
    }
    m_priority = s_priority++;
    if ((!m_visible || !m_enabled) && v) {
        COMManager::GetInstance()->addDisableObject(this);
        v = false;
    }
    if (m_children.size() > 0)
    {
        for (auto iter = m_children.begin();
             iter != m_children.end(); ++iter)
        {
            (*iter)->priority(v);
        }
    }
    m_priorityMax = s_priority++;
}

void Object::visit()
{
    if (!m_visible) {
        return;
    }
    transform();
    if (m_children.size() > 0)
    {
        auto iter = m_children.begin();
        for ( ;iter != m_children.end() ; ++iter) {
            auto node = *iter;
            if (node->getZ() >= 0) {
                break;
            }
            node->visit();
        }
        onPaint();
        for ( ;iter != m_children.end() ; ++iter) {
            (*iter)->visit();
        }
    }
    else
    {
        onPaint();
    }
}

void Object::addAction(Action* act)
{
    act->setTarget(this);
    m_actions.insert(act);
}

void Object::removeAction(Action* act)
{
    act->setTarget(null);
    m_actions.erase(act);
}

void Object::addChild(Object* src)
{
    if (src->getParent())
    {
        src->getParent()->removeChild(src);
    }
    m_children.push_back(src);
    src->m_parent = this;
    auto iter = m_children.end();
    --iter;
    src->m_iterInParent = iter;
    m_needSortChild = true;
    System::GetInstance()->setOrderChanged(true);
}

void Object::removeChild(Object* src)
{
    ASSERT(src->getParent() == this);
    m_children.erase(src->m_iterInParent);
    src->m_parent = this;
    src->m_iterInParent = s_child_iter_end.end();
    m_needSortChild = true;
    System::GetInstance()->setOrderChanged(true);
}

void Object::setZ(int v)
{
    if (m_z != v)
    {
        m_z = v;
        if (getParent()) {
            getParent()->m_needSortChild = true;
        }
        System::GetInstance()->setOrderChanged(true);
    }
}

void Object::setOpacity(float v)
{
    if (v > 255)
    {
        m_opacity = 255;
    }
    else if (v < 0)
    {
        m_opacity = 0;
    }
    else
    {
        m_opacity=v;
    }
    System::GetInstance()->setTransChanged(true);
}

void Object::setEnabled(bool v)
{
    m_enabled = v;
    System::GetInstance()->setOrderChanged(true);
}

void Object::setVisible(bool v)
{
    m_visible=v;
    System::GetInstance()->setOrderChanged(true);
}

