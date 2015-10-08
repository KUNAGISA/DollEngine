//
//  Component.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Component.h"
#include "CompManager.h"
//#include "GameObject.h"

DE_BEGIN

Component::Component()
:m_type(COMP_UNKNOW)
,m_isReleased(false)
,m_enabled(true)
,m_time(0)
{
    
}

Component::~Component()
{
    CompManager::GetInstance()->removeReleaseComp(this);
}

void Component::release()
{
    if (!m_isReleased) {
        m_isReleased=true;
        CompManager::GetInstance()->addReleaseComp(this);
    }
}

DE_END
