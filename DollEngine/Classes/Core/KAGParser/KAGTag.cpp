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
#include "System.h"

DE_BEGIN


void KAGTag::addParam(const String& key, const String& value,bool entity,bool macroarg)
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
        if(value.size() > 1)
        {
            wchar_t ch1 = value.at(startIdx);
            wchar_t ch2 = value.at(value.size()-1);
            if (ch1 == ch2 &&
                (ch1 == L'\"' || ch1 == L'\'')) {
                v.isstring = true;
            }
        }
        params.push_back(v);
    }
}

bool KAGTag::exsitKey(const String& key)
{
    for (const KAGTagParamValue& pr : params)
    {
        if (pr.key == key) {
            return true;
        }
    }
    return false;
}

String KAGTag::getValue(const String& key)
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

void KAGTag::print(bool cond)
{
    if (System::GetInstance()->getDebugMode() <= 1) {
        return;
    }
    if (System::GetInstance()->getDebugMode() <= 2 &&
        label->isMacro) {
        return;
    }
    if(cond){
        String str = L"(#";
        if (name == L"ch") {
            str = L"";
        }
        else
        {
            str += String::fromFormat(L"%d",line);
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
        DE::Console::GetInstance()->log(str);
    }
    else {
        DE::Console::GetInstance()->log(L"[COND FALSE] ");
    }
}

DE_END
