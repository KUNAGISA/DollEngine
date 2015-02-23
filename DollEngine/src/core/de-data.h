//
//  de-data.h
//  DollEngine
//
//  Created by DollStudio on 15/2/16.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_data__
#define __DollEngine__de_data__

#include "de-functions.h"

NAMESPACE_DE_BEGIN

class Data
{
public:
    enum encode
    {
        bin,
        utf8_nobom,
        utf8,
        unicode
    };
    Data(encode type=bin);
    static Data* empty();
    bool isEmpty(){return m_bytes==null;}
    const wchar_t* getWChar();
    
    PROPERTY(unsigned char*, Bytes, m_bytes);
    PROPERTY(long, Size, m_size){m_size=v;}
private:
    wstring m_wBytes;
};

NAMESPACE_DE_END

#endif /* defined(__DollEngine__de_data__) */
