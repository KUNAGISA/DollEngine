//
//  StringUtils.h
//  Krkr_GL
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__StringUtils__
#define __Krkr_GL__StringUtils__

#include "Macros.h"

class IOData;
class StringUtils
{
public:
    static wstring IntToWString(int value);
    static wstring StringFromFormat(const wchar_t* format,...);
    static void StringSplit(const wstring& src, const wstring& code, vector<wstring>& vec);
//    static int GetUtf8Len(const  char* str);
//    static string SubUtf8String(const  char* str,int start,int end);
//    static void ConvertUtf8ToVector(const string& _in, vector<string>& _out);
    static void ConvertUtf8ToUnicode(const string& src, wchar_t& target);
    static unsigned char* ConvertUtf8ToUnicode(unsigned char* src, wchar_t& target);
    static void ConvertUtf8ToUnicode(const char* src, wstring& target);
    static void ConvertUnicodeToUtf8(const wstring& src, string& target);
    static unsigned char* ConvertUnicodeToUtf8(int& src, unsigned char* target);
};

#endif /* defined(__Krkr_GL__StringUtils__) */
