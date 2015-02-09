//
//  TJSObject.h
//  DollEngine
//
//  Created by ios开发－b on 14/12/25.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TJSObject__
#define __DollEngine__TJSObject__

#include "GlobalTJS.h"
#include "Object.h"


class TJSTransform;
class TJSObject: public Object
{
public:
    TJSObject();
    tTJSCustomObject* m_tjsObject;
    iTJS_METHOD_OBJECT(Object,assign,Object);
    iTJS_METHOD_OBJECT(Object,addChild,Object);
    iTJS_METHOD_OBJECT(Object,removeChild,Object);
    iTJS_PROPERTY_OBJECT(Object, Parent, Object);
    void onPaint();
    ttstr getClass(){return m_tjsObject->ClassNames[0];}
};

#endif /* defined(__DollEngine__TJSObject__) */
