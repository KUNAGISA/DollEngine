//
//  IOData.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__IOData__
#define __DollEngine__IOData__

#include "CoreUnits.h"

DE_BEGIN

class IOData
{
public:
    IOData();
    ~IOData();
    void clear();
    void initWithSize(size_t size);
    void clearBuffer();
    unsigned short getUShort(int idx);
    void convertToUnicode(wstring&target);
    
    PROPERTY(unsigned char*, Buffer, m_buffer);
    PROPERTY(size_t, Size, m_size){m_size=v;}
};


DE_END

#endif /* defined(__DollEngine__IOData__) */
