//
//  TjsCharacter.h
//  DollEngine
//
//  Created by DollStudio on 15/7/28.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsCharacter__
#define __DollEngine__TjsCharacter__

#include "TjsPainter.h"
#include "Character.h"

TJS_NCB_COM(Character)

void setText(tTJSVariant v){
    TJS_STRING(v, str);
    Character::setText(str);
}
tTJSVariant getText(){
    TJS_WSTRING(m_text,str);
    return str.c_str();
}
void setFontName(tTJSVariant v){
    TJS_STRING(v, str);
    Character::setFontName(str);
}
tTJSVariant getFontName(){
    TJS_WSTRING(m_fontName,str);
    return str.c_str();
}

};

#endif /* defined(__DollEngine__TjsCharacter__) */
