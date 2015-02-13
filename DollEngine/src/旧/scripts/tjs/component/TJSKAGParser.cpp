//
//  TJSKAGParser.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/11/22.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSKAGParser.h"

void TJSKAGParser::jumpTo(ttstr storage, ttstr label)
{
    if (label.IsEmpty() || label.length() == 0)
    {
        label = L"_def_";
    }
    if (storage.IsEmpty() || storage.length() == 0)
    {
        storage = m_currentStorage->fileName;
    }
    KAGParser::jumpTo(storage.AsStdString(),label.AsStdString());
}

void TJSKAGParser::callLabel(ttstr storage,ttstr label)
{
    if (label.IsEmpty() || label.length() == 0)
    {
        label = L"_def_";
    }
    if (storage.IsEmpty() || storage.length() == 0)
    {
        storage = m_currentStorage->fileName;
    }
    KAGParser::callLabel(storage.AsStdString(),label.AsStdString());
}

int TJSKAGParser::execute(KAGTag* tag)
{
    tag->print();
    if (tag->name == L"return")
    {
        returnCall();
        return -1;
    }
    Scripts::GetInstance()->pushFile(tag->storage->fileName);
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
            ScriptsTJS::GetTjs()->EvalExpression( kv.value, &ret) ;
        }
        else if (kv.macroarg)
        {
            ScriptsTJS::GetTjs()->EvalExpression( (L"mp."+kv.value.substr(1)), &ret) ;
        }
        else
        {
            ret = kv.value;
        }
        iTJSProSet(params, key.GetString(), ret);
    }
    tTJSVariant params_t = params;
    params->Release();
    iTJSEventCall(onExecute,2,&name,&params_t);
    Scripts::GetInstance()->popFile();
    return (int)result.AsInteger();
}

NCB_REGISTER_CLASS_DIFFER(KAGParser, TJSKAGParser)
{
    iTJS_FACTORY_COM
    NCB_METHOD(jumpTo);
    NCB_METHOD(doNext);
    NCB_METHOD(callLabel);
    NCB_METHOD(callMacro);
    NCB_METHOD(returnCall);
    NCB_METHOD(onExecute);
};
