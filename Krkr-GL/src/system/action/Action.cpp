//
//  Action.cpp
//  DollEngine
//
//  Created by DollStudio on 15/1/17.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Action.h"
#include "ActionManager.h"

Action::Action()
:m_perc(0)
,m_target(null)
,m_startTime(0)
,m_time(0)
{
    
}

Action::~Action()
{
    ActionManager::GetInstance()->removeAction(this);
    if (getTarget())
    {
        getTarget()->removeAction(this);
    }
}
