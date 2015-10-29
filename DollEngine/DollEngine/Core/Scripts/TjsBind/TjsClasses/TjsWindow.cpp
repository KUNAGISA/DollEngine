//
//  TjsWindow.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsWindow.h"


NCB_REGISTER_CLASS_DIFFER(Window,TjsQtWindow)
{
    TJS_FACTORY
    NCB_METHOD(setSize);
    NCB_PROPERTY(fullScreen, getFullScreen, setFullScreen);
    NCB_PROPERTY(title, getTitle, setTitle);
    NCB_PROPERTY(visible, getVisible, setVisible);
    NCB_PROPERTY_RO(width, getWidth);
    NCB_PROPERTY_RO(height, getHeight);
}
