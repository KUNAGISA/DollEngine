//
//  CompManager.cpp
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CompManager.h"

DE_BEGIN

CompManager::CompManager()
{
    
}

void CompManager::addTouchComp(Component* comp)
{
    m_touchComps.push_back(comp);
    CompIter end = m_touchComps.end();
    --end;
    comp->setCompIter(end);
}

void CompManager::removeTouchComp(Component* comp)
{
    m_touchComps.erase(comp->getCompIter());
    comp->setCompIter(Component::EndIter());
}

void CompManager::addReleaseComp(DE::Component *comp)
{
    m_releasePools.insert(comp);
    switch (comp->getType()) {
        case COMP_TOUCH:
        {
            removeTouchComp(comp);
        }
            break;
            
        default:
            break;
    }
}

void CompManager::removeReleaseComp(DE::Component *comp)
{
    m_releasePools.erase(comp);
}

DE_END
