//
//  AsyncTrigger.cpp
//  DollEngine
//
//  Created by DollStudio on 14/11/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "AsyncTrigger.h"

AsyncTrigger::AsyncTrigger()
{
    setComName(L"AsyncTrigger");
    setTriggerType(TRIGGER_UPDATE);
}

void AsyncTrigger::trigger()
{
    if (m_handler) {
        m_handler();
    }
    release();
}
