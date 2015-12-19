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
                ScriptEngine::Global()->EvalExpression( kv.value.substr(2,kv.value.length()-3), &ret) ;
            }TJS_CATCH
        }
        else {
            try {
                ScriptEngine::Global()->EvalExpression( kv.value.substr(1), &ret) ;
            }TJS_CATCH
        }
    }
    else if (kv.isstring)
    {
        try {
            ScriptEngine::Global()->EvalExpression( kv.value, &ret) ;
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
                ScriptEngine::Global()->EvalExpression( (L"mp."+v1), &r1) ;
                if (r1.operator bool()) {
                    ret = r1;
                }
                else {
                    v2 = kv.value.substr(p+1);
                    tTJSVariant r2;
                    ScriptEngine::Global()->EvalExpression( v2, &r2) ;
                    ret = r2;
                }
            }
            else {
                ScriptEngine::Global()->EvalExpression( (L"mp."+kv.value.substr(1)), &ret) ;
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
        if(!stepNext())
        {
            return -2;
        }
    }
    KAGTag * tag = m_label->allTags[m_tagIndex];
    if (tag->name == L"macro") {
        wstring macroname = tag->getValue(L"name");
        KAGParser::GetInstance()->startMacro(macroname);
        while (true) {
            ++m_tagIndex;
            if (m_tagIndex>=m_label->allTags.size()) {
                EM(ERROR_KAG_UNKONW);
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
            ScriptEngine::Global()->EvalExpression( ret, &cond);
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
            ScriptEngine::Global()->EvalExpression( ret, &cond);
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
            EM(ERROR_KAG_IF_FAIL, tag->line);
        }
    }
    else if (tag->name == L"elsif")
    {
        tag->print();
        tTJSVariant ret;
        GetTagParamsValue(tag,L"exp",ret);
        if (m_ifKey.size() == 0) {
            EM(ERROR_KAG_IF_FAIL, tag->line);
        }
        else
        {
            if (m_ifKey.top() == L"doing") {
                m_ifKey.top() = L"toend";
            }
            else if(m_ifKey.top() == L"toelse"){
                tTJSVariant cond;
                try {
                    ScriptEngine::Global()->EvalExpression( ret, &cond);
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
    ScriptEngine::GetInstance()->pushFile(tag->storage->fileName);
    tTJSDictionaryObject* params = (tTJSDictionaryObject*)TJSCreateDictionaryObject();
    tTJSVariant name = tag->name.c_wstr();
    for (auto iter = tag->params.begin();
         iter != tag->params.end(); ++iter)
    {
        KAGTagParamValue& kv = *iter;
        tTJSVariant key = kv.key.c_wstr();
        tTJSVariant ret;
        GetTagParamValue(kv,ret);
        params->PropSet(TJS_MEMBERENSURE,key.GetString(),NULL,&ret,params);
    }
    tTJSVariant params_t = params;
    params->Release();
    TJS_EVENT_CALL(onExecute,2,&name,&params_t);
    ScriptEngine::GetInstance()->popFile();
    return (int)result.AsInteger();
}

tTJSVariant TjsKAGController::saveStack()
{
    tTJSArrayObject* datas = (tTJSArrayObject*)TJSCreateArrayObject();
    
    vector<KAGStack> tempStack = m_stack;
    KAGStack cur={m_storage,m_label,m_tagIndex-1};
    tempStack.push_back(cur);
    int idx = 0;
    for(const KAGStack& stack : tempStack) {
        tTJSVariant storagePath = stack.storage->fullPath.c_wstr();
        tTJSVariant labelKey = stack.label->key.c_wstr();
        tTJSVariant tagIndex = stack.tagIndex;
        
        datas->PropSetByNum(TJS_MEMBERENSURE,idx,&storagePath,datas);
        ++idx;
        datas->PropSetByNum(TJS_MEMBERENSURE,idx,&labelKey,datas);
        ++idx;
        datas->PropSetByNum(TJS_MEMBERENSURE,idx,&tagIndex,datas);
        ++idx;
    }
    return datas;
}

bool TjsKAGController::loadStack(tTJSVariant v)
{
    tTJSArrayObject* datas = dynamic_cast<tTJSArrayObject*>(v.AsObjectNoAddRef());
    if(!datas) {
        return false;
    }
    int count = TJSGetArrayElementCount(datas);
    if(count%3!=0){
        return false;
    }
    DE::ScriptEngine::GetInstance()->clearFile();
    
    m_stack.clear();
    for(int i = 0; i < count; i+= 3) {
        tTJSVariant storagePath;
        datas->PropGetByNum(TJS_MEMBERENSURE,i,&storagePath,datas);
        tTJSVariant labelKey;
        datas->PropGetByNum(TJS_MEMBERENSURE,i+1,&labelKey,datas);
        tTJSVariant tagIndex;
        datas->PropGetByNum(TJS_MEMBERENSURE,i+2,&tagIndex,datas);
        
        KAGStorage* storage = KAGParser::GetInstance()->loadScenario(storagePath.AsStringNoAddRef()->operator const tjs_char *());
        ScriptEngine::GetInstance()->pushFile(storage->fileName);
        KAGLabel* label = storage->getLabel(labelKey.AsStringNoAddRef()->operator const tjs_char *());
        KAGStack cur = {storage, label, (int)tagIndex.AsInteger()};
        m_stack.push_back(cur);
    }
    return true;
}

NCB_REGISTER_CLASS_DIFFER(KAGController, TjsKAGController)
{
    TJS_FACTORY
    NCB_METHOD(doTag);
    NCB_METHOD(stepOutLabel);
    NCB_METHOD(stepNext);
    NCB_METHOD(stepInLabel);
    NCB_METHOD(saveStack);
    NCB_METHOD(loadStack);
    NCB_PROPERTY_RO(lastTarget,getLastTargetTJS);
};
