//
//  TJSTouchEvent.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/12/28.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSTouchEvent.h"

void TJSTouchEvent::onMouseDown(float x,float y )
{
    tTJSVariant p1 = x;
    tTJSVariant p2 = y;
    iTJSEventCall(onMouseDown, 2,&p1,&p2);
}

void TJSTouchEvent::onMouseUp(float x,float y )
{
    tTJSVariant p1 = x;
    tTJSVariant p2 = y;
    iTJSEventCall(onMouseUp, 2,&p1,&p2);
}

void TJSTouchEvent::onMouseMove(float x,float y )
{
    tTJSVariant p1 = x;
    tTJSVariant p2 = y;
    iTJSEventCall(onMouseMove, 2,&p1,&p2);
}

void TJSTouchEvent::onClick(float x,float y)
{
    tTJSVariant p1 = x;
    tTJSVariant p2 = y;
    iTJSEventCall(onClick, 2,&p1,&p2);
}

void TJSTouchEvent::onMouseEnter()
{
    iTJSEventCall(onMouseEnter, 00);
}

void TJSTouchEvent::onMouseLeave()
{
    iTJSEventCall(onMouseLeave, 0);
}

NCB_REGISTER_CLASS_DIFFER(TouchEvent, TJSTouchEvent)
{
    iTJS_FACTORY_COM
    NCB_PROPERTY(ignore, getIgnore, setIgnore);
    NCB_PROPERTY(swallow, getSwallow, setSwallow);
};
