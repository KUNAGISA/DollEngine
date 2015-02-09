//
//  TJSCOM.cpp
//  DollEngine
//
//  Created by DollStudio on 14/11/23.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSCOM.h"

void TJSCOM::trigger()
{
    iTJSEventCall(trigger,0);
}

NCB_REGISTER_CLASS_DIFFER(COM, TJSCOM)
{
    iTJS_FACTORY_COM
    NCB_METHOD(trigger);
    NCB_PROPERTY(time, getTime, setTime);
};