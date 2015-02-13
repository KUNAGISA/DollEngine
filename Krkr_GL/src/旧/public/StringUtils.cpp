//
//  StringUtils.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "StringUtils.h"
#include "IOData.h"
#include "GlobalTJS.h"

wstring StringUtils::IntToWString(int value)
{
    wchar_t temp[64];
    memset(temp, 0, 64);
    swprintf(temp, 64, L"%d", value);
    return temp;
}

static const int kMaxFormatLen = 16*1024;
static wchar_t s_sff[kMaxFormatLen+1];
wstring StringUtils::StringFromFormat(const wchar_t* format,...)
{
    __darwin_va_list args;
    va_start(args, format);
    memset(s_sff, 0, sizeof(s_sff));
    vswprintf(s_sff, kMaxFormatLen, format, args);
    va_end(args);
    return s_sff;
}

void StringUtils::StringSplit(const wstring& src, const wstring& code, vector<wstring>& vec)
{
    vec.clear();
    if (src.length() == 0)
    {
        return;
    }
    size_t pos = src.find(code);
    size_t last_pos = 0;
    while (pos != src.npos)
    {
        wstring temp = src.substr(last_pos,pos-last_pos);
        vec.push_back(temp);
        last_pos = pos;
        pos = src.find(code,last_pos+code.length());
    }
    wstring tem = src.substr(last_pos);
    vec.push_back(tem);
}

//定义查找表，长度256，表中的数值表示以此为起始字节的utf8字符长度
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

void StringUtils::ConvertUtf8ToUnicode(const string& ch, wchar_t& ot)
{
    ot = 0;
    if (ch.empty())
    {
        return;
    }
    switch(ch.size())
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
            return;
    }
}

unsigned char* StringUtils::ConvertUtf8ToUnicode(unsigned char* ch, wchar_t& ot)
{
    ot = 0;
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
    return ch+len;
}

void StringUtils::ConvertUtf8ToUnicode(const char* src, wstring& target)
{
    target.clear();
    if (src == null) {
        return;
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
        target += ot;
        ch+=len;
    }
}

void StringUtils::ConvertUnicodeToUtf8(const wstring& src, string& target)
{
    unsigned char out[7];
    for (int i=0; i<src.size(); ++i)
    {
        memset(out, 0, 7);
        int t = src[i];
        StringUtils::ConvertUnicodeToUtf8(t,out);
        target.append((const char*)out);
    }
}

unsigned char* StringUtils::ConvertUnicodeToUtf8(int& unic, unsigned char* pOutput)
{
    if ( unic <= 0x0000007F )
    {
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *pOutput     = (unic & 0x7F);
        return pOutput+1;
    }
    else if ( unic >= 0x00000080 && unic <= 0x000007FF )
    {
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(pOutput+1) = (unic & 0x3F) | 0x80;
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        return pOutput+2;
    }
    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
    {
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(pOutput+2) = (unic & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        return pOutput+3;
    }
    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
    {
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+3) = (unic & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
        return pOutput+4;
    }
    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
    {
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+4) = (unic & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
        return pOutput+5;
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
        return pOutput+6;
    }
    return null;
}

//
//int StringUtils::GetUtf8Len(const  char* str)
//{
//    size_t clen = strlen(str);
//    int len = 0;
//
//    for(const char *ptr = str;
//        *ptr!=0&&len<clen;
//        len++, ptr+=UTFLEN((unsigned char)*ptr));
//
//    return len;
//}
//
//string StringUtils::SubUtf8String(const  char* str,int start,int end)
//{
//    int len = StringUtils::GetUtf8Len(str);
//
//    if(start >= len) return NULL;
//    if(end > len) end = len;
//
//    const char *sptr = str;
//    for(int i = 0; i < start; ++i,sptr+=UTFLEN((unsigned char)*sptr));
//
//    const char *eptr = sptr;
//    for(int i = start; i < end; ++i,eptr += UTFLEN((unsigned char)*eptr));
//
//    size_t retLen = eptr - sptr;
//    char *retStr = (char*)malloc(retLen+1);
//    memcpy(retStr, sptr, retLen);
//    retStr[retLen] = 0;
//    string tmp = retStr;
//    free(retStr);
//    return tmp;
//}
//
//void StringUtils::ConvertUtf8ToVector(const string& _in, vector<string>& _out)
//{
//    for (int i = 0; i < _in.size();)
//    {
//        int len = UTFLEN(_in[i] & 0xff);
//        string o(_in.c_str()+i,len);
//        _out.push_back(o);
//        i+=len;
//    }
//}

