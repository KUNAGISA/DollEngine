//
//  COMManager.h
//  Krkr_GL
//
//  Created by ios开发－b on 14/12/25.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__COMManager__
#define __Krkr_GL__COMManager__

#include "COM.h"

class TouchEvent;
class COMManager
{
public:
    COMManager();
    Shared(COMManager);
    
    void addRelease(COM* com);
    void addUpdate(COM* com);
    void removeUpdate(COM* com);
    void addTouch(TouchEvent* com);
    void removeTouch(TouchEvent* com);
    void addDisableObject(Object* obj);
public:
    void release();
    void update();
    void sortTouch();
    bool touchBegan(float x,float y);
    void touchMoved(float x,float y);
    void touchEnded(float x,float y);
    void touchClick(float x,float y);
public:
    list<TouchEvent*>::iterator end();
//    PROPERTY(bool, TouchMoved, m_touchMoved){m_touchMoved=v;}
private:
    set<COM*> m_releaseCom;
    set<COM*> m_updateCom;
    list<TouchEvent*> m_touchCOM;
    vector<TouchEvent*> m_validTouch;
    list<Object*> m_disableObject;
    double m_nowTime;
};

#endif /* defined(__Krkr_GL__COMManager__) */
