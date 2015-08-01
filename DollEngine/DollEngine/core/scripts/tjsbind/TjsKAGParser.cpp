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

int TjsKAGParser::execute(KAGTag* tag)
{
    tag->print();
    if (tag->name == L"return")
    {
        returnCall();
        return -1;
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
        if (kv.entity)
        {
            if (kv.isstring) {
                TjsEngine::Global()->EvalExpression( kv.value.substr(2,kv.value.length()-3), &ret) ;
            }
            else {
                TjsEngine::Global()->EvalExpression( kv.value.substr(1), &ret) ;
            }
        }
        else if (kv.isstring)
        {
            TjsEngine::Global()->EvalExpression( kv.value, &ret) ;
        }
        else if (kv.macroarg)
        {
            TjsEngine::Global()->EvalExpression( (L"mp."+kv.value.substr(1)), &ret) ;
        }
        else
        {
            ret = kv.value;
        }
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
    NCB_METHOD(callLabel);
    NCB_METHOD(callMacro);
    NCB_METHOD(returnCall);
    NCB_METHOD(onExecute);
};
