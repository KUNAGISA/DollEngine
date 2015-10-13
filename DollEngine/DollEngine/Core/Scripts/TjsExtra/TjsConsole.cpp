//
//  TjsConsole.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsConsole.h"

tjs_uint32 tTJSNC_Console::ClassID = -1;
tTJSNC_Console::tTJSNC_Console() : inherited(TJS_W("Console"))
{
    TJS_BEGIN_NATIVE_MEMBERS(Console)
    TJS_DECL_EMPTY_FINALIZE_METHOD
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/Console)
    {
        return TJS_S_OK;
    }
    TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/Console)
    //----------------------------------------------------------------------
    
    //-- methods
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/log)
    {
        if ( numparams <1 ) return TJS_E_BADPARAMCOUNT ;
        tTJSVariantString *res;
        res = TJSFormatString(param[0]->AsString()->operator const wchar_t *(), numparams-1, &param[1]);
        DE::String dg = L"【TJS】: ";
        if(res) {
            dg += (const tjs_char*)*res;
        }
        if(DE::Console::GetInstance())
            DE::Console::GetInstance()->log(dg);
        
        if(res) res->Release();
        return TJS_S_OK ;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/log)
    
    
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/throwMsg)
    {
        if ( numparams <1 ) return TJS_E_BADPARAMCOUNT ;
        tTJSVariantString *res;
        res = TJSFormatString(param[0]->GetString(), numparams, &param[1]);
        if(res) {
            TJS_eTJSError(*res);
        }
        else {
            TJS_eTJSError(L"");
        }
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/throwMsg)
    
    //--property
    
    //----------------------------------------------------------------------
    
    TJS_NATIVE_PROP(visible,
                    DE::Console::GetInstance()->getVisible(),
                    DE::Console::GetInstance()->setVisible((bool)param->AsInteger()))
            
    
    TJS_END_NATIVE_MEMBERS
}
tTJSNativeInstance * tTJSNC_Console::CreateNativeInstance()
{
    // this class cannot create an instance
    TVPThrowExceptionMessage(TVPCannotCreateInstance);
    return NULL;
}
