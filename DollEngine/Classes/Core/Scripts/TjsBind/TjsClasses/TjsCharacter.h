//
//  TjsCharacter.h
//  DollEngine
//
//  Created by DollStudio on 15/7/28.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsCharacter__
#define __DollEngine__TjsCharacter__

#include "TjsImage.h"
#include "Character.h"

TJS_NCB(Character){}

void paint(tTJSVariant trans);

void setText(tTJSVariant v){
    TJS_STRING(v, str);
    Character::setText(str);
}
tTJSVariant getText(){
    return m_text.c_wstr();
}
void setFontName(tTJSVariant v){
    TJS_STRING(v, str);
    Character::setFontName(str);
}
tTJSVariant getFontName(){
    return m_fontName.c_wstr();
}

};

#endif /* defined(__DollEngine__TjsCharacter__) */
