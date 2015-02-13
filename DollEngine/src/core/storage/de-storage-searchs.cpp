//
//  de-storage-searchs.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-storage-searchs.h"

NAMESPACE_DE_STORAGE


void storage_searchs::addAutoPath(const wstring& storage)
{
    // ( 增加自动检索路径 )
    
    if (storage.back() != '/')
    {
        m_autoPaths.push_front(m_resourcePath+storage+L"/");
        m_autoPaths.push_front(m_documentPath+storage+L"/");
        m_autoPaths.push_front(m_cachePath+storage+L"/");
    }
    else
    {
        m_autoPaths.push_front(m_resourcePath+storage);
        m_autoPaths.push_front(m_documentPath+storage);
        m_autoPaths.push_front(m_cachePath+storage);
    }
}

bool storage_searchs::isExistentStorage(const wstring& storage)
{
    // ( 检查文件是否存在 )
    string temp;
    if (storage.size() == 0)
    {
        return false;
    }
    if (storage[0] == L'/')
    {
        convert_wstring_to_string(storage, temp);
        return access(temp.c_str(), 0) == 0;
    }
    else
    {
        auto cache_iter = m_searchPathsCache.find(storage);
        if (cache_iter != m_searchPathsCache.end())
        {
            return true;
        }
        else
        {
            auto auto_iter = m_autoPaths.begin();
            for (; auto_iter != m_autoPaths.end(); ++auto_iter)
            {
                wstring temp_path = (*auto_iter)+storage;
                convert_wstring_to_string(temp_path, temp);
                if (access(temp.c_str(),0) == 0)
                {
                    m_searchPathsCache[storage] = temp_path;
                    return true;
                }
            }
        }
    }
    return false;
}

void storage_searchs::removeAutoPath(const wstring& storage)
{
    // ( 删除自动检索路径 )
    std::remove(m_autoPaths.begin(), m_autoPaths.end(), storage);
}

void storage_searchs::setResourcePath(const wstring &v)
{
    m_resourcePath=v;
    m_autoPaths.push_front(v);
}

void storage_searchs::setDocumentPath(const wstring &v)
{
    m_documentPath=v;
    m_autoPaths.push_front(v);
}

void storage_searchs::setCachePath(const wstring &v)
{
    m_cachePath = v;
    m_autoPaths.push_front(v);
}

NAMESPACE_DE_END2
