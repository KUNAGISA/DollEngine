//
//  TJSActions.cpp
//  Krkr_GL
//
//  Created by DollStudio on 15/1/31.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TJSActions.h"
#include "TJSObject.h"

tjs_uint32 tTJSNC_Actions::ClassID = -1;
tTJSNC_Actions::tTJSNC_Actions() : inherited(TJS_W("Actions"))
{
    TJS_BEGIN_NATIVE_MEMBERS(Actions)
    TJS_DECL_EMPTY_FINALIZE_METHOD
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/Actions)
    {
        return TJS_S_OK;
    }
    TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/Actions)
    //----------------------------------------------------------------------
    
    //-- methods
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/run)
    {
        TJSObject* obj = iTJSGetObject(TJSObject, (*param[0]).AsObjectNoAddRef());
        tjs_int64 param1 = numparams > 1 ? (*param[1]).AsInteger() : 0;
        switch (param1) {
            case 0: //ACTION_UNKNOW
            {
                eTJSError(L"未知的Action类型");
                return TJS_E_FAIL;
            }
                break;
            case 2: //ACTION_FADETO
            {
                float time = numparams > 2 ? (*param[2]).AsReal()/1000 : 0;
                float opt = numparams > 3 ? (*param[3]).AsReal() : 255;
                ActionManager::GetInstance()->fadeTo(obj, time, opt,[obj](){
                    obj->postMsg(obj->m_tjsObject, TJS_W("ACTION_FADETO_END"), TJS::tTJSVariant());
                });
            }
                break;
            case 100://TRANS_CROSSFADE
            {
                float time = numparams > 2 ? (*param[2]).AsReal()/1000 : 0;
                float opt = numparams > 3 ? (*param[3]).AsReal() : 255;
                ActionManager::GetInstance()->fadeTo(obj, time, opt,[obj](){
                    obj->postMsg(obj->m_tjsObject, TJS_W("TRANS_CROSSFADE_END"), TJS::tTJSVariant());
                });
            }
                break;
            default:
            {
                eTJSError(L"未知的Action类型");
                return TJS_E_FAIL;
            }
                break;
        }
        
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/run)
    
    TJS_END_NATIVE_MEMBERS
}

tTJSNativeInstance * tTJSNC_Actions::CreateNativeInstance()
{
    // this class cannot create an instance
    TVPThrowExceptionMessage(TVPCannotCreateInstance);
    return NULL;
}
