//
//  TjsScripts.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsScripts.h"
#include "ScriptEngine.h"
#include "Storages.h"
#include "JsonParser.h"

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
        if(DE::ScriptEngine::GetInstance()->exec((*param[0]).GetString(), result)){
            return TJS_S_OK;
        }
        return TJS_E_FAIL;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/exec)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/eval)
    {
        if(DE::ScriptEngine::GetInstance()->eval((*param[0]).GetString(), result)){
            return TJS_S_OK;
        }
        return TJS_E_FAIL;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/eval)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/execStorage)
    {
        DE::String path = (*param[0]).GetString();
        DE::String code;
        if(!code.loadFromFile(path)) {
            DM(L"文件加载失败");
            return TJS_E_FAIL;
        }
        DE::ScriptEngine::GetInstance()->pushFile(path);
        DE::ScriptEngine::GetInstance()->exec(code, result);
        DE::ScriptEngine::GetInstance()->popFile();
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/execStorage)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/evalStorage)
    {
        DE::String path = (*param[0]).GetString();
        DE::String code;
        if(!code.loadFromFile(path)) {
            DM(L"文件加载失败");
            return TJS_E_FAIL;
        }
        DE::ScriptEngine::GetInstance()->pushFile(path);
        DE::ScriptEngine::GetInstance()->eval(code, result);
        DE::ScriptEngine::GetInstance()->popFile();
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/evalStorage)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/jsonStorage)
    {
        DE::String path = (*param[0]).GetString();
        DE::String code;
        if(!code.loadFromFile(path)) {
            DM(L"文件加载失败");
            return TJS_E_FAIL;
        }
        *result = JsonParser::GetInstance()->fromJsonString(code.c_wstr());
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/jsonStorage)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/json)
    {
        const wchar_t* code = (*param[0]).GetString();
        *result = JsonParser::GetInstance()->fromJsonString(code);
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/json)
    
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
