//
//  TjsPainter.h
//  DollEngine
//
//  Created by DollStudio on 15/7/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsPainter__
#define __DollEngine__TjsPainter__

#include "TjsBind.h"
#include "Image.h"

TJS_NCB(Image){}

bool loadImages(tTJSVariant v1,tTJSVariant v2)
{
    TJS_STRING(v1, path);
    TJS_STRING(v2, plist);
    return Image::loadImages(path,plist);
}

void setProgramTJS(tTJSVariant v)
{
    TJS_STRING(v, name);
    Image::setProgram(name);
}

void paint(tTJSVariant trans);
};

#endif /* defined(__DollEngine__TjsPainter__) */
