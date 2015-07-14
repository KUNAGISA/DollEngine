//
//  InputEventPool.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "InputEventPool.h"
#include "Device.h"
#include "Canvas.h"

DE_BEGIN

static list<InputEvent*> s_iterEnd;
list<InputEvent*>::iterator InputEventPool::InputIterEnd()
{
    return s_iterEnd.end();
}

void InputEventPool::clearTouches()
{
    for (InputEvent* event : m_allInputs) {
        event->setIterInPool(InputIterEnd());
    }
    m_allInputs.clear();
}

void InputEventPool::addTouch(InputEvent* event)
{
    if (!event) {
        return;
    }
    m_allInputs.push_front(event);
    event->setIterInPool(m_allInputs.begin());
}

void InputEventPool::removeTouch(InputEvent* event)
{
    if (event->getIterInPool() == InputIterEnd()) {
        return;
    }
    m_allInputs.erase(event->getIterInPool());
    event->setIterInPool(InputIterEnd());
}

bool InputEventPool::onTouchDown(float x,float y )
{
    Device* device = Device::GetInstance();
    Canvas* canvas = device->getCurrentCanvas();
    x /= device->getDeviceWidth()/canvas->getLayerWidth();
    y /= device->getDeviceHeight()/canvas->getLayerHeight();
    list<InputEvent*> all_event = m_allInputs;
    m_validTouches.clear();
    for (auto iter = all_event.begin();
         iter != all_event.end(); ++iter)
    {
        InputEvent* obj = *iter;
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

void InputEventPool::onTouchUp(float x,float y )
{
    Device* device = Device::GetInstance();
    Canvas* canvas = device->getCurrentCanvas();
    x /= device->getDeviceWidth()/canvas->getLayerWidth();
    y /= device->getDeviceHeight()/canvas->getLayerHeight();
    for (auto iter = m_validTouches.begin();
         iter != m_validTouches.end(); ++iter)
    {
        InputEvent* obj = *iter;
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

void InputEventPool::onTouchMove(float x,float y )
{
    Device* device = Device::GetInstance();
    Canvas* canvas = device->getCurrentCanvas();
    x /= device->getDeviceWidth()/canvas->getLayerWidth();
    y /= device->getDeviceHeight()/canvas->getLayerHeight();
    for (auto iter = m_validTouches.begin();
         iter != m_validTouches.end(); ++iter)
    {
        InputEvent* obj = *iter;
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