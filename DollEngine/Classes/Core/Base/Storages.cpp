//
//  Storages.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Storages.h"
#include "System.h"
#include "IOData.h"

DE_BEGIN

Storages::Storages()
{
}

IOData* Storages::GetFileData(const String& fullpath)
{
    if (fullpath.size() == 0)
    {
        EM(ERROR_FILE_NOT_EXIST,fullpath);
        return NULL;
    }
    
    FILE * fp = fopen(fullpath.c_nstr(), "rb");
    if (!fp) {
        EM(L"文件打开失败:"+fullpath);
        return NULL;
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

void Storages::addAutoPath(const String& path)
{
    // ( 增加自动检索路径 )
    string storage = path.utf8Value();
    DM("增加自动检索路径:%s",storage.c_str());
    if (storage.back() != '/')
    {
        m_autoPaths.push_front(storage+"/");
    }
    else
    {
        m_autoPaths.push_front(storage);
    }
}

String Storages::getFullPath(const String& storage)
{
    // ( 获取统一文件路径 )
    if (storage.empty()) {
        return "";
    }
    if(access(storage.c_nstr(), 0) == 0)
        return storage;
    
    auto cache_iter = m_searchPathsCache.find(storage);
    if (cache_iter != m_searchPathsCache.end())
    {
        return cache_iter->second;
    }
    else
    {
        String temp_path = System::GetInstance()->getPatchPath()+storage;
        if (access(temp_path.c_nstr(),0) == 0)
        {
            m_searchPathsCache[storage] = temp_path;
            return temp_path;
        }
        temp_path = System::GetInstance()->getSaveDataPath()+storage;
        if (access(temp_path.c_nstr(),0) == 0)
        {
            m_searchPathsCache[storage] = temp_path;
            return temp_path;
        }
        temp_path = System::GetInstance()->getDataPath()+storage;
        if (access(temp_path.c_nstr(),0) == 0)
        {
            m_searchPathsCache[storage] = temp_path;
            return temp_path;
        }
        temp_path = System::GetInstance()->getAppPath()+storage;
        if (access(temp_path.c_nstr(),0) == 0)
        {
            m_searchPathsCache[storage] = temp_path;
            return temp_path;
        }
        auto auto_iter = m_autoPaths.begin();
        for (; auto_iter != m_autoPaths.end(); ++auto_iter)
        {
            temp_path = System::GetInstance()->getPatchPath()+(*auto_iter)+storage;
            if (access(temp_path.c_nstr(),0) == 0)
            {
                m_searchPathsCache[storage] = temp_path;
                return temp_path;
            }
        }
        auto_iter = m_autoPaths.begin();
        for (; auto_iter != m_autoPaths.end(); ++auto_iter)
        {
            temp_path = System::GetInstance()->getSaveDataPath()+(*auto_iter)+storage;
            if (access(temp_path.c_nstr(),0) == 0)
            {
                m_searchPathsCache[storage] = temp_path;
                return temp_path;
            }
        }
        auto_iter = m_autoPaths.begin();
        for (; auto_iter != m_autoPaths.end(); ++auto_iter)
        {
            temp_path = System::GetInstance()->getDataPath()+(*auto_iter)+storage;
            if (access(temp_path.c_nstr(),0) == 0)
            {
                m_searchPathsCache[storage] = temp_path;
                return temp_path;
            }
        }
    }
    return L"";
}

void Storages::removeAutoPath(const String& storage)
{
    // ( 删除自动检索路径 )
    std::remove(m_autoPaths.begin(), m_autoPaths.end(), storage);
}

void Storages::clearAutoPath()
{
    m_autoPaths.clear();
}

DE_END
