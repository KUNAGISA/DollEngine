//
//  TjsTouchListener.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/29.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsTouchListener.h"

NCB_REGISTER_CLASS_DIFFER(Touch, TjsTouchListener)
{
    TJS_FACTORY_COM
    NCB_METHOD(addToManager);
    NCB_PROPERTY(focus,getFocus,setFocus);
    NCB_PROPERTY(global,getGlobal,setGlobal);
    NCB_PROPERTY(ignore,getIgnore,setIgnore);
    NCB_PROPERTY(swallow,getSwallow,setSwallow);
    NCB_PROPERTY(priority,getPriority,setPriority);
    NCB_PROPERTY(moved,getMoved,setMoved);
};

