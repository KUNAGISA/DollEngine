//
//  ActionManager.cpp
//  Krkr_GL
//
//  Created by DollStudio on 15/1/17.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "ActionManager.h"
#include "FadeTo.h"

ActionManager::ActionManager()
{
    setComName(L"ActionManager");
    setTriggerType(TRIGGER_UPDATE);
    setEnabled(true);
}

ActionManager::~ActionManager()
{
    set<ActionBase*> clone = m_allActions;
    for (auto iter = clone.begin();
         iter != clone.end(); ++iter)
    {
        delete (*iter);
    }
    m_allActions.clear();
}

void ActionManager::trigger()
{
    vector<ActionBase*> removed;
    for (auto action : m_allActions) {
        float t = getTime()-action->getStartTime();
        action->setPerc( t / action->getTime());
        action->update();
        if (action->getPerc() >= 1)
        {
            action->onStop();
            removed.push_back(action);
        }
    }
    for (auto action: removed) {
        delete action;
    }
}

void ActionManager::addAction(ActionBase* action)
{
    action->setStartTime(getTime());
    m_allActions.insert(action);
}

void ActionManager::removeAction(ActionBase* action)
{
    m_allActions.erase(action);
}

void ActionManager::moveTo(Object* target, float time, float x, float y)
{
    
}

void ActionManager::fadeTo(Object* target, float time, float opt,function<void()> callback)
{
    ASSERT(target);
    FadeTo* fade = new FadeTo();
    target->addAction(fade);
    fade->setTime(time);
    fade->setBeginOpacity(target->getOpacity());
    fade->setEndOpacity(opt);
    addAction(fade);
}