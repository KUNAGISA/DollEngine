//
//  Action.h
//  DollEngine
//
//  Created by DollStudio on 15/8/5.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Action__
#define __DollEngine__Action__

#include "Component.h"

DE_BEGIN

class Action:public Component
{
public:
    Action();
    virtual ~Action();
    virtual void setEnabled(bool v);
    void start();
    void stop();
    virtual void update();
    virtual void onActionStop(){}
    virtual void onAction(float p){}
    PROPERTY(bool, Pause, m_pause){m_pause=v;}
    PROPERTY(float, TimeScale, m_timeScale){m_timeScale=v;}
    PROPERTY(float, TargetTime, m_targetTime){m_targetTime=v;}
    PROPERTY(bool, Running, m_running){m_running=v;}
protected:
    float m_lastTime;
};

DE_END

#endif /* defined(__DollEngine__Action__) */
