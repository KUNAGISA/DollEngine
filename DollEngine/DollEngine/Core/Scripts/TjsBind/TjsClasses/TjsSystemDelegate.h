#ifndef TJSSYSTEMDELEGATE_H
#define TJSSYSTEMDELEGATE_H

#include "TjsBind.h"
#include "SystemDelegate.h"


TJS_NCB(SystemDelegate){}

virtual void onMainLoop(){
    TJS_EVENT_CALL(onMainLoop,0);
}

virtual void onMouseDown(float x,float y){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onMouseDown, 2,&v1,&v2);
}
virtual void onMouseUp(float x,float y){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onMouseUp, 2,&v1,&v2);
}
virtual void onMouseMove(float x,float y){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onMouseMove, 2,&v1,&v2);
}
virtual void onClick(float x,float y){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onClick, 2,&v1,&v2);
}

};

#endif // TJSSYSTEMDELEGATE_H
