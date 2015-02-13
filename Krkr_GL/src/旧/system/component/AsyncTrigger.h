//
//  AsyncTrigger.h
//  Krkr_GL
//
//  Created by DollStudio on 14/11/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__AsyncTrigger__
#define __Krkr_GL__AsyncTrigger__

#include "COM.h"

class AsyncTrigger:public COM
{
public:
    AsyncTrigger();
    void trigger();
    
    PROPERTY(std::function<void(void)>, Handler, m_handler){m_handler=v;}
};

#endif /* defined(__Krkr_GL__AsyncTrigger__) */
