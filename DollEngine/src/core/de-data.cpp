//
//  de-data.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/16.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-data.h"
#include "de.h"

NAMESPACE_DE_BEGIN

Data::Data(encode type)
:m_bytes(null)
,m_size(0)
{
    
}

Data::~Data()
{
    DELETE_ARRAY(m_bytes);
}

Data* Data::DataWithSize(long size)
{
    Data* data = new Data();
    unsigned char* bytes = new unsigned char[size];
    memset(bytes, 0, size);
    data->setBytes(bytes);
    data->setSize(size);
    return data;
}

Data* Data::Empty()
{
    static Data* s_empty = null;
    if (!s_empty) {
        s_empty = new Data();
    }
    return s_empty;
}

void Data::clear()
{
    DELETE_ARRAY(m_bytes);
    m_size = 0;
}

void Data::setBytes(unsigned char *v)
{
    DELETE_ARRAY(m_bytes);
    m_bytes = v;
}

const wchar_t* Data::getWChar()
{
    if (m_wBytes.size() == 0)
    {
        de::convert_utf8_to_wstring((const char*)m_bytes, m_wBytes);
    }
    return m_wBytes.c_str();
}

NAMESPACE_DE_END