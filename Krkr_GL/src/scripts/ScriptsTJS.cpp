//
//  ScriptsTJS.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "ScriptsTJS.h"
#include "StringUtils.h"
#include "GlobalTJS.h"
#include "Storages.h"
#include "TJSSystem.h"
#include "TJSScripts.h"
#include "TJSStorages.h"
#include "TJSActions.h"

void TVPAddLog(const ttstr& var)
{
//    DM(var.AsNarrowStdString().c_str());
}

iTJSDispatch2* TVPGetScriptDispatch()
{
    return ScriptsTJS::GetTjs()->GetGlobal();
}


void TVPExecuteExpression(const ttstr & content , tTJSVariant* result = NULL)
{
    try {
        ScriptsTJS::GetTjs()->ExecScript ( content,
                                          result, NULL,
                                          NULL ) ;
    }
    iTJSErrorCatch
}

static tTJS* s_tjs = null;

ScriptsTJS::ScriptsTJS()
:m_tjs(null)
{
}

ScriptsTJS::~ScriptsTJS()
{
    ncbAutoRegister::AllUnregist();
    m_tjs->Release();
    s_tjs = null;
}

void ScriptsTJS::releaseScriptID(long _id)
{
    iTJSDispatch2* obj = (iTJSDispatch2*)_id;
    obj->Release();
}

tTJS* ScriptsTJS::GetTjs()
{
    return s_tjs;
}

void ScriptsTJS::init()
{
    m_tjs = new tTJS();
    s_tjs = m_tjs;
    
    tTJSVariant val;
    iTJSDispatch2 *dsp;
    iTJSDispatch2* global = m_tjs->GetGlobalNoAddRef () ;
    
    REGIST_TJS_CLASS(System)
    REGIST_TJS_CLASS(Storages)
    REGIST_TJS_CLASS(Scripts)
    REGIST_TJS_CLASS(Actions)
    
    TVPLoadMessage();
    REGIST_TJS_FUNCTION(TJSPrint,"print")
    REGIST_TJS_FUNCTION(TJSConsoleShow,"__console_show")
    
    NCB_LOG_W("V2Link");
    
	// AutoRegisterで登録されたクラス等を登録する
	ncbAutoRegister::AllRegist();
    
}

int ScriptsTJS::exec(const wchar_t* code)
{
    if (code == null) {
        return 0;
    }
    try {
        tTJSVariant result ;
        m_tjs->ExecScript ( code,
                           &result, NULL,
                           NULL ) ;
        return (int)result;
    }
    iTJSErrorCatch
    return 0;
}

int ScriptsTJS::eval(const wchar_t* code)
{
    if (code == null) {
        return 0;
    }
    try {
        tTJSVariant result ;
        m_tjs->EvalExpression( code,
                           &result, NULL,
                           NULL ) ;
        result.ToString();
        DM("%ls",result.GetString());
        return (int)result;
    }
    iTJSErrorCatch
    return 0;
}

int ScriptsTJS::execStorage(const char* filePath)
{
    wstring wpath;
    StringUtils::ConvertUtf8ToUnicode(filePath, wpath);
    wstring fullpath = Storages::GetInstance()->getFullPath(wpath);
    IOData* code = Storages::GetFileText(fullpath);
    int ret = 0;
    if (code)
    {
        pushFile(wpath);
        code->convertToWString();
        ret = exec(code->getWBuffer());
        SAFF_DELETE_NULL(code);
        popFile();
    }
    return ret;
}


