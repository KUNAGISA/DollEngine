//
//  TjsSystem.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsSystem.h"


tjs_uint32 tTJSNC_System::ClassID = -1;
tTJSNC_System::tTJSNC_System() : inherited(TJS_W("System"))
{
    TJS_BEGIN_NATIVE_MEMBERS(System)
    TJS_DECL_EMPTY_FINALIZE_METHOD
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/System)
    {
        return TJS_S_OK;
    }
    TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/System)
    //----------------------------------------------------------------------
    
    //-- methods
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/exit)
    {
        tjs_int64 code = numparams > 0 ? (*param[0]).AsInteger() : 0;
        exit((int)code);
        
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/exit)
    
    //--property
    
    //----------------------------------------------------------------------
//    TJS_NATIVE_PROP(graphicCacheLimit,
//                    System::GetInstance()->getGraphicCacheLimit(),
//                    System::GetInstance()->setGraphicCacheLimit(param->AsReal()))
//    TJS_NATIVE_PROP_RO(exeName,System::GetInstance()->getExeName().c_str())
//    TJS_NATIVE_PROP_RO(exePath,System::GetInstance()->getExePath().c_str())
//    TJS_NATIVE_PROP_RO(appDataPath,System::GetInstance()->getAppDataPath().c_str())
//    TJS_NATIVE_PROP_RO(personalPath,System::GetInstance()->getPersonalPath().c_str())
//    TJS_NATIVE_PROP_RO(patchPath,System::GetInstance()->getPatchPath().c_str())
    
    TJS_END_NATIVE_MEMBERS
}
tTJSNativeInstance * tTJSNC_System::CreateNativeInstance()
{
    // this class cannot create an instance
    TVPThrowExceptionMessage(TVPCannotCreateInstance);
    return NULL;
}
