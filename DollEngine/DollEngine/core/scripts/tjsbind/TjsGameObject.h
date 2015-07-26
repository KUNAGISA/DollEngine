//
//  TjsGameObject.h
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsGameObject__
#define __DollEngine__TjsGameObject__

#include "TjsBind.h"
#include "GameObject.h"

TJS_NCB(GameObject){}
void addChild(iTJSDispatch2* v) {
    TjsGameObject* obj = TJS_GET_OBJECT(TjsGameObject, v);
    GameObject::addChild(obj);
}
iTJSDispatch2* getParent() {
    auto obj = dynamic_cast<TjsGameObject*>(GameObject::getParent());
    if (obj) {
        return obj->_self;
    } else {
        return null;
    }
}
void addCOM(iTJSDispatch2* v);
};

#endif /* defined(__DollEngine__TjsGameObject__) */
