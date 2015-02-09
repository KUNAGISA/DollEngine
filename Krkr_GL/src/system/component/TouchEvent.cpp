//
//  TouchEvent.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/12/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TouchEvent.h"
#include "COMManager.h"
#include "Object.h"

TouchEvent::TouchEvent()
:m_priority(-1)
,m_swallow(false)
,m_ignore(false)
,m_enter(false)
,m_moved(false)
{
    setComName(L"TouchEvent");
    setTriggerType(TRIGGER_TOUCH);
}

bool TouchEvent::isPointInside(float x,float y)
{
    if (!getEnabled())
    {
        return false;
    }
    if (!getObject()) {
        return true;
    }
    auto trans = getObject()->getWorldTrans();
    if (trans)
    {
        return trans->isPointInside(x, y);
    }
    return false;
}

