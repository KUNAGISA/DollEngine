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

static list<Component*> s_endCompList;

CompIter Component::EndIter()
{
    return s_endCompList.end();
}

Component::Component()
:m_type(COMP_UNKNOW)
,m_isReleased(false)
,m_object(null)
,m_enabled(true)
,m_compIter(Component::EndIter())
{
    
}

Component::~Component()
{
    if (!m_isReleased) {
        CompManager::GetInstance()->removeReleaseComp(this);
    }
}

void Component::release()
{
    if (!m_isReleased) {
        m_isReleased=true;
        CompManager::GetInstance()->addReleaseComp(this);
    }
}

DE_END
