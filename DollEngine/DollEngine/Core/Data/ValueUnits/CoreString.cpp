//
//  String.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/7.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CoreString.h"
#include "Storages.h"
#include "IOData.h"

DE_BEGIN

unsigned int utf8_len_for_table[256] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
};

#define UTFLEN(x)  utf8_len_for_table[(int)(x)]

static const int g_maxLen = 16*1024-1;
static char g_tmpStr[g_maxLen+1];
static wchar_t g_tmpWStr[g_maxLen+1];

String String::fromFormat(const char* format,...)
{
    va_list args;
    memset(g_tmpStr, 0, sizeof(g_tmpStr));
    va_start(args, format);
    vsprintf(g_tmpStr, format, args);
    va_end(args);
    return String((const char*)g_tmpStr);
}

String String::fromFormat(const wchar_t* format,...)
{
    va_list args;
    memset(g_tmpWStr, 0, sizeof(g_tmpStr));
    va_start(args, format);
    vswprintf(g_tmpWStr,g_maxLen, format, args);
    va_end(args);
    return String(g_tmpWStr);
}

String::String()
{

}

String::String(wchar_t* v,size_type l)
{
    wstring::assign(v, l);
}

String::String(const char* v)
{
    assign(v);
}

String::String(const string& v)
{
    assign(v.c_str());
}

String::String(const wchar_t* v)
{
    wstring::assign(v);
}

String::String(const wstring& v)
{
    wstring::assign(v);
}

String::String(const String& v)
{
    wstring::assign(v);
}

String::String(int v)
{

}

String::String(double v)
{

}

String::String(int64_t v)
{

}

String::~String()
{

}

bool String::loadFromFile(const String& path)
{
    String fullpath = Storages::GetInstance()->getFullPath(path);
    if(fullpath.empty()){
        return false;
    }
    IOData* data = Storages::GetFileString(fullpath);
    if(!data){
        return false;
    }
    //这里应该判断是哪种编码格式
    assign((const char*)data->getBuffer());
    delete data;
    return true;
}

String& String::assign(const char* src)
{
    clear();
    if (src == NULL) {
        return *this;
    }
    char* ch = (char*)src;
    while (*ch != '\0')
    {
        wchar_t ot;
        int len = UTFLEN(*ch & 0xff);
        switch(len)
        {
            case 1:
            {
                ot = ch[0];
            }
                break;
            case 2:
            {
                ot = ((int)(ch[0]&0x1F)) << 6;
                ot |= ch[1]&0x3F;
            }
                break;
            case 3:
            {
                ot = ((int)(ch[0]&0x1F)) << 12;
                ot |= ((int)(ch[1]&0x3F)) << 6;
                ot |= ch[2]&0x3F;
            }
                break;
            case 4:
            {
                ot = ((int)(ch[0]&0x07)) << 18;
                ot |= ((int)(ch[1]&0x3F)) << 12;
                ot |= ((int)(ch[2]&0x3F)) << 6;
                ot |= ch[3]&0x3F;
            }
                break;
            case 5:
            {
                ot = ((int)(ch[0]&0x03)) << 24;
                ot |= ((int)(ch[1]&0x3F)) << 18;
                ot |= ((int)(ch[2]&0x3F)) << 12;
                ot |= ((int)(ch[3]&0x3F)) << 6;
                ot |= ch[4]&0x3F;
            }
                break;
            case 6:
            {
                ot = ((int)(ch[0]&0x01)) << 30;
                ot |= ((int)(ch[1]&0x3F)) << 24;
                ot |= ((int)(ch[2]&0x3F)) << 18;
                ot |= ((int)(ch[3]&0x3F)) << 12;
                ot |= ((int)(ch[4]&0x3F)) << 6;
                ot |= ch[5]&0x3F;
            }
                break;
            default:
                break;
        }
        push_back(ot);
        ch+=len;
    }
    return *this;
}

String& String::assign(wchar_t* v,size_type l)
{
    wstring::assign(v,l);
    return *this;
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




static string g_target;
string String::utf8Value() const
{
    g_target.clear();
    if (empty()) {
        return g_target;
    }
    wchar_t* ch = (wchar_t*)c_str();
    unsigned char pOutput[7];
    while (*ch != L'\0')
    {
        memset(pOutput, 0, 7);
        int unic = (int)*ch;
        
        if ( unic <= 0x0000007F )
        {
            // * U-00000000 - U-0000007F:  0xxxxxxx
            *pOutput     = (unic & 0x7F);
        }
        else if ( unic >= 0x00000080 && unic <= 0x000007FF )
        {
            // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
            *(pOutput+1) = (unic & 0x3F) | 0x80;
            *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        }
        else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
        {
            // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
            *(pOutput+2) = (unic & 0x3F) | 0x80;
            *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
            *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        }
        else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
        {
            // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            *(pOutput+3) = (unic & 0x3F) | 0x80;
            *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
            *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
            *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
        }
        else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
        {
            // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            *(pOutput+4) = (unic & 0x3F) | 0x80;
            *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
            *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
            *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
            *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
        }
        else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
        {
            // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            *(pOutput+5) = (unic & 0x3F) | 0x80;
            *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;
            *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;
            *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;
            *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;
            *pOutput     = ((unic >> 30) & 0x01) | 0xFC;
        }
        g_target.append((const char*)pOutput);
        ++ch;
    }
    return g_target;
}

const char* String::c_nstr() const
{
    return utf8Value().c_str();
}


DE_END
