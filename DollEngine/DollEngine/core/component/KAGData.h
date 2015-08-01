//
//  KAGData.h
//  Krkr_GL
//
//  Created by DollStudio on 14/11/16.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__KAGData__
#define __Krkr_GL__KAGData__

#include "CoreUnits.h"

DE_BEGIN

typedef wchar_t kagchar;

struct KAGTagParamValue
{
    KAGTagParamValue():entity(false),macroarg(false),isstring(false){}
    wstring key;
    wstring value;
    bool entity;//是否是需要eval的参数
    bool isstring;//是否是字符串
    bool macroarg;//是否是宏参数
};

class KAGStorage;
class KAGLabel;
class KAGParser;

class KAGTag
{
public:
    KAGTag():storage(null),label(null){}
    ~KAGTag(){
        params.clear();
    }
    void addParam(const wstring& key, const wstring& value,bool entity=false,bool macroarg=false)
    {
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
    
    bool exsitKey(const wstring& key)
    {
        for (const KAGTagParamValue& pr : params)
        {
            if (pr.key == key) {
                return true;
            }
        }
        return false;
    }
    
    wstring getValue(const wstring& key)
    {
        for (const KAGTagParamValue& pr : params)
        {
            if (pr.key == key) {
                return pr.value;
            }
        }
        return L"";
    }
    
    void print()
    {
        wstring str = L"(#";
        str += DE::UnicodeWithFormat(L"%d",line);
        str += L") @";
        str += name;
        if (name == L"iscript")
        {
            str += L"\n// some code...";
        }
        else
        {
            for(auto iter=params.begin();iter != params.end();++iter)
            {
                str += L" ";
                str += (*iter).key;
                str += L"=";
                str += (*iter).value;
            }
        }
        DM("%ls",str.c_str());
    }
    int exec(KAGParser* parser);
    int line;
    KAGStorage* storage;
    KAGLabel* label;
    wstring name;
    vector<KAGTagParamValue> params;
};

class KAGLabel
{
public:
    KAGLabel():isMacro(false),storage(null),nextLabel(null){}
    ~KAGLabel(){
        for(KAGTag* tag : allTags)
        {
            delete tag;
        }
        allTags.clear();
    }
    
    void addTag(KAGTag* tag){
        allTags.push_back(tag);
    }
    int exec(KAGParser* parser, int tag_index);
    KAGStorage* storage;
    wstring key;
    wstring name;
    vector<KAGTag*> allTags;
    bool isMacro;
    KAGLabel* nextLabel;
};

class KAGStorage
{
public:
    KAGStorage(){}
    ~KAGStorage(){
        for(auto iter : allLabels)
        {
            delete iter.second;
        }
        allLabels.clear();
    }
    void addLabel(KAGLabel* title){
        allLabels[title->key] = title;
    }
    KAGLabel* getLabel(const wstring& key)
    {
        auto iter = allLabels.find(key);
        if (iter == allLabels.end()) {
            return NULL;
        }
        return iter->second;
    }
    int exec(KAGParser* parser,const wstring& label_key, int tag_index);
    wstring fullPath;
    wstring fileName;
    map<wstring,KAGLabel*> allLabels;
};

struct KAGStack
{
    KAGStorage* storage;
    wstring labelKey;
    int tagIndex;
};

DE_END

#endif /* defined(__Krkr_GL__KAGData__) */
