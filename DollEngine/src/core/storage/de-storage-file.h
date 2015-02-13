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

NAMESPACE_DE_STORAGE

class storage_file
{
public:
    PROPERTY_CONST(de_string, FileName, m_fileName);
    PROPERTY_CONST(de_string, FullPath, m_fullPath){m_fullPath=v;}
    
protected:
    void updateFullPath();
};

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_storage_file__) */
