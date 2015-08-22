//
//  CompManager.cpp
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CompManager.h"
#include "TouchListener.h"
#include "GLCanvas.h"
#include "System.h"

DE_BEGIN

CompManager::CompManager()
:m_lastTime(-1)
{
    
}

void CompManager::addUpdateComp(Component* comp)
{
    m_updatePools.insert(comp);
}

void CompManager::removeUpdateComp(Component* comp)
{
    m_updatePools.erase(comp);
}

void CompManager::updateComp()
{
    if (m_lastTime < 0) {
        m_lastTime = GetSeconds();
    }
    double time = GetSeconds();
    double dt = time - m_lastTime;
    if (System::GetInstance()->getDebugMode()>0) {
        dt = 1/60.0f;
        m_lastTime = m_lastTime+dt;
    }
    else {
        m_lastTime = time;
    }
    set<Component*> tmp = m_updatePools;
    for (Component* comp : tmp) {
        comp->setTime(comp->getTime()+dt);
        comp->update();
    }
}

void CompManager::releaseComp()
{
    set<Component*> tmp = m_releasePools;
    for (Component* comp : tmp) {
        delete comp;
    }
    m_releasePools.clear();
}

void CompManager::addReleaseComp(DE::Component *comp)
{
    m_releasePools.insert(comp);
    comp->setIsReleased(true);
}

void CompManager::removeReleaseComp(DE::Component *comp)
{
    m_releasePools.erase(comp);
}

void CompManager::addGlobalTouchComp(Component* comp)
{
    m_globalTouchs.insert(comp);
}

void CompManager::removeGlobalTouchComp(Component* comp)
{
    m_globalTouchs.erase(comp);
}

void CompManager::addTouchComp(Component* comp)
{
    m_touchComps.push_front(comp);
}


void CompManager::clearTouches()
{
    m_touchComps.clear();
}


bool CompManager::onMouseDown(float x,float y )
{
    x /= DESystem->getDeviceWidth()/GLCanvas::GetInstance()->getLayerWidth();
    y /= DESystem->getDeviceHeight()/GLCanvas::GetInstance()->getLayerHeight();
    list<Component*> allTouchs = m_touchComps;
    for (auto iter = m_globalTouchs.begin();
         iter != m_globalTouchs.end(); ++iter) {
        allTouchs.push_front(*iter);
    }
    m_validTouches.clear();
    for (auto iter = allTouchs.begin();
         iter != allTouchs.end(); ++iter)
    {
        TouchListener* obj = dynamic_cast<TouchListener*>(*iter);
        if (!obj||obj->getIsReleased()) {
            continue;
        }
        obj->setMoved(false);
        obj->setFocus(false);
        obj->setIgnore(false);
        float ox,oy;
        if (obj->getEnabled() && obj->pointInside(x,y,ox,oy))
        {
            obj->onMouseDown(ox, oy);
            if (!obj->getIgnore())
            {
                obj->setFocus(true);
                obj->onMouseEnter();
                m_validTouches.push_back(obj);
                if (obj->getSwallow()) {
                    return true;
                }
            }
            else
            {
                obj->setIgnore(false);
            }
        }
    }
    return m_validTouches.size() > 0 ? true : false;
}

void CompManager::onMouseUp(float x,float y )
{
    x /= DESystem->getDeviceWidth()/GLCanvas::GetInstance()->getLayerWidth();
    y /= DESystem->getDeviceHeight()/GLCanvas::GetInstance()->getLayerHeight();
    for (auto iter = m_validTouches.begin();
         iter != m_validTouches.end(); ++iter)
    {
        TouchListener* obj = *iter;
        if (obj->getIsReleased()) {
            continue;
        }
        obj->setFocus(false);
        float ox,oy;
        bool pointInside = obj->pointInside(x, y,ox,oy);
        if (pointInside) {
            obj->onMouseUp(ox, oy);
            if (!obj->getMoved()) {
                obj->onClick(ox, oy);
            }
        }
        else {
            obj->onMouseUp(ox, oy);
        }
    }
}

void CompManager::onMouseMove(float x,float y )
{
    x /= DESystem->getDeviceWidth()/GLCanvas::GetInstance()->getLayerWidth();
    y /= DESystem->getDeviceHeight()/GLCanvas::GetInstance()->getLayerHeight();
    for (auto iter = m_validTouches.begin();
         iter != m_validTouches.end(); ++iter)
    {
        TouchListener* obj = *iter;
        if (obj->getIsReleased()) {
            continue;
        }
        float ox,oy;
        bool pointInside = obj->pointInside(x, y,ox,oy);
        if (!pointInside && obj->getFocus() == true) {
            obj->setFocus(false);
            obj->onMouseLeave();
        }
        else if (pointInside && obj->getFocus() == false) {
            obj->setFocus(true);
            obj->onMouseEnter();
        }
        obj->setMoved(true);
        obj->onMouseMove(ox, oy);
    }
}



DE_END
