//
//  TjsGameObject.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsGameObject.h"
#include "TjsPainter.h"
#include "TjsCharacter.h"
#include "TjsTouchListener.h"

void TjsGameObject::addCOM(TJS::iTJSDispatch2 *v)
{
#define _ADD_COM(TYPE) \
{\
    TYPE* OBJ = TJS_GET_OBJECT(TYPE, v);\
    if (OBJ) {\
        addComponent(OBJ);\
        return;\
    }\
}
    
    _ADD_COM(TjsCharacter)
    _ADD_COM(TjsPainter)
    _ADD_COM(TjsTouchListener)
    _ADD_COM(TjsComponent)
}

NCB_REGISTER_CLASS_DIFFER(GameObject,TjsGameObject)
{
    TJS_FACTORY
    NCB_METHOD(addCOM);
    NCB_METHOD(onPaint);
    NCB_METHOD(onTouchUpdate);
    NCB_METHOD(transform);
    NCB_PROPERTY(parent, getParent,setParent);
    NCB_PROPERTY(absolute,getZ,setZ);
    NCB_PROPERTY(enabled,getEnabled,setEnabled);
    NCB_PROPERTY(opacity,getOpacity,setOpacity);
    NCB_PROPERTY(color,getColor,setColor);
    NCB_PROPERTY(visible,getVisible,setVisible);
    NCB_PROPERTY(x,getX,setX);
    NCB_PROPERTY(y,getY,setY);
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