//
//  TjsAction.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/5.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsAction.h"

NCB_REGISTER_CLASS_DIFFER(Action, TjsAction)
{
    TJS_FACTORY_COM
    NCB_METHOD(start);
    NCB_METHOD(stop);
    NCB_PROPERTY(object, getObject, setObject);
    NCB_PROPERTY(pause, getPause, setPause);
    NCB_PROPERTY(targetTime, getTargetTime, setTargetTime);
    NCB_PROPERTY(timeScale, getTimeScale, setTimeScale);
};