#include "TjsColorRect.h"
#include "TjsTransform.h"

void TjsColorRect::paint(tTJSVariant trans)
{
    if(m_info == NULL) return;
    TjsTransform* obj = TJS_GET_OBJECT(TjsTransform,trans.AsObjectNoAddRef());
    ColorRect::paint(obj);
}

NCB_REGISTER_CLASS_DIFFER(ColorRect, TjsColorRect)
{
    TJS_FACTORY
    NCB_METHOD(loadSize);
    NCB_METHOD(paint);
    NCB_PROPERTY(paintWidth,getPaintWidth,setPaintWidth);
    NCB_PROPERTY(paintHeight,getPaintHeight,setPaintHeight);
    NCB_PROPERTY(startOpacity,getStartOpacity,setStartOpacity);
    NCB_PROPERTY(endOpacity,getEndOpacity,setEndOpacity);
    NCB_PROPERTY(startColor,getStartColor,setStartColor);
    NCB_PROPERTY(endColor,getEndColor,setEndColor);
};

