//
//  TJSStorages.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/11/21.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSStorages.h"


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
        const tjs_char* path = numparams > 0 ? (*param[0]).GetString() : 0;
        Storages::GetInstance()->addAutoPath(path);
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/addAutoPath)
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/getFullPath)
    {
        const tjs_char* path = numparams > 0 ? (*param[0]).GetString() : 0;
        wstring fullpath = Storages::GetInstance()->getFullPath(path);
        *result = fullpath;
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