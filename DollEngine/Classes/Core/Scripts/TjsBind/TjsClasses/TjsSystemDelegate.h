#ifndef TJSSYSTEMDELEGATE_H
#define TJSSYSTEMDELEGATE_H

#include "TjsBind.h"
#include "SystemDelegate.h"
#include "System.h"

class TjsSystemDelegate : public DE::SystemDelegate
{
public:
tTJSCustomObject* _self;
virtual ~TjsSystemDelegate(){ 
for(tjs_int i=TJS_MAX_NATIVE_CLASS-1; i>=0; i--)
{
    if(_self->ClassIDs[i]!=-1)
    {
        if(_self->ClassInstances[i]) {
            ncbInstanceAdaptor<TjsSystemDelegate>* d= dynamic_cast<ncbInstanceAdaptor<TjsSystemDelegate>*>(_self->ClassInstances[i]);
            if(d){
                d->setSticky();
            }
        }
    }
}
_self->_Finalize();
}
tTJSVariant getClass()
{
return _self->ClassNames[0];
}
TjsSystemDelegate():_self(NULL){}

virtual void onMainLoop(){
    static ttstr eventName(TJS_W("onMainLoop"));
    tTJSVariant* param[] = {};
    tTJSVariant result;
    try{
        _self->FuncCall(0, eventName.c_str(), eventName.GetHint(), &result, 0, param, _self);
    }TJS_CATCH_RETURN(
                DE::System::GetInstance()->stopMainLoop();
            )
}

virtual void onMouseDown(float x,float y){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onCheckMouseDown, 2,&v1,&v2);
}
virtual void onMouseUp(float x,float y){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onCheckMouseUp, 2,&v1,&v2);
}
virtual void onMouseMove(float x,float y){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onCheckMouseMove, 2,&v1,&v2);
}
virtual void onClick(float x,float y){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onCheckClick, 2,&v1,&v2);
}

};

#endif // TJSSYSTEMDELEGATE_H
