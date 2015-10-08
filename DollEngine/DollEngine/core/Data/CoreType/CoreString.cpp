//
//  String.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/7.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CoreString.h"

DE_BEGIN

static const int g_maxLen = 16*1024;
static char g_tmpStr[g_maxLen+1];

String String::fromFormat(const char* format,...)
{
    va_list args;
    memset(g_tmpStr, 0, sizeof(g_tmpStr));
    va_start(args, format);
    vsprintf(g_tmpStr, format, args);
    va_end(args);
    return String((const char*)g_tmpStr);
}

String::String()
{

}

String::String(char v)
{

}

String::String(wchar_t v)
{

}

String::String(char* v,int len)
{

}

String::String(wchar_t* v,int len)
{

}

String::String(const string& v)
{

}

String::String(const wstring& v)
{

}

String::String(const String& v)
{

}

String::String(int v)
{

}

String::String(double v)
{

}

String::String(float v)
{

}

String::String(int64_t v)
{

}

String::~String()
{

}

bool String::readFromFile(const String& path)
{
    return false;
}

int String::intValue()
{
    return -1;
}

int64_t String::int64Value()
{
    return -1;
}

double String::doubleValue()
{
    return 0;
}

string String::utf8Value() const
{
    return "";
}


DE_END
