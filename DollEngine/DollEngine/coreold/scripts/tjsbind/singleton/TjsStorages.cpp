//
//  TjsStorage.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsStorages.h"
#include "Storages.h"

tjs_uint32 tTJSNC_Storages::ClassID = -1;
tTJSNC_Storages::tTJSNC_Storages() : inherited(TJS_W("Storages"))
{
    TJS_BEGIN_NATIVE_MEMBERS(Storages)
    TJS_DECL_EMPTY_FINALIZE_METHOD
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_CONSTRUCTOR_DECL_NO_INSTANCE(/*TJS class name*/Storages)
    {
        return TJS_S_OK;
    }
    TJS_END_NATIVE_CONSTRUCTOR_DECL(/*TJS class name*/Storages)
    //----------------------------------------------------------------------
    
    //-- methods
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/addAutoPath)
    {
        string path;
        DE::UnicodeToUtf8((*param[0]).GetString(), path);
        DE::Storages::GetInstance()->addAutoPath(path);
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/addAutoPath)
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/getFullPath)
    {
        string path;
        DE::UnicodeToUtf8((*param[0]).GetString(), path);
        string fullPath = DE::Storages::GetInstance()->getFullPath(path);
        wstring wfullPath;
        DE::Utf8ToUnicode((char*)fullPath.c_str(), wfullPath);
        *result = wfullPath.c_str();
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/getFullPath)
    
    //--property
    
    //----------------------------------------------------------------------
    TJS_END_NATIVE_MEMBERS
}
tTJSNativeInstance * tTJSNC_Storages::CreateNativeInstance()
{
    // this class cannot create an instance
    TVPThrowExceptionMessage(TVPCannotCreateInstance);
    return NULL;
}