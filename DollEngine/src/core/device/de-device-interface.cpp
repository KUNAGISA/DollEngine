//
//  de-device-interface.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-device-interface.h"

NAMESPACE_DE_DEVICE
static device_window* s_window_instance = null;

device_window* window()
{
    return s_window_instance;
}

void new_window()
{
    if (!s_window_instance) {
        s_window_instance = new device_window();
    }
}

float get_inner_width()
{
    ASSERT(s_window_instance);
    return s_window_instance->getInnerWidth();
}

float get_inner_height()
{
    ASSERT(s_window_instance);
    return s_window_instance->getInnerHeight();
}

NAMESPACE_DE_END2