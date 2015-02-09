//
//  Action.h
//  DollEngine
//
//  Created by DollStudio on 15/1/17.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Action__
#define __DollEngine__Action__

#include "Functions.h"
#include "Object.h"

#define _Lerp(A,B) ((B-A)*getPerc()+A)

class Action
{
public:
    Action();
    virtual ~Action();
    virtual void onStop(){DM("Action End");}
    virtual void update(){}
    PROPERTY(float, Perc, m_perc){
        if(v >= 1) m_perc=1;
        else if(v <= 0) m_perc=0;
        else m_perc = v;
    }
    PROPERTY(float, Time, m_time){m_time = v;}
    PROPERTY(float, StartTime, m_startTime){m_startTime=v;}
    PROPERTY(Object*, Target, m_target){m_target=v;}
};

#endif /* defined(__DollEngine__Action__) */
