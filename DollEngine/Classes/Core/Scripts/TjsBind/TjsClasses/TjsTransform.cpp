#include "TjsTransform.h"

NCB_REGISTER_CLASS_DIFFER(Transform, TjsTransform)
{
    TJS_FACTORY
    NCB_METHOD(assign);
    NCB_METHOD(transform);
    NCB_METHOD(init);
    NCB_METHOD(flush);
    NCB_METHOD_DIFFER(pointInside,pointInsideTJS);
    NCB_PROPERTY( x, getX, setX);
    NCB_PROPERTY( y, getY, setY);
    NCB_PROPERTY( width, getWidth, setWidth);
    NCB_PROPERTY( height, getHeight, setHeight);
    NCB_PROPERTY( anchorX, getAnchorX, setAnchorX);
    NCB_PROPERTY( anchorY, getAnchorY, setAnchorY);
    NCB_PROPERTY( scale, getScale, setScale);
    NCB_PROPERTY( scaleX, getScaleX, setScaleX);
    NCB_PROPERTY( scaleY, getScaleY, setScaleY);
    NCB_PROPERTY( rotation, getRotation, setRotation);
    NCB_PROPERTY( rotationX, getRotationX, setRotationX);
    NCB_PROPERTY( rotationY, getRotationY, setRotationY);
    NCB_PROPERTY( rotationZ, getRotationZ, setRotationZ);
    NCB_PROPERTY( ignoreAnchorPoint, getIgnoreAnchorPoint, setIgnoreAnchorPoint);
};

