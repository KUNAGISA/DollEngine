//
//  TjsWindow.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsWindow.h"


NCB_REGISTER_CLASS_DIFFER(Window,TjsWindow)
{
    TJS_FACTORY
    NCB_METHOD(initialize);
}