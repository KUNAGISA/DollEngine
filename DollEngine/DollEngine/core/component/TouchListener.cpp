//
//  TouchListener.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/12/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TouchListener.h"
#include "GameObject.h"
#include "CompManager.h"

DE_BEGIN


TouchListener::TouchListener()
:m_priority(-1)
,m_swallow(false)
,m_ignore(false)
,m_focus(false)
,m_moved(false)
{
    setCompName("TouchListener");
    m_type = COMP_TOUCH;
}

bool TouchListener::pointInside(float x,float y,float& ox,float &oy)
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
