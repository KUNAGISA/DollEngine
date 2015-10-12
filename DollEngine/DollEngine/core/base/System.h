//
//  System.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__System__
#define __DollEngine__System__

#include "CoreUnits.h"

DE_BEGIN

class System
{
public:
    System();
    Shared(System)
    virtual ~System();
    
public:
    void mainLoop();
    void startup(); //脚本入口
    
    int64_t GetMilliSeconds();
    double GetSeconds();
    
    PROPERTY(bool,NeedRedraw,m_needRedraw){m_needRedraw=v;}
    PROPERTY(bool,IsError,m_isError){m_isError=v;}
    
protected:
    
};

DE_END

#endif /* defined(__DollEngine__Device__) */
