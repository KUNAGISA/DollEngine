//
//  ActionManager.h
//  DollEngine
//
//  Created by DollStudio on 15/1/17.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__ActionManager__
#define __DollEngine__ActionManager__

#include "COM.h"
#include "Action.h"

class ActionManager: public COM
{
public:
    Shared(ActionManager)
    ActionManager();
    ~ActionManager();
    void trigger();
    
    void addAction(Action* action);
    void removeAction(Action* action);
    
    
public:
    void moveTo(Object* target, float time, float x, float y);
    void fadeTo(Object* target, float time, float opt);
protected:
    set<Action*> m_allActions;
};

#endif /* defined(__DollEngine__ActionManager__) */
