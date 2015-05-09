//
//  BaseComp.h
//  DollEngine
//
//  Created by DollStudio on 15/4/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__BaseComp__
#define __DollEngine__BaseComp__

#include "Units.h"
#include "GameObject.h"

DE_BEGIN

enum COMP_TYPE
{
    COMP_UNKNOW=0,
    COMP_UPDATE,
    COMP_PAINT,
    COMP_TOUCH
};

class BaseComp
{
public:
    BaseComp();
    virtual ~BaseComp();
    virtual void update(){}
    void release();
    
    PROPERTY(bool, Enabled, m_enabled){m_enabled=v;}
    PROPERTY(GameObject*, Object, m_object){m_object=v;}
    PROPERTY(bool, IsReleased, m_isReleased){m_isReleased=v;}
    PROPERTY_RO(COMP_TYPE, Type, m_type);
    PROPERTY_CONST(string, CompName, m_compName){m_compName=v;}
};

DE_END

#endif /* defined(__DollEngine__BaseComp__) */
