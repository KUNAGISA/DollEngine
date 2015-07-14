//
//  InputEvent.h
//  DollEngine
//
//  Created by DollStudio on 15/5/13.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__InputEvent__
#define __DollEngine__InputEvent__

#include "BaseComp.h"

DE_BEGIN

class InputEvent: public BaseComp
{
public:
    InputEvent();
    bool pointInside(float x,float y,float& ox,float &oy);
    PROPERTY(bool, Ignore, m_ignore){m_ignore=v;}
    PROPERTY(bool, Swallow, m_swallow){m_swallow=v;}
    PROPERTY(int, Priority, m_priority){m_priority=v;}
    PROPERTY(bool, Focus, m_focus){m_focus=v;}
    PROPERTY(bool, Moved, m_moved){m_moved=v;}
    PROPERTY(list<InputEvent*>::iterator, IterInPool, m_iterInPool){m_iterInPool=v;}
public:
    virtual void onTouchDown(float x,float y ){DM("down:%f,%f",x,y);}
    virtual void onTouchUp(float x,float y ){DM("up:%f,%f",x,y);}
    virtual void onTouchMove(float x,float y ){DM("move:%f,%f",x,y);}
    virtual void onClick(float x,float y){DM("click:%f,%f",x,y);}
    virtual void onMouseEnter(){}
    virtual void onMouseLeave(){}
};

DE_END

#endif /* defined(__Krkr_GL__InputEvent__) */
