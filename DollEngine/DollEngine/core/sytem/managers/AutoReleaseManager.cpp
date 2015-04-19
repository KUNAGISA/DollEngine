//
//  AutoReleaseManager.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "AutoReleaseManager.h"


DE_BEGIN

void AutoReleaseManager::autoRelease()
{
    set<BaseComp*> temp = m_comps;
    for (BaseComp* comp : temp) {
        delete comp;
    }
    m_comps.clear();
}

void AutoReleaseManager::addAutoRelease(BaseComp* comp)
{
    m_comps.insert(comp);
}

void AutoReleaseManager::removeAutoRelease(DE::BaseComp *comp)
{
    m_comps.erase(comp);
}

DE_END