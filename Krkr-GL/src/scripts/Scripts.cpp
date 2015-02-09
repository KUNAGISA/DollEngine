//
//  Scripts.cpp
//  DollEngine
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Scripts.h"

#if(SCRIPT_TYPE == SCRIPT_TYPE_TJS2)
#include "ScriptsTJS.h"
static ScriptsTJS* s_instance = null;
#else

#endif

Scripts::Scripts()
{
}

Scripts* Scripts::GetInstance()
{
    if(!s_instance)
    {
#if(SCRIPT_TYPE == SCRIPT_TYPE_TJS2)
        s_instance = new ScriptsTJS();
#else
        
#endif
        s_instance->init();
    }
    return s_instance;
}

void Scripts::Delloc()
{
    if(s_instance)
    {
        delete s_instance;
        s_instance = null;
    }
}
