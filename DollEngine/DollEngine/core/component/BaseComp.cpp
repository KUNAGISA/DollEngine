//
//  BaseComp.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "BaseComp.h"
#include "AutoReleasePool.h"
#include "GameObject.h"

DE_BEGIN


BaseComp::BaseComp()
:m_type(COMP_UNKNOW)
,m_isReleased(false)
,m_object(null)
,m_enabled(true)
{
    
}

BaseComp::~BaseComp()
{
    if (!m_isReleased) {
        AutoReleasePool::GetInstance()->removeAutoRelease(this);
    }
}

void BaseComp::release()
{
    if (!m_isReleased) {
        m_isReleased=true;
        AutoReleasePool::GetInstance()->addAutoRelease(this);
    }
}

DE_END
