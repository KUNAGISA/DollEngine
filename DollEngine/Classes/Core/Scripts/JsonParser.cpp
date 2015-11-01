//
//  JsonParser.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "JsonParser.h"
#include "Storages.h"

DE_BEGIN

tTJSVariant JsonParser::fromJsonFile(const String& path)
{
    String code;
    if(code.loadFromFile(path))
    {
        return fromJsonString(code.c_str());
    }
    return tTJSVariant();
}

tTJSVariant JsonParser::fromJsonString(const wchar_t* str)
{
    tTJSVariant result;
    wchar_t* str2 = (wchar_t*)str;
    str2 = emptyWithString(str2);
    const wchar_t& ch = *str2;
    if (ch == L'[') {
        str2 = arrayWithString(str2+1,result);
        if (!str2) {
            return tTJSVariant();
        }
        return result;
    }
    else if (ch == L'{') {
        str2 = dictWithString(str2+1, result);
        if (!str2) {
            return tTJSVariant();
        }
        return result;
    }
    else {
        return tTJSVariant();
    }
}

wchar_t* JsonParser::arrayWithString(wchar_t* str,tTJSVariant& _out)
{
    tTJSArrayObject* obj = (tTJSArrayObject*)TJSCreateArrayObject();
    int i=0;
    while (true) {
        tTJSVariant value;
        str = emptyWithString(str);
        if (!str) {
            EM("JSON语法错误");
            return NULL;
        }
        if (*str == ']') {
            _out.SetObject(obj, obj);
            return str+1;
        }
        str = valueWithString(str, value);
        if (!str) {
            EM("JSON语法错误");
            return NULL;
        }
        obj->PropSetByNum(TJS_MEMBERENSURE, i, &value, obj);
        
        str = emptyWithString(str);
        if (!str) {
            EM("JSON语法错误");
            return NULL;
        }
        if (*str == ']') {
            _out.SetObject(obj, obj);
            return str+1;
        }
        if (*str == ',') {
            ++str;
            ++i;
            continue;
        }
        EM("JSON语法错误");
        return NULL;
    }
    return str;
}

wchar_t* JsonParser::dictWithString(wchar_t* str,tTJSVariant& _out)
{
    tTJSDictionaryObject* obj = dynamic_cast<tTJSDictionaryObject*>(TJSCreateDictionaryObject());
    while (true) {
        String key;
        tTJSVariant value;
        str = emptyWithString(str);
        if (!str) {
            EM("JSON语法错误");
            return NULL;
        }
        if (*str == '}') {
            _out.SetObject(obj,obj);
            return str+1;
        }
        if (*str != '\"') {
            EM("JSON语法错误");
            return NULL;
        }
        str = stringWithString(str+1, key);
        str = emptyWithString(str);
        if (*str != ':') {
            EM("JSON语法错误");
            return NULL;
        }
        str = valueWithString(str+1,value);
        if (!str) {
            EM("JSON语法错误");
            return NULL;
        }
        obj->PropSet(TJS_MEMBERENSURE, key.c_str(), NULL, &value, obj);
        str = emptyWithString(str);
        if (!str) {
            EM("JSON语法错误");
            return NULL;
        }
        if (*str == '}') {
            _out.SetObject(obj,obj);
            return str+1;
        }
        if (*str == ',') {
            ++str;
            continue;
        }
        EM("JSON语法错误");
        return NULL;
    }
}

wchar_t* JsonParser::valueWithString(wchar_t* str,tTJSVariant& _out)
{
    wchar_t* str2 = emptyWithString(str);
    if (!str2) {
        EM("JSON语法错误");
        return NULL;
    }
    wchar_t& ch = *str2;
    if (ch == ',') {
        EM("JSON语法错误");
        return NULL;
    }
    if (str2[0]=='f'&&
        str2[1]=='a'&&
        str2[2]=='l'&&
        str2[3]=='s'&&
        str2[4]=='e') {
        _out = false;
        return str2+5;
    }
    if (str2[0]=='t'&&
        str2[1]=='r'&&
        str2[2]=='u'&&
        str2[3]=='e') {
        _out = true;
        return str2+4;
    }
    if (str2[0]=='n'&&
        str2[1]=='u'&&
        str2[2]=='l'&&
        str2[3]=='l') {
        return str2+4;
    }
    if (str2[0]=='N'&&
        str2[1]=='U'&&
        str2[2]=='L'&&
        str2[3]=='L') {
        return str2+4;
    }
    if (ch <= '9' && ch >= '0') {
        return nunberWithString(str2,_out);
    }
    if (ch == '-') {
        return nunberWithString(str2,_out);
    }
    if (ch == '\"') {
        return stringWithString(str2+1, _out);
    }
    if (ch == '{') {
        return dictWithString(str2+1, _out);
    }
    if (ch == '[') {
        return arrayWithString(str2+1, _out);
    }
    
    
    EM("JSON语法错误");
    return NULL;
    
}

wchar_t* JsonParser::stringWithString(wchar_t* str,String& _out)
{
    _out.clear();
    while (*str != L'\0') {
        wchar_t& ch = *str;
        switch (ch) {
            case L'\\':
            {
                str++;
                _out.push_back(*str);
            }
                break;
            case L'\"':
            {
                return str+1;
            }
                break;
            default:
                _out.push_back(ch);
                break;
        }
        str++;
    }
    EM("JSON语法错误");
    return NULL;
}

wchar_t* JsonParser::stringWithString(wchar_t* str,tTJSVariant& _out)
{
    String wstr;
    wchar_t* res = stringWithString(str, wstr);
    if (res) {
        _out = wstr;
        return res;
    }
    EM("JSON语法错误");
    return NULL;
}

wchar_t* JsonParser::nunberWithString(wchar_t* str,tTJSVariant& _out)
{
    String wstr;
    int dcount = 0;
    int ccount = 0;
    while (*str != L'\0') {
        wchar_t& ch = *str;
        if (ch <= '9' && ch >= '0') {
            wstr.push_back(ch);
            ++str;
            continue;
        }
        else if (ch == '.' && dcount==0) {
            dcount++;
            wstr.push_back(ch);
            ++str;
            continue;
        }
        else if (ch == '-' && ccount==0) {
            ccount++;
            wstr.push_back(ch);
            ++str;
            continue;
        }
        else {
            _out = wstr;
            _out.tonumber();
            return str;
        }
    }
    EM("JSON语法错误");
    return NULL;
}

wchar_t* JsonParser::emptyWithString(wchar_t* str)
{
    while (*str != L'\0') {
        if (*str <= L' ') {
            ++str;
            continue;
        }
        else {
            return str;
        }
    }
    EM("JSON语法错误");
    return NULL;
}

DE_END
