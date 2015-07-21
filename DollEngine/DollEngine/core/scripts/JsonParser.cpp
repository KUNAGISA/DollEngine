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

tTJSVariant JsonParser::FromJsonFile(const string& path)
{
    string fullpath = Storages::GetInstance()->getFullPath(path);
    IOData* data = Storages::GetFileString(fullpath);
    if (data) {
        string error;
        wstring code;
        data->convertToUnicode(code);
        SAFF_DELETE(data);
        tTJSVariant ret = JsonParser::FromJsonString(code.c_str());
        return ret;
    }
    return tTJSVariant();
}

tTJSVariant JsonParser::FromJsonString(const char *str)
{
    wstring wstr;
    Utf8ToUnicode(str, wstr);
    return FromJsonString(wstr.c_str());
}

tTJSVariant JsonParser::FromJsonString(const wchar_t* str)
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
            Debug::throwMsg("JSON语法错误");
            return null;
        }
        str = valueWithString(str, value);
        if (!str) {
            Debug::throwMsg("JSON语法错误");
            return null;
        }
        obj->PropSetByNum(TJS_MEMBERENSURE, i, &value, obj);
        
        str = emptyWithString(str);
        if (!str) {
            Debug::throwMsg("JSON语法错误");
            return null;
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
        Debug::throwMsg("JSON语法错误");
        return null;
    }
    return str;
}

wchar_t* JsonParser::dictWithString(wchar_t* str,tTJSVariant& _out)
{
    tTJSDictionaryObject* obj = dynamic_cast<tTJSDictionaryObject*>(TJSCreateDictionaryObject());
    while (true) {
        wstring key;
        tTJSVariant value;
        str = emptyWithString(str);
        if (!str) {
            Debug::throwMsg("JSON语法错误");
            return null;
        }
        if (*str != '\"') {
            Debug::throwMsg("JSON语法错误");
            return null;
        }
        str = stringWithString(str+1, key);
        str = emptyWithString(str);
        if (*str != ':') {
            Debug::throwMsg("JSON语法错误");
            return null;
        }
        str = valueWithString(str+1,value);
        if (!str) {
            Debug::throwMsg("JSON语法错误");
            return null;
        }
        obj->PropSet(TJS_MEMBERENSURE, key.c_str(), null, &value, obj);
        str = emptyWithString(str);
        if (!str) {
            Debug::throwMsg("JSON语法错误");
            return null;
        }
        if (*str == '}') {
            _out = obj;
            return str+1;
        }
        if (*str == ',') {
            ++str;
            continue;
        }
        Debug::throwMsg("JSON语法错误");
        return null;
    }
}

wchar_t* JsonParser::valueWithString(wchar_t* str,tTJSVariant& _out)
{
    wchar_t* str2 = emptyWithString(str);
    if (!str2) {
        Debug::throwMsg("JSON语法错误");
        return null;
    }
    wchar_t& ch = *str2;
    if (ch == ',') {
        Debug::throwMsg("JSON语法错误");
        return null;
    }
    if (ch <= '9' && ch >= '0') {
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
    Debug::throwMsg("JSON语法错误");
    return null;
    
}

wchar_t* JsonParser::stringWithString(wchar_t* str,wstring& _out)
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
    Debug::throwMsg("JSON语法错误");
    return null;
}

wchar_t* JsonParser::stringWithString(wchar_t* str,tTJSVariant& _out)
{
    wstring wstr;
    wchar_t* res = stringWithString(str, wstr);
    if (res) {
        _out = wstr;
        return res;
    }
    Debug::throwMsg("JSON语法错误");
    return null;
}

wchar_t* JsonParser::nunberWithString(wchar_t* str,tTJSVariant& _out)
{
    wstring wstr;
    while (*str != L'\0') {
        wchar_t& ch = *str;
        if (ch <= '9' && ch >= '0') {
            wstr.push_back(ch);
            ++str;
            continue;
        }
        else {
            _out = wstr;
            _out.ToInteger();
            return str;
        }
    }
    Debug::throwMsg("JSON语法错误");
    return null;
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
    Debug::throwMsg("JSON语法错误");
    return null;
}

DE_END
