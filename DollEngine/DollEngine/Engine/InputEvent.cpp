//
//  InputEvent.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/12/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "InputEvent.h"
#include "GameObject.h"
#include "InputEventPool.h"

DE_BEGIN


InputEvent::InputEvent()
:m_priority(-1)
,m_swallow(false)
,m_ignore(false)
,m_focus(false)
,m_moved(false)
,m_iterInPool(InputEventPool::InputIterEnd())
{
    setCompName("InputEvent");
    m_type = COMP_TOUCH;
    NEED_RETOUCH;
}

bool InputEvent::pointInside(float x,float y,float& ox,float &oy)
{
    if (!getEnabled())
    {
        ox=-1;
        oy=-1;
        return false;
    }
    if (!getObject()) {
        ox=x;
        oy=y;
        return true;
    }
    auto trans = getObject()->getTransInWorld();
    if (trans)
    {
        return trans->pointInside(x, y,ox,oy);
    }
    ox=-1;
    oy=-1;
    return false;
}

DE_END
