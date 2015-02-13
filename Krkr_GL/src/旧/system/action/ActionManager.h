//
//  ActionManager.h
//  Krkr_GL
//
//  Created by DollStudio on 15/1/17.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__ActionManager__
#define __Krkr_GL__ActionManager__

#include "COM.h"
#include "ActionBase.h"

class ActionManager: public COM
{
public:
    Shared(ActionManager)
    ActionManager();
    ~ActionManager();
    void trigger();
    
    void addAction(ActionBase* action);
    void removeAction(ActionBase* action);
    
    
public:
    void moveTo(Object* target, float time, float x, float y);
    void fadeTo(Object* target, float time, float opt,function<void()> callback);
protected:
    set<ActionBase*> m_allActions;
};

#endif /* defined(__Krkr_GL__ActionManager__) */
