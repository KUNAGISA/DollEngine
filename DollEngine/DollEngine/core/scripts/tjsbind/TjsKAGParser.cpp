//
//  TJSKAGParser.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/11/22.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TjsKAGParser.h"

using namespace DE;

void TjsKAGParser::jumpTo(ttstr storage, ttstr label)
{
    if (label.IsEmpty() || label.length() == 0)
    {
        label = L"_def_";
    }
    if (storage.IsEmpty() || storage.length() == 0)
    {
        storage = m_currentStorage->fileName;
    }
    DE::KAGParser::jumpTo(storage.AsStdString(),label.AsStdString());
}

void TjsKAGParser::callLabel(ttstr storage,ttstr label)
{
    if (label.IsEmpty() || label.length() == 0)
    {
        label = L"_def_";
    }
    if (storage.IsEmpty() || storage.length() == 0)
    {
        storage = m_currentStorage->fileName;
    }
    DE::KAGParser::callLabel(storage.AsStdString(),label.AsStdString());
}

static void GetTagParamValue(KAGTagParamValue& kv, tTJSVariant &ret)
{
    if (kv.entity)
    {
        if (kv.isstring) {
            try {
                TjsEngine::Global()->EvalExpression( kv.value.substr(2,kv.value.length()-3), &ret) ;
            }TJS_CATCH
        }
        else {
            try {
                TjsEngine::Global()->EvalExpression( kv.value.substr(1), &ret) ;
            }TJS_CATCH
        }
    }
    else if (kv.isstring)
    {
        try {
            TjsEngine::Global()->EvalExpression( kv.value, &ret) ;
        }TJS_CATCH
    }
    else if (kv.macroarg)
    {
        try {
            TjsEngine::Global()->EvalExpression( (L"mp."+kv.value.substr(1)), &ret) ;
        }TJS_CATCH
    }
    else
    {
        ret = kv.value;
    }
}

static void GetTagParamsValue(KAGTag* tag,const wstring& key,tTJSVariant &value)
{
    for (auto iter = tag->params.begin();
         iter != tag->params.end(); ++iter)
    {
        KAGTagParamValue& kv = *iter;
        if (kv.key == key) {
            GetTagParamValue(kv,value);
            return;
        }
    }
}

int TjsKAGParser::execute(KAGTag* tag)
{
    tag->print();
    if (tag->hasCond) {
        tTJSVariant ret;
        GetTagParamsValue(tag,L"cond",ret);
        tTJSVariant cond;
        try {
            TjsEngine::Global()->EvalExpression( ret, &cond);
        }TJS_CATCH
        if (cond.operator bool()) {
        }
        else {
            return 0;
        }
    }
    if (tag->name == L"return")
    {
        returnCall();
        return -1;
    }
    else if (tag->name == L"if")
    {
        tTJSVariant ret;
        GetTagParamsValue(tag,L"exp",ret);
        tTJSVariant cond;
        try {
            TjsEngine::Global()->EvalExpression( ret, &cond);
        }TJS_CATCH
        if (cond.operator bool()) {
            m_ifKey.push_back(L"doing");
        }
        else{
            m_ifKey.push_back(L"toelse");
        }
        return 0;
    }
    else if (tag->name == L"else")
    {
        if (m_ifKey.size() > 0) {
            if (m_ifKey.back() == L"doing") {
                m_ifKey.back() = L"toend";
            }
            else if(m_ifKey.back() == L"toelse"){
                m_ifKey.back() = L"doing";
            }
            else if (m_ifKey.back() == L"toend"){
            }
            return 0;
        }
        else {
            Debug::throwMsg(ERROR_KAG_IF_FAIL, tag->line);
        }
    }
    else if (tag->name == L"elsif")
    {
        tTJSVariant ret;
        GetTagParamsValue(tag,L"exp",ret);
        if (m_ifKey.size() == 0) {
            Debug::throwMsg(ERROR_KAG_IF_FAIL, tag->line);
        }
        else
        {
            if (m_ifKey.back() == L"doing") {
                m_ifKey.back() = L"toend";
            }
            else if(m_ifKey.back() == L"toelse"){
                tTJSVariant cond;
                try {
                    TjsEngine::Global()->EvalExpression( ret, &cond);
                }TJS_CATCH
                if (cond.operator bool()) {
                    m_ifKey.back() = L"doing";
                }
                return 0;
            }
            else if (m_ifKey.back() == L"toend"){
                return 0;
            }
            return 0;
        }
    }
    else if (tag->name == L"endif")
    {
        m_ifKey.pop_back();
        return 0;
    }
    if (m_ifKey.size()>0 && (m_ifKey.back() == L"toend" || m_ifKey.back() == L"toelse")) {
        return 0;
    }
    string fileName;
    UnicodeToUtf8(tag->storage->fileName.c_str(), fileName);
    TjsEngine::GetSelf()->pushFile(fileName);
    tTJSDictionaryObject* params = (tTJSDictionaryObject*)TJSCreateDictionaryObject();
    tTJSVariant name = tag->name.c_str();
    for (auto iter = tag->params.begin();
         iter != tag->params.end(); ++iter)
    {
        KAGTagParamValue& kv = *iter;
        tTJSVariant key = kv.key.c_str();
        tTJSVariant ret;
        GetTagParamValue(kv,ret);
        params->PropSet(TJS_MEMBERENSURE,key.GetString(),NULL,&ret,params);
    }
    tTJSVariant params_t = params;
    params->Release();
    TJS_EVENT_CALL(onExecute,2,&name,&params_t);
    TjsEngine::GetSelf()->popFile();
    return (int)result.AsInteger();
}

NCB_REGISTER_CLASS_DIFFER(KAGParser, TjsKAGParser)
{
    TJS_FACTORY
    NCB_METHOD(jumpTo);
    NCB_METHOD(doNext);
    NCB_METHOD(callLabel);
    NCB_METHOD(callMacro);
    NCB_METHOD(returnCall);
    NCB_METHOD(onExecute);
};
