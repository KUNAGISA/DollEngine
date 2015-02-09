//
//  TJSRTTCanvas.cpp
//  DollEngine
//
//  Created by DollStudio on 15/1/12.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TJSRTTCanvas.h"

void TJSRTTCanvas::render(tTJSVariant v,float x,float y)
{
    TJSObject* src = iTJSGetObject(TJSObject, v.AsObjectNoAddRef());
    RTTCanvas::render(src, x, y);
}


NCB_REGISTER_CLASS_DIFFER(RTTCanvas, TJSRTTCanvas)
{
    iTJS_FACTORY_COM
    NCB_METHOD(render);
    NCB_PROPERTY(opacity, getOpacity, setOpacity);
    NCB_PROPERTY(width, getWidth, setWidth);
    NCB_PROPERTY(height, getHeight, setHeight);
};
