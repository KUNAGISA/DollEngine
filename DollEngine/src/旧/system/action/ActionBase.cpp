//
//  Action.cpp
//  Krkr_GL
//
//  Created by DollStudio on 15/1/17.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "ActionBase.h"
#include "ActionManager.h"

ActionBase::ActionBase()
:m_perc(0)
,m_target(null)
,m_startTime(0)
,m_time(0)
{
    
}

ActionBase::~ActionBase()
{
    ActionManager::GetInstance()->removeAction(this);
    if (getTarget())
    {
        getTarget()->removeAction(this);
    }
}