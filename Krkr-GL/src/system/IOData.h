//
//  IOData.h
//  DollEngine
//
//  Created by DollStudio on 14/12/20.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__IOData__
#define __DollEngine__IOData__

#include "Functions.h"

class IOData
{
public:
    IOData();
    ~IOData();
    void clear();
    void initWithSize(size_t size);
    void clearBuffer();
    unsigned short getUShort(int idx);
    void convertToWString();
    
    PROPERTY(unsigned char*, Buffer, m_buffer);
    PROPERTY(wchar_t*, WBuffer, m_wBuffer);
    PROPERTY(size_t, Size, m_size){m_size=v;}
    PROPERTY(size_t, WSize, m_wSize){m_wSize=v;}
};

#endif /* defined(__DollEngine__IOData__) */
