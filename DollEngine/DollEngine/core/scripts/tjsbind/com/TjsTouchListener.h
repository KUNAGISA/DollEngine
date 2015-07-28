//
//  TjsTouchListener.h
//  DollEngine
//
//  Created by DollStudio on 15/7/29.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsTouchListener__
#define __DollEngine__TjsTouchListener__


#include "TjsCOM.h"
#include "TouchListener.h"

TJS_NCB_COM(TouchListener)

virtual void onMouseDown(float x,float y ){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onMouseDown, 2,&v1,&v2);
}
virtual void onMouseUp(float x,float y ){
    tTJSVariant v1=x;
    tTJSVariant v2=y;
    TJS_EVENT_CALL(onMouseUp, 2,&v1,&v2);
}
virtual void onMouseMove(float x,float y ){
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

#endif /* defined(__DollEngine__TjsTouchListener__) */
