//
//  TjsPainter.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsPainter.h"

NCB_REGISTER_CLASS_DIFFER(Painter, TjsPainter)
{
    TJS_FACTORY_COM
    NCB_METHOD(loadImages);
    NCB_METHOD(loadSize);
    NCB_METHOD(setSizeToImageSize);
    NCB_METHOD(setColor);
    NCB_METHOD(setGradientColor);
    NCB_PROPERTY(paintWidth,getPaintWidth,setPaintWidth);
    NCB_PROPERTY(paintHeight,getPaintHeight,setPaintHeight);
    NCB_PROPERTY(scale9,getScale9,setScale9);
    NCB_PROPERTY(scale9B,getScale9B,setScale9B);
    NCB_PROPERTY(scale9L,getScale9L,setScale9L);
    NCB_PROPERTY(scale9R,getScale9R,setScale9R);
    NCB_PROPERTY(scale9T,getScale9T,setScale9T);
};
