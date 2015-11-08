#include "TjsRTT.h"
#include "TjsTransform.h"


void TjsRTT::paint(tTJSVariant trans)
{
    if(m_info == NULL) return;
    TjsTransform* obj = TJS_GET_OBJECT(TjsTransform,trans.AsObjectNoAddRef());
    Image::paint(obj);
}
NCB_REGISTER_CLASS_DIFFER(RTT, TjsRTT)
{
    TJS_FACTORY
    NCB_METHOD(begin);
    NCB_METHOD(end);
    NCB_METHOD(paint);
};
