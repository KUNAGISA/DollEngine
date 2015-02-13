//
//  TJSCanvas.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/11/23.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSCanvas.h"

NCB_REGISTER_CLASS_DIFFER(Canvas, TJSCanvas)
{
    iTJS_FACTORY_COM
    NCB_METHOD(colorRect);
    NCB_METHOD(loadImages);
    NCB_METHOD(freeImages);
    NCB_PROPERTY_RO(graphPath, getGraphPath);
    NCB_PROPERTY(opacity, getOpacity,setOpacity);
    NCB_PROPERTY(imageWidth, getImageWidth,setImageWidth);
    NCB_PROPERTY(imageHeight, getImageHeight,setImageHeight);
};