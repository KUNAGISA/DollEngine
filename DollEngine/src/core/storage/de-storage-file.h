//
//  de-storage-file.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_storage_file__
#define __DollEngine__de_storage_file__

#include "de-functions.h"
#include "de-data.h"

NAMESPACE_DE_STORAGE

class File
{
public:
    File();
    ~File();
    bool open();
    void close();
    bool exist();
    long getSize();
    Data* getData(){return &m_data;}
    PROPERTY_CONST(de_string, FileName, m_fileName){m_fileName=v;}
protected:
    void updateFullPath();
    
    FILE* m_file;
    string m_fullPath;
    Data m_data;
};

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_storage_file__) */
