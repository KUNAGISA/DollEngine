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
        wstring path = (*param[0]).GetString();
        string fullpath;
        DE::UnicodeToUtf8(path.c_str(),fullpath);
        fullpath = DE::Storages::GetInstance()->getFullPath(fullpath);
        DE::IOData* data = DE::Storages::GetInstance()->GetFileString(fullpath);
        wstring code;
        data->convertToUnicode(code);
        SAFF_DELETE(data);
        TjsEngine::GetSelf()->pushFile(fullpath);
        DE::TjsEngine::GetSelf()->exec(code, result);
        TjsEngine::GetSelf()->popFile();
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/execStorage)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/evalStorage)
    {
        wstring path = (*param[0]).GetString();
        string fullpath;
        DE::UnicodeToUtf8(path.c_str(),fullpath);
        fullpath = DE::Storages::GetInstance()->getFullPath(fullpath);
        DE::IOData* data = DE::Storages::GetInstance()->GetFileString(fullpath);
        wstring code;
        data->convertToUnicode(code);
        SAFF_DELETE(data);
        TjsEngine::GetSelf()->pushFile(fullpath);
        DE::TjsEngine::GetInstance()->eval(code, result);
        TjsEngine::GetSelf()->popFile();
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/evalStorage)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/jsonStorage)
    {
        wstring path = (*param[0]).GetString();
        string fullpath;
        DE::UnicodeToUtf8(path.c_str(),fullpath);
        fullpath = DE::Storages::GetInstance()->getFullPath(fullpath);
        DE::IOData* data = DE::Storages::GetInstance()->GetFileString(fullpath);
        wstring code;
        data->convertToUnicode(code);
        SAFF_DELETE(data);
        *result = JsonParser::GetInstance()->FromJsonString(code.c_str());
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/jsonStorage)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/json)
    {
        const wchar_t* code = (*param[0]).GetString();
        *result = JsonParser::GetInstance()->FromJsonString(code);
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/json)
    
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/addAsyncFunction)
    {
        if (numparams<1) {
            return TJS_E_BADPARAMCOUNT;
        }
        iTJSDispatch2* f = (param[0])->AsObjectNoAddRef();
        iTJSDispatch2* objthis = (param[0])->AsObjectThisNoAddRef();
        tTJSInterCodeContext* func = dynamic_cast<tTJSInterCodeContext*>(f);
        if (!func) {
            return TJS_E_INVALIDTYPE;
        }
        tTVInteger p = 0;
        if (numparams >= 2) {
            p = param[1]->AsInteger();
        }
        AsyncFunction af;
        af.priority = p;
        af.objthis = objthis;
        af.handler = func;
        TjsEngine::GetSelf()->addAsyncFunction(af);
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/addAsyncFunction)
    
    
    
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
