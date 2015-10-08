//
//  String.h
//  DollEngine
//
//  Created by DollStudio on 15/10/7.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__String__
#define __DollEngine__String__

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
    static const char* fromFormat(const char* format,...);
public:
    String();
    String(char v);
    String(wchar_t v);
    String(char* v,int len);
    String(wchar_t* v,int len);
    String(const char* v);
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
    const String& operator+ (const String& v) const;
    const String& operator+= (const String& v) const;
    const String& operator<< (const String& v) const;
    bool operator< (const String& v) const;
    bool operator> (const String& v) const;
    bool operator== (const String& v) const;
    bool operator!= (const String& v) const;
    String operator[] (const String& v);
public:
    int toInt();
    int64_t toInt64();
    double toDouble();
    char toChar();
    wchar_t toWChar();
    const string& toUtf8() const;
    const wstring& toUnicode() const;
    const char* c_str() const;
    const wchar_t* c_wstr() const;
private:
    string str;
    wstring wstr;
    Encode encode;
};

DE_END



#endif /* defined(__DollEngine__String__) */
