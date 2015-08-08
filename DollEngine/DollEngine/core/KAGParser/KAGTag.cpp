//
//  KAGTag.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "KAGTag.h"
#include "KAGStorage.h"
#include "KAGLabel.h"
#include "ScriptEngine.h"

DE_BEGIN


void KAGTag::addParam(const wstring& key, const wstring& value,bool entity,bool macroarg)
{
    {
        if (key == L"cond") {
            hasCond = true;
        }
        KAGTagParamValue v;
        v.key = key;
        v.value = value;
        v.macroarg = macroarg;
        v.entity = entity;
        int startIdx = 0;
        if (entity) {
            startIdx = 1;
        }
        if(value.size() > 1 && value.at(startIdx) == value.at(value.size()-1))
        {
            if(value.at(startIdx)=='\"'||value.at(startIdx) == '\'')
            {
                v.isstring = true;
            }
        }
        params.push_back(v);
    }
}

bool KAGTag::exsitKey(const wstring& key)
{
    for (const KAGTagParamValue& pr : params)
    {
        if (pr.key == key) {
            return true;
        }
    }
    return false;
}

wstring KAGTag::getValue(const wstring& key)
{
    for (const KAGTagParamValue& pr : params)
    {
        if (pr.key == key) {
            return pr.value;
        }
    }
    return L"";
}

KAGTag* KAGTag::clone()
{
    KAGTag* tag = new KAGTag();
    tag->line = line;
    tag->storage = storage;
    tag->label = label;
    tag->name = name;
    tag->hasCond = hasCond;
    for (auto iter = params.begin();
         iter != params.end(); ++iter) {
        KAGTagParamValue v(*iter);
        tag->params.push_back(v);
    }
    return tag;
}

void KAGTag::print()
{
    wstring str = L"(#";
    if (name == L"ch") {
        str = L"";
    }
    else
    {
        str += DE::UnicodeWithFormat(L"%d",line);
        str += L") @";
        str += name;
    }
    if (name == L"iscript")
    {
        str += L"\n// some code...";
    }
    else
    {
        for(auto iter=params.begin();iter != params.end();++iter)
        {
            if(name == L"ch" && (*iter).key==L"text") {
                str = (*iter).value;
            }
            else {
                str += L" ";
                str += (*iter).key;
                str += L"=";
                str += (*iter).value;
            }
        }
    }
    ScriptEngine::GetInstance()->print(str);
}

DE_END