//
//  TouchEvent.h
//  Krkr_GL
//
//  Created by DollStudio on 14/12/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__TouchEvent__
#define __Krkr_GL__TouchEvent__

#include "COM.h"

class TouchEvent: public COM
{
public:
    TouchEvent();
    bool isPointInside(float x,float y);
    PROPERTY(bool, Ignore, m_ignore){m_ignore=v;}
    PROPERTY(bool, Swallow, m_swallow){m_swallow=v;}
    PROPERTY(int, Priority, m_priority){m_priority=v;}
    PROPERTY(bool, Enter, m_enter){m_enter=v;}
    PROPERTY(bool, Moved, m_moved){m_moved=v;}
public:
    virtual void onMouseDown(float x,float y ){}
    virtual void onMouseUp(float x,float y ){}
    virtual void onMouseMove(float x,float y ){}
    virtual void onClick(float x,float y){}
    virtual void onMouseEnter(){}
    virtual void onMouseLeave(){}
};

#endif /* defined(__Krkr_GL__TouchEvent__) */
