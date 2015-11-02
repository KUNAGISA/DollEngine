//
//  TjsWindow.h
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsWindow__
#define __DollEngine__TjsWindow__

#include "TjsBind.h"
#ifdef __QT__
#include "QtWindow.h"
#else
#include "Window.h"
#endif
TJS_NCB(Window){}
void setTitle(tTJSVariant v){
    TJS_STRING(v, str);
    Window::setTitle(str);
}
tTJSVariant getTitle(){
    return m_title.c_str();
}

};

#endif /* defined(__DollEngine__TjsWindow__) */
