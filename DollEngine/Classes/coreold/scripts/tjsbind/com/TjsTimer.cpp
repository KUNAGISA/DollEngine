//
//  TjsTimer.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsTimer.h"

NCB_REGISTER_CLASS_DIFFER(COMTimer, TjsTimer)
{
    TJS_FACTORY_COM
    NCB_PROPERTY(interval, getInterval, setInterval);
    NCB_PROPERTY_RO(activeCount, getActiveCount);
};
