#ifndef TJSTRANSFORM_H
#define TJSTRANSFORM_H

#include "TjsBind.h"
#include "Transform.h"

TJS_NCB(Transform){}
virtual void assign(tTJSVariant src)
{
    TjsTransform* obj = TJS_GET_OBJECT(TjsTransform,src.AsObjectNoAddRef());
    Transform::assign(obj);
}
virtual void transform(tTJSVariant v)
{
    TjsTransform* obj = TJS_GET_OBJECT(TjsTransform,v.AsObjectNoAddRef());
    Transform::transform(obj);
}
bool pointInsideTJS(float x,float y,tTJSVariant v)
{
    float ox=0;
    float oy=0;
    bool ret = Transform::pointInside(x,y,ox,oy);
    tTJSDictionaryObject* object = dynamic_cast<tTJSDictionaryObject*>(v.AsObjectNoAddRef());
    if(object){
        tTJSVariant tox=round(ox);
        tTJSVariant toy=round(oy);
        object->PropSet(TJS_MEMBERENSURE,L"x",NULL,&tox,object);
        object->PropSet(TJS_MEMBERENSURE,L"y",NULL,&toy,object);
    }
    return ret;
}
};

#endif // TJSTRANSFORM_H
