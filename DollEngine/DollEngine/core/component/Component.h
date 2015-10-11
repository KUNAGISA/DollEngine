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
#include "AppInfo.h"

DE_BEGIN


enum COMP_TYPE
{
    COMP_UNKNOW=0,
    COMP_UPDATE,
    COMP_PAINT,
    COMP_TOUCH
};

class Component
{
public:
    Component();
    virtual ~Component();
    virtual void update(){}
    void release();
    
    PROPERTY(bool, Enabled, m_enabled){m_enabled=v;}
    PROPERTY(bool, IsReleased, m_isReleased){m_isReleased=v;}
    PROPERTY(float, Time, m_time){m_time=v;}
    PROPERTY(int, Type, m_type){m_type=v;}
    PROPERTY_CONST(String, CompName, m_compName){m_compName=v;}
};

DE_END

#endif /* defined(__DollEngine__Component__) */
