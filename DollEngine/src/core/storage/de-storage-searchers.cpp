//
//  de-storage-searchers.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-storage-searchers.h"
#include "de.h"

NAMESPACE_DE_STORAGE

void Searchers::reset()
{
    m_autoPaths.clear();
    m_searchPathsCache.clear();
}

void Searchers::addAutoPath(const de_string& storage)
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
    DM("新增自动搜索路径%ls",storage.c_str());
}

bool Searchers::isExistentStorage(const de_string& storage)
{
    // ( 检查文件是否存在 )
    string temp;
    m_lastFullPath = de_w("");
    if (storage.size() == 0)
    {
        return false;
    }
    if (storage[0] == L'/')
    {
        convert_wstring_to_string(storage, temp);
        if(access(temp.c_str(), 0) == 0)
        {
            m_lastFullPath = storage;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        auto cache_iter = m_searchPathsCache.find(storage);
        if (cache_iter != m_searchPathsCache.end())
        {
            m_lastFullPath = cache_iter->second;
            return true;
        }
        else
        {
            auto auto_iter = m_autoPaths.begin();
            for (; auto_iter != m_autoPaths.end(); ++auto_iter)
            {
                de_string temp_path = (*auto_iter)+storage;
                convert_wstring_to_string(temp_path, temp);
                if (access(temp.c_str(),0) == 0)
                {
                    m_lastFullPath = temp_path;
                    m_searchPathsCache[storage] = m_lastFullPath;
                    return true;
                }
            }
        }
    }
    return false;
}

de_string Searchers::getFullPath(const de_string& path)
{
    if (isExistentStorage(path))
    {
        return m_lastFullPath;
    }
    return de_w("");
}

void Searchers::removeAutoPath(const de_string& storage)
{
    // ( 删除自动检索路径 )
    std::remove(m_autoPaths.begin(), m_autoPaths.end(), storage);
}

void Searchers::setResourcePath(const de_string &v)
{
    m_resourcePath=v;
    m_autoPaths.push_front(v);
}

void Searchers::setDocumentPath(const de_string &v)
{
    m_documentPath=v;
    m_autoPaths.push_front(v);
}

void Searchers::setCachePath(const de_string &v)
{
    m_cachePath = v;
    m_autoPaths.push_front(v);
}

NAMESPACE_DE_END2
