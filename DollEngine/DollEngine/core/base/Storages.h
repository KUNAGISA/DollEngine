//
//  Storages.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Storages__
#define __DollEngine__Storages__

#include "CoreUnits.h"
#include "IOData.h"

DE_BEGIN

class Storages
{
public:
    Storages();
    Shared(Storages)
    static IOData* GetFileData(const String& fullpath);
    static IOData* GetFileString(const String& fullpath);
public:
    void addAutoPath(const String& storage);// ( 增加自动检索路径 )
    String getFullPath(const String& storage);// ( 获取统一文件路径 )
    void removeAutoPath(const String& storage);// ( 删除自动检索路径 )
    void clearAutoPath();
private:
    list<string> m_autoPaths;
    map<String, String> m_searchPathsCache;
};

DE_END

#endif /* defined(__DollEngine__Storages__) */
