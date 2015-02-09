//
//  TJSObject.cpp
//  DollEngine
//
//  Created by ios开发－b on 14/12/25.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSObject.h"

TJSObject::TJSObject()
:m_tjsObject(null)
{
}

void TJSObject::onPaint()
{
    iTJSEventCall(onPaint, 0);
}


NCB_REGISTER_CLASS_DIFFER(Object, TJSObject)
{
    iTJS_FACTORY
    NCB_METHOD(assign);
    NCB_METHOD(visit);
    NCB_METHOD(addChild);
    NCB_METHOD(removeChild);
    NCB_PROPERTY(parent, getParent, setParent);
    NCB_PROPERTY(visible, getVisible, setVisible);
    NCB_PROPERTY(enabled,getEnabled,setEnabled);
    NCB_PROPERTY(opacity,getOpacity,setOpacity);
    NCB_PROPERTY(absolute, getZ, setZ);
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
};
