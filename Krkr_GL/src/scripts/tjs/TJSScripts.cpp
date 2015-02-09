//
//  TJSScripts.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/11/22.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSScripts.h"
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
        try {
            ScriptsTJS::GetTjs()->ExecScript ( (*param[0]).GetString(), result) ;
        }
        iTJSErrorCatch
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/exec)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/eval)
    {
        try {
            ScriptsTJS::GetTjs()->EvalExpression( (*param[0]).GetString(), result) ;
        }
        iTJSErrorCatch
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/eval)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/execStorage)
    {
        wstring fullPath = Storages::GetInstance()->getFullPath((*param[0]).GetString());
        IOData* code = Storages::GetFileText(fullPath);
        if (code)
        {
            Scripts::GetInstance()->pushFile((*param[0]).GetString());
            try {
                code->convertToWString();
                ScriptsTJS::GetTjs()->ExecScript (code->getWBuffer(),result) ;
            }
            iTJSErrorCatch
            Scripts::GetInstance()->popFile();
            SAFF_DELETE_NULL(code);
        }
        return TJS_S_OK;
    }
    TJS_END_NATIVE_STATIC_METHOD_DECL(/*func. name*/execStorage)
    //----------------------------------------------------------------------
    TJS_BEGIN_NATIVE_METHOD_DECL(/*func. name*/evalStorage)
    {
        ttstr path = (*param[0]).GetString();
        wstring fullPath = Storages::GetInstance()->getFullPath((*param[0]).GetString());
        IOData* code = Storages::GetFileText(fullPath);
        if (code)
        {
            Scripts::GetInstance()->pushFile((*param[0]).GetString());
            try
            {
                code->convertToWString();
                ScriptsTJS::GetTjs()->EvalExpression ( code->getWBuffer(),result) ;
            }
            iTJSErrorCatch
            Scripts::GetInstance()->popFile();
            SAFF_DELETE_NULL(code);
        }
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

