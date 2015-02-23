//
//  de-functions.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-functions.h"

//定义查找表，长度256，表中的数值表示以此为起始字节的utf8字符长度
static unsigned int s_utf8_lens[256] =
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

#define UTFLEN(x)  s_utf8_lens[(int)(x)]

NAMESPACE_DE_BEGIN

void convert_utf8_to_wchar(const string& ch_in, wchar_t& ch_out)
{
    ch_out = 0;
    if (ch_in.empty())
    {
        return;
    }
    switch(ch_in.size())
    {
        case 1:
        {
            ch_out = ch_in[0];
        }
            break;
        case 2:
        {
            ch_out = ((int)(ch_in[0]&0x1F)) << 6;
            ch_out |= ch_in[1]&0x3F;
        }
            break;
        case 3:
        {
            ch_out = ((int)(ch_in[0]&0x1F)) << 12;
            ch_out |= ((int)(ch_in[1]&0x3F)) << 6;
            ch_out |= ch_in[2]&0x3F;
        }
            break;
        case 4:
        {
            ch_out = ((int)(ch_in[0]&0x07)) << 18;
            ch_out |= ((int)(ch_in[1]&0x3F)) << 12;
            ch_out |= ((int)(ch_in[2]&0x3F)) << 6;
            ch_out |= ch_in[3]&0x3F;
        }
            break;
        case 5:
        {
            ch_out = ((int)(ch_in[0]&0x03)) << 24;
            ch_out |= ((int)(ch_in[1]&0x3F)) << 18;
            ch_out |= ((int)(ch_in[2]&0x3F)) << 12;
            ch_out |= ((int)(ch_in[3]&0x3F)) << 6;
            ch_out |= ch_in[4]&0x3F;
        }
            break;
        case 6:
        {
            ch_out = ((int)(ch_in[0]&0x01)) << 30;
            ch_out |= ((int)(ch_in[1]&0x3F)) << 24;
            ch_out |= ((int)(ch_in[2]&0x3F)) << 18;
            ch_out |= ((int)(ch_in[3]&0x3F)) << 12;
            ch_out |= ((int)(ch_in[4]&0x3F)) << 6;
            ch_out |= ch_in[5]&0x3F;
        }
            break;
        default:
            return;
    }
}

void convert_utf8_to_wstring(const char* ch_in, wstring& ch_out)
{
    ch_out.clear();
    if (ch_in == null) {
        return;
    }
    char* ch = (char*)ch_in;
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
        ch_out += ot;
        ch+=len;
    }
}


void convert_wstring_to_string(const wstring& src, string& target)
{
    target.clear();
    unsigned char out[7];
    for (int i=0; i<src.size(); ++i)
    {
        memset(out, 0, 7);
        int t = src[i];
        convert_wchar_to_char(t,out);
        target.append((const char*)out);
    }
}

unsigned char* convert_wchar_to_char(int& unic, unsigned char* pOutput)
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

NAMESPACE_DE_END