//
//  TjsPainter.h
//  DollEngine
//
//  Created by DollStudio on 15/7/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsPainter__
#define __DollEngine__TjsPainter__

#include "TjsCOM.h"
#include "Painter.h"

TJS_NCB_COM(Painter)

bool loadImages(tTJSVariant v1,tTJSVariant v2)
{
    TJS_STRING(v1, path);
    TJS_STRING(v2, plist);
    return Painter::loadImages(path,plist);
}
bool loadImageWithMargin(tTJSVariant v,float l,float t,float r,float b)
{
    TJS_STRING(v, path)
    return Painter::loadImageWithMargin(path, l, t, r, b);
}
void setProgramTJS(tTJSVariant v)
{
    TJS_STRING(v, name);
    Painter::setProgram(name);
}
};

#endif /* defined(__DollEngine__TjsPainter__) */
