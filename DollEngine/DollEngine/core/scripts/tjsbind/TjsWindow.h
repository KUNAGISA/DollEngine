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
#include "Window.h"
#include "TjsGameObject.h"

TJS_NCB(Window){}
tTJSVariant getWorld() {
    auto obj = dynamic_cast<TjsGameObject*>(Window::getWorld());
    if (obj) {
        return obj->_self;
    } else {
        return tTJSVariant();
    }
}
void setWorld(tTJSVariant v){
    if (v.Type() == tvtVoid) {
        Window::setWorld(null);
        return;
    }
    TjsGameObject* obj = TJS_GET_OBJECT(TjsGameObject, v.AsObject());
    Window::setWorld(obj);
}
void setTitle(tTJSVariant v){
    TJS_STRING(v, str);
    Window::setTitle(str);
}
tTJSVariant getTitle(){
    TJS_WSTRING(m_title,str);
    return str.c_str();
}
};

#endif /* defined(__DollEngine__TjsWindow__) */
