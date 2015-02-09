//
//  Storages.h
//  DollEngine
//
//  Created by DollStudio on 14-9-18.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Storages__
#define __DollEngine__Storages__

#include "Functions.h"
#include "IOData.h"

class Storages
{
public:
    Storages();
    Shared(Storages)
    static IOData* GetFileData(const wstring& fullpath);
    static IOData* GetFileText(const wstring& fullpath);
public:
    void addAutoPath(const wstring& storage);// ( 增加自动检索路径 )
    wstring chopStorageExt(const wstring& storage);// ( 返回忽略扩展名的文件名 )
    wstring extractStorageExt(const wstring& storage);// ( 返回文件的扩展名 )
    wstring extractStorageName(const wstring& storage);// ( 返回文件名 )
    wstring extractStoragePath(const wstring& storage);// ( 返回文件存储路径 )
    wstring getFullPath(const wstring& storage);// ( 获取统一文件路径 )
    wstring getLocalName(const wstring& storage);// ( 获取本地文件名 )
    wstring getPlacedPath(const wstring& storage);// ( 检索并返回文件 )
    bool isExistentStorage(const wstring& storage);// ( 检查文件是否存在 )
    void removeAutoPath(const wstring& storage);// ( 删除自动检索路径 )
//    void searchCD ( 检索CD )
//    void selectFile ( 弹出选择文件对话框 )
public:
    PROPERTY_CONST(wstring, ResourcePath, m_resourcePath);
    PROPERTY_CONST(wstring, DocumentPath, m_documentPath);
    PROPERTY_CONST(wstring, CachePath, m_cachePath);
private:
    list<wstring> m_autoPaths;
    map<wstring, wstring> m_searchPathsCache;
};

#endif /* defined(__DollEngine__Storages__) */
