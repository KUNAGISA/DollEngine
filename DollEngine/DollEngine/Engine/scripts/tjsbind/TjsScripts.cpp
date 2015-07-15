//
//  TjsScripts.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsScripts.h"
#include "TjsEngine.h"
#include "Storages.h"

tjs_uint32 tTJSNC_Scripts::ClassID = -1;
tTJSNC_Scripts::tTJSNC_Scripts() : inherited(TJS_W("Scripts"))
{
    TJS_BEGIN_NATIVE_MEMBERS(Scripts)
    TJS_DECL_EMPTY_FINALIZE_METHOD
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/Scripts)
    {
        return TJS_S_OK;
    }
    TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/Scripts)
    //----------------------------------------------------------------------
    
    //-- methods
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/exec)
    {
        if(DE::TjsEngine::GetInstance()->exec((*param[0]).GetString(), result)){
            return TJS_S_OK;
        }
        return TJS_E_FAIL;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/exec)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/eval)
    {
        if(DE::TjsEngine::GetInstance()->eval((*param[0]).GetString(), result)){
            return TJS_S_OK;
        }
        return TJS_E_FAIL;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/eval)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/execStorage)
    {
        wstring fullpath = (*param[0]).GetString();
        string path;
        DE::UnicodeToUtf8(fullpath.c_str(),path);
        path = DE::Storages::GetInstance()->getFullPath(path);
        DE::IOData* data = DE::Storages::GetInstance()->GetFileString(path);
        wstring code;
        data->convertToUnicode(code);
        SAFF_DELETE(data);
        DE::TjsEngine::GetInstance()->exec(code, result);
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/execStorage)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/evalStorage)
    {
        wstring fullpath = (*param[0]).GetString();
        string path;
        DE::UnicodeToUtf8(fullpath.c_str(),path);
        path = DE::Storages::GetInstance()->getFullPath(path);
        DE::IOData* data = DE::Storages::GetInstance()->GetFileString(path);
        wstring code;
        data->convertToUnicode(code);
        SAFF_DELETE(data);
        DE::TjsEngine::GetInstance()->eval(code, result);
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/evalStorage)
    
    //--property
    
    //----------------------------------------------------------------------
    TJS_END_NATIVE_MEMBERS
}
tTJSNativeInstance * tTJSNC_Scripts::CreateNativeInstance()
{
    // this class cannot create an instance
    TVPThrowExceptionMessage(TVPCannotCreateInstance);
    return NULL;
}
