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
    static String fromFormat(const wchar_t* format,...);
public:
    String();
    String(wchar_t* v,size_type l);
    String(const char* v);
    String(const string& v);
    String(const wchar_t* v);
    String(const wstring& v);
    String(const String& v);
    String(int v);
    String(double v);
    String(int64_t v);
    ~String();
public:
    bool loadFromFile(const String& path);
    String& assign(const char* v);
    String& assign(wchar_t* v,size_type l);
    void split(const String& t,vector<String>& ret,bool ignoreEmpty=false);
public:
    String& operator += (const String& v){
        append(v);
        return *this;
    }
    String& operator = (const char* v){
        assign(v);
        return *this;
    }
public:
    int intValue();
    int64_t int64Value();
    double doubleValue();
    double floatValue();
    string utf8Value() const;
    const char* c_nstr() const;
};


DE_END

//bool operator != (const DE::String& lv,const char* rv) {
//    return lv != DE::String(rv);
//}
//bool operator == (const DE::String& lv,const char* rv) {
//    return lv == DE::String(rv);
//}
//DE::String operator + (const DE::String& lv,const char* rv){
//    return lv+DE::String(rv);
//}
//DE::String operator + (const char* lv,const DE::String& rv){
//    return DE::String(lv)+rv;
//}


#endif /* defined(__DollEngine__String__) */
