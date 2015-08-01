//
//  Timer.h
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Timer__
#define __DollEngine__Timer__

#include "Component.h"

DE_BEGIN

class Timer : public Component
{
    
public:
    Timer();
    ~Timer();
    void update();
    virtual void onTimer(){}
    virtual void setEnabled(bool v);
    PROPERTY(float, Interval, m_interval){m_interval=v;}
    PROPERTY(float, NextTime, m_nextTime){m_nextTime=v;}
    PROPERTY_RO(int, ActiveCount, m_activeCount)
};

DE_END

#endif /* defined(__DollEngine__Timer__) */
