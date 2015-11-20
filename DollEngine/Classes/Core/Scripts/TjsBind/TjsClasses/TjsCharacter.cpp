//
//  TjsCharacter.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/28.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsCharacter.h"
#include "TjsTransform.h"


void TjsCharacter::paint(tTJSVariant trans)
{
    if(m_info == NULL) return;
    TjsTransform* obj = TJS_GET_OBJECT(TjsTransform,trans.AsObjectNoAddRef());
    TjsCharacter::paint(obj);
}

NCB_REGISTER_CLASS_DIFFER(Character, TjsCharacter)
{
    TJS_FACTORY
    NCB_METHOD(setSizeToImageSize);
    NCB_PROPERTY(fontName,getFontName,setFontName);
    NCB_PROPERTY(text,getText,setText);
    NCB_PROPERTY(paintWidth,getPaintWidth,setPaintWidth);
    NCB_PROPERTY(paintWidth,getPaintWidth,setPaintWidth);
    NCB_PROPERTY(paintHeight,getPaintHeight,setPaintHeight);
    NCB_PROPERTY(startOpacity,getStartOpacity,setStartOpacity);
    NCB_PROPERTY(endOpacity,getEndOpacity,setEndOpacity);
    NCB_PROPERTY(startColor,getStartColor,setStartColor);
    NCB_PROPERTY(endColor,getEndColor,setEndColor);
};
