//
//  TjsPainter.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsImage.h"
#include "TjsTransform.h"

void TjsImage::paint(tTJSVariant trans)
{
    if(m_info == NULL) return;
    TjsTransform* obj = TJS_GET_OBJECT(TjsTransform,trans.AsObjectNoAddRef());
    Image::paint(obj);
}


NCB_REGISTER_CLASS_DIFFER(Image, TjsImage)
{
    TJS_FACTORY
    NCB_METHOD(loadImages);
    NCB_METHOD(freeImage);
    NCB_METHOD(paint);
//    NCB_METHOD(setSizeToImageSize);
//    NCB_METHOD(setColor);
//    NCB_METHOD(setGradientColor);
//    NCB_METHOD(setMargin);
//    NCB_METHOD(setSizeToOrginSize);
    NCB_METHOD_DIFFER(setProgram, setProgramTJS);
    NCB_PROPERTY(paintWidth,getPaintWidth,setPaintWidth);
    NCB_PROPERTY(paintHeight,getPaintHeight,setPaintHeight);
    NCB_PROPERTY(startOpacity,getStartOpacity,setStartOpacity);
    NCB_PROPERTY(endOpacity,getEndOpacity,setEndOpacity);
    NCB_PROPERTY(startColor,getStartColor,setStartColor);
    NCB_PROPERTY(endColor,getEndColor,setEndColor);
//    NCB_PROPERTY(scale9,getScale9,setScale9);
//    NCB_PROPERTY(scale9B,getScale9B,setScale9B);
//    NCB_PROPERTY(scale9L,getScale9L,setScale9L);
//    NCB_PROPERTY(scale9R,getScale9R,setScale9R);
//    NCB_PROPERTY(scale9T,getScale9T,setScale9T);
};
