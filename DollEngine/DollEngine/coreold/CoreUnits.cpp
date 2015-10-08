//
//  CoreUnits.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CoreUnits.h"
#include "GLProgram.h"
#include "GLShaderObject.h"
#include <sys/time.h>

DE_BEGIN

void GLCheckError()
{
    GLint v = glGetError();
    if(v){
        DM("OpenGL 出错:%x\n%s",v);
    }
}

void GLCheckProgramError(GLProgram* program)
{
    GLint v = glGetError();
    if (v) {
        DM("Error GL:0x%x", v);
        char infoLog[128];
        memset(infoLog, 0, 128);
        
        glGetProgramInfoLog ( program->getProgramId(), 127, NULL, infoLog );
        DM("Error program:%s", (const char*)infoLog);
        
        for (int i=0; i< program->getShaderCount(); ++i)
        {
            GLShaderObject* obj = program->getShader(i);
            memset(infoLog, 0, 128);
            glGetShaderInfoLog ( obj->getId(), 127, NULL, infoLog );
            DM("Error shader:%s", (const char*)infoLog);
        }
    }
}

static const int kMaxFormatLen = 16*1024;
static char s_sff[kMaxFormatLen+1];
string Utf8WithFormat(const char* format,...)
{
    va_list args;
    memset(s_sff, 0, sizeof(s_sff));
    va_start(args, format);
    vsprintf(s_sff, format, args);
    va_end(args);
    return s_sff;
}

static wchar_t s_wsff[kMaxFormatLen+1];
wstring UnicodeWithFormat(const wchar_t* format,...)
{
    va_list args;
    memset(s_wsff, 0, sizeof(s_wsff));
    va_start(args, format);
    vswprintf(s_wsff, kMaxFormatLen, format, args);
    va_end(args);
    return s_wsff;
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

void Utf8ToVector(const string& _in, vector<string>& _out)
{
    for (int i = 0; i < _in.size();)
    {
        int len = UTFLEN(_in[i] & 0xff);
        string o(_in.c_str()+i,len);
        _out.push_back(o);
        i+=len;
    }
}

void Utf8ToUnicode(const char* src, wstring& target)
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

void UnicodeToUtf8(const wchar_t* src, string& target)
{
    target.clear();
    if (src == null) {
        return;
    }
    wchar_t* ch = (wchar_t*)src;
    unsigned char out[7];
    while (*ch != L'\0')
    {
        memset(out, 0, 7);
        int t = (int)*ch;
        WCharToChar(t,out);
        target.append((const char*)out);
        ++ch;
    }
}

unsigned char* WCharToChar(int& unic, unsigned char*pOutput)
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

void CharToWChar(const char* src,wchar_t* target)
{
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
        *target = ot;
        ch+=len;
        target++;
    }
}

int64_t GetMilliSeconds()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

double GetSeconds()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec/1000000.0f;
}

DE_END
