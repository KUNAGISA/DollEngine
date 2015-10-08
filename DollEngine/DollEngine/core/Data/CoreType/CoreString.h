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

class String : public std::wstring
{
public:
    static String fromFormat(const char* format,...);
public:
    String();
    String(char v);
    String(wchar_t v);
    String(char* v,int len);
    String(wchar_t* v,int len);
    String(const char* v);
    String(const wchar_t* v);
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
    void append(const String& v);
    size_type find(const String& v,size_type start=0);
    size_type rfind(const String& v,size_type start=0);
    String substr(size_type start=0,size_type length=-1);
    void split(const String& t,vector<String>& ret,bool ignoreEmpty=false);
    bool empty() const;
public:
public:
    int intValue();
    int64_t int64Value();
    double doubleValue();
    double floatValue();
    string utf8Value() const;
    const char* c_nstr() const;
};

bool operator != (const String& lv,const char* rv) {
    return lv != String(rv);
}
bool operator == (const String& lv,const char* rv) {
    return lv == String(rv);
}
String operator + (const String& lv,const char* rv){
    return lv+String(rv);
}
String operator + (const char* lv,const String& rv){
    return String(lv)+rv;
}

DE_END



#endif /* defined(__DollEngine__String__) */
