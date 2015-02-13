//
//  de-storage-searchs.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_storage_searchs__
#define __DollEngine__de_storage_searchs__

#include "de-functions.h"
#include "de-storage-file.h"

NAMESPACE_DE_STORAGE

class storage_searchs
{
public:
    void addAutoPath(const de_string& storage);// ( 增加自动检索路径 )
    void removeAutoPath(const de_string& storage);// ( 删除自动检索路径 )
    bool isExistentStorage(const de_string& storage);// ( 检查文件是否存在 )
    
    PROPERTY_CONST(wstring, ResourcePath, m_resourcePath);
    PROPERTY_CONST(wstring, DocumentPath, m_documentPath);
    PROPERTY_CONST(wstring, CachePath, m_cachePath);
private:
    list<wstring> m_autoPaths;
    map<wstring, wstring> m_searchPathsCache;
    
};

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_storage_searchs__) */
