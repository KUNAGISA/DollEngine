//
//  TouchListener.h
//  DollEngine
//
//  Created by DollStudio on 15/5/13.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TouchListener__
#define __DollEngine__TouchListener__

#include "Component.h"
#include "System.h"

DE_BEGIN

class TouchListener: public Component
{
public:
    TouchListener();
    ~TouchListener();
    void addToManager();
    bool pointInside(float x,float y,float& ox,float &oy,Transform* trans);
    virtual void setEnabled(bool v){ Component::setEnabled(v);NEED_REDRAW;}
    PROPERTY(bool, Global, m_global);
    PROPERTY(bool, Ignore, m_ignore){m_ignore=v;}
    PROPERTY(bool, Swallow, m_swallow){m_swallow=v;}
    PROPERTY(int, Priority, m_priority){m_priority=v;}
    PROPERTY(bool, Focus, m_focus){m_focus=v;}
    PROPERTY(bool, Moved, m_moved){m_moved=v;}
public:
    virtual void onMouseDown(float x,float y ){}
    virtual void onMouseUp(float x,float y ){}
    virtual void onMouseMove(float x,float y ){}
    virtual void onClick(float x,float y){}
    virtual void onMouseEnter(){}
    virtual void onMouseLeave(){}
};

DE_END

#endif /* defined(__Krkr_GL__TouchListener__) */
