//
//  TjsSystem.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsSystem.h"
#include "System.h"
#include "TjsGameObject.h"

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
    
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/log)
    {
        if ( numparams <1 ) return TJS_E_BADPARAMCOUNT ;
        tTJSVariantString *res;
        res = TJSFormatString(param[0]->AsString()->operator const wchar_t *(), numparams-1, &param[1]);
        wstring dg = L"【TJS】: ";
        if(res) {
            dg += (const tjs_char*)*res;
        }
        if(TjsEngine::Global()) {
            TjsEngine::Global()->OutputToConsole(dg.c_str());
        }
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
        return TJS_S_OK ;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/throwMsg)
    
    //--property
    
    //----------------------------------------------------------------------
    
    TJS_BEGIN_NATIVE_PROP_DECL(appPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            wstring path;
            DE::Utf8ToUnicode(DESystem->getAppPath().c_str(),path);
            *result = path;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(appPath)
    
    TJS_BEGIN_NATIVE_PROP_DECL(dataPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            wstring path;
            DE::Utf8ToUnicode(DESystem->getDataPath().c_str(),path);
            *result = path;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(dataPath)
    
    TJS_BEGIN_NATIVE_PROP_DECL(saveDataPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            wstring path;
            DE::Utf8ToUnicode(DESystem->getSaveDataPath().c_str(),path);
            *result = path;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(saveDataPath)
    
    TJS_BEGIN_NATIVE_PROP_DECL(patchPath)
    {
        TJS_BEGIN_NATIVE_PROP_GETTER
        {
            wstring path;
            DE::Utf8ToUnicode(DESystem->getPatchPath().c_str(),path);
            *result = path;
            return TJS_S_OK;
        }
        TJS_END_NATIVE_PROP_GETTER
        TJS_DENY_NATIVE_PROP_SETTER
    }
    TJS_END_NATIVE_STATIC_PROP_DECL(patchPath)
    
    
    TJS_NATIVE_PROP(debugMode,
                    System::GetInstance()->getDebugMode(),
                    System::GetInstance()->setDebugMode((int)param->AsInteger()))
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
