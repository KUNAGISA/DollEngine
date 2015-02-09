//
//  TJSWindow.h
//  Krkr_GL
//
//  Created by DollStudio on 14/12/7.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__TJSWindow__
#define __Krkr_GL__TJSWindow__

#include "GlobalTJS.h"
#include "Krkr_GL.h"
#include "TJSObject.h"

class TJSWindow: public Window
{
public:
    iTJS_NCB(TJSWindow)
    iTJS_PROPERTY_OBJECT(Object, PrimaryLayer, Window);
};
#endif /* defined(__Krkr_GL__TJSWindow__) */
