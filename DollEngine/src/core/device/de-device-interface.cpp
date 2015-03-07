//
//  de-device-interface.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-device-interface.h"
#include "de.h"

NAMESPACE_DE_DEVICE
static Window* s_window_instance = null;
static Transform* s_main_trans = null;

void initialize()
{
    de::storage::searchers()->reset();
    de::storage::searchers()->setResourcePath(de::storage::get_app_path());
    de::storage::searchers()->setDocumentPath(de::storage::get_data_path());
    de::storage::searchers()->setCachePath(de::storage::get_cache_path());
    de::fonts::Fonts::GetInstance()->initDefautFont();
}

Window* window(Window*v)
{
    if (v) {
        s_window_instance = v;
    }
    return s_window_instance;
}

Transform* main_trans()
{
    if (!s_main_trans) {
        s_main_trans = new Transform();
    }
    return s_main_trans;
}


void reset_viewport()
{
    
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