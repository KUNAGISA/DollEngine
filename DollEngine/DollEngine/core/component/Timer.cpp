//
//  Timer.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Timer.h"

DE_BEGIN

Timer::Timer()
{
    setCompName("Timer");
    m_type = COMP_UPDATE;
    m_enabled = false;
}

Timer::~Timer()
{
    setEnabled(false);
}

void Timer::setEnabled(bool v)
{
    if (v!=m_enabled) {
        m_enabled = v;
        if (v) {
            m_activeCount = 0;
            m_time = 0;
            m_nextTime = m_interval;
        }
        else {
        }
    }
}

void Timer::update()
{
    if (m_nextTime <= m_time) {
        m_nextTime += m_interval;
        m_activeCount++;
        onTimer();
    }
}

DE_END