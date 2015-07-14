//
//  CompManager.h
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DECore__CompManager__
#define __DECore__CompManager__

#include "CoreUnits.h"
#include "Component.h"

DE_BEGIN

class CompManager
{
public:
    CompManager();
    Shared(CompManager)
public:
    void addTouchComp(Component* comp);
    void removeTouchComp(Component* comp);
    
public:
    void addReleaseComp(Component* comp);
    void removeReleaseComp(Component* comp);
    
protected:
    set<Component*> m_releasePools;
    list<Component*> m_touchComps;
};

DE_END

#endif /* defined(__DECore__CompManager__) */
