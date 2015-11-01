//
//  IOData.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "IOData.h"

DE_BEGIN


IOData::IOData()
:m_buffer(NULL)
,m_size(0)
{
}

IOData::~IOData()
{
    SAFF_DELETE_ARRAY(m_buffer);
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

void IOData::setBuffer(unsigned char *v)
{
    SAFF_DELETE_ARRAY(m_buffer);
    m_buffer = v;
}


DE_END
