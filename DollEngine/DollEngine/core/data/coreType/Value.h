//
//  Value.h
//  DollEngine
//
//  Created by DollStudio on 15/10/7.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Value__
#define __DollEngine__Value__

#include "CoreMacros.h"

DE_BEGIN

class String
{
public:
    enum Encode {
        Utf8 = 0,
        Unicode
    };
public:
    String();
    String(char v);
    String(wchar_t v);
    String(char* v,int len);
    String(wchar_t* v,int len);
    String(const string& v);
    String(const wstring& v);
    String(const String& v);
    String(int v);
    String(double v);
    String(float v);
    String(int64_t v);
    ~String();
public:
    bool readFromFile(const String& path);
public:
    const String& operator+ (const String& v);
    const String& operator+= (const String& v);
    const String& operator<< (const String& v);
    String operator[] (const String& v);
    bool operator< (const String& v);
    bool operator> (const String& v);
    bool operator== (const String& v);
public:
    int toInt();
    int64_t toInt64();
    double toDouble();
    char toChar();
    wchar_t toWChar();
    const string& toUtf8();
    const wstring& toUnicode();
    const char* c_str();
    const wchar_t* c_wstr();
private:
    string str;
    wstring wstr;
    Encode encode;
};

DE_END



#endif /* defined(__DollEngine__Value__) */
