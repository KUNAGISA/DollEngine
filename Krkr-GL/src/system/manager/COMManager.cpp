//
//  COMManager.cpp
//  DollEngine
//
//  Created by ios开发－b on 14/12/25.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "COMManager.h"
#include "System.h"
#include "TouchEvent.h"
#include "Object.h"

COMManager::COMManager()
{
    m_nowTime = get_utc_time();
}

void COMManager::addRelease(COM* com)
{
    m_releaseCom.insert(com);
}

void COMManager::addUpdate(COM* com)
{
    m_updateCom.insert(com);
}

void COMManager::removeUpdate(COM* com)
{
    m_updateCom.erase(com);
}

void COMManager::addTouch(TouchEvent* com)
{
    m_touchCOM.push_front(com);
    com->setIter(m_touchCOM.begin());
}

void COMManager::removeTouch(TouchEvent* com)
{
    m_touchCOM.erase(com->getIter());
    com->setIter(end());
}

void COMManager::addDisableObject(Object* obj)
{
    m_disableObject.push_front(obj);
}

void COMManager::release()
{
    for (auto iter = m_releaseCom.begin();
         iter != m_releaseCom.end(); ++iter)
    {
        delete *iter;
    }
    m_releaseCom.clear();
}

void COMManager::update()
{
    double time = m_nowTime+1/60.0f;//get_utc_time();
    double delay = time - m_nowTime;
    m_nowTime = time;
    set<COM*> all = m_updateCom;
    for (auto iter = all.begin();
         iter != all.end();++iter)
    {
        auto obj = *iter;
        obj->setTime(obj->getTime()+delay);
        obj->trigger();
    }
}

void COMManager::sortTouch()
{
    m_touchCOM.sort([](TouchEvent* a,TouchEvent* b){
        if (a->getObject() == null) {
            return true;
        }
        else if (b->getObject() == null)
        {
            return false;
        }
        else
        {
            return a->getObject()->getPriority() > b->getObject()->getPriority();
        }
    });
    auto iterTouch = m_touchCOM.begin();
    for (; iterTouch != m_touchCOM.end(); ++iterTouch) {
        (*iterTouch)->setIgnore(false);
    }
    iterTouch = m_touchCOM.begin();
    auto iterObject = m_disableObject.begin();
    while (iterTouch != m_touchCOM.end() &&
           iterObject != m_disableObject.end())
    {
        Object* object = *iterObject;
        TouchEvent* event = *iterTouch;
        if (event->getObject())
        {
            if (event->getObject()->getPriority() < object->getPriority())
            {
                ++iterObject;
            }
            else if (event->getObject()->getPriority() >= object->getPriority() &&
                     event->getObject()->getPriority() < object->getPriorityMax())
            {
                event->setIgnore(true);
                ++iterTouch;
            }
            else
            {
                ++iterTouch;
            }
        }
        else
        {
            ++iterTouch;
        }
    }
    m_disableObject.clear();
}

bool COMManager::touchBegan(float x,float y)
{
    list<TouchEvent*> all_event = m_touchCOM;
    m_validTouch.clear();
    for (auto iter = all_event.begin();
         iter != all_event.end(); ++iter)
    {
        TouchEvent* obj = *iter;
        if (obj->getEnabled() && !obj->getIgnore() && obj->isPointInside(x,y))
        {
            obj->onMouseDown(x, y);
            if (!obj->getIgnore())
            {
                obj->setEnter(true);
                obj->onMouseEnter();
                m_validTouch.push_back(obj);
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
    return m_validTouch.size() > 0 ? true : false;
}

void COMManager::touchMoved(float x,float y)
{
    for (auto iter = m_validTouch.begin();
         iter != m_validTouch.end(); ++iter)
    {
        TouchEvent* obj = *iter;
        if (!obj->isPointInside(x, y) && obj->getEnter() == true) {
            obj->setEnter(false);
            obj->onMouseLeave();
        }
        else if (obj->isPointInside(x, y) && obj->getEnter() == false) {
            obj->setEnter(true);
            obj->onMouseEnter();
        }
        obj->setMoved(true);
        obj->onMouseMove(x, y);
    }
}

void COMManager::touchEnded(float x,float y)
{
    for (auto iter = m_validTouch.begin();
         iter != m_validTouch.end(); ++iter)
    {
        TouchEvent* obj = *iter;
        if (obj->getEnter() == true) {
            obj->setEnter(false);
            obj->onMouseLeave();
        }
        obj->onMouseUp(x, y);
    }
    touchClick(x,y);
}

void COMManager::touchClick(float x,float y)
{
    for (auto iter = m_validTouch.begin();
         iter != m_validTouch.end(); ++iter)
    {
        TouchEvent* obj = *iter;
        if (obj->isPointInside(x, y))
        {
            obj->onClick(x, y);
        }
        obj->setMoved(false);
    }
}

static list<TouchEvent*> s_touches_iter_end;
list<TouchEvent*>::iterator COMManager::end()
{
    return s_touches_iter_end.end();
}
