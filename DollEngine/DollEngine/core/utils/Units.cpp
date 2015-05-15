//
//  Units.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Units.h"

DE_BEGIN

void GLCheckError()
{
    if(glGetError()){
        printf("OpenGL 出错:%x\n",glGetError());
    }
}

static const int kMaxFormatLen = 16*1024;
static char s_sff[kMaxFormatLen+1];
string StringWithFormat(const char* format,...)
{
    va_list args;
    memset(s_sff, 0, sizeof(s_sff));
    va_start(args, format);
    vsprintf(s_sff, format, args);
    va_end(args);
    return s_sff;
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

DE_END
