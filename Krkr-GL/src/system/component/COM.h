//
//  COM.h
//  DollEngine
//
//  Created by DollStudio on 14/11/9.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__COM__
#define __DollEngine__COM__

#include "Functions.h"

class Object;
class TouchEvent;
class COM
{
public:
    //组件触发功能的时机
    enum TRIGGER_TYPE
    {
        TRIGGER_NONE = 0,
        TRIGGER_UPDATE,
        TRIGGER_TOUCH,
        TRIGGER_NETWORK,
    };
    COM();
    virtual ~COM();
    virtual void trigger(){}
    virtual void release();
    virtual COM* clone();
    virtual void assign(COM* src);
    
public:
//    PROPERTY(Object*, Object, m_object){m_object=v;}
    PROPERTY(Object*, Object, m_object){m_object=v;}
    PROPERTY(bool, Enabled, m_enabled);
    //    PROPERTY(uint, UniqueKey, m_uniqueKey){m_uniqueKey=v;}
    PROPERTY_CONST(wstring, ComName, m_comName){m_comName=v;}
    PROPERTY(bool, AutoRelease, m_autoRelease){m_autoRelease=v;}
    PROPERTY(double, Time, m_time){m_time=v;}
    PROPERTY(int, TriggerType, m_triggerType){m_triggerType=v;}
    PROPERTY(list<TouchEvent*>::iterator, Iter, m_iter){m_iter=v;}
};

#endif /* defined(__DollEngine__COM__) */
