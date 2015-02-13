//
//  TJSCharLabel.cpp
//  Krkr_GL
//
//  Created by ios开发－b on 14/12/27.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSCharLabel.h"

NCB_REGISTER_CLASS_DIFFER(CharLabel, TJSCharLabel)
{
    iTJS_FACTORY_COM
    NCB_PROPERTY(fontName, getFontName, setFontName);
    NCB_PROPERTY(fontSize, getFontSize, setFontSize);
    NCB_PROPERTY(string, getString, setString);
    NCB_PROPERTY(x, getX, setX);
    NCB_PROPERTY(y, getY, setY);
    NCB_PROPERTY(offsetY, getOffsetY, setOffsetY);
    NCB_PROPERTY(bottom, getBottom, setBottom);
    NCB_PROPERTY_RO(imageHeight, getImageHeight);
    NCB_PROPERTY_RO(width, getWidth);
    NCB_PROPERTY_RO(bearingY, getBearingY);
};

