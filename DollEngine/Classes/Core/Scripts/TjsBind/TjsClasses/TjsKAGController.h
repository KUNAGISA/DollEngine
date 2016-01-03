//
//  TjsKAGController.h
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsKAGController__
#define __DollEngine__TjsKAGController__

#include <stdio.h>

#include "TjsBind.h"
#include "KAGController.h"

TJS_NCB(KAGController){}

enum IF_KEY {
    DOING=0,
    TOELSE,
    TOEND
};

int doTag();
bool stepInLabel(tTJSVariant storage, tTJSVariant label, bool iscall)
{
    wstring v1,v2;
    const kagchar* v11 = storage.AsStringNoAddRef()->operator const wchar_t *();
    if(v11)v1=v11;
    const kagchar* v22 = label.AsStringNoAddRef()->operator const wchar_t *();
    if(v22)v2=v22;
    return KAGController::stepInLabel(v1, v2, iscall);
}

tTJSVariant saveStack();
tTJSVariant getLastTargetTJS(){
    tTJSVariant ret = getLastTarget().c_wstr();
    return ret;
}
tTJSVariant getCurStorageTJS(){
    tTJSVariant ret = getCurStorage().c_wstr();
    return ret;
}
tTJSVariant getCurTargetTJS(){
    tTJSVariant ret = getCurTarget().c_wstr();
    return ret;
}
bool loadStack(tTJSVariant v);
protected:
vector<IF_KEY> m_ifKey;
};

#endif /* defined(__DollEngine__TjsKAGController__) */
