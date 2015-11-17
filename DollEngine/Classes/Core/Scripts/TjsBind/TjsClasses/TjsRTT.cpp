#include "TjsRTT.h"
#include "TjsTransform.h"


void TjsRTT::paint(tTJSVariant trans)
{
    if(m_info == NULL) return;
    TjsTransform* obj = TJS_GET_OBJECT(TjsTransform,trans.AsObjectNoAddRef());
    RTT::paint(obj);
}
NCB_REGISTER_CLASS_DIFFER(RTT, TjsRTT)
{
    TJS_FACTORY
    NCB_METHOD(begin);
    NCB_METHOD(end);
    NCB_METHOD(paint);
    NCB_PROPERTY(opacity,getOpacity,setOpacity);
    NCB_PROPERTY(paintWidth,getPaintWidth,setPaintWidth);
    NCB_PROPERTY(paintHeight,getPaintHeight,setPaintHeight);
    NCB_PROPERTY(startOpacity,getStartOpacity,setStartOpacity);
    NCB_PROPERTY(endOpacity,getEndOpacity,setEndOpacity);
    NCB_PROPERTY(startColor,getStartColor,setStartColor);
    NCB_PROPERTY(endColor,getEndColor,setEndColor);
};
