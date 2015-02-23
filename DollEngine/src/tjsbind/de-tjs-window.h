//
//  de-tjs-window.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_tjs_window__
#define __DollEngine__de_tjs_window__

#include "de-tjs-bind.h"

class deTJSWindow
:public deTJSClass
,public de::device::Window
{
public:
    TJS_NCB(deTJSWindow);
    void initWidget();
};

#endif /* defined(__DollEngine__de_tjs_window__) */
