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

NCB_REGISTER_CLASS_DIFFER(GameObject,TjsGameObject)
{
    TJS_FACTORY
    NCB_METHOD(transform);
    NCB_PROPERTY(parent, getParent,setParent);
    NCB_PROPERTY(zOrder,getZ,setZ);
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