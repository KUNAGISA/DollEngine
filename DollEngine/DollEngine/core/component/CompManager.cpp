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
#include "Application.h"

DE_BEGIN

CompManager::CompManager()
{
    
}

void CompManager::addTouchComp(Component* comp)
{
    m_touchComps.push_back(comp);
    CompIter end = m_touchComps.end();
    --end;
    comp->setCompIter(end);
}

void CompManager::removeTouchComp(Component* comp)
{
    m_touchComps.erase(comp->getCompIter());
    comp->setCompIter(Component::EndIter());
}

void CompManager::clearTouches()
{
    for (Component* comp : m_touchComps) {
        comp->setCompIter(Component::EndIter());
    }
    m_touchComps.clear();
}

void CompManager::addReleaseComp(DE::Component *comp)
{
    m_releasePools.insert(comp);
    switch (comp->getType()) {
        case COMP_TOUCH:
        {
            removeTouchComp(comp);
        }
            break;
            
        default:
            break;
    }
}

void CompManager::removeReleaseComp(DE::Component *comp)
{
    m_releasePools.erase(comp);
}


bool CompManager::onTouchDown(float x,float y )
{
    x /= DEApplication->getDeviceWidth()/GLCanvas::GetInstance()->getLayerWidth();
    y /= DEApplication->getDeviceHeight()/GLCanvas::GetInstance()->getLayerHeight();
    list<Component*> allTouchs = m_touchComps;
    m_validTouches.clear();
    for (auto iter = allTouchs.begin();
         iter != allTouchs.end(); ++iter)
    {
        TouchListener* obj = dynamic_cast<TouchListener*>(*iter);
        if (!obj) {
            continue;
        }
        obj->setMoved(false);
        obj->setFocus(false);
        float ox,oy;
        if (obj->getEnabled() && !obj->getIgnore() && obj->pointInside(x,y,ox,oy))
        {
            obj->onTouchDown(ox, oy);
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

void CompManager::onTouchUp(float x,float y )
{
    x /= DEApplication->getDeviceWidth()/GLCanvas::GetInstance()->getLayerWidth();
    y /= DEApplication->getDeviceHeight()/GLCanvas::GetInstance()->getLayerHeight();
    for (auto iter = m_validTouches.begin();
         iter != m_validTouches.end(); ++iter)
    {
        TouchListener* obj = *iter;
        obj->setFocus(false);
        float ox,oy;
        bool pointInside = obj->pointInside(x, y,ox,oy);
        if (pointInside) {
            obj->onTouchUp(ox, oy);
            if (!obj->getMoved()) {
                obj->onClick(ox, oy);
            }
        }
        else {
            obj->onTouchUp(ox, oy);
        }
    }
}

void CompManager::onTouchMove(float x,float y )
{
    x /= DEApplication->getDeviceWidth()/GLCanvas::GetInstance()->getLayerWidth();
    y /= DEApplication->getDeviceHeight()/GLCanvas::GetInstance()->getLayerHeight();
    for (auto iter = m_validTouches.begin();
         iter != m_validTouches.end(); ++iter)
    {
        TouchListener* obj = *iter;
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
        obj->onTouchMove(ox, oy);
    }
}



DE_END
