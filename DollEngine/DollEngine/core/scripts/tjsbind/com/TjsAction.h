//
//  TjsAction.h
//  DollEngine
//
//  Created by DollStudio on 15/8/5.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsAction__
#define __DollEngine__TjsAction__

#include "TjsBind.h"
#include "Action.h"
#include "TjsGameObject.h"

TJS_NCB_COM(Action)
tTJSVariant getObject() {
    auto obj = dynamic_cast<TjsGameObject*>(Action::getObject());
    if (obj) {
        return obj->_self;
    } else {
        return tTJSVariant();
    }
}
void setObject(tTJSVariant v){
    if (v.Type() == tvtVoid) {
        auto obj = dynamic_cast<TjsGameObject*>(Action::getObject());
        if(obj){
            obj->_self->Release();
        }
        Action::setObject(null);
        return;
    }
    TjsGameObject* obj = TJS_GET_OBJECT(TjsGameObject, v.AsObject());
    Action::setObject(obj);
}

virtual void onActionStop(){
    TJS_EVENT_CALL(onActionStop, 0);
}
virtual void onAction(float p){
    tTJSVariant v1=p;
    TJS_EVENT_CALL(onAction, 1,&v1);
}
};
#endif /* defined(__DollEngine__TjsAction__) */
