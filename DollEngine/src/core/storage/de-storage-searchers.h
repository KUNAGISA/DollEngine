//
//  de-storage-searchers.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_storage_searchers__
#define __DollEngine__de_storage_searchers__

#include "de-functions.h"
#include "de-storage-file.h"

NAMESPACE_DE_STORAGE

class Searchers
{
public:
    Shared(Searchers)
    void reset();
    void addAutoPath(const de_string& storage);// ( 增加自动检索路径 )
    void removeAutoPath(const de_string& storage);// ( 删除自动检索路径 )
    bool isExistentStorage(const de_string& storage);// ( 检查文件是否存在 )
    de_string getFullPath(const de_string& path);
    
    PROPERTY_CONST(de_string, ResourcePath, m_resourcePath);
    PROPERTY_CONST(de_string, DocumentPath, m_documentPath);
    PROPERTY_CONST(de_string, CachePath, m_cachePath);
protected:
    list<de_string> m_autoPaths;
    map<de_string, de_string> m_searchPathsCache;
    de_string m_lastFullPath;
};

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_storage_searchers__) */
