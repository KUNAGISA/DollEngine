//
//  KAGTag.h
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__KAGTag__
#define __DollEngine__KAGTag__

#include "CoreUnits.h"

DE_BEGIN

typedef wchar_t kagchar;
class KAGParser;
class KAGLabel;
class KAGStorage;

struct KAGTagParamValue
{
    KAGTagParamValue():entity(false),macroarg(false),isstring(false){}
    KAGTagParamValue(const KAGTagParamValue& v){
        key = v.key;
        value = v.value;
        entity = v.entity;
        isstring = v.isstring;
        macroarg = v.macroarg;
    }
    wstring key;
    wstring value;
    bool entity;//是否是需要eval的参数
    bool isstring;//是否是字符串
    bool macroarg;//是否是宏参数
};


class KAGTag
{
public:
    KAGTag():storage(null),label(null),hasCond(false){}
    ~KAGTag(){
        params.clear();
    }
    void addParam(const wstring& key, const wstring& value,bool entity=false,bool macroarg=false);
    
    bool exsitKey(const wstring& key);
    
    wstring getValue(const wstring& key);
    
    KAGTag* clone();
    
    void print();
    int line;
    KAGStorage* storage;
    KAGLabel* label;
    wstring name;
    bool hasCond;
    vector<KAGTagParamValue> params;
};

DE_END

#endif /* defined(__DollEngine__KAGTag__) */
