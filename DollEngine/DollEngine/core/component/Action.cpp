//
//  Action.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/5.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Action.h"
#include "CompManager.h"

DE_BEGIN


Action::Action()
:m_pause(false)
,m_targetTime(0)
,m_timeScale(1)
,m_lastTime(0)
,m_running(false)
{
    setCompName("Action");
    setType(COMP_UPDATE);
    m_enabled = false;
}

Action::~Action()
{
}

void Action::setEnabled(bool v)
{
    if (v!=m_enabled) {
        m_enabled = v;
        if (v) {
            m_time = 0;
            m_lastTime = 0;
            CompManager::GetInstance()->addUpdateComp(this);
        }
        else {
            CompManager::GetInstance()->removeUpdateComp(this);
        }
    }
}

void Action::start()
{
    if (m_targetTime < 0.00001f) {
        m_targetTime = 0;
        onAction(1);
        onActionStop();
        return;
    }
    setEnabled(true);
    setRunning(true);
}

void Action::stop()
{
    setEnabled(false);
    setRunning(false);
}

void Action::update()
{
    if (m_pause) {
        m_time = m_lastTime;
        return;
    }
    m_lastTime = m_time;
    float dt = m_time / m_targetTime;
    dt *= m_timeScale;
    if (dt >= 1) {
        setRunning(false);
        stop();
        onAction(1);
        onActionStop();
    }
    else
    {
        onAction(dt);
    }
}

DE_END

