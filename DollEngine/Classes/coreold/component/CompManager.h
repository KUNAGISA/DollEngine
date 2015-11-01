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

class TouchListener;

class CompManager
{
public:
    CompManager();
    Shared(CompManager)
    
public:
    void addUpdateComp(Component* comp);
    void removeUpdateComp(Component* comp);
    void updateComp();
    
public:
    void addGlobalTouchComp(Component* comp);
    void removeGlobalTouchComp(Component* comp);
    void addTouchComp(Component* comp);
    void clearTouches();
    
    bool onMouseDown(float x,float y );
    void onMouseUp(float x,float y );
    void onMouseMove(float x,float y );
    
public:
    void addReleaseComp(Component* comp);
    void removeReleaseComp(Component* comp);
    void releaseComp();
public:
protected:
    set<Component*> m_releasePools;
    list<Component*> m_touchComps;
    set<Component*> m_globalTouchs;
    vector<TouchListener*> m_validTouches;
    set<Component*> m_updatePools;
    double m_lastTime;
};

DE_END

#endif /* defined(__DECore__CompManager__) */
