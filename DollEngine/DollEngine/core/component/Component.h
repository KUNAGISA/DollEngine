//
//  Component.h
//  DollEngine
//
//  Created by DollStudio on 15/4/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Component__
#define __DollEngine__Component__

#include "CoreUnits.h"

DE_BEGIN

class GameObject;

enum COMP_TYPE
{
    COMP_UNKNOW=0,
    COMP_UPDATE,
    COMP_PAINT,
    COMP_TOUCH
};

class Component;
typedef list<Component*>::iterator CompIter;

class Component
{
public:
    Component();
    virtual ~Component();
    virtual void update(){}
    void release();
    
    static CompIter EndIter();
    
    PROPERTY(bool, Enabled, m_enabled){m_enabled=v;}
    PROPERTY(GameObject*, Object, m_object){m_object=v;}
    PROPERTY(bool, IsReleased, m_isReleased){m_isReleased=v;}
    PROPERTY(float, Time, m_time){m_time=v;}
    PROPERTY(int, Type, m_type){m_type=v;}
    PROPERTY(CompIter, CompIter, m_compIter){m_compIter=v;}
    PROPERTY_CONST(string, CompName, m_compName){m_compName=v;}
};

DE_END

#endif /* defined(__DollEngine__Component__) */
