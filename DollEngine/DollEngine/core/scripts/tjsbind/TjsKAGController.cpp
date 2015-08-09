//
//  TjsKAGController.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TjsKAGController.h"


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
            size_t p = kv.value.find(L"|");
            wstring v1, v2;
            if (p != string::npos) {
                v1 = kv.value.substr(1,p-1);
                tTJSVariant r1;
                TjsEngine::Global()->EvalExpression( (L"mp."+v1), &r1) ;
                if (r1.operator bool()) {
                    ret = r1;
                }
                else {
                    v2 = kv.value.substr(p+1);
                    tTJSVariant r2;
                    TjsEngine::Global()->EvalExpression( v2, &r2) ;
                    ret = r2;
                }
            }
            else {
                TjsEngine::Global()->EvalExpression( (L"mp."+kv.value.substr(1)), &ret) ;
            }
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



int TjsKAGController::doTag()
{
    if (m_tagIndex >= m_label->allTags.size()) {
        stepNext();
    }
    KAGTag * tag = m_label->allTags[m_tagIndex];
    if (tag->name == L"macro") {
        wstring macroname = tag->getValue(L"name");
        KAGParser::GetInstance()->startMacro(macroname);
        while (true) {
            ++m_tagIndex;
            if (m_tagIndex>=m_label->allTags.size()) {
                Debug::throwMsg(ERROR_KAG_UNKONW);
                return -2;
            }
            KAGTag * tt = m_label->allTags[m_tagIndex];
            KAGTag* c = tt->clone();
            KAGParser::GetInstance()->pushMacro(c);
            if (c->name == L"endmacro") {
                KAGParser::GetInstance()->endMacro();
                break;
            }
        }
        tag->print();
        return 0;
    }
    
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
            tag->print();
            return 0;
        }
    }
    if (tag->name == L"if")
    {
        tag->print();
        tTJSVariant ret;
        GetTagParamsValue(tag,L"exp",ret);
        tTJSVariant cond;
        try {
            TjsEngine::Global()->EvalExpression( ret, &cond);
        }TJS_CATCH
        if (cond.operator bool()) {
            m_ifKey.push(L"doing");
        }
        else{
            m_ifKey.push(L"toelse");
        }
        return 0;
    }
    else if (tag->name == L"else")
    {
        tag->print();
        if (m_ifKey.size() > 0) {
            if (m_ifKey.top() == L"doing") {
                m_ifKey.top() = L"toend";
            }
            else if(m_ifKey.top() == L"toelse"){
                m_ifKey.top() = L"doing";
            }
            else if (m_ifKey.top() == L"toend"){
            }
            return 0;
        }
        else {
            Debug::throwMsg(ERROR_KAG_IF_FAIL, tag->line);
        }
    }
    else if (tag->name == L"elsif")
    {
        tag->print();
        tTJSVariant ret;
        GetTagParamsValue(tag,L"exp",ret);
        if (m_ifKey.size() == 0) {
            Debug::throwMsg(ERROR_KAG_IF_FAIL, tag->line);
        }
        else
        {
            if (m_ifKey.top() == L"doing") {
                m_ifKey.top() = L"toend";
            }
            else if(m_ifKey.top() == L"toelse"){
                tTJSVariant cond;
                try {
                    TjsEngine::Global()->EvalExpression( ret, &cond);
                }TJS_CATCH
                if (cond.operator bool()) {
                    m_ifKey.top() = L"doing";
                }
                return 0;
            }
            else if (m_ifKey.top() == L"toend"){
                return 0;
            }
            return 0;
        }
    }
    else if (tag->name == L"endif")
    {
        tag->print();
        m_ifKey.pop();
        return 0;
    }
    if (m_ifKey.size()>0 && (m_ifKey.top() == L"toend" || m_ifKey.top() == L"toelse")) {
        return 0;
    }
    tag->print();
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


NCB_REGISTER_CLASS_DIFFER(KAGController, TjsKAGController)
{
    TJS_FACTORY
    NCB_METHOD(doTag);
    NCB_METHOD(stepOutLabel);
    NCB_METHOD(stepNext);
    NCB_METHOD(stepInLabel);
};
