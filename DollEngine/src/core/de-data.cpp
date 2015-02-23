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
{
    
}

Data* Data::empty()
{
    static Data* s_empty = null;
    if (!s_empty) {
        s_empty = new Data();
    }
    return s_empty;
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