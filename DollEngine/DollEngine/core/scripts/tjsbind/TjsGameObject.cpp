//
//  TjsGameObject.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsGameObject.h"
#include "TjsPainter.h"

void TjsGameObject::addCOM(TJS::iTJSDispatch2 *v)
{
    tTJSCustomObject* obj2 = dynamic_cast<tTJSCustomObject*>(v);
    TjsPainter* obj1 = TJS_GET_OBJECT(TjsPainter, v);
    if (obj1) {
        addComponent(obj1);
        return;
    }
    TjsComponent* obj = TJS_GET_OBJECT(TjsComponent, v);
    if (obj) {
        addComponent(obj);
        return;
    }
}

NCB_REGISTER_CLASS_DIFFER(GameObject,TjsGameObject)
{
    TJS_FACTORY
    NCB_METHOD(addChild);
    NCB_METHOD(addCOM);
    NCB_PROPERTY_RO(parent, getParent);
    NCB_PROPERTY(z,setZ,getZ);
    NCB_PROPERTY(enabled,getEnabled,setEnabled);
    NCB_PROPERTY(visible,getVisible,setVisible);
    NCB_PROPERTY(left,getLeft,setLeft);
    NCB_PROPERTY(top,getTop,setTop);
    NCB_PROPERTY(width,getWidth,setWidth);
    NCB_PROPERTY(height,getHeight,setHeight);
    NCB_PROPERTY(anchorX,getAnchorX,setAnchorX);
    NCB_PROPERTY(anchorY,getAnchorY,setAnchorY);
    NCB_PROPERTY(scaleX,getScaleX,setScaleX);
    NCB_PROPERTY(scaleY,getScaleY,setScaleY);
    NCB_PROPERTY(scale,getScale,setScale);
    NCB_PROPERTY(rotationX,getRotationX,setRotationX);
    NCB_PROPERTY(rotationY,getRotationY,setRotationY);
    NCB_PROPERTY(rotationZ,getRotationZ,setRotationZ);
    NCB_PROPERTY(rotation,getRotation,setRotation);
    NCB_PROPERTY(ignoreAnchorPoint,getIgnoreAnchorPoint,setIgnoreAnchorPoint);
}