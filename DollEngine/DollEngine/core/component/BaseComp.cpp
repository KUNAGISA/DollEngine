//
//  BaseComp.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "BaseComp.h"
#include "AutoReleaseManager.h"
#include "GameObject.h"

DE_BEGIN


BaseComp::BaseComp()
:m_type(COMP_UNKNOW)
,m_isReleased(false)
,m_object(null)
{
    
}

BaseComp::~BaseComp()
{
    if (!m_isReleased) {
        AutoReleaseManager::GetInstance()->removeAutoRelease(this);
    }
}

void BaseComp::release()
{
    if (!m_isReleased) {
        m_isReleased=true;
        AutoReleaseManager::GetInstance()->addAutoRelease(this);
    }
}

DE_END
