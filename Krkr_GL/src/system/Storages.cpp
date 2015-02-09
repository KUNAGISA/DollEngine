//
//  Storages.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14-9-18.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Storages.h"
#include "System.h"
#include "StringUtils.h"

Storages::Storages()
{
}

IOData* Storages::GetFileData(const wstring& fullpath)
{
    if (fullpath.size() == 0)
    {
        THROW_EM(ERROR_FILE_OPENFAIL_PATH_CANTFIND,"");
        return null;
    }
    string sfullpath;
    StringUtils::ConvertUnicodeToUtf8(fullpath, sfullpath);
    
    FILE *fp = fopen(sfullpath.c_str(), "rb");
    if (!fp) {
        return null;
    }
    
    IOData* ret = new IOData();
    
    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    unsigned char* buffer = new unsigned char[size];
    ret->setSize(fread(buffer,sizeof(unsigned char), size,fp));
    ret->setBuffer(buffer);
    fclose(fp);
    
    return ret;
}

IOData* Storages::GetFileText(const wstring& fullpath)
{
    if (fullpath.size() == 0)
    {
        THROW_EM(ERROR_FILE_OPENFAIL_PATH_CANTFIND,"");
        return null;
    }
    string sfullpath;
    StringUtils::ConvertUnicodeToUtf8(fullpath, sfullpath);
    FILE *fp = fopen(sfullpath.c_str(), "rb");
    if (!fp) {
        return null;
    }
    
    IOData* ret = new IOData();
    
    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    unsigned char* buffer = new unsigned char[size+1];
    size = fread(buffer,sizeof(unsigned char), size,fp);
    buffer[size] = '\0';
    ret->setSize(size+1);
    ret->setBuffer(buffer);
//    for (int i = 0; i < size+1; ++i)
//    {
//        if(*(buffer+i) == '\r')
//        {
//            *(buffer+i) = '\n';
//        }
//    }
    fclose(fp);
    
    return ret;
}

void Storages::addAutoPath(const wstring& storage)
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

wstring Storages::chopStorageExt(const wstring& storage)
{
	// ( 返回忽略扩展名的文件名 )
    wstring filename = extractStorageName(storage);
    return filename.substr(0,filename.rfind(L"."));
}

wstring Storages::extractStorageExt(const wstring& storage)
{
    // ( 返回文件的扩展名 )
    size_t idx = storage.rfind(L".");
    if (idx == storage.npos) {
        return L"";
    }
    return storage.substr(idx+1);
}

wstring Storages::extractStorageName(const wstring& storage)
{
    // ( 返回文件名 )
    return storage.substr(storage.rfind(L"/")+1);
}

wstring Storages::extractStoragePath(const wstring& storage)
{
    // ( 返回文件存储路径 )
    wstring fullpath = getFullPath(storage);
    return fullpath.substr(0,fullpath.rfind(L"/")+1);
}

wstring Storages::getFullPath(const wstring& storage)
{
    // ( 获取统一文件路径 )
    string temp;
    if (storage.size() == 0) {
        return L"";
    }
    if (storage[0] == L'/')
    {
        StringUtils::ConvertUnicodeToUtf8(storage, temp);
        if(access(temp.c_str(), 0) == 0)
            return storage;
    }
    else
    {
        auto cache_iter = m_searchPathsCache.find(storage);
        if (cache_iter != m_searchPathsCache.end())
        {
            return cache_iter->second;
        }
        else
        {
            auto auto_iter = m_autoPaths.begin();
            for (; auto_iter != m_autoPaths.end(); ++auto_iter)
            {
                wstring temp_path = (*auto_iter)+storage;
                temp.clear();
                StringUtils::ConvertUnicodeToUtf8(temp_path, temp);
                if (access(temp.c_str(),0) == 0)
                {
                    m_searchPathsCache[storage] = temp_path;
                    return temp_path;
                }
            }
        }
    }
    return L"";
}

wstring Storages::getLocalName(const wstring& storage)
{
    // ( 获取本地文件名 )
    wstring fullpath = getFullPath(storage);
    return fullpath.substr(System::GetInstance()->getPersonalPath().length());
}

wstring Storages::getPlacedPath(const wstring& storage)
{
    // ( 检索并返回文件 )
    return getFullPath(storage);
}

bool Storages::isExistentStorage(const wstring& storage)
{
    // ( 检查文件是否存在 )
    string temp;
    if (storage.size() == 0)
    {
        return false;
    }
    if (storage[0] == L'/')
    {
        StringUtils::ConvertUnicodeToUtf8(storage, temp);
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
                StringUtils::ConvertUnicodeToUtf8(temp_path, temp);
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

void Storages::removeAutoPath(const wstring& storage)
{
	// ( 删除自动检索路径 )
    std::remove(m_autoPaths.begin(), m_autoPaths.end(), storage);
}

void Storages::setResourcePath(const wstring &v)
{
    m_resourcePath=v;
    m_autoPaths.push_front(v);
}

void Storages::setDocumentPath(const wstring &v)
{
    m_documentPath=v;
    m_autoPaths.push_front(v);
}

void Storages::setCachePath(const wstring &v)
{
    m_cachePath = v;
    m_autoPaths.push_front(v);
}
