//
//  IOData.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/12/20.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "IOData.h"
#include "StringUtils.h"

IOData::IOData()
:m_buffer(null)
,m_size(0)
,m_wBuffer(null)
,m_wSize(0)
{
}

IOData::~IOData()
{
    SAFF_DELETE_ARRAY(m_buffer);
    SAFF_DELETE_ARRAY(m_wBuffer);
}

void IOData::clear()
{
    SAFF_DELETE_ARRAY(m_buffer);
    m_size=0;
}

void IOData::initWithSize(size_t size)
{
    SAFF_DELETE_ARRAY(m_buffer);
    m_buffer = new unsigned char[size];
    m_size = size;
}

void IOData::clearBuffer()
{
    if (m_buffer)
    {
        memset(m_buffer, 0, m_size);
    }
}
void IOData::setBuffer(unsigned char *v)
{
    SAFF_DELETE_ARRAY(m_buffer);
    m_buffer = v;
}

void IOData::setWBuffer(wchar_t *v)
{
    SAFF_DELETE_ARRAY(m_wBuffer);
    m_wBuffer = v;
}

unsigned short IOData::getUShort(int idx)
{
    unsigned short ret;
    unsigned short* tbuffer = (unsigned short*)m_buffer;
    ret = tbuffer[idx];
    return ret;
}

void IOData::convertToWString()
{
    wchar_t* dchar = new wchar_t[m_size+1];
    unsigned char* buffer = m_buffer;
    for (int i=0; i<m_size; ++i)
    {
        buffer = StringUtils::ConvertUtf8ToUnicode(buffer,dchar[i]);
        if (buffer - m_buffer >= m_size)
        {
            dchar[i+1] = '\0';
            setWSize(i);
            break;
        }
    }
    SAFF_DELETE_ARRAY(m_buffer);
    setWBuffer(dchar);
}
