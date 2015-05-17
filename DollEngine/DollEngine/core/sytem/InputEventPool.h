//
//  InputEventPool.h
//  DollEngine
//
//  Created by DollStudio on 15/5/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__InputEventPool__
#define __DollEngine__InputEventPool__

#include "Units.h"
#include "InputEvent.h"

DE_BEGIN

class InputEventPool
{
public:
    Shared(InputEventPool)
    
    static list<InputEvent*>::iterator InputIterEnd();
    /*鼠标点击事件*/
    void clearTouches();
    void addTouch(InputEvent* event);
    void removeTouch(InputEvent* event);
    bool onMouseDown(float x,float y );
    void onMouseUp(float x,float y );
    void onMouseMove(float x,float y );
private:
    list<InputEvent*> m_allInputs;
    vector<InputEvent*> m_validTouches;
};

DE_END

#endif /* defined(__DollEngine__InputEventPool__) */
