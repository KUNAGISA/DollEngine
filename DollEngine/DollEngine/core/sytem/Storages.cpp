//
//  Storages.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Storages.h"
#include "Debug.h"
#include "Device.h"

DE_BEGIN

Storages::Storages()
{
}

IOData* Storages::GetFileData(const string& fullpath)
{
    if (fullpath.size() == 0)
    {
        throw Debug::throwMsg(ERROR_FILE_EXIST_FAILD,fullpath);
        return null;
    }
    
    FILE * fp = fopen(fullpath.c_str(), "rb");
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

IOData* Storages::GetFileString(const string& fullpath)
{
    if (fullpath.size() == 0)
    {
        throw Debug::throwMsg(ERROR_FILE_EXIST_FAILD,fullpath);
        return null;
    }
    FILE *fp = fopen(fullpath.c_str(), "rb");
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
    fclose(fp);
    
    return ret;
}

void Storages::addAutoPath(const string& storage)
{
    // ( 增加自动检索路径 )
    if (storage.back() != '/')
    {
        m_autoPaths.push_front(storage+"/");
    }
    else
    {
        m_autoPaths.push_front(storage);
    }
}

string Storages::getFullPath(const string& storage)
{
    // ( 获取统一文件路径 )
    if (storage.size() == 0) {
        return "";
    }
    if (storage[0] == '/')
    {
        if(access(storage.c_str(), 0) == 0)
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
            string temp_path = Device::GetInstance()->getPatchPath()+storage;
            if (access(temp_path.c_str(),0) == 0)
            {
                m_searchPathsCache[storage] = temp_path;
                return temp_path;
            }
            temp_path = Device::GetInstance()->getSaveDataPath()+storage;
            if (access(temp_path.c_str(),0) == 0)
            {
                m_searchPathsCache[storage] = temp_path;
                return temp_path;
            }
            temp_path = Device::GetInstance()->getDataPath()+storage;
            if (access(temp_path.c_str(),0) == 0)
            {
                m_searchPathsCache[storage] = temp_path;
                return temp_path;
            }
            auto auto_iter = m_autoPaths.begin();
            for (; auto_iter != m_autoPaths.end(); ++auto_iter)
            {
                temp_path = Device::GetInstance()->getPatchPath()+(*auto_iter)+storage;
                if (access(temp_path.c_str(),0) == 0)
                {
                    m_searchPathsCache[storage] = temp_path;
                    return temp_path;
                }
            }
            auto_iter = m_autoPaths.begin();
            for (; auto_iter != m_autoPaths.end(); ++auto_iter)
            {
                temp_path = Device::GetInstance()->getSaveDataPath()+(*auto_iter)+storage;
                if (access(temp_path.c_str(),0) == 0)
                {
                    m_searchPathsCache[storage] = temp_path;
                    return temp_path;
                }
            }
            auto_iter = m_autoPaths.begin();
            for (; auto_iter != m_autoPaths.end(); ++auto_iter)
            {
                temp_path = Device::GetInstance()->getDataPath()+(*auto_iter)+storage;
                if (access(temp_path.c_str(),0) == 0)
                {
                    m_searchPathsCache[storage] = temp_path;
                    return temp_path;
                }
            }
        }
    }
    return "";
}

void Storages::removeAutoPath(const string& storage)
{
    // ( 删除自动检索路径 )
    std::remove(m_autoPaths.begin(), m_autoPaths.end(), storage);
}

void Storages::clearAutoPath()
{
    m_autoPaths.clear();
}

DE_END